#include "spells.h"

Particle::Particle(glm::vec3 worldPos, glm::vec3 dir, float pSize, std::vector<glm::vec3> mesh,glm::mat4 viewMatrix){
    size = pSize;
    aim = dir;
    position = worldPos;
    for(int i=0;i<mesh.size();i++){
        glm::vec3 vertex = glm::vec3(glm::vec4(mesh[i],1.0f)); // * viewMatrix
        create(vertex,dir);
    }

}

void Particle::shift(float deltaTime, float velocity){
    //move particle forward
    glm::vec3 forward = (aim * deltaTime) * velocity;
    position += forward;
    off += forward;
}

void Particle::create(glm::vec3 modelPos, glm::vec3 dir){
    glm::vec3 offset = modelPos;
    
    glm::vec3 p0 = glm::vec3(offset.x-0.5f,offset.y-0.5f,offset.z-0.5f); //front-bottom-left
    glm::vec3 p1 = glm::vec3(offset.x-0.5f,offset.y+0.5f,offset.z-0.5f); //front-top-left
    glm::vec3 p2 = glm::vec3(offset.x+0.5f,offset.y+0.5f,offset.z-0.5f); //front-top-right
    glm::vec3 p3 = glm::vec3(offset.x+0.5f,offset.y-0.5f,offset.z-0.5f); //front-bottom-right
    glm::vec3 p4 = glm::vec3(offset.x-0.5f,offset.y-0.5f,offset.z+0.5f); //back-bottom-left
    glm::vec3 p5 = glm::vec3(offset.x-0.5f,offset.y+0.5f,offset.z+0.5f); //back-top-left
    glm::vec3 p6 = glm::vec3(offset.x+0.5f,offset.y+0.5f,offset.z+0.5f); //back-top-right
    glm::vec3 p7 = glm::vec3(offset.x+0.5f,offset.y-0.5f,offset.z+0.5f);

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


void Spell::tick(float deltaTime, glm::vec3 worldPos, glm::vec3 right, glm::vec3 pos){
    std::cout<<"spell tick";
}

std::vector<Particle> Spell::getParticles(){
    return m_particles;
}

void Spell::summon(glm::vec3 origin, glm::vec3 dir, glm::vec3 right,glm::mat4 viewMatrix){
    int random = -spellRadius + (std::rand() % (spellRadius * 2 + 1));
    for(int i=0;i<spellDensity;i++){
        float randomX = (-spellRadius + (std::rand() % (spellRadius * 2 + 1)))*0.02;
        float randomY = (-spellRadius + (std::rand() % (spellRadius * 2 + 1)))*0.02;
        glm::vec3 offsetOrigin = origin + (right*randomX);
        offsetOrigin += glm::vec3(0,randomY,0);
        Particle p = Particle(offsetOrigin,dir,particleSize,m_mesh,viewMatrix);
        m_particles.push_back(p);
    }
}

void Spell::createSpellMesh(){
    std::vector<glm::vec3> mesh;
    mesh.push_back(glm::vec3(0,0,0));
    m_mesh = mesh;
}

Lightning::Lightning(){
    spellVelocity = 5.0f;
    spellRange = 10.0f;
    spellDensity = 10;
    spellRadius = 10;
    particleSize = 0.025f;
    numParticles = 7;
    id = LIGHTNING;

    createSpellMesh();
}


void Lightning::jolt(float deltaTime, glm::vec3 right){
    const int delay = 120;
    if(m_particles.size() == 0){
        return;
    }

    for(int i=0;i<m_particles.size();i++){
        const int verticesPerCube = m_particles[i].vertices.size() / numParticles;
    
        if(m_particles[i].moveIndex == 0){
            float randX = -0.5f + static_cast<float>(rand()) / RAND_MAX * 1.0f;
            float randY = -0.5f + static_cast<float>(rand()) / RAND_MAX * 1.0f;
        
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

void Lightning::tick(float deltaTime,glm::vec3 dir, glm::vec3 right,glm::vec3 pos){
    jolt(deltaTime,right);
    for(auto it = m_particles.begin();it != m_particles.end();){
        Particle& p = *it;
        float magnitude = std::abs(glm::length(p.off));

        if(magnitude <= spellRange){
            p.shift(deltaTime,spellVelocity);
            ++it;
        }
        else{
            it = m_particles.erase(it);
        }
    }
}

void Lightning::createSpellMesh(){
    std::vector<glm::vec3> mesh;
    for(int i=0;i<numParticles;i++){
        glm::vec3 vertex = glm::vec3(0,0,i);
        mesh.push_back(vertex);
    }

    m_mesh = mesh;
}

WaterBall::WaterBall(){
    spellVelocity = 5.0f;
    spellRange = 20.0f;
    spellDensity = 1;
    spellRadius = 10;
    particleSize = 0.025f;
    numParticles = 1;
    id = WATERBALL;

    createSpellMesh();
}

void WaterBall::tick(float deltaTime, glm::vec3 dir, glm::vec3 right, glm::vec3 pos){
    for(auto it = m_particles.begin();it != m_particles.end();){
        Particle& p = *it;
        float magnitude = std::abs(glm::length(p.off));
        if(!release){
            if(magnitude <= spellRange){
                p.shift(deltaTime,spellVelocity);
                ++it;
            }
            else{
                it = m_particles.erase(it);
                release = !release;
            }
        }
        else{
            grow(deltaTime);
            it->position = pos;
            it->aim = dir;
            ++it;
        }
    }
}

void WaterBall::grow(float deltaTime){
    for(int i=0;i<m_particles.size();i++){
        if(m_particles[i].size < maxSize){
            m_particles[i].size += growFactor * deltaTime;
        }
    }

}

void WaterBall::createSpellMesh(){
    std::vector<glm::vec3> mesh;
    int xRange = 3;
    int yRange = 3;
    int zRange = 3;
    int cornerNum = xRange / 2;
    int cornerOff = 0;
    
    for(int y=1;y<=yRange;y++){
        //corners
        for(int c=0;c<cornerNum;c++){
            for(int d=0;d<cornerNum;d++){
                int tempc = xRange - (c + y + cornerOff);
                int tempd = xRange - (d + y + cornerOff);
                if(cornerNum > 1 && d == c){
                    continue;
                }
                mesh.push_back(glm::vec3(tempc,y,tempd));
                mesh.push_back(glm::vec3(-tempc,y,tempd));
                mesh.push_back(glm::vec3(tempc,y,-tempd));
                mesh.push_back(glm::vec3(-tempc,y,-tempd));
                //std::cout<<"x: " << tempc << "z: " << tempd << std::endl;
                //std::cout<<"x: " << -tempc << "z: " << tempd << std::endl;
                //std::cout<<"x: " << tempc << "z: " << -tempd << std::endl;
                //std::cout<<"x: " << -tempc << "z: " << -tempd << std::endl;
            }
        }
        cornerNum -= 1;
        cornerOff += 1;
        for(int i=-xRange/2;i<=xRange/2;i++){
            for(int j=-zRange;j<=zRange;j+=zRange*2){
                mesh.push_back(glm::vec3(j,y,i));
                mesh.push_back(glm::vec3(i,y,j));
                //std::cout<<"x: " << j << "y: " << y << "z: " << i << std::endl; 
                //std::cout<<"x: " << i << "y: " << y << "z: " << j << std::endl; 
            }
        }
        zRange -= 1;
    }

    zRange = 3;
    yRange = -3;
    cornerNum = xRange / 2;
    cornerOff = 0;
    for(int y=-1;y>=yRange;y--){
        //corners
        for(int c=0;c<cornerNum;c++){
            for(int d=0;d<cornerNum;d++){
                int tempc = xRange - (c - y + cornerOff);
                int tempd = xRange - (d - y + cornerOff);
                if(cornerNum > 1 && d == c){
                    continue;
                }
                mesh.push_back(glm::vec3(tempc,y,tempd));
                mesh.push_back(glm::vec3(-tempc,y,tempd));
                mesh.push_back(glm::vec3(tempc,y,-tempd));
                mesh.push_back(glm::vec3(-tempc,y,-tempd));
                //std::cout<<"x: " << tempc << "z: " << tempd << std::endl;
                //std::cout<<"x: " << -tempc << "z: " << tempd << std::endl;
                //std::cout<<"x: " << tempc << "z: " << -tempd << std::endl;
                //std::cout<<"x: " << -tempc << "z: " << -tempd << std::endl;
            }
        }
        cornerNum -= 1;
        cornerOff += 1;
        for(int i=-xRange/2;i<=xRange/2;i++){
            for(int j=-zRange;j<=zRange;j+=zRange*2){
                mesh.push_back(glm::vec3(j,y,i));
                mesh.push_back(glm::vec3(i,y,j));
                //std::cout<<"x: " << j << "y: " << y << "z: " << i << std::endl; 
                //std::cout<<"x: " << i << "y: " << y << "z: " << j << std::endl; 
            }
        }
        zRange -= 1;
    }

    m_mesh = mesh;
}

void WaterBall::summon(glm::vec3 origin, glm::vec3 dir, glm::vec3 right,glm::mat4 viewMatrix){
    
    if(release && m_particles.size() == 0){
        for(int i=0;i<spellDensity;i++){
            Particle p = Particle(origin,dir,particleSize,m_mesh,viewMatrix);
            m_particles.push_back(p);
        }
    }
    else{
        release = false;
    }
}