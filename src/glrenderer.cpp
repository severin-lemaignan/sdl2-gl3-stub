#include <glm/gtc/type_ptr.hpp>

#include "glrenderer.h"

using namespace glm;
using namespace std;

GLRenderer::GLRenderer() : camera(), assimploader(){}


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

   recursiveRender(root);
}

void GLRenderer::recursiveRender(const Node& node) {

    for (auto mesh : node.meshes) {

        glBindVertexArray(mesh.vao);


        glUniformMatrix4fv(shader.uniformLocations[Shader::MODELVIEW_UNIFORM], 1, GL_FALSE, value_ptr(node.transformation * camera.world2eye()));
        glUniformMatrix4fv(shader.uniformLocations[Shader::PROJECTION_UNIFORM], 1, GL_FALSE, value_ptr(camera.projection()));
        glUniform4fv(shader.uniformLocations[Shader::DIFFUSE_UNIFORM], 1, value_ptr(mesh.diffuse));

        glDrawElements(GL_TRIANGLES, mesh.numfaces * 3, GL_UNSIGNED_INT, 0);
        glFlush();
    }

    for (auto n : node.children) {
        recursiveRender(*n);
    }
}

void GLRenderer::resize(const int w, const int h)
{
    glViewport(0,0,w,h);
}
