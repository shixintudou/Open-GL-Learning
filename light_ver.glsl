#version 330 core
layout (location=0) in vec3 apos

uniform mat4 model;
uniform mat4 view;
uniform mat4 projective;

void main()
{
    gl_Position=projective*view*model*vec4(apos,1.0f);
}