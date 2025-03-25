#ifndef SPELLS_H
#define SPELLS_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "types.h"


class Particle{
    public:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    std::vector<float> vertices;
    std::vector<int> indices;
    glm::vec3 offset = glm::vec3(0,0,0);
    glm::vec3 aim;
    int moveIndex = 0;
    glm::vec3 lastMove;
    float size = 0.025f;

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
    std::vector<Particle> m_particles;
    float spellVelocity;
    float spellRange;
    int spellDensity;
    int spellRadius;
    SPELL_TYPE id;

    void drawParticle(glm::vec3);
    std::vector<Particle> getParticles();

    virtual void tick(float,glm::vec3,glm::vec3);
};

class Lightning: public Spell{
    public:
    SPELL_TYPE id;

    Lightning();
    void tick(float,glm::vec3,glm::vec3);
    void jolt(float,glm::vec3);
};

#endif