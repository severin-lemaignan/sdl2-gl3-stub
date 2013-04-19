#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif

#include "node.h"

struct Node;

struct Mesh
{
    const Node* node;
    std::string name;
    GLuint vao;
    int numvertices;
    GLuint vbo;
    int numfaces;
    GLuint ibo;
};

#endif // MESH_H
