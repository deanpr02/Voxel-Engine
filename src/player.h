#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include "physics.h"
#include "chunk_manager.h"
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef std::function<void()> FuncType;

class Player{
    public:
    Camera* m_camera;
    PhysicsObject* m_body; 
    std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> m_currentChunks;
    std::unordered_map<int,FuncType> m_inputMap;
    float m_deltaTime = 0.0f;

    Player();
    void moveBodyLeft(float);
    void moveBodyRight(float);
    void moveBodyForward(float);
    void moveBodyBack(float);
    void setMovementSpeed(float);
    void processMovement(int);
    void processLookAround(float,float);
    std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> getCurrentChunks();
    void update(float,std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal>);
    void init();

};


#endif