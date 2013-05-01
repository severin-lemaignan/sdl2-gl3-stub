#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <string>

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif


#include "shader.h"

class Postprocess
{
public:
    Postprocess(int screen_width, int screen_height, const std::string &vertex_shader, const std::string &fragment_shader);

    ~Postprocess();

    static Postprocess noop();

    void resize(int w, int h);

    void recordDraw();
    void process();

private:
    Shader shader;

    GLuint fbo, fbo_texture, rbo_depth;
    GLuint vbo_fbo_vertices;

    void init(int screen_width, int screen_height);

};

#endif // POSTPROCESS_H
