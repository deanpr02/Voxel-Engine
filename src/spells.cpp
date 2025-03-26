#include "spells.h"

Particle::Particle(glm::vec3 worldPos, glm::vec3 dir, float pSize, float pNum){
    size = pSize;
    aim = dir;
    for(int i=-(pNum/2);i<=pNum/2;i++){
        glm::vec3 offsetPos = worldPos + (dir * (size*2*i)); // originally 0.05f*i
        create(offsetPos,dir);
    }
}

void Particle::shift(float deltaTime, float velocity){

    //move particle forward
    glm::vec3 forward = (aim * deltaTime) * velocity;
    offset += forward;
}

void Particle::create(glm::vec3 worldPos, glm::vec3 dir){
    glm::vec3 offset = dir;
    glm::vec3 p0 = glm::vec3(worldPos.x+offset.x-size,worldPos.y+offset.y-size,worldPos.z+offset.z-size); //front-bottom-left
    glm::vec3 p1 = glm::vec3(worldPos.x+offset.x-size,worldPos.y+offset.y+size,worldPos.z+offset.z-size); //front-top-left
    glm::vec3 p2 = glm::vec3(worldPos.x+offset.x+size,worldPos.y+offset.y+size,worldPos.z+offset.z-size); //front-top-right
    glm::vec3 p3 = glm::vec3(worldPos.x+offset.x+size,worldPos.y+offset.y-size,worldPos.z+offset.z-size); //front-bottom-right
    glm::vec3 p4 = glm::vec3(worldPos.x+offset.x-size,worldPos.y+offset.y-size,worldPos.z+offset.z+size); //back-bottom-left
    glm::vec3 p5 = glm::vec3(worldPos.x+offset.x-size,worldPos.y+offset.y+size,worldPos.z+offset.z+size); //back-top-left
    glm::vec3 p6 = glm::vec3(worldPos.x+offset.x+size,worldPos.y+offset.y+size,worldPos.z+offset.z+size); //back-top-right
    glm::vec3 p7 = glm::vec3(worldPos.x+offset.x+size,worldPos.y+offset.y-size,worldPos.z+offset.z+size);

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

void Spell::tick(float deltaTime, glm::vec3 worldPos, glm::vec3 right){
    std::cout<<"spell tick";
}

std::vector<Particle> Spell::getParticles(){
    return m_particles;
}

void Spell::summon(glm::vec3 origin, glm::vec3 dir, glm::vec3 right){
    int random = -spellRadius + (std::rand() % (spellRadius * 2 + 1));
    for(int i=0;i<spellDensity;i++){
        float randomX = (-spellRadius + (std::rand() % (spellRadius * 2 + 1)))*0.02;
        float randomY = (-spellRadius + (std::rand() % (spellRadius * 2 + 1)))*0.02;
        glm::vec3 offsetOrigin = origin + (right*randomX);
        offsetOrigin += glm::vec3(0,randomY,0);
        Particle p = Particle(offsetOrigin,dir,particleSize,numParticles);
        m_particles.push_back(p);
    }
}

Lightning::Lightning(){
    spellVelocity = 5.0f;
    spellRange = 10.0f;
    spellDensity = 10;
    spellRadius = 10;
    particleSize = 0.025f;
    numParticles = 7;
    id = LIGHTNING;
}


void Lightning::jolt(float deltaTime, glm::vec3 right){
    //const int numParticles = 7;
    const int delay = 120;
    if(m_particles.size() == 0){
        return;
    }

    for(int i=0;i<m_particles.size();i++){
        const int verticesPerCube = m_particles[i].vertices.size() / numParticles;
    
        if(m_particles[i].moveIndex == 0){
            float randX = -0.05f + static_cast<float>(rand()) / RAND_MAX * 0.1f;
            float randY = -0.05f + static_cast<float>(rand()) / RAND_MAX * 0.1f;
        
            glm::vec3 shift = (right * randX + glm::vec3(0, 1, 0) * randY);
            m_particles[i].lastMove = shift;
        }

        if(m_particles[i].moveIndex % delay == 0){
            int moveIndex = m_particles[i].moveIndex / delay;
        // Calculate start/end indices for THIS cube's vertices
            int startIdx = moveIndex * verticesPerCube;
            int endIdx = (moveIndex + 1) * verticesPerCube;

            // Apply same shift to all vertices of THIS cube
            glm::vec3 move = m_particles[i].lastMove;
            for (int k = startIdx; k < endIdx; k += 3) {
                m_particles[i].vertices[k]   += move.x;
                m_particles[i].vertices[k+1] += move.y;
                m_particles[i].vertices[k+2] += move.z;
            }
        }
        m_particles[i].moveIndex += 1;
        if(m_particles[i].moveIndex >= 7*delay){
            m_particles[i].moveIndex = 0;
        }

        glBindVertexArray(m_particles[i].vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_particles[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, m_particles[i].vertices.size() * sizeof(m_particles[i].vertices[0]), m_particles[i].vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_particles[i].ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_particles[i].indices.size() * sizeof(m_particles[i].indices[0]), m_particles[i].indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
    }

}


void Lightning::tick(float deltaTime,glm::vec3 dir, glm::vec3 right){
    jolt(deltaTime,right);
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