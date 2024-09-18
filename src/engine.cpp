#include "engine.h"

/*
float _vertices[] = {
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};
*/

float _vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

unsigned int _indices[] = {
    //front
    0, 1, 3,
    1, 2, 3,
    //right
    0, 1, 4,
    0, 5, 4,
    //left
    2, 3, 6,
    6, 3, 7,
    //top
    3, 7, 0,
    0, 7, 5,
    //bottom
    1, 2, 6,
    4, 6, 1,
    //back
    5, 4, 7,
    4, 7, 6
};

struct Shaders _shaders;

//OUTDATED
/*
void Engine::processInput(GLFWwindow* window, bool& exit){
    //Exit key since our mouse is locked/hidden when running
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        exit = false;
        return;
    }
    //Shift key allows for faster movement speed
    _camera._movementSpeed = (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS) ? 2.0f : 1.0f;
    //WASD allows for forward/backward/left/right movement
    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS){
        _camera.moveCamera(FORWARD,_deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
        _camera.moveCamera(BACKWARD,_deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
        _camera.moveCamera(LEFT,_deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
        _camera.moveCamera(RIGHT,_deltaTime);
    }
}
*/

void Engine::processInput(GLFWwindow* window){
    for(int key: _pressedKeys){
        if(key == GLFW_KEY_ESCAPE){
            _gameState = false;
            return;
        }
        if(_inputMap.find(key) != _inputMap.end()){
            _inputMap[key]();
        }
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
    _window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Maze Runner",NULL,NULL);
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window,frameBufferCallback);
    glfwSetCursorPosCallback(_window,mouseCallback);
    glfwSetKeyCallback(_window, keyCallback);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    float yoffset = engine->_lastY - ypos;
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
    glfwMakeContextCurrent(_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    return 1;

}

void Engine::configureBuffers(){
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    //glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(_vertices),_vertices,GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

void Engine::configureLightBuffers(){
    unsigned int VBO,EBO;
    unsigned int lightVAO, mazeVAO;
    glGenVertexArrays(1,&lightVAO);
    glGenBuffers(1,&VBO);
    //glGenBuffers(1,&EBO);

    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(_vertices),_vertices,GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    Mesh lightMesh;
    //lightMesh.eboID = EBO;
    lightMesh.vboID = VBO;
    lightMesh.vaoID = lightVAO;
    _meshMap["lightMesh"] = lightMesh;

    glGenVertexArrays(1,&mazeVAO);
    glBindVertexArray(mazeVAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Mesh mazeMesh;
    //mazeMesh.eboID = EBO;
    mazeMesh.vboID = VBO;
    mazeMesh.vaoID = mazeVAO;
    _meshMap["mazeMesh"] = mazeMesh;

}

void Engine::loadShaders(){
    //_shaders.s_camera.Load("../res/shader/camera.vert","../res/shader/camera.frag");
    //_shaders.s_camera.use();
    _shaders.s_wall.Load("../res/shader/wall.vert","../res/shader/wall.frag");
    _shaders.s_floor.Load("../res/shader/floor.vert","../res/shader/floor.frag");
    _shaders.s_light.Load("../res/shader/light.vert","../res/shader/light.frag");
}

void Engine::updateCamera(){
    //Since our direction is calculated as a quaternion we need to extract ijk components to make a vec3.
    //Our we generate our view matrix using the camera's position, direction from current position, and camera up vec
    glm::vec3 camDirection = glm::vec3(_camera._direction.i,_camera._direction.j,_camera._direction.k);
    glm::mat4 view = glm::lookAt(_camera._pos,_camera._pos+camDirection,_camera._up);
    _camera._viewMatrix = view;
}

void Engine::drawMazeWalls(){
    _shaders.s_wall.use();
    _shaders.s_wall.setMat4("perspective",_camera._projMatrix);
    _shaders.s_wall.setMat4("view",_camera.getViewMatrix());
    glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3(2.0f,5.0f,2.0f));
    _shaders.s_wall.setMat4("model",scale);
    for(int i = 0; i < _map._numWalls; ++i){
        _shaders.s_wall.setVec2(("offsets[" + std::to_string(i) + "]"),_wallTranslations[i]);
    }
    glBindVertexArray(_meshMap["mazeMesh"].vaoID);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36*_map._numWalls, _map._numWalls);

}

void Engine::drawMazePaths(){
    _shaders.s_floor.use();
    _shaders.s_floor.setMat4("perspective",_camera._projMatrix);
    _shaders.s_floor.setMat4("view",_camera.getViewMatrix());
    glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3(2.0f,0.5f,2.0f));
    glm::mat4 model = glm::translate(scale,glm::vec3(0.0f,-4.5f,0.0f));
    _shaders.s_floor.setMat4("model",model);
    for(int i = 0; i < _map._numFloors; ++i){
        _shaders.s_floor.setVec2(("offsets[" + std::to_string(i) + "]"),_floorTranslations[i]);
    }
    glBindVertexArray(_meshMap["mazeMesh"].vaoID);
    //glDrawElementsInstanced(GL_TRIANGLES, 36*_map._numFloors,GL_UNSIGNED_INT, 0, _map._numFloors);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36*_map._numFloors, _map._numFloors);
}



//rotate the cube based on the direction the player is looking so the front face is the direction of where the light should point (like a flashlight)
void Engine::drawPlayer(){
    //SETUP BUFFER STUFF FOR LIGHT
    //HERE
    //
    glBindVertexArray(_meshMap["lightMesh"].vaoID);
    //glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    glDrawArrays(GL_TRIANGLES,0,36);

}
void Engine::updateLighting(){
    _lightingSystem.adjustFlashlight(_shaders.s_light,_camera);
    _lightingSystem.phongAlgorithm(_camera);
}


void Engine::drawObjects(){
    drawMazeWalls();
    drawMazePaths();
    //drawPlayer();
}

void Engine::generateMaze(){
    //glm::vec2 wallTranslations[_map._numWalls];
    _wallTranslations = new glm::vec2[_map._numWalls];
    _floorTranslations = new glm::vec2[_map._numFloors];
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    int wallIndex = 0;
    int floorIndex = 0;
    glm::vec2 translation;
    for(int x = 0;x < _map.grid.size(); ++x){
        offsetY = 0.0f;
        for(int y = 0;y < _map.grid[x].size(); ++y){
            //Wall
            translation.x = offsetX;
            translation.y = offsetY;
            if(_map.grid[x][y]->_state == 0){
                _wallTranslations[wallIndex++] = translation;
            }
            //Floor
            else{
                _floorTranslations[floorIndex++] = translation;
            }
            offsetY += 1.0f;
        }
        offsetX += 1.0f;
    }
    //drawMazeWall(wallTranslations);
}

void Engine::spawnPlayer(){
    float x = _map._spawnX;
    float z = _map._spawnZ;
    _camera.setPlayerSpawn(x,z);
}

void Engine::render(){
    if(!checkInit()){
        return;
    }
    configureLightBuffers(); 
    loadShaders();
    generateMaze();
    spawnPlayer();
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
        updateLighting();

        drawObjects();
        
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    glfwTerminate();
}