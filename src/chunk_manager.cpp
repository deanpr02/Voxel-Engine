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


//change blocks[i] to new *[CHUNK_HEIGHT] and change j loop to CHUNK_HEIGHT
Chunk::Chunk(glm::vec3 position){
    m_blocks = new Block **[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        m_blocks[i] = new Block *[CHUNK_HEIGHT];
        for (int j = 0; j < CHUNK_HEIGHT; j++) {
            m_blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
    m_worldPos = position;
    //createMesh();
}

//void Chunk::createMesh(){
//    for(int x = 0; x < CHUNK_SIZE; x++){
//        for(int y = 0; y < CHUNK_HEIGHT; y++){
//            for(int z = 0; z < CHUNK_SIZE; z++){
//                //get noise value which will be height map value;
//
//                if(m_blocks[x][y][z].m_active == false){
//                    continue;
//                }
//                createCube(x,y,z);
//            }
//        }
//    }
//    initializeBuffer();
//}

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
    glm::vec3 spawn = glm::vec3(0,-CHUNK_HEIGHT,0);
    m_generator = new ProceduralGenerator();
    
    initializeChunks(spawn);
}

//maybe change where i pass the heightmap into the chunk constructor itself
//void ChunkManager::createChunkMesh(Chunk* chunk, glm::vec3 worldPos){
//    std::unordered_map<glm::vec3,float,Vec3Hash,Vec3Equal> heightMap = getHeightMap(worldPos);
//    //std::cout<<heightMap[glm::vec3(16,0,16)]<<std::endl;
//    for(int x = 0; x < CHUNK_SIZE; x++){
//        for(int y = 0; y < CHUNK_HEIGHT; y++){
//            for(int z = 0; z < CHUNK_SIZE; z++){
//                glm::vec3 pos = glm::vec3(x,0,z);
//                int height = std::floor((heightMap[pos]*CHUNK_HEIGHT));
//                //std::cout<<height;
//                if(y > height){
//                    chunk->m_blocks[x][y][z].m_active = false;
//                }
//                if(chunk->m_blocks[x][y][z].m_active == false){
//                    continue;
//                }
//                chunk->createCube(x,y,z);
//            }
//        }
//    }
//    chunk->initializeBuffer();
//}

void ChunkManager::createChunkMesh(Chunk* chunk, glm::vec3 worldPos){
    std::unordered_map<glm::vec3,float,Vec3Hash,Vec3Equal> heightMap = getHeightMap(worldPos);
   //std::cout<<heightMap[glm::vec3(16,0,16)]<<std::endl;
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            glm::vec3 pos = glm::vec3(x,0,z);
            int height = std::floor((heightMap[pos]*CHUNK_HEIGHT));
            //if(x == 0 && z == 0){
            //    height = CHUNK_HEIGHT-1;
            //}
            //if(x == 1 && z == 1){
            //    height = CHUNK_HEIGHT-1;
            //}
           //std::cout<<height;
            chunk->m_blocks[x][height][z].m_active = true;
            chunk->createCube(x,height,z);
        }
    }
    chunk->initializeBuffer();
}

Chunk* ChunkManager::generateChunk(glm::vec3 worldPos){
    Chunk* generatedChunk = new Chunk(worldPos);
    createChunkMesh(generatedChunk,worldPos);
    return generatedChunk;
}


std::unordered_map<glm::vec3,float,Vec3Hash,Vec3Equal> ChunkManager::getHeightMap(glm::vec3 worldPos){
    std::unordered_map<glm::vec3,float,Vec3Hash,Vec3Equal> heightMap;
    //std::cout<<"x: " << worldPos.x << "z: " << worldPos.z<<std::endl;
    for(int x = 0; x < CHUNK_WIDTH; x++){
        for(int z = 0; z < CHUNK_WIDTH; z++){
            float xPos = ((worldPos.x + x + BLOCK_SIZE))*0.1;
            float zPos = ((worldPos.z + z + BLOCK_SIZE))*0.1;
            float mappedHeight = m_generator->generate(xPos,zPos,0);
            //std::cout<<mappedHeight;
            heightMap[glm::vec3(x,0,z)] = mappedHeight;
            //std::cout<<"x: " << xPos << "z: " << zPos << std::endl;
        }
    }

    //for(auto it=heightMap.begin();it!=heightMap.end();it++){
    //    std::cout<<it->second<<std::endl;
    //}
    return heightMap;
}

//void ChunkManager::generateChunks(){
//    for(int x = -CHUNK_SIZE; x <= CHUNK_SIZE; x+= CHUNK_SIZE){
//        for(int z = -CHUNK_SIZE; z <= CHUNK_SIZE; z+= CHUNK_SIZE){
//            glm::vec3 pos = glm::vec3(x,-CHUNK_SIZE,z);
//            Chunk* chunk = new Chunk(pos);
//            m_chunks.push_back(chunk);
//        }
//    }
//    std::cout<<m_chunks.size();
//}


//still need to remove chunks when out of range. only call this when you cross a chunk boundary
void ChunkManager::initializeChunks(glm::vec3 worldPos){
    int currentChunkX = std::floor(static_cast<double>(worldPos.x + BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    int currentChunkZ = std::floor(static_cast<double>(worldPos.z + BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    m_currentChunk = glm::vec2(currentChunkX,currentChunkZ);

    for(int x = -1*(m_renderDistance/2); x <= m_renderDistance/2; x++){
        for(int z = -1*(m_renderDistance/2); z <= m_renderDistance/2; z++){
            //need to modify this so we get chunk origin now somewhere within chunk
            int clampedX = currentChunkX + (x*CHUNK_SIZE);
            int clampedZ = currentChunkZ + (z*CHUNK_SIZE);
            glm::vec3 pos = glm::vec3(clampedX,-CHUNK_HEIGHT,clampedZ);
            //if chunk is already visible, then continue rendering
            auto vi = m_visibleChunks.find(pos);
            if(vi == m_visibleChunks.end()){
                //see if we have already generated chunk before
                auto ch = m_chunkStorage.find(pos);
                //generate chunk and store it
                if(ch == m_chunkStorage.end()){
                    //Chunk* chunk = new Chunk(pos);
                    Chunk* chunk = generateChunk(pos);
                    m_chunkStorage[pos] = chunk;
                    m_visibleChunks[pos] = chunk;
                }
                else{
                    m_visibleChunks[pos] = ch->second;
                }
            }
            
        }
    }
    //for(int i = 0; i < m_chunks.size(); i++){
    //    glBindVertexArray(m_chunks[i]->m_vao);
    //    glDrawElements(GL_TRIANGLES,m_chunks[i]->m_indices.size(),GL_UNSIGNED_INT,0);
    //}
}

void ChunkManager::pollChunks(int xChunk, int zChunk, int newXChunk, int newZChunk){
    //check if x changed
    if(newXChunk < xChunk){
        //change it to m_renderDistance / 2 * CHUNK_SIZE
        int loadX = newXChunk - CHUNK_SIZE;
        int unloadX = xChunk + CHUNK_SIZE;

        for(int i=-1*(m_renderDistance/2);i<=m_renderDistance/2;i++){
            glm::vec3 chunkToLoad = glm::vec3(loadX,-CHUNK_HEIGHT,zChunk+(i*CHUNK_SIZE));
            glm::vec3 chunkToUnload = glm::vec3(unloadX,-CHUNK_HEIGHT,zChunk+(i*CHUNK_SIZE));
            loadChunk(chunkToLoad);
            unloadChunk(chunkToUnload);
        }
    }
    else if(newXChunk > xChunk){
        int loadX = newXChunk + CHUNK_SIZE;
        int unloadX = xChunk - CHUNK_SIZE;

        for(int i=-1*(m_renderDistance/2);i<=m_renderDistance/2;i++){
            glm::vec3 chunkToLoad = glm::vec3(loadX,-CHUNK_HEIGHT,zChunk+(i*CHUNK_SIZE));
            glm::vec3 chunkToUnload = glm::vec3(unloadX,-CHUNK_HEIGHT,zChunk+(i*CHUNK_SIZE));
            loadChunk(chunkToLoad);
            unloadChunk(chunkToUnload);
        }
        
    }

    //check if z changed
    if(newZChunk < zChunk){
        int loadZ = newZChunk - CHUNK_SIZE;
        int unloadZ = zChunk + CHUNK_SIZE;

        for(int i=-1*(m_renderDistance/2);i<=m_renderDistance/2;i++){
            glm::vec3 chunkToLoad = glm::vec3(xChunk+(i*CHUNK_SIZE),-CHUNK_HEIGHT,loadZ);
            glm::vec3 chunkToUnload = glm::vec3(xChunk+(i*CHUNK_SIZE),-CHUNK_HEIGHT,unloadZ);
            loadChunk(chunkToLoad);
            unloadChunk(chunkToUnload);
        }
        
    }
    else if(newZChunk > zChunk){
        int loadZ = newZChunk + CHUNK_SIZE;
        int unloadZ = zChunk - CHUNK_SIZE;
        
        for(int i=-1*(m_renderDistance/2);i<=m_renderDistance/2;i++){
            glm::vec3 chunkToLoad = glm::vec3(xChunk+(i*CHUNK_SIZE),-CHUNK_HEIGHT,loadZ);
            glm::vec3 chunkToUnload = glm::vec3(xChunk+(i*CHUNK_SIZE),-CHUNK_HEIGHT,unloadZ);
            loadChunk(chunkToLoad);
            unloadChunk(chunkToUnload);
        }
        
    }
    //std::cout<<m_visibleChunks.size();


}

void ChunkManager::loadChunk(glm::vec3 chunkPos){
    auto it = m_chunkStorage.find(chunkPos);
    if(it != m_chunkStorage.end()){
        m_visibleChunks[chunkPos] = it->second;
    }
    else{
        //Chunk* chunk = new Chunk(chunkPos);
        Chunk* chunk = generateChunk(chunkPos);
        m_chunkStorage[chunkPos] = chunk;
        m_visibleChunks[chunkPos] = chunk;
    }
}

void ChunkManager::unloadChunk(glm::vec3 chunkPos){
    m_visibleChunks.erase(chunkPos);
}

void ChunkManager::checkBoundary(glm::vec3 worldPos){
    int chunkX = m_currentChunk.x;
    int chunkZ = m_currentChunk.y;
    int newXChunk = std::floor(static_cast<double>(worldPos.x + BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    int newZChunk = std::floor(static_cast<double>(worldPos.z + BLOCK_SIZE)/CHUNK_SIZE)*CHUNK_SIZE;
    bool isNewChunk = false;

    if(m_currentChunk.x != newXChunk){
        m_currentChunk.x = newXChunk;
        isNewChunk = true;
    }
    if(m_currentChunk.y != newZChunk){
        m_currentChunk.y = newZChunk;
        isNewChunk = true;
    }
    
    if(isNewChunk){
        pollChunks(chunkX,chunkZ,newXChunk,newZChunk);
    }
}

void ChunkManager::renderChunk(Chunk* chunk){
    glBindVertexArray(chunk->m_vao);
    glDrawElements(GL_TRIANGLES,chunk->m_indices.size(),GL_UNSIGNED_INT,0);
}

void ChunkManager::renderChunks(){
    for(auto it = m_visibleChunks.begin();it != m_visibleChunks.end();it++){
        Chunk* chunk = it->second;
        renderChunk(chunk);
    }
}

//everytime we move we will need to check to see if new chunks need to be rendered
