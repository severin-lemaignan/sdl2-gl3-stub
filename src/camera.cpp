#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

using namespace glm;

Camera::Camera()
{
    _aspect = DEFAULT_ASPECT;
}

Camera::Camera(int width, int heigh)
{
    setAspect(width, heigh);
}

void Camera::lookAt(float x, float y, float z)
{
    lookat.x = x;
    lookat.y = y;
    lookat.z = z;
}

void Camera::moveAt(float x, float y, float z)
{
    pose.x = x;
    pose.y = y;
    pose.z = z;
}

void Camera::setAspect(int width, int height)
{
    _aspect = width/height;
}

// GL_PROJECTION
mat4 Camera::projection()
{
    return glm::perspective(DEFAULT_FOV, _aspect, ZNEAR, ZFAR);
}

// GL_MODELVIEW (well, WORLDVIEW in fact)
mat4 Camera::world2eye()
{
    return glm::lookAt(pose, lookat, vec3(0.0, 1.0, 0.0));
}
