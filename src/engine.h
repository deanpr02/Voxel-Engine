#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "camera.h"
#include "shader.h"
#include "renderer.h"
#include "physics.h"
#include "player.h"
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
    //Camera m_camera; /* Camera class object that controlling viewable portion of map */
    Renderer* m_renderer;
    PhysicsObject* m_player;
    Player* player;
    //Player _player;
    std::unordered_map<int,FuncType> m_inputMap; /* HashTable holding different game objects and their functions */
    std::set<int> m_pressedKeys; /* All the keys currently being pressed during a certain frame */  /* Offset information for the floors for drawing */
    GLFWwindow* m_window;    /* Game window */
    float m_lastX;
    float m_lastY;
    bool m_firstMouse;
    bool m_gameState;
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;
    Engine(){
        m_lastX = SCR_WIDTH / 2.0f;
        m_lastY = SCR_HEIGHT / 2.0f;
        m_firstMouse = true;
        m_gameState = true;
        init();
        player = new Player();
        m_renderer = new Renderer(player->m_weapons);
        //m_player = new PhysicsObject(&m_camera.m_pos);

    }

    void processInput(GLFWwindow*);
    void init();
    static void mouseCallback(GLFWwindow*,double,double);
    static void mouseClickCallback(GLFWwindow*,int,int,int);
    static void frameBufferCallback(GLFWwindow*,int,int);
    static void keyCallback(GLFWwindow*,int,int,int,int);
    int checkInit();
    void render();
    void loadShaders();
    void updateCamera();
    void draw();
};
#endif