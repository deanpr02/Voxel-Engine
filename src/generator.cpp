#include "generator.h"

RandomSeed::RandomSeed(int s){
    seed = s;
}

int RandomSeed::next(){
    seed = (a * seed + c ) % m;
    return static_cast<int>(seed);
}

float RandomSeed::nextFloat(){
    return next() / static_cast<float>(m);
}

PerlinNoise::PerlinNoise(int seed){
    randomSeed = new RandomSeed(seed);
    permutationTable.resize(tableSize * 2);
    std::vector<int> tempTable(tableSize);
    for(int i = 0; i < tableSize; i++){
        tempTable[i] = i;
    }

    for(int i = 0; i < tableSize; i++){
        int j = randomSeed->next() % tableSize;
        std::swap(tempTable[i],tempTable[j]);
    }

    for(int i = 0; i < tableSize; i++){
        permutationTable[i] = tempTable[i];
        permutationTable[tableSize + i] = tempTable[i];
    }
}

float PerlinNoise::fade(float t){
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float a, float b, float t){
    return a + t * (b - a);
}

float PerlinNoise::grad(int hash, float x, float y, float z){
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise::noise(float x, float y, float z){
    int X = static_cast<int>(std::floor(x)) & tableSizeMask;
    int Y = static_cast<int>(std::floor(y)) & tableSizeMask;
    int Z = static_cast<int>(std::floor(z)) & tableSizeMask;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    int A = permutationTable[X] + Y;
    int AA = permutationTable[A] + Z;
    int AB = permutationTable[A+1] + Z;
    int B = permutationTable[X+1] + Y;
    int BA = permutationTable[B] + Z;
    int BB = permutationTable[B+1] + Z;

    float res = 
        lerp(w,
            lerp(v,
                lerp(u,grad(permutationTable[AA],x,y,z),
                        grad(permutationTable[BA],x-1,y,z)),
                lerp(u,grad(permutationTable[AB],x,y-1,z),
                        grad(permutationTable[BB],x-1,y-1,z))),
            lerp(v,
                lerp(u,grad(permutationTable[AA+1],x,y,z-1),
                    grad(permutationTable[BA+1],x-1,y,z-1)),
                lerp(u,grad(permutationTable[AB+1],x,y-1,z-1),
                    grad(permutationTable[BB+1],x-1,y-1,z-1))));
    return (res + 1.0f) / 2.0f;
}

float PerlinNoise::fractalNoise(float x, float y, float z, int octaves, float persistence, float lacunarity){
    float total = 0;
    float frequency = 1;
    float amplitude = 1;
    float maxValue = 0;

    for(int i = 0; i < octaves; i++){
        int offset = i * 2;
        total += noise((x+offset) * frequency,(y+offset) * frequency,z * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;
    }

    return total / maxValue;
}

ProceduralGenerator::ProceduralGenerator(){
    m_noiseGenerator = new PerlinNoise(seed);
}

float ProceduralGenerator::generate(float x, float y, float z){
    return m_noiseGenerator->fractalNoise(x,y,z,octaves,persistence,lacunarity);
}