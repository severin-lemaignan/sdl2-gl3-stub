#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <string>
#include <map>

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif

#include "shader.h"
#include "camera.h"
#include "node.h"
#include "assimploader.h"
#include "postprocess.h"

#define BUFFER_OFFSET(x)  ((void *) (x))

class GLRenderer
{
public:
    Camera camera;

    GLRenderer();

    void load(const std::string &file);
    void display();

    void resize(const int w, const int h);

private:

    void recursiveRender(const Node &node, const glm::mat4& parent2worldTransformation);

    Node root;
    std::vector<Node> nodes;

    AssimpLoader assimploader;

    Shader shader;

    std::map<std::string, GLint> VAO_IDs;
    std::map<std::string, GLint> Buffer_IDs;

    Postprocess effect;
};

#endif // GLRENDERER_H
