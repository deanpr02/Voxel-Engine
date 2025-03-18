#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

const float GRAVITY = -0.01f;

class PhysicsObject{
    public:
    glm::vec3* m_position;

    PhysicsObject(glm::vec3*);
    void applyGravity();
};

#endif