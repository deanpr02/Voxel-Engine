#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 view;
uniform mat4 perspective;
uniform mat4 model;

#define MAX_OFFSETS 900
uniform vec2 offsets[MAX_OFFSETS];

out vec3 Normal;
out vec3 FragPos;

void main()
    {
        gl_Position = perspective * view * model * vec4(aPos.x + offsets[gl_InstanceID].x,aPos.y,aPos.z+offsets[gl_InstanceID].y,1.0f);
        Normal = mat3(transpose(inverse(model))) * aNormal;
        FragPos = vec3(model * vec4(aPos.x + offsets[gl_InstanceID].x,aPos.y,aPos.z+offsets[gl_InstanceID].y,1.0f));
    };