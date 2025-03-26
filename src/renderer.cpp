#include "renderer.h"

Renderer::Renderer(WeaponSystem* weapons){
    m_chunkManager = new ChunkManager();
    m_weapons = weapons;

    this->loadShaders();
    loadTextures();

    m_spellShaders = {{LIGHTNING,m_shaders.s_lightning}};

    m_chunkManager->setTextureMap(m_textureMap);
}

void Renderer::loadShaders(){
    m_shaders.s_cube->Load("../res/shader/cube.vert","../res/shader/cube.frag");
    m_shaders.s_lightning->Load("../res/shader/lightning.vert","../res/shader/lightning.frag");
}

void Renderer::updateChunks(Camera* camera){
    m_chunkManager->checkBoundary(camera->m_pos);
}

void Renderer::drawWorld(Camera* camera){
    m_shaders.s_cube->use();
    m_shaders.s_cube->setMat4("perspective",camera->m_projMatrix);
    m_shaders.s_cube->setMat4("view",camera->getViewMatrix());
    
    glm::mat4 blockSize = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    m_shaders.s_cube->setMat4("model",blockSize);

    m_chunkManager->renderChunks();
}

void Renderer::drawWeapons(Camera* camera){
    Shader* currentShader = m_spellShaders[m_weapons->m_currentSpell->id];
    currentShader->use();
    currentShader->setMat4("perspective",camera->m_projMatrix);
    currentShader->setMat4("view",camera->getViewMatrix());
    
    glm::mat4 blockSize = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    
    std::vector<Particle> particles = m_weapons->m_currentSpell->m_particles;
    for(int i=0;i<particles.size();i++){
        Particle currParticle = particles[i];
        glm::mat4 translatedBlock = glm::translate(blockSize,currParticle.offset);
        currentShader->setMat4("model",translatedBlock);
        currParticle.draw();
    }
}

void Renderer::render(Camera* camera){
    drawWorld(camera);
    drawWeapons(camera);
}

void Renderer::loadTextures(){
    glGenTextures(1,&m_textureMap);
    glBindTexture(GL_TEXTURE_2D,m_textureMap);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width,height,nrChannels;
    unsigned char* data = stbi_load("../res/assets/testmap.png",&width,&height,&nrChannels,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
        m_chunkManager->m_texWidth = width;
    }
    else{
        std::cout<<"failed to load texture"<<std::endl;
    }
    stbi_image_free(data);
}  

