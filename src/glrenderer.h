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

#define BUFFER_OFFSET(x)  ((void *) (x))

class GLRenderer
{
public:
    GLRenderer();

    void load(const std::string &file);
    void display();

    void resize(const int w, const int h);
    Camera camera;

private:

    Node root;
    std::vector<Node> nodes;

    AssimpLoader assimploader;

    Shader shader;

    std::map<std::string, GLint> VAO_IDs;
    std::map<std::string, GLint> Buffer_IDs;

    enum Attrib_IDs { vPosition = 0 };

};

#endif // GLRENDERER_H
