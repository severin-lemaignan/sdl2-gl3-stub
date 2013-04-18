#include <glm/gtc/type_ptr.hpp>

#include "glrenderer.h"

using namespace glm;
using namespace std;

GLRenderer::GLRenderer() : camera(), assimploader() {}

void GLRenderer::load(const string& file)
{

    assimploader.Import3DFromFile(file);

    assimploader.loadNodes(root, nodes);

    shader.init(string("share/") + APPNAME + "/shaders/triangles.vert", string("share/") + APPNAME + "/shaders/triangles.frag");

    shader.bind();

    //glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);
}

void GLRenderer::display()
{
   glClear(GL_COLOR_BUFFER_BIT);

    //glBindVertexArray(VAOs[Triangles]);

    GLuint modelview_matrix = glGetUniformLocation(shader.id(), "modelview_matrix");
    GLuint projection_matrix = glGetUniformLocation(shader.id(), "projection_matrix");
    glUniformMatrix4fv(modelview_matrix, 1, GL_FALSE, value_ptr(camera.world2eye()));
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, value_ptr(camera.projection()));

    //glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    //glFlush();
}

void GLRenderer::resize(const int w, const int h)
{
    glViewport(0,0,w,h);
}
