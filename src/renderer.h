#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "shader.h"
#include "camera.h"

extern Shaders _shaders;

class Renderer{
    public:
    unsigned int _vbo;
    unsigned int _vao;
    unsigned int _ebo;

    void initializeBuffer();
    void drawCube(float,float,float);
    void drawWorld(Camera);
    void loadShaders();
    void init();

};

#endif