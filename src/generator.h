#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

class RandomSeed{
    private:
    long seed;
    static const long a = 48271;
    static const long c = 0;
    static const long m = 2147483647;

    public:
    RandomSeed(int);
    int next();
    float nextFloat();

};

class PerlinNoise{
    private:
    std::vector<int> permutationTable;
    static const int tableSize = 256;
    static const int tableSizeMask = tableSize - 1;
    RandomSeed* randomSeed;

    float fade(float);
    float lerp(float,float,float);
    float grad(int,float,float,float);

    public:
    PerlinNoise(int);
    float noise(float,float,float);
    float fractalNoise(float,float,float,int,float,float);
};

class ProceduralGenerator{
    private:
    int seed = 123456;
    int octaves = 4;
    float persistence = 0.5;
    float lacunarity = 2.0;

    public:
    PerlinNoise* m_noiseGenerator;
    ProceduralGenerator();
    float generate(float,float,float);
};