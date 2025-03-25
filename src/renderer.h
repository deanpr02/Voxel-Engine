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
#include "types.h"

class Renderer{
    public:
    struct Shaders {
        Shader* s_camera = new Shader();
        Shader* s_wall = new Shader();
        Shader* s_floor = new Shader();
        Shader* s_light = new Shader();
        Shader* s_cube = new Shader();
        Shader* s_lightning = new Shader();
    };

    ChunkManager* m_chunkManager;
    unsigned int m_textureMap;
    WeaponSystem* m_weapons;
    std::unordered_map<SPELL_TYPE,Shader*> m_spellShaders;
    struct Shaders m_shaders;

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