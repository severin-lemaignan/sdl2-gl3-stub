#ifndef GLRENDERER_H
#define GLRENDERER_H

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

#include "shader.h"

#define BUFFER_OFFSET(x)  ((void *) (x))

const GLuint NumVertices = 6;

class GLRenderer
{
public:
    GLRenderer();

    void load();
    void display();

private:
    Shader shader;

    enum VAO_IDs { Triangles, NumVAOs };
    enum Buffer_IDs { ArrayBuffer, NumBuffers };
    enum Attrib_IDs { vPosition = 0 };

    GLuint VAOs[NumVAOs];
    GLuint Buffers[NumBuffers];


};

#endif // GLRENDERER_H
