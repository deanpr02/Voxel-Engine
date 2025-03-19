#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "q_math.cpp"

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    public:
    //camera variables
    qtn::Quaternion m_direction;
    qtn::Quaternion m_forward;
    glm::vec3 m_globalUp;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_pos;
    float m_horizontal;
    float m_vertical;
    float m_tilt;
    float m_movementSpeed;
    float m_mouseSensitivity;
    glm::mat4 m_projMatrix;
    glm::mat4 m_viewMatrix;
    Camera();
    Camera(float, float, float);
    Camera(float, float, float, float, float, float);
    void init();
    void moveCamera(CameraMovement, float);
    void moveCameraUp(float,float);
    void moveCameraForward(float);
    void moveCameraBackward(float);
    void moveCameraLeft(float);
    void moveCameraRight(float);
    void processMouseMovement(float,float,bool);
    void rotateCamera();
    void checkWinBoundaries();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix();
    void setPlayerSpawn(float,float);
};

#endif