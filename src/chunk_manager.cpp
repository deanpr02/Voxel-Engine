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


void Chunk::createCube(float x, float y, float z, float width){
    glm::vec3 p0 = glm::vec3(m_worldPos.x+x-width,m_worldPos.y+y-width,m_worldPos.z+z-width); //front-bottom-left
    glm::vec3 p1 = glm::vec3(m_worldPos.x+x-width,m_worldPos.y+y+width,m_worldPos.z+z-width); //front-top-left
    glm::vec3 p2 = glm::vec3(m_worldPos.x+x+width,m_worldPos.y+y+width,m_worldPos.z+z-width); //front-top-right
    glm::vec3 p3 = glm::vec3(m_worldPos.x+x+width,m_worldPos.y+y-width,m_worldPos.z+z-width); //front-bottom-right
    glm::vec3 p4 = glm::vec3(m_worldPos.x+x-width,m_worldPos.y+y-width,m_worldPos.z+z+width); //back-bottom-left
    glm::vec3 p5 = glm::vec3(m_worldPos.x+x-width,m_worldPos.y+y+width,m_worldPos.z+z+width); //back-top-left
    glm::vec3 p6 = glm::vec3(m_worldPos.x+x+width,m_worldPos.y+y+width,m_worldPos.z+z+width); //back-top-right
    glm::vec3 p7 = glm::vec3(m_worldPos.x+x+width,m_worldPos.y+y-width,m_worldPos.z+z+width); //back-bottom-right

    glm::vec2 t0 = glm::vec2(1.0f,1.0f);
    glm::vec2 t1 = glm::vec2(1.0,0.0f);
    glm::vec2 t2 = glm::vec2(0.0f,1.0f);
    glm::vec2 t3 = glm::vec2(0.0f,0.0f);
    //need to eventually add normal data/color data probably
    
    //front face
    //addVertex(p0); addTex(t0);
    //addVertex(p1); addTex(t1);
    //addVertex(p2); addTex(t3);
    //addVertex(p3); addTex(t2);
    addVertex(p0); addTex(glm::vec2(32.0f/64.0f,1.0f));
    addVertex(p1); addTex(glm::vec2(32.0f/64.0f,0.0f));
    addVertex(p2); addTex(glm::vec2(0.0f,0.0f));
    addVertex(p3); addTex(glm::vec2(0.0f,1.0f));


    //back face
    //addVertex(p4); addTex(t0);
    //addVertex(p5); addTex(t1);
    //addVertex(p6); addTex(t3);
    //addVertex(p7); addTex(t2);
    addVertex(p4); addTex(glm::vec2(32.0f/64.0f,1.0f));
    addVertex(p5); addTex(glm::vec2(32.0f/64.0f,0.0f));
    addVertex(p6); addTex(glm::vec2(0.0f,0.0f));
    addVertex(p7); addTex(glm::vec2(0.0f,1.0f));

    //left face
    //addVertex(p4); addTex(t0);
    //addVertex(p5); addTex(t1);
    //addVertex(p1); addTex(t3);
    //addVertex(p0); addTex(t2);
    addVertex(p4); addTex(glm::vec2(32.0f/64.0f,1.0f));
    addVertex(p5); addTex(glm::vec2(32.0f/64.0f,0.0f));
    addVertex(p1); addTex(glm::vec2(0.0f,0.0f));
    addVertex(p0); addTex(glm::vec2(0.0f,1.0f));

    //right face
    //addVertex(p3); addTex(t0);
    //addVertex(p2); addTex(t1);
    //addVertex(p6); addTex(t3);
    //addVertex(p7); addTex(t2);
    addVertex(p3); addTex(glm::vec2(32.0f/64.0f,1.0f));
    addVertex(p2); addTex(glm::vec2(32.0f/64.0f,0.0f));
    addVertex(p6); addTex(glm::vec2(0.0f,0.0f));
    addVertex(p7); addTex(glm::vec2(0.0f,1.0f));

    //top face
    //addVertex(p1); addTex(t0);
    addVertex(p1); addTex(glm::vec2(32.0f/64.0f,0.0f));
    //addVertex(p5); addTex(t1);
    addVertex(p5); addTex(glm::vec2(32.0f/64.0f,1.0f));
    //addVertex(p6); addTex(t3);
    addVertex(p6); addTex(glm::vec2(1.0f,1.0f));
    //addVertex(p2); addTex(t2);
    addVertex(p2); addTex(glm::vec2(1.0,0.0f));

    //bottom face
    addVertex(p0); addTex(t0);
    addVertex(p4); addTex(t1);
    addVertex(p7); addTex(t3);
    addVertex(p3); addTex(t2);

    int indexOffset = m_vertices.size() / 5 - 24;

    for (int i = 0; i < 6; i++) {
        int baseIndex = indexOffset + i * 4;
        addTriangle(baseIndex, baseIndex + 1, baseIndex + 2);
        addTriangle(baseIndex, baseIndex + 2, baseIndex + 3);
}
}

void Chunk::addVertex(glm::vec3 point){
    m_vertices.push_back(point.x);
    m_vertices.push_back(point.y);
    m_vertices.push_back(point.z);
}

void Chunk::addTex(glm::vec2 point){
    m_vertices.push_back(point.x);
    m_vertices.push_back(point.y);
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

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
        5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

ChunkManager::ChunkManager(){
    glm::vec3 spawn = glm::vec3(0,-CHUNK_HEIGHT,0);
    m_generator = new ProceduralGenerator();
    
    initializeChunks(spawn);
}

void ChunkManager::setTextureMap(unsigned int texture){
    m_textureMap = texture;
}

void ChunkManager::createChunkMesh(Chunk* chunk, glm::vec3 worldPos){
    std::unordered_map<glm::vec3,float,Vec3Hash,Vec3Equal> heightMap = getHeightMap(worldPos);
    
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            glm::vec3 pos = glm::vec3(x,0,z);
            int height = std::floor((heightMap[pos]*CHUNK_HEIGHT));
            
            chunk->m_blocks[x][height][z].m_active = true;
            chunk->createCube(x,height,z,0.5f);
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

    for(int x = 0; x < CHUNK_WIDTH; x++){
        for(int z = 0; z < CHUNK_WIDTH; z++){
            float xPos = ((worldPos.x + x + BLOCK_SIZE))*0.1;
            float zPos = ((worldPos.z + z + BLOCK_SIZE))*0.1;
            float mappedHeight = m_generator->generate(xPos,zPos,0);
            
            heightMap[glm::vec3(x,0,z)] = mappedHeight;
        }
    }
    return heightMap;
}

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
    glBindTexture(GL_TEXTURE_2D,m_textureMap);
    glBindVertexArray(chunk->m_vao);
    glDrawElements(GL_TRIANGLES,chunk->m_indices.size(),GL_UNSIGNED_INT,0);
}

void ChunkManager::renderChunks(){
    for(auto it = m_visibleChunks.begin();it != m_visibleChunks.end();it++){
        Chunk* chunk = it->second;
        renderChunk(chunk);
    }
}

