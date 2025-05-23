#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 perspective;
uniform mat4 model;

out vec2 TexCoord;

void main()
    {
        gl_Position = perspective * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        TexCoord = aTexCoord;
    };