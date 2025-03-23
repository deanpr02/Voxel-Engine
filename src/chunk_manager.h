#pragma once

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <unordered_map>
#include "block.h"
#include <iostream>
#include <cmath>
#include "generator.h"

const int CHUNK_SIZE = 16;
const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 64;

struct Vec3Hash {
    size_t operator()(const glm::vec3& v) const {
        // Combine the hash of each component
        size_t h1 = std::hash<float>()(v.x);
        size_t h2 = std::hash<float>()(v.y);
        size_t h3 = std::hash<float>()(v.z);
        
        // A simple hash combine function
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

// Custom equality function for glm::vec3
struct Vec3Equal {
    bool operator()(const glm::vec3& v1, const glm::vec3& v2) const {
        // For exact equality
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }
};

class Chunk{
    public:
    std::vector<float> m_vertices;
    std::vector<int> m_indices;
    glm::vec3 m_worldPos;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    Block *** m_blocks;

    Chunk();
    Chunk(glm::vec3);
    ~Chunk();
    void createMesh();
    void createCube(float,float,float,float);
    void setWorldPos(glm::vec3);
    void addVertex(glm::vec3);
    void addTex(glm::vec2);
    void addTriangle(int,int,int);
    void initializeBuffer();
    //glm::vec3 getChunkPosition(glm::vec3);
};

class ChunkManager{
    public:
    int m_renderDistance = 3;
    glm::vec2 m_currentChunk;
    std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> m_chunkStorage;
    std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> m_visibleChunks; 
    ProceduralGenerator* m_generator;
    unsigned int m_textureMap;
    float m_texWidth;


    ChunkManager();
    void createChunkMesh(Chunk*,glm::vec3);
    void generateChunks();
    std::unordered_map<glm::vec3,float,Vec3Hash,Vec3Equal> getHeightMap(glm::vec3);
    //void generateChunk();
    Chunk* generateChunk(glm::vec3);
    void initializeChunks(glm::vec3);
    void pollChunks(int,int,int,int);
    void renderChunks();
    void loadChunk(glm::vec3);
    void unloadChunk(glm::vec3);
    void renderChunk(Chunk*);
    void checkBoundary(glm::vec3);
    void setTextureMap(unsigned int);
};

#endif