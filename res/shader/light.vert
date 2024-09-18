#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 perspective;
uniform mat4 model;

#define MAX_OFFSETS 900
uniform vec2 offsets[MAX_OFFSETS];

void main()
    {
        gl_Position = perspective * view * model * vec4(aPos,1.0f);
    };