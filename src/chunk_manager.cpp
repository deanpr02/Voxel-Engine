#include "chunk_manager.h"



Chunk::Chunk(){
    m_blocks = new Block **[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        m_blocks[i] = new Block *[CHUNK_SIZE];
        for (int j = 0; j < CHUNK_SIZE; j++) {
            m_blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
    //createMesh();
}

Chunk::Chunk(glm::vec3 position){
    m_blocks = new Block **[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        m_blocks[i] = new Block *[CHUNK_SIZE];
        for (int j = 0; j < CHUNK_SIZE; j++) {
            m_blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
    m_worldPos = position;
    createMesh();
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
    glm::vec3 p0 = glm::vec3(m_worldPos.x+x-BLOCK_SIZE,m_worldPos.y+y-BLOCK_SIZE,m_worldPos.z+z-BLOCK_SIZE); //front-bottom-left
    glm::vec3 p1 = glm::vec3(m_worldPos.x+x-BLOCK_SIZE,m_worldPos.y+y+BLOCK_SIZE,m_worldPos.z+z-BLOCK_SIZE); //front-top-left
    glm::vec3 p2 = glm::vec3(m_worldPos.x+x+BLOCK_SIZE,m_worldPos.y+y+BLOCK_SIZE,m_worldPos.z+z-BLOCK_SIZE); //front-top-right
    glm::vec3 p3 = glm::vec3(m_worldPos.x+x+BLOCK_SIZE,m_worldPos.y+y-BLOCK_SIZE,m_worldPos.z+z-BLOCK_SIZE); //front-bottom-right
    glm::vec3 p4 = glm::vec3(m_worldPos.x+x-BLOCK_SIZE,m_worldPos.y+y-BLOCK_SIZE,m_worldPos.z+z+BLOCK_SIZE); //back-bottom-left
    glm::vec3 p5 = glm::vec3(m_worldPos.x+x-BLOCK_SIZE,m_worldPos.y+y+BLOCK_SIZE,m_worldPos.z+z+BLOCK_SIZE); //back-top-left
    glm::vec3 p6 = glm::vec3(m_worldPos.x+x+BLOCK_SIZE,m_worldPos.y+y+BLOCK_SIZE,m_worldPos.z+z+BLOCK_SIZE); //back-top-right
    glm::vec3 p7 = glm::vec3(m_worldPos.x+x+BLOCK_SIZE,m_worldPos.y+y-BLOCK_SIZE,m_worldPos.z+z+BLOCK_SIZE); //back-bottom-right

    //need to eventually add normal data/color data probably
    addVertex(p0);
    addVertex(p1);
    addVertex(p2);
    addVertex(p3);
    addVertex(p4);
    addVertex(p5);
    addVertex(p6);
    addVertex(p7);

    int indexOffset = m_vertices.size() / 3 - 8;
    //front
    addTriangle(0+indexOffset,1+indexOffset,2+indexOffset);
    addTriangle(0+indexOffset,2+indexOffset,3+indexOffset);
    
    //back face
    addTriangle(4+indexOffset, 5+indexOffset, 6+indexOffset);
    addTriangle(4+indexOffset, 6+indexOffset, 7+indexOffset);

    //left face
    addTriangle(0+indexOffset, 4+indexOffset, 5+indexOffset);
    addTriangle(0+indexOffset, 5+indexOffset, 1+indexOffset);

    //right face
    addTriangle(3+indexOffset, 2+indexOffset, 6+indexOffset);
    addTriangle(3+indexOffset, 7+indexOffset, 6+indexOffset);

    //top face
    addTriangle(1+indexOffset, 5+indexOffset, 6+indexOffset);
    addTriangle(1+indexOffset, 2+indexOffset, 6+indexOffset);

    //bottom face
    addTriangle(4+indexOffset, 0+indexOffset, 3+indexOffset);
    addTriangle(4+indexOffset, 3+indexOffset, 7+indexOffset);
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

ChunkManager::ChunkManager(){
    return;
}

void ChunkManager::generateChunks(){
    for(int x = -CHUNK_SIZE; x <= CHUNK_SIZE; x+= CHUNK_SIZE){
        for(int z = -CHUNK_SIZE; z <= CHUNK_SIZE; z+= CHUNK_SIZE){
            glm::vec3 pos = glm::vec3(x,-CHUNK_SIZE,z);
            Chunk* chunk = new Chunk(pos);
            m_chunks.push_back(chunk);
        }
    }
    std::cout<<m_chunks.size();
}

void ChunkManager::renderChunks(glm::vec3 worldPos){
    for(int x = -CHUNK_SIZE+worldPos.x; x <= CHUNK_SIZE+worldPos.x; x += CHUNK_SIZE){
        for(int z = -CHUNK_SIZE+worldPos.z; z <= CHUNK_SIZE+worldPos.z; z += CHUNK_SIZE){
            glm::vec3 pos = glm::vec3(x,-CHUNK_SIZE,z);
            auto it = m_chunkStorage.find(pos);
            
            if(it != m_chunkStorage.end()){
                Chunk* chunk = it->second;
                loadChunk(chunk);
            }
            //chunk doesn't exist, generate chunk
            else{
                Chunk* chunk = new Chunk(pos);
                m_chunkStorage[pos] = chunk;
                loadChunk(chunk);
            }
        }
    }
    //for(int i = 0; i < m_chunks.size(); i++){
    //    glBindVertexArray(m_chunks[i]->m_vao);
    //    glDrawElements(GL_TRIANGLES,m_chunks[i]->m_indices.size(),GL_UNSIGNED_INT,0);
    //}
}

void ChunkManager::loadChunk(Chunk* chunk){
    glBindVertexArray(chunk->m_vao);
    glDrawElements(GL_TRIANGLES,chunk->m_indices.size(),GL_UNSIGNED_INT,0);
}