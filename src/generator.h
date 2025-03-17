#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstdint>

/*
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
    void test();
};
*/

class Perlin{
    public:
    Perlin(int);
    int seed;
    int *p;
    float *Gx;
    float *Gy;
    float *Gz;

    float noise(float,float,float);

};

class FractalNoise{
    public:
    FractalNoise(int);
	float noise(float,float,float);	

private:
	Perlin *m_perlinSource;

	int m_octaves; // Number of octaves to sum together. Default is 10.
	float m_persistence; // Amplitude multiplier for each subsequent octave. Default is 0.5.
	float m_lacunarity; // Frequency multiplier for each subsequent octave. Default is 2.0.
	float m_baseFrequency; // Initial starting frequency. Default is 1.0.
	float m_baseAmplitude;
};

class ProceduralGenerator{
    private:
    int s = 123456;
    int octaves = 3;
    float persistence = 0.5;
    float lacunarity = 1.8;

    public:
    FractalNoise* m_noiseGenerator;
    ProceduralGenerator();
    float generate(float,float,float);
};