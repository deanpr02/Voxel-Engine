#include "player.h"


Player::Player(){
    m_inputMap = {
        {GLFW_KEY_W, [this]() {moveBodyForward(m_deltaTime);}},
        {GLFW_KEY_S, [this]() {moveBodyBack(m_deltaTime);}},
        {GLFW_KEY_A, [this]() {moveBodyLeft(m_deltaTime);}},
        {GLFW_KEY_D, [this]() {moveBodyRight(m_deltaTime);}},
        {GLFW_KEY_SPACE, [this]() {jump(m_deltaTime);}}
    };

    m_camera = new Camera();
    m_body = new PhysicsObject(&m_camera->m_pos);
    m_weapons = new WeaponSystem(m_camera);
}

void Player::update(float deltaTime,std::unordered_map<glm::vec3,Chunk*,Vec3Hash,Vec3Equal> chunks){
    m_deltaTime = deltaTime;
    glm::vec3 camDirection = glm::vec3(m_camera->m_direction.i,m_camera->m_direction.j,m_camera->m_direction.k);
    glm::vec3 forwardVec = glm::vec3(m_camera->m_forward.i,m_camera->m_forward.j,m_camera->m_forward.k);
    glm::mat4 view = glm::lookAt(m_camera->m_pos,m_camera->m_pos+camDirection,m_camera->m_up);
    m_camera->m_viewMatrix = view;

    m_currentChunks = chunks;
    m_body->applyGravity(m_currentChunks,deltaTime);

    //need to optimize where this is only called when a spell is equipped
    m_weapons->m_currentSpell->tick(deltaTime,camDirection,m_camera->m_right,m_camera->m_pos);
}

void Player::processMovement(int key){
    if(m_inputMap.find(key) != m_inputMap.end()){
        m_inputMap[key]();
    }
}

void Player::processLookAround(float xoffset, float yoffset){
    m_camera->processMouseMovement(xoffset,yoffset,true);
}

void Player::setMovementSpeed(float speed){
    m_camera->m_movementSpeed = speed;
}

void Player::moveBodyForward(float deltaTime){
    float velocity = m_camera->m_movementSpeed * deltaTime; 
    glm::vec3 forwardVec = glm::vec3(velocity*m_camera->m_direction.i,0,velocity*m_camera->m_direction.k);
    bool isColliding = m_body->checkIfColliding(m_currentChunks,*m_body->m_position,forwardVec);
    if(!isColliding){
        m_camera->moveCameraForward(deltaTime);
    }
}

void Player::moveBodyBack(float deltaTime){
    float velocity = m_camera->m_movementSpeed * deltaTime;
    glm::vec3 backwardsVec = glm::vec3(-velocity*m_camera->m_direction.i,0,-velocity*m_camera->m_direction.k);
    bool isColliding = m_body->checkIfColliding(m_currentChunks,*m_body->m_position,backwardsVec);
    if(!isColliding){
        m_camera->moveCameraBackward(deltaTime);
    }
}

void Player::moveBodyLeft(float deltaTime){
    float velocity = m_camera->m_movementSpeed * deltaTime;
    glm::vec3 leftVec = -velocity*m_camera->m_right;
    bool isColliding = m_body->checkIfColliding(m_currentChunks,*m_body->m_position,leftVec);
    if(!isColliding){
        m_camera->moveCameraLeft(deltaTime);
    }
}

void Player::moveBodyRight(float deltaTime){
    float velocity = m_camera->m_movementSpeed * deltaTime;
    glm::vec3 rightVec = velocity*m_camera->m_right;
    bool isColliding = m_body->checkIfColliding(m_currentChunks,*m_body->m_position,rightVec);
    if(!isColliding){
        m_camera->moveCameraRight(deltaTime);
    }
}

void Player::jump(float deltaTime){
    m_camera->moveCameraUp(m_jumpHeight,deltaTime);
}

void Player::cast(){
    glm::vec3 dir = glm::vec3(m_camera->m_direction.i,m_camera->m_direction.j,m_camera->m_direction.k);
    //glm::vec3 origin = m_camera->m_pos + (m_camera->m_right * 1.0f);
    glm::vec3 origin = m_camera->m_pos;
    m_weapons->spawn(origin,dir,m_camera->m_right,m_camera->getViewMatrix());
}