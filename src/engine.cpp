#include "engine.h"

void Engine::processInput(GLFWwindow* window){
    for(int key: _pressedKeys){
        if(key == GLFW_KEY_ESCAPE){
            _gameState = false;
            return;
        }
        if(_inputMap.find(key) != _inputMap.end()){
            _inputMap[key]();
        }
        _vRenderer->updateChunks(_camera);
    }
}

void Engine::init(){
    //change this
    _camera._projMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    _inputMap = {
        {GLFW_KEY_W, [this]() {_camera.moveCameraForward(_deltaTime);}},
        {GLFW_KEY_S, [this]() {_camera.moveCameraBackward(_deltaTime);}},
        {GLFW_KEY_A, [this]() {_camera.moveCameraLeft(_deltaTime);}},
        {GLFW_KEY_D, [this]() {_camera.moveCameraRight(_deltaTime);}}
    };
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Dat Engine",NULL,NULL);
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window,frameBufferCallback);
    glfwSetCursorPosCallback(_window,mouseCallback);
    glfwSetKeyCallback(_window, keyCallback);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(_window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
}

void Engine::frameBufferCallback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void Engine::mouseCallback(GLFWwindow* window, double xposIn, double yposIn){
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if(engine->_firstMouse){
        engine->_lastX = xpos;
        engine->_lastY = ypos;
        engine->_firstMouse = false;
    }
    float xoffset = engine->_lastX - xpos;
    //this was flipped from engine->lastY to ypos
    float yoffset = ypos - engine->_lastY;
    engine->_lastX = xpos;
    engine->_lastY = ypos;
    
    engine->_camera.processMouseMovement(xoffset,yoffset,true);
}

void Engine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        if(key == GLFW_KEY_LEFT_SHIFT){
            engine->_camera._movementSpeed = 2.0f;
        }
        engine->_pressedKeys.insert(key);
    }
    else if(action == GLFW_RELEASE){
        if(key == GLFW_KEY_LEFT_SHIFT){
            engine->_camera._movementSpeed = 1.0f;
        }
        engine->_pressedKeys.erase(key);
    }
}

int Engine::checkInit(){
    if(_window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //glfwMakeContextCurrent(_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //glEnable(GL_DEPTH_TEST);
    return 1;

}


void Engine::updateCamera(){
    //Since our direction is calculated as a quaternion we need to extract ijk components to make a vec3.
    //Our we generate our view matrix using the camera's position, direction from current position, and camera up vec
    glm::vec3 camDirection = glm::vec3(_camera._direction.i,_camera._direction.j,_camera._direction.k);
    glm::mat4 view = glm::lookAt(_camera._pos,_camera._pos+camDirection,_camera._up);
    _camera._viewMatrix = view;
}

void Engine::draw(){
    _vRenderer->drawWorld(_camera);
}

void Engine::render(){
    if(!checkInit()){
        return;
    }
    //_vRenderer->init();

    while(!glfwWindowShouldClose(_window)){
        if(!_gameState){
            break;
        }
        float currentFrame = static_cast<float>(glfwGetTime());
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //processInput(_window,_gameState);
        processInput(_window);
        updateCamera();

        draw();
        //_vRenderer.drawCube(_camera);
        //drawObjects();
        
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    glfwTerminate();
}