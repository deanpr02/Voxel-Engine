#include "physics.h"

PhysicsObject::PhysicsObject(glm::vec3* position){
    m_position = position;
}

void PhysicsObject::applyGravity(){
    glm::vec3 grav = glm::vec3(0,GRAVITY,0);
    *m_position += grav; 
}