#include <iostream>
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

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_CULL_FACE);
}

void GLRenderer::display()
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glUniformMatrix4fv(shader.uniformLocations[Shader::PROJECTION_UNIFORM], 1, GL_FALSE, value_ptr(camera.projection()));
   glUniformMatrix4fv(shader.uniformLocations[Shader::VIEW_UNIFORM], 1, GL_FALSE, value_ptr(camera.world2eye()));
   recursiveRender(root, mat4(1.0));
}

void GLRenderer::recursiveRender(const Node& node, const mat4& parent2worldTransformation) {

    mat4 transformation = parent2worldTransformation * node.transformation;
    glUniformMatrix4fv(shader.uniformLocations[Shader::MODEL_UNIFORM], 1, GL_FALSE, value_ptr(transformation));

    for (auto mesh : node.meshes) {

        glBindVertexArray(mesh.vao);


        glUniform4fv(shader.uniformLocations[Shader::DIFFUSE_UNIFORM], 1, value_ptr(mesh.diffuse));

        glDrawElements(GL_TRIANGLES, mesh.numfaces * 3, GL_UNSIGNED_INT, 0);
        glFlush();
    }

    for (auto n : node.children) {
        //recursiveRender(*n, mat4(1.0));
        recursiveRender(*n, transformation);
    }
}

void GLRenderer::resize(const int w, const int h)
{
    glViewport(0,0,w,h);
}
