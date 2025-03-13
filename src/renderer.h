#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "shader.h"
#include "camera.h"
#include "block.h"
#include "chunk_manager.h"

extern Shaders _shaders;


class Renderer{
    public:
    Chunk* _chunk = new Chunk();

    void initializeBuffer(Chunk);
    void drawCube(float,float,float);
    void drawWorld(Camera);
    void loadShaders();
    void init();

};

#endif