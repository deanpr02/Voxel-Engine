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
    glm::vec3 position;
    glm::vec3 off = glm::vec3(0,0,0);
    glm::vec3 aim;
    int moveIndex = 0;
    glm::vec3 lastMove;
    float size;

    Particle(glm::vec3,glm::vec3,float,float);
    Particle(glm::vec3,glm::vec3,float,std::vector<glm::vec3>,glm::mat4);
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
    std::vector<glm::vec3> m_mesh;
    float spellVelocity;
    float spellRange;
    int spellDensity;
    int spellRadius;
    int numParticles;
    float particleSize;
    SPELL_TYPE id;

    void drawParticle(glm::vec3);
    virtual void summon(glm::vec3,glm::vec3,glm::vec3,glm::mat4);
    std::vector<Particle> getParticles();

    virtual void createSpellMesh();
    virtual void tick(float,glm::vec3,glm::vec3,glm::vec3,glm::mat4);
};

class Lightning: public Spell{
    public:

    Lightning();
    void tick(float,glm::vec3,glm::vec3,glm::vec3,glm::mat4);
    void jolt(float,glm::vec3);
    void createSpellMesh();
};

class WaterBall: public Spell{
    public:
    float growFactor = 0.05f;
    float maxSize = 0.3f;
    bool release = true;

    WaterBall();
    void tick(float,glm::vec3,glm::vec3,glm::vec3,glm::mat4);
    void grow(float);
    void createSpellMesh();
    void summon(glm::vec3,glm::vec3,glm::vec3,glm::mat4);
};

#endif