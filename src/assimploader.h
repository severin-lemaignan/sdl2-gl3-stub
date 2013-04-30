#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif
#include <glm/glm.hpp>

#include "node.h"
#include "mesh.h"
#include "shader.h"

class AssimpLoader
{
    // the global Assimp scene object
    const aiScene* scene;
    //GLuint scene_list = 0;
    aiVector3D scene_min, scene_max, scene_center;

    // images / texture
    //std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
    //GLuint*		textureIds;							// pointer to texture Array

    // Create an instance of the Importer class
    Assimp::Importer importer;

    Node* recursiveLoad(const struct aiNode* nd, std::vector<Node> &nodes, const Shader &shader);
    void makeMesh(const aiMesh& in, Mesh& out, const Node &node, const Shader &shader);
    std::size_t countNodes(const aiNode *nd);
    void fillMaterial(const aiMaterial &mat, Mesh &mesh);

public:

    bool Import3DFromFile(const std::string& name);

    void loadNodes(Node& root, std::vector<Node>& nodes, const Shader& shader);


};
