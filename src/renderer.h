#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "block.h"
#include "chunk_manager.h"
#include "player.h"

extern Shaders _shaders;


class Renderer{
    public:
    ChunkManager* m_chunkManager;
    unsigned int m_textureMap;
    WeaponSystem* m_weapons;

    Renderer(WeaponSystem*);
    void initializeBuffer(Chunk);
    void drawCube(float,float,float);
    void drawWorld(Camera*);
    void updateChunks(Camera*);
    void loadShaders();
    void init();
    void loadTextures();
    void drawWeapons(Camera*);
    void render(Camera*);


};

#endif