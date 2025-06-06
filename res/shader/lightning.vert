#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 perspective;
uniform mat4 model;

void main()
    {
        gl_Position = perspective * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    };