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
#include "block.h"

class Chunk{
    public:
    int CHUNK_SIZE = 16;
    float BLOCK_SIZE = 0.5f;
    std::vector<float> m_vertices;
    std::vector<int> m_indices;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    Block *** m_blocks;

    Chunk();
    ~Chunk();
    void createMesh();
    void createCube(float,float,float);
    void addVertex(glm::vec3);
    void addTriangle(int,int,int);
    void initializeBuffer();
};

class ChunkManager{
    public:
    
    
};

#endif