#version 130

uniform mat4 modelview;
uniform mat4 projection;

in vec4 position;

void main(void)
{
    gl_Position = projection * modelview * position;
}
