#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "chunk_manager.h"

const float GRAVITY = 0.02f;
//const float GRAVITY = -9.8f;
const float TERMINAL_VELOCITY = 98.0f;

class PhysicsObject{
    public:
    glm::vec3* m_position;
    float m_fallSpeed = 0.0f;

    PhysicsObject(glm::vec3*);
    void applyGravity(std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal>,float);
    glm::vec3 getChunkPosition(glm::vec3);
    bool checkIfColliding(std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal>,glm::vec3,glm::vec3);
};

#endif