#ifndef CAMERA_H
#define CAMERA_H

#ifndef GL3_PROTOTYPES
#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#endif

#include <glm/glm.hpp>

const float DEFAULT_FOV = 45.0f;
const float DEFAULT_ASPECT = 1.33f;

const float ZNEAR = 0.1f;
const float ZFAR = 100.0f;

class Camera
{
public:
    Camera();
    Camera(int width, int height);

    void lookAt(float x, float y, float z);
    void moveAt(float x, float y, float z);

    void setAspect(int width, int height);

    glm::mat4 projection();
    glm::mat4 world2eye();

    glm::vec3 pose;
    glm::vec3 lookat;

private:
    float _aspect;
};

#endif // CAMERA_H
