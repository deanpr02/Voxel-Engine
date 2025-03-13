#include "chunk_manager.h"

Chunk::Chunk(){
    m_blocks = new Block **[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        m_blocks[i] = new Block *[CHUNK_SIZE];
        for (int j = 0; j < CHUNK_SIZE; j++) {
            m_blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
}

void Chunk::createMesh(){
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){
                if(m_blocks[x][y][z].m_active == false){
                    continue;
                }
                createCube(x,y,z);
            }
        }
    }
    initializeBuffer();
}

void Chunk::createCube(float x, float y, float z){
    glm::vec3 p0 = glm::vec3(x-BLOCK_SIZE,y-BLOCK_SIZE,z-BLOCK_SIZE); //front-bottom-left
    glm::vec3 p1 = glm::vec3(x-BLOCK_SIZE,y+BLOCK_SIZE,z-BLOCK_SIZE); //front-top-left
    glm::vec3 p2 = glm::vec3(x+BLOCK_SIZE,y+BLOCK_SIZE,z-BLOCK_SIZE); //front-top-right
    glm::vec3 p3 = glm::vec3(x+BLOCK_SIZE,y-BLOCK_SIZE,z-BLOCK_SIZE); //front-bottom-right
    glm::vec3 p4 = glm::vec3(x-BLOCK_SIZE,y-BLOCK_SIZE,z+BLOCK_SIZE); //back-bottom-left
    glm::vec3 p5 = glm::vec3(x-BLOCK_SIZE,y+BLOCK_SIZE,z+BLOCK_SIZE); //back-top-left
    glm::vec3 p6 = glm::vec3(x+BLOCK_SIZE,y+BLOCK_SIZE,z+BLOCK_SIZE); //back-top-right
    glm::vec3 p7 = glm::vec3(x+BLOCK_SIZE,y-BLOCK_SIZE,z+BLOCK_SIZE); //back-bottom-right

    addVertex(p0);
    addVertex(p1);
    addVertex(p2);
    addVertex(p3);
    addVertex(p4);
    addVertex(p5);
    addVertex(p6);
    addVertex(p7);

    int currentIndex = m_vertices.size() / 3 - 8;
    //front
    addTriangle(0+currentIndex,1+currentIndex,2+currentIndex);
    addTriangle(0+currentIndex,2+currentIndex,3+currentIndex);
    
    //back face
    addTriangle(4+currentIndex, 5+currentIndex, 6+currentIndex);
    addTriangle(4+currentIndex, 6+currentIndex, 7+currentIndex);

    //left face
    addTriangle(0+currentIndex, 4+currentIndex, 5+currentIndex);
    addTriangle(0+currentIndex, 5+currentIndex, 1+currentIndex);

    //right face
    addTriangle(3+currentIndex, 2+currentIndex, 6+currentIndex);
    addTriangle(3+currentIndex, 7+currentIndex, 6+currentIndex);

    //top face
    addTriangle(1+currentIndex, 5+currentIndex, 6+currentIndex);
    addTriangle(1+currentIndex, 2+currentIndex, 6+currentIndex);

    //bottom face
    addTriangle(4+currentIndex, 0+currentIndex, 3+currentIndex);
    addTriangle(4+currentIndex, 3+currentIndex, 7+currentIndex);
}

void Chunk::addVertex(glm::vec3 point){
    m_vertices.push_back(point.x);
    m_vertices.push_back(point.y);
    m_vertices.push_back(point.z);
}

void Chunk::addTriangle(int v1, int v2, int v3){
    m_indices.push_back(v1);
    m_indices.push_back(v2);
    m_indices.push_back(v3);
}

void Chunk::initializeBuffer(){
    glGenVertexArrays(1,&m_vao);
    glGenBuffers(1,&m_vbo);
    glGenBuffers(1,&m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}