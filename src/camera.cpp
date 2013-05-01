#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
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


void Camera::moveAt(float dx, float dy, float dz)
{

    vec3 direction = normalize(lookat - pose);
    vec3 horiz = cross(direction, UP);
    vec3 vert = cross(direction, horiz);

    pose = pose + horiz * dx + vert * dy + direction * dz;
    lookat = lookat + horiz * dx + vert * dy + direction * dz;
}

void Camera::moveLookAt(float dx, float dy)
{

    vec3 direction = normalize(lookat - pose);
    vec3 horiz = cross(direction, UP);
    vec3 vert = cross(direction, horiz);

    lookat = lookat + horiz * dx + vert * dy;
}

void Camera::setAspect(int width, int height)
{
    _aspect = width/height;
}

// GL_PROJECTION
mat4 Camera::projection() const
{
    return perspective(DEFAULT_FOV, _aspect, ZNEAR, ZFAR);
}

// GL_MODELVIEW (well, WORLDVIEW in fact)
mat4 Camera::world2eye() const
{
    mat4 m = lookAt(pose, lookat, UP);
    return m;
}
