#include "camera.h"

const float MOVEMENT_SPEED = 0.5f;
const float MOUSE_SENSITIVITY = 0.1f;
const float EDGE_STEP = 0.1f;

Camera::Camera()
{
    //camera attributes
    _pos = glm::vec3(0.0f,0.0f,0.0f);
    _direction = qtn::Quaternion(0,0,0,1.0f);
    _up = glm::vec3(0,1.0f,0);
    _right = glm::vec3(1.0f,0.0f,0.0f);
    //globals
    _forward = qtn::Quaternion(0,0,0,1.0f);
    _globalUp = glm::vec3(0,1.0f,0);
    //measures of rotations
    _horizontal = 0;
    _vertical = 0;
    //customs
    _movementSpeed = MOVEMENT_SPEED;
    _mouseSensitivity = MOUSE_SENSITIVITY;
}


//This camera takes the current direction vector and multiplies by a certain velocity and then adds it to
//the cameras current position so it moves in an accurate direction
void Camera::moveCamera(CameraMovement direction, float delta_time)
{
    float velocity = _movementSpeed * delta_time;
    glm::vec3 directionVector = glm::vec3(_direction.i,0,_direction.k);
    if(direction == FORWARD)
    {
        _pos += directionVector * velocity;
    }
    if(direction == BACKWARD)
    {
        _pos -= directionVector * velocity;
    }
    if(direction == LEFT)
    {
        _pos -= _right * velocity;
    }
    if(direction == RIGHT)
    {
        _pos += _right * velocity;
    }

}

void Camera::moveCameraForward(float deltaTime){
    float velocity = _movementSpeed * deltaTime;
    glm::vec3 directionVector = glm::vec3(_direction.i,0,_direction.k);
    _pos += directionVector * velocity;
}

void Camera::moveCameraBackward(float deltaTime){
    float velocity = _movementSpeed * deltaTime;
    glm::vec3 directionVector = glm::vec3(_direction.i,0,_direction.k);
    _pos -= directionVector * velocity;
}

void Camera::moveCameraLeft(float deltaTime){
    float velocity = _movementSpeed * deltaTime;
    _pos -= _right * velocity;
}

void Camera::moveCameraRight(float deltaTime){
    float velocity = _movementSpeed * deltaTime;
    _pos += _right * velocity;
}

//Adds our offsets to our cameras total horizontal/vertical movement
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch=true){
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;
    _horizontal += xoffset;
    _vertical += yoffset;
    
    if(constrainPitch){
        if(_vertical > 89.0f){
            _vertical = 89.0f;
        }
        else if(_vertical < -89.0f){
            _vertical = -89.0f;
        }
    }
    
    
    rotateCamera();


}

//Uses quaternion multiplication to generate the horizontal and vertical rotations of the camera
void Camera::rotateCamera(){
    checkWinBoundaries();
    //convert our angles into radians. Note: we need to use half the angle because we are using quaternions
    float horiAngle = glm::radians(_horizontal)/2.0f;
    float vertAngle = glm::radians(_vertical)/2.0f;
    
    qtn::Quaternion hRotation = qtn::Quaternion(cos(horiAngle),0,sin(horiAngle),0);
    qtn::Quaternion vRotation = qtn::Quaternion(cos(vertAngle),sin(vertAngle),0,0);

    //combination of horizontal and vertical rotation quaternions
    qtn::Quaternion camRotation = (hRotation*vRotation).normalize();
    _direction = camRotation*_forward*camRotation.conjugate();
    _direction = _direction.normalize();
    
    //update our orientation vectors
    _right = glm::normalize(glm::cross(glm::vec3(_direction.i,_direction.j,_direction.k),_globalUp));
    _up = glm::normalize(glm::cross(_right,glm::vec3(_direction.i,_direction.j,_direction.k)));
    
}

void Camera::checkWinBoundaries(){
    bool onEdge = false;
}

glm::mat4 Camera::getProjMatrix(){
    return _projMatrix;
}

glm::mat4 Camera::getViewMatrix(){
    return _viewMatrix;
}

void Camera::setPlayerSpawn(float spawnX, float spawnZ){
    _pos.x = spawnX;
    _pos.z = spawnZ;
}