#version 130

uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;

in vec4 vPosition;

void main(void)
{
    gl_Position = projection_matrix * modelview_matrix * vPosition;
}
