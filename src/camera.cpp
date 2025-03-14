#include "camera.h"

const float MOVEMENT_SPEED = 0.5f;
const float MOUSE_SENSITIVITY = 0.1f;
const float EDGE_STEP = 0.1f;

Camera::Camera()
{
    //camera attributes
    m_pos = glm::vec3(0.0f,0.0f,0.0f);
    m_direction = qtn::Quaternion(0,0,0,1.0f);
    m_up = glm::vec3(0,1.0f,0);
    m_right = glm::vec3(1.0f,0.0f,0.0f);
    //globals
    m_forward = qtn::Quaternion(0,0,0,1.0f);
    m_globalUp = glm::vec3(0,1.0f,0);
    //measures of rotations
    m_horizontal = 0;
    m_vertical = 0;
    //customs
    m_movementSpeed = MOVEMENT_SPEED;
    m_mouseSensitivity = MOUSE_SENSITIVITY;
}


//This camera takes the current direction vector and multiplies by a certain velocity and then adds it to
//the cameras current position so it moves in an accurate direction
void Camera::moveCamera(CameraMovement direction, float delta_time)
{
    float velocity = m_movementSpeed * delta_time;
    glm::vec3 directionVector = glm::vec3(m_direction.i,0,m_direction.k);
    if(direction == FORWARD)
    {
        m_pos += directionVector * velocity;
    }
    if(direction == BACKWARD)
    {
        m_pos -= directionVector * velocity;
    }
    if(direction == LEFT)
    {
        m_pos -= m_right * velocity;
    }
    if(direction == RIGHT)
    {
        m_pos += m_right * velocity;
    }

}

void Camera::moveCameraForward(float deltaTime){
    float velocity = m_movementSpeed * deltaTime;
    glm::vec3 directionVector = glm::vec3(m_direction.i,0,m_direction.k);
    m_pos += directionVector * velocity;
}

void Camera::moveCameraBackward(float deltaTime){
    float velocity = m_movementSpeed * deltaTime;
    glm::vec3 directionVector = glm::vec3(m_direction.i,0,m_direction.k);
    m_pos -= directionVector * velocity;
}

void Camera::moveCameraLeft(float deltaTime){
    float velocity = m_movementSpeed * deltaTime;
    m_pos -= m_right * velocity;
}

void Camera::moveCameraRight(float deltaTime){
    float velocity = m_movementSpeed * deltaTime;
    m_pos += m_right * velocity;
}

//Adds our offsets to our cameras total horizontal/vertical movement
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch=true){
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;
    m_horizontal += xoffset;
    m_vertical += yoffset;
    
    if(constrainPitch){
        if(m_vertical > 89.0f){
            m_vertical = 89.0f;
        }
        else if(m_vertical < -89.0f){
            m_vertical = -89.0f;
        }
    }
    
    
    rotateCamera();


}

//Uses quaternion multiplication to generate the horizontal and vertical rotations of the camera
void Camera::rotateCamera(){
    checkWinBoundaries();
    //convert our angles into radians. Note: we need to use half the angle because we are using quaternions
    float horiAngle = glm::radians(m_horizontal)/2.0f;
    float vertAngle = glm::radians(m_vertical)/2.0f;
    
    qtn::Quaternion hRotation = qtn::Quaternion(cos(horiAngle),0,sin(horiAngle),0);
    qtn::Quaternion vRotation = qtn::Quaternion(cos(vertAngle),sin(vertAngle),0,0);

    //combination of horizontal and vertical rotation quaternions
    qtn::Quaternion camRotation = (hRotation*vRotation).normalize();
    m_direction = camRotation*m_forward*camRotation.conjugate();
    m_direction = m_direction.normalize();
    
    //update our orientation vectors
    m_right = glm::normalize(glm::cross(glm::vec3(m_direction.i,m_direction.j,m_direction.k),m_globalUp));
    m_up = glm::normalize(glm::cross(m_right,glm::vec3(m_direction.i,m_direction.j,m_direction.k)));
    
}

void Camera::checkWinBoundaries(){
    bool onEdge = false;
}

glm::mat4 Camera::getProjMatrix(){
    return m_projMatrix;
}

glm::mat4 Camera::getViewMatrix(){
    return m_viewMatrix;
}

void Camera::setPlayerSpawn(float spawnX, float spawnZ){
    m_pos.x = spawnX;
    m_pos.z = spawnZ;
}