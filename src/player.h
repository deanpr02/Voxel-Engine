#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

struct Flashlight{
    //glm::vec3 light = glm::vec3(2.0f,0.0f,2.0f);
    float x =0;
};

class Player{
    Flashlight light;
};
#endif