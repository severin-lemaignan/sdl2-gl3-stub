#include <glm/gtc/type_ptr.hpp>

#include "glrenderer.h"

using namespace glm;
using namespace std;

GLRenderer::GLRenderer() : camera() {}

void GLRenderer::load()
{

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[NumVertices][2] = {
        {-0.90, -0.90},
        { 0.85, -0.90},
        {-0.90,  0.85},
        { 0.90, -0.85},
        { 0.90,  0.90},
        {-0.85,  0.90}
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader.init(string("share/") + APPNAME + "/shaders/triangles.vert", string("share/") + APPNAME + "/shaders/triangles.frag");

    shader.bind();

    //glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);
}

void GLRenderer::display()
{
   glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);

    GLuint modelview_matrix = glGetUniformLocation(shader.id(), "modelview_matrix");
    GLuint projection_matrix = glGetUniformLocation(shader.id(), "projection_matrix");
    glUniformMatrix4fv(modelview_matrix, 1, GL_FALSE, value_ptr(camera.world2eye()));
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, value_ptr(camera.projection()));

    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    glFlush();
}

void GLRenderer::resize(const int w, const int h)
{
    glViewport(0,0,w,h);
}
