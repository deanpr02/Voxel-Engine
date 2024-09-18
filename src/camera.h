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
    qtn::Quaternion _direction;
    qtn::Quaternion _forward;
    glm::vec3 _globalUp;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _pos;
    float _horizontal;
    float _vertical;
    float _tilt;
    float _movementSpeed;
    float _mouseSensitivity;
    glm::mat4 _projMatrix;
    glm::mat4 _viewMatrix;
    Camera();
    Camera(float, float, float);
    Camera(float, float, float, float, float, float);
    void init();
    void moveCamera(CameraMovement, float);
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