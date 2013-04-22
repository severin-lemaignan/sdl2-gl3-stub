#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "mesh.h"

struct Mesh;

struct Node
{
    std::string name;
    glm::mat4 transformation; // model2world transformation
    std::vector<Node*> children;
    std::vector<Mesh> meshes;
};

#endif // NODE_H
