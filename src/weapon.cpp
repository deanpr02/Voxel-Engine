#include "weapon.h"


const glm::vec3 handPos = glm::vec3(-2.0f,0.5f,-2.0f);

void Spell::tick(float deltaTime,glm::vec3 dir){
    for(auto it = m_particles.begin();it != m_particles.end();){
        Particle& p = *it;
        float magnitude = std::abs(glm::length(p.offset));

        if(magnitude <= spellRange){
            p.shift(deltaTime,spellVelocity);
            ++it;
        }
        else{
            it = m_particles.erase(it);
        }
    }
}

std::vector<Particle> Spell::getParticles(){
    return m_particles;
}

Particle::Particle(glm::vec3 worldPos, glm::vec3 dir){
    aim = dir;
    create(worldPos,dir);
}

void Particle::shift(float deltaTime, float velocity){
    glm::vec3 forward = (aim * deltaTime) * velocity;
    float magnitude = std::abs(glm::length(offset));
    if(magnitude <= 10.0f){
        offset += forward;
    }
    else{

    }
}

void Particle::create(glm::vec3 worldPos, glm::vec3 dir){
    glm::vec3 offset = dir;
    glm::vec3 p0 = glm::vec3(worldPos.x+offset.x-0.1,worldPos.y+offset.y-0.1,worldPos.z+offset.z-0.1); //front-bottom-left
    glm::vec3 p1 = glm::vec3(worldPos.x+offset.x-0.1,worldPos.y+offset.y+0.1,worldPos.z+offset.z-0.1); //front-top-left
    glm::vec3 p2 = glm::vec3(worldPos.x+offset.x+0.1,worldPos.y+offset.y+0.1,worldPos.z+offset.z-0.1); //front-top-right
    glm::vec3 p3 = glm::vec3(worldPos.x+offset.x+0.1,worldPos.y+offset.y-0.1,worldPos.z+offset.z-0.1); //front-bottom-right
    glm::vec3 p4 = glm::vec3(worldPos.x+offset.x-0.1,worldPos.y+offset.y-0.1,worldPos.z+offset.z+0.1); //back-bottom-left
    glm::vec3 p5 = glm::vec3(worldPos.x+offset.x-0.1,worldPos.y+offset.y+0.1,worldPos.z+offset.z+0.1); //back-top-left
    glm::vec3 p6 = glm::vec3(worldPos.x+offset.x+0.1,worldPos.y+offset.y+0.1,worldPos.z+offset.z+0.1); //back-top-right
    glm::vec3 p7 = glm::vec3(worldPos.x+offset.x+0.1,worldPos.y+offset.y-0.1,worldPos.z+offset.z+0.1);

    addVertex(p0);
    addVertex(p1);
    addVertex(p2);
    addVertex(p3);
    addVertex(p4);
    addVertex(p5);
    addVertex(p6);
    addVertex(p7);

    int indexOffset = vertices.size() / 3 - 8;
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

    initialize();
}

void Particle::initialize(){
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

void Particle::addVertex(glm::vec3 point){
    vertices.push_back(point.x);
    vertices.push_back(point.y);
    vertices.push_back(point.z);
}

void Particle::addTriangle(int i1, int i2, int i3){
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

void Particle::draw(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
}


//void WeaponSystem::render(){
//    //for(int i=0;i<m_particles.size();i++){
//    //    m_particles[i].draw();
//    //}
//}

