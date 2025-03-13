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

void Renderer::drawWorld(Camera camera){
    _shaders.s_cube.use();
    _shaders.s_cube.setMat4("perspective",camera._projMatrix);
    _shaders.s_cube.setMat4("view",camera.getViewMatrix());
    
    glm::mat4 blockSize = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    _shaders.s_cube.setMat4("model",blockSize);

    glBindVertexArray(_chunk->m_vao);
    glDrawElements(GL_TRIANGLES,_chunk->m_indices.size(),GL_UNSIGNED_INT,0);
}

void Renderer::init(){
    this->loadShaders();
    _chunk->createMesh();
}