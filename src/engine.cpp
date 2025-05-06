#include "engine.h"

void Engine::processInput(GLFWwindow* window){
    for(int key: m_pressedKeys){
        if(key == GLFW_KEY_ESCAPE){
            m_gameState = false;
            return;
        }
        player->processMovement(key);
    }
    
    m_renderer->updateChunks(player->m_camera);
}

void Engine::init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Dat Engine",NULL,NULL);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window,frameBufferCallback);
    glfwSetCursorPosCallback(m_window,mouseCallback);
    glfwSetMouseButtonCallback(m_window,mouseClickCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(m_window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Engine::frameBufferCallback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void Engine::mouseCallback(GLFWwindow* window, double xposIn, double yposIn){
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if(engine->m_firstMouse){
        engine->m_lastX = xpos;
        engine->m_lastY = ypos;
        engine->m_firstMouse = false;
    }
    float xoffset = engine->m_lastX - xpos;
    //this was flipped from engine->lastY to ypos
    float yoffset = engine->m_lastY - ypos;
    engine->m_lastX = xpos;
    engine->m_lastY = ypos;
    
    engine->player->processLookAround(xoffset,yoffset);
}

void Engine::mouseClickCallback(GLFWwindow* window, int button, int action, int mods){
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        engine->player->cast();
    }
}

void Engine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        if(key == GLFW_KEY_LEFT_SHIFT){
            engine->player->setMovementSpeed(15.0f);
        }
        engine->m_pressedKeys.insert(key);
    }
    else if(action == GLFW_RELEASE){
        if(key == GLFW_KEY_LEFT_SHIFT){
            engine->player->setMovementSpeed(5.0f);
        }
        engine->m_pressedKeys.erase(key);
    }
}

int Engine::checkInit(){
    if(m_window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 1;

}


//void Engine::updateCamera(){
//    //Since our direction is calculated as a quaternion we need to extract ijk components to make a vec3.
//    //Our we generate our view matrix using the camera's position, direction from current position, and camera up vec
//    glm::vec3 camDirection = glm::vec3(m_camera.m_direction.i,m_camera.m_direction.j,m_camera.m_direction.k);
//    glm::mat4 view = glm::lookAt(m_camera.m_pos,m_camera.m_pos+camDirection,m_camera.m_up);
//    m_camera.m_viewMatrix = view;
//}

void Engine::draw(){
    m_renderer->render(player->m_camera);
}

void Engine::render(){
    if(!checkInit()){
        return;
    }

    while(!glfwWindowShouldClose(m_window)){
        if(!m_gameState){
            break;
        }
        float currentFrame = static_cast<float>(glfwGetTime());
        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;

        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        processInput(m_window);
        player->update(m_deltaTime,m_renderer->m_chunkManager->m_visibleChunks);

        draw();
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwTerminate();
}