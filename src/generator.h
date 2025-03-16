#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdint>

class RandomSeed{
    private:
    int64_t seed;
    const int64_t a = 48271;
    const int64_t c = 0;
    const int64_t m = 2147483647;

    public:
    RandomSeed(int s);
    int Next();
    float nextFloat();
    void setSeed(long);

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
    int s = 123456;
    int octaves = 4;
    float persistence = 0.5;
    float lacunarity = 2.0;

    public:
    PerlinNoise* m_noiseGenerator;
    ProceduralGenerator();
    float generate(float,float,float);
};