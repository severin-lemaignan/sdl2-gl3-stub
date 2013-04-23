#version 130

uniform vec4 diffuse;

out vec4 fColor;

void main(void)
{
    fColor = diffuse;
}
