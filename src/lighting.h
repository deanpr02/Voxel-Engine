#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "shader.h"
#include "camera.h"

class LightingSystem{
    public:
    glm::vec3 _flashlightColor = glm::vec3(1.0f,1.0f,1.0f);
    glm::vec3 _flashlightPos = glm::vec3(0.0f);

    void setAmbientLighting(Shader,float);
    void setDiffuseLighting(Shader,Camera);
    void setSpecularLighting(Shader,Camera,float);
    void adjustFlashlight(Shader,Camera);
    void phongAlgorithm(Camera);
    glm::mat4 rotateLightToCamera(const glm::vec3&,const glm::vec3&,const glm::vec3&);
};
#endif