#ifndef GLRENDERER_H
#define GLRENDERER_H

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif

#include "shader.h"
#include "camera.h"

#define BUFFER_OFFSET(x)  ((void *) (x))

const GLuint NumVertices = 6;

class GLRenderer
{
public:
    GLRenderer();

    void load();
    void display();

    void resize(const int w, const int h);
    Camera camera;

private:
    Shader shader;

    enum VAO_IDs { Triangles, NumVAOs };
    enum Buffer_IDs { ArrayBuffer, NumBuffers };
    enum Attrib_IDs { vPosition = 0 };

    GLuint VAOs[NumVAOs];
    GLuint Buffers[NumBuffers];


};

#endif // GLRENDERER_H
