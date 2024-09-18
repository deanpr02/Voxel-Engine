#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "maze.h"
#include "camera.h"
#include "player.h"
#include "shader.h"
#include "lighting.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include <set>

//constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

typedef std::function<void()> FuncType;


//extern struct Shaders{
//    Shader s_camera;
//    Shader s_wall;
//    Shader s_floor;
//    Shader s_light;
//}_shaders;
extern Shaders _shaders;

struct GameObject{
    Shader objShader;
    unsigned int* indices;
    float* vertices;
    glm::mat4 transform;
};

struct Mesh{
    unsigned int vboID;
    unsigned int vaoID;
    unsigned int eboID;
};

class Engine{
    public:
    Camera _camera; /* Camera class object that controlling viewable portion of map */
    Maze _map;  /* Maze object which holds the data for the generated maze */
    LightingSystem _lightingSystem;
    //Player _player;
    std::vector<GameObject> _gameObjects; /* Stores game objects */
    std::unordered_map<std::string,Mesh> _meshMap;
    std::unordered_map<int,FuncType> _inputMap; /* HashTable holding different game objects and their functions */
    std::set<int> _pressedKeys; /* All the keys currently being pressed during a certain frame */
    glm::vec2* _wallTranslations; /* Offset information for the walls for drawing */
    glm::vec2* _floorTranslations;  /* Offset information for the floors for drawing */
    GLFWwindow* _window;    /* Game window */
    float _lastX;
    float _lastY;
    bool _firstMouse;
    bool _gameState;
    float _deltaTime = 0.0f;
    float _lastFrame = 0.0f;
    Engine(){
        _lastX = SCR_WIDTH / 2.0f;
        _lastY = SCR_HEIGHT / 2.0f;
        _firstMouse = true;
        _gameState = true;
        init();
    }

    void processInput(GLFWwindow*);
    void init();
    static void mouseCallback(GLFWwindow*,double,double);
    static void frameBufferCallback(GLFWwindow*,int,int);
    static void keyCallback(GLFWwindow*,int,int,int,int);
    void drawMazeWalls();
    void drawMazePaths();
    void drawPlayer();
    void drawObjects();
    void generateMaze();
    void configureBuffers();
    void configureLightBuffers();
    int checkInit();
    void render();
    void loadShaders();
    void updateLighting();
    //create the wall and floor game objects for rendering
    void createObjects();
    //create the wall
    void createWall();
    void createFloor();
    void updateCamera();
    void spawnPlayer();
};
#endif