#include "postprocess.h"

using namespace std;
Postprocess::Postprocess(int screen_width, int screen_height, const string& vertex_shader, const string& fragment_shader)
{
    init(screen_width, screen_height);
    shader.init(vertex_shader, fragment_shader);
}

Postprocess::~Postprocess()
{
    /* free_resources */
      glDeleteRenderbuffers(1, &rbo_depth);
      glDeleteTextures(1, &fbo_texture);
      glDeleteFramebuffers(1, &fbo);
}


void Postprocess::init(int screen_width, int screen_height)
{
    /* Create back-buffer, used for post-processing */

    /* Texture */
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &fbo_texture);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Depth buffer */
    glGenRenderbuffers(1, &rbo_depth);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screen_width, screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    /* Framebuffer to link everything together */
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);
    GLenum status;
    if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
      fprintf(stderr, "glCheckFramebufferStatus: error %p\n", status);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* init_resources */
      GLfloat fbo_vertices[] = {
        -1, -1,
         1, -1,
        -1,  1,
         1,  1,
      };
      glGenBuffers(1, &vbo_fbo_vertices);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices);
      glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Postprocess::resize(int w, int h)
{
      // Rescale FBO and RBO as well
      glBindTexture(GL_TEXTURE_2D, fbo_texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      glBindTexture(GL_TEXTURE_2D, 0);

      glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, w, h);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Postprocess::recordDraw()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Postprocess::process()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    shader.bind();
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    shader.setUniform("fbo_texture", 0);
    //glUniform1i(uniform_fbo_texture, /*GL_TEXTURE*/0);
    glEnableVertexAttribArray(shader.getAttrib("v_coord"));

    glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices);
    glVertexAttribPointer(
      shader.getAttrib("v_coord"),  // attribute
      2,                  // number of elements per vertex, here (x,y)
      GL_FLOAT,           // the type of each element
      GL_FALSE,           // take our values as-is
      0,                  // no extra data between each position
      0                   // offset of first element
    );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(shader.getAttrib("v_coord"));
    shader.unbind();
}
