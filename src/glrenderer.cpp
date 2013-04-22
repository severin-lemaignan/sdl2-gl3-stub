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

}

void GLRenderer::display()
{
   glClear(GL_COLOR_BUFFER_BIT);


    GLuint modelview_matrix = glGetUniformLocation(shader.id(), "modelview_matrix");
    GLuint projection_matrix = glGetUniformLocation(shader.id(), "projection_matrix");

    recursiveRender(root);
}

void GLRenderer::recursiveRender(const Node& node, GLuint mv_uniform, GLuint proj_uniform) {

    for (auto mesh : node.meshes) {

    glBindVertexArray(mesh.vao);

    //glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);

    glUniformMatrix4fv(mv_uniform, 1, GL_FALSE, value_ptr(node.transformation * camera.world2eye()));
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, value_ptr(camera.projection()));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glDrawArrays(GL_TRIANGLES, 0, mesh.numvertices);
    glFlush();
    }
}

void GLRenderer::resize(const int w, const int h)
{
    glViewport(0,0,w,h);
}
