#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "camera.h"
#include "shader.h"
#include "renderer.h"
//#include "block.h"
#include <vector>
#include <unordered_map>
#include <functional>
#include <set>

//constants
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

typedef std::function<void()> FuncType;

class Engine{
    public:
    Camera _camera; /* Camera class object that controlling viewable portion of map */
    Renderer _vRenderer;
    //Player _player;
    std::unordered_map<int,FuncType> _inputMap; /* HashTable holding different game objects and their functions */
    std::set<int> _pressedKeys; /* All the keys currently being pressed during a certain frame */  /* Offset information for the floors for drawing */
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
    void drawCube();
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
    void draw();
};
#endif