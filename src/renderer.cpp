#include "renderer.h"

struct Shaders _shaders;

void Renderer::loadShaders(){
    _shaders.s_cube.Load("../res/shader/cube.vert","../res/shader/cube.frag");
}

/*void Renderer::initializeBuffer(Chunk chunk){
    glGenVertexArrays(1,&chunk.m_vao);
    glGenBuffers(1,&chunk.m_vbo);
    glGenBuffers(1,&chunk.m_ebo);

    glBindVertexArray(chunk.m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.m_vbo);
    glBufferData(GL_ARRAY_BUFFER, chunk.m_vertices.size() * sizeof(chunk.m_vertices[0]), chunk.m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,chunk.m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}*/

/*void Renderer::drawCube(float x, float y, float z){
    _shaders.s_cube.use();
    //_shaders.s_cube.setMat4("perspective",camera._projMatrix);
    //_shaders.s_cube.setMat4("view",camera.getViewMatrix());

    glm::mat4 blockSize = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    glm::mat4 world = glm::translate(blockSize,glm::vec3(x,y,z));

    _shaders.s_cube.setMat4("model",world);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, sizeof(_indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}*/

void Renderer::updateChunks(Camera* camera){
    m_chunkManager->checkBoundary(camera->m_pos);
}

void Renderer::drawWorld(Camera* camera){
    _shaders.s_cube.use();
    _shaders.s_cube.setMat4("perspective",camera->m_projMatrix);
    _shaders.s_cube.setMat4("view",camera->getViewMatrix());
    
    glm::mat4 blockSize = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    _shaders.s_cube.setMat4("model",blockSize);

    m_chunkManager->renderChunks();
}

Renderer::Renderer(){
    this->loadShaders();
    loadTextures();
    m_chunkManager = new ChunkManager();
    m_chunkManager->setTextureMap(m_textureMap);
}

void Renderer::loadTextures(){
    glGenTextures(1,&m_textureMap);
    glBindTexture(GL_TEXTURE_2D,m_textureMap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width,height,nrChannels;
    unsigned char* data = stbi_load("../res/assets/pixelmap.png",&width,&height,&nrChannels,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout<<"failed to load texture"<<std::endl;
    }
    stbi_image_free(data);
}  

