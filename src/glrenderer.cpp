#include <iostream>

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


   shader.setUniform("global_ambient", .4,.2,.2,.1 );
   shader.setUniform("light_ambient", .4,.4,.4, 1.0 );
   shader.setUniform("light_diffuse", 1,1,1,1 );
   shader.setUniform("light_location", 2,2,10 );


}


void GLRenderer::display()
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   shader.setUniform("projection", camera.projection());
   recursiveRender(root, mat4(1.0));
}

void GLRenderer::recursiveRender(const Node& node, const mat4& parent2worldTransformation) {

    mat4 transformation = parent2worldTransformation * node.transformation;
    shader.setUniform("modelview", camera.world2eye() * transformation);
    shader.setUniform("normalmatrix", transpose(inverse(camera.world2eye() * transformation))); // normal matrix = transpose(inverse(modelview))

    for (auto mesh : node.meshes) {

        glBindVertexArray(mesh.vao);

        shader.setUniform("mat_diffuse", mesh.diffuse);
        shader.setUniform("mat_ambient", mesh.ambient);

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
