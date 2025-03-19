#include "physics.h"

PhysicsObject::PhysicsObject(glm::vec3* position){
    m_position = position;
}

glm::vec3 PhysicsObject::getChunkPosition(glm::vec3 worldPos){
    int x = std::floor(static_cast<double>(worldPos.x + BLOCK_SIZE));
    int y = CHUNK_HEIGHT - std::ceil(std::abs(worldPos.y)) - 1;
    int z = std::floor(static_cast<double>(worldPos.z + BLOCK_SIZE));

    x = (x % CHUNK_SIZE) & CHUNK_SIZE-1;
    z = (z % CHUNK_SIZE) & CHUNK_SIZE-1;

    return glm::vec3(x,y,z);
}


void PhysicsObject::applyGravity(std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> chunks,float deltaTime){
    glm::vec3 grav = glm::vec3(0,GRAVITY,0);
    int chunkX = std::floor(static_cast<double>(m_position->x+BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    int chunkZ = std::floor(static_cast<double>(m_position->z+BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    glm::vec3 chunkPosition = getChunkPosition(*m_position);
    
    int x = chunkPosition.x;
    int y = chunkPosition.y;
    int z = chunkPosition.z;
    
//issue is when we go negative we need to get checking from opposite end of chunk not beginning
    Chunk* currentChunk = chunks[glm::vec3(chunkX,-CHUNK_HEIGHT,chunkZ)];
    
    if(currentChunk->m_blocks[x][y][z].m_active == false){
        m_fallSpeed = m_fallSpeed < TERMINAL_VELOCITY ? m_fallSpeed + GRAVITY : m_fallSpeed;
        m_position->y -= m_fallSpeed*deltaTime;
    }
    else{
        m_fallSpeed = 0;
    }
}


bool PhysicsObject::checkIfColliding(std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> chunks, glm::vec3 worldPos, glm::vec3 direction){
    glm::vec3 collisionPos = worldPos + direction;
    int chunkX = std::floor(static_cast<double>(collisionPos.x+BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    int chunkZ = std::floor(static_cast<double>(collisionPos.z+BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    
    Chunk* chunk = chunks[glm::vec3(chunkX,-CHUNK_HEIGHT,chunkZ)];
    glm::vec3 chunkPos = getChunkPosition(collisionPos);
    
    //need to check the heights, currently we arechecking block under us, we need to look up 1/2 blocks
    int x = chunkPos.x;
    int y = (chunkPos.y < CHUNK_HEIGHT-1) ? chunkPos.y+1 : chunkPos.y;
    int z = chunkPos.z;

    return chunk->m_blocks[x][y][z].m_active;
}

