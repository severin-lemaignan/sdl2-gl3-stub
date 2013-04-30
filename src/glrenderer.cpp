#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "glrenderer.h"

using namespace glm;
using namespace std;

GLRenderer::GLRenderer() : camera(), assimploader(){}


void GLRenderer::load(const string& file)
{

    assimploader.Import3DFromFile(file);

    shader.init(string("share/") + APPNAME + "/shaders/phong.vert", string("share/") + APPNAME + "/shaders/phong.frag");
    assimploader.loadNodes(root, nodes, shader);

    shader.bind();


   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_CULL_FACE);


   glUniform4f( shader.getUniform("global_ambient"), .4,.2,.2,.1 );
   glUniform4f( shader.getUniform("light_ambient"), .4,.4,.4, 1.0 );
   glUniform4f( shader.getUniform("light_diffuse"), 1,1,1,1 );
   glUniform3f( shader.getUniform("light_location"), 2,2,10 );


}


void GLRenderer::display()
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glUniformMatrix4fv(shader.getUniform("projection"), 1, GL_FALSE, value_ptr(camera.projection()));
   recursiveRender(root, mat4(1.0));
}

void GLRenderer::recursiveRender(const Node& node, const mat4& parent2worldTransformation) {

    mat4 transformation = parent2worldTransformation * node.transformation;
    glUniformMatrix4fv(shader.getUniform("modelview"), 1, GL_FALSE, value_ptr(camera.world2eye() * transformation));
    glUniformMatrix4fv(shader.getUniform("normalmatrix"), 1, GL_FALSE, value_ptr(transpose(inverse(camera.world2eye() * transformation)))); // normal matrix = transpose(inverse(modelview))

    for (auto mesh : node.meshes) {

        glBindVertexArray(mesh.vao);

        glUniform4fv(shader.getUniform("mat_diffuse"), 1, value_ptr(mesh.diffuse));
        glUniform4fv(shader.getUniform("mat_ambient"), 1, value_ptr(mesh.ambient));

        glDrawElements(GL_TRIANGLES, mesh.numfaces * 3, GL_UNSIGNED_INT, 0);
        glFlush();
    }

    for (auto n : node.children) {
        recursiveRender(*n, transformation);
    }
}

void GLRenderer::resize(const int w, const int h)
{
    glViewport(0,0,w,h);
}
