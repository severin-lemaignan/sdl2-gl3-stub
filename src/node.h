#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include "mesh.h"

struct Mesh;

struct Node
{
    std::string name;
    std::vector<Node*> children;
    std::vector<Mesh> meshes;
};

#endif // NODE_H
