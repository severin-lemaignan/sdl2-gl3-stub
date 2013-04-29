#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif

#include <glm/glm.hpp>

#include "node.h"

struct Node;

struct Mesh
{
    const Node* node;
    std::string name;

    GLuint vao; // vertex array object
    int numvertices;
    GLuint vbo; // vertices + normals
     int numfaces;
    GLuint ibo; // elements

    glm::vec4 diffuse;
    glm::vec4 ambient;
    glm::vec4 specular;
    float shininess;
};

#endif // MESH_H
