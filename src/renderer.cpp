#include "renderer.h"

float _vertices[] = {
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f
};

unsigned int _indices[] = {
    //front
    0, 1, 3,
    1, 2, 3,
    //right
    0, 1, 4,
    0, 5, 4,
    //left
    2, 3, 6,
    6, 3, 7,
    //top
    3, 7, 0,
    0, 7, 5,
    //bottom
    1, 2, 6,
    4, 6, 1,
    //back
    5, 4, 7,
    4, 7, 6
};

struct Shaders _shaders;

void Renderer::loadShaders(){
    _shaders.s_cube.Load("../res/shader/cube.vert","../res/shader/cube.frag");
}

void Renderer::initializeBuffer(){
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(_vertices),_vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::drawCube(float x, float y, float z){
    //_shaders.s_cube.use();
    //_shaders.s_cube.setMat4("perspective",camera._projMatrix);
    //_shaders.s_cube.setMat4("view",camera.getViewMatrix());

    glm::mat4 blockSize = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    glm::mat4 world = glm::translate(blockSize,glm::vec3(x,y,z));

    _shaders.s_cube.setMat4("model",world);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, sizeof(_indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

void Renderer::drawWorld(Camera camera){
    _shaders.s_cube.use();
    _shaders.s_cube.setMat4("perspective",camera._projMatrix);
    _shaders.s_cube.setMat4("view",camera.getViewMatrix());
    for(int z=0;z<32;z++){
        for(int y=0;y<32;y++){
            for(int x=0;x<32;x++){
                drawCube(x,y,z);
            }
        }
    }
}

void Renderer::init(){
    this->loadShaders();
    this->initializeBuffer();
}