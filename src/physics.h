#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "chunk_manager.h"

const float GRAVITY = -0.01f;

class PhysicsObject{
    public:
    glm::vec3* m_position;

    PhysicsObject(glm::vec3*);
    void applyGravity(std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal>);
    glm::vec3 getChunkPosition(glm::vec3);
    bool checkIfColliding(std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal>,glm::vec3,glm::vec3);
};

#endif