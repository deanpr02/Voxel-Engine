#ifndef WEAPON_H
#define WEAPON_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


class Particle{
    public:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    std::vector<float> vertices;
    std::vector<int> indices;
    glm::vec3 offset = glm::vec3(0,0,0);
    glm::vec3 aim;

    Particle(glm::vec3,glm::vec3);
    void create(glm::vec3,glm::vec3);
    void initialize();
    void addVertex(glm::vec3);
    void addTriangle(int,int,int);
    void shift(float,float);
    void draw();
};

class Spell{
    public:
    //unsigned int particle;
    std::vector<Particle> m_particles;
    float spellVelocity = 10.0f;
    float spellRange = 10.0f;
    int spellDensity = 3;
    int spellRadius = 3;
    //Shader m_shader;


    void tick(float,glm::vec3);
    void drawParticle(glm::vec3);
    std::vector<Particle> getParticles();
};


class WeaponSystem{
    public:
    //std::vector<Spell> m_spells;
    Spell currentSpell;

    void render();
    void draw();
    void spawn(glm::vec3,glm::vec3,glm::vec3);
};

#endif