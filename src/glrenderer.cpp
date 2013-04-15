#include "glrenderer.h"
#include "loadshaders.h"


#include <GL3/gl3.h>
GLRenderer::GLRenderer() {}

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

    ShaderInfo shaders = {
        GL_VERTEX_SHADER, '../shaders/triangles.vert',
        GL_FRAGMENT_SHADER, '../shaders/triangles.frag',
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    //glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);
}

void GLRenderer::display()
{
   glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    glFlush();
}
