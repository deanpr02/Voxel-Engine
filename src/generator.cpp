#include "generator.h"

RandomSeed::RandomSeed(int s){
    seed = s;
}

int RandomSeed::Next(){
    seed = (a * seed + c) % m;
    return seed;
}

float RandomSeed::nextFloat(){
    return Next() / static_cast<float>(m);
}

void RandomSeed::setSeed(long s){
    seed = s;
}

PerlinNoise::PerlinNoise(int seed){
    randomSeed = new RandomSeed(seed);
    //randomSeed = new RandomSeed(seed);
    permutationTable.resize(tableSize * 2);
    std::vector<int> tempTable(tableSize);
    for(int i = 0; i < tableSize; i++){
        tempTable[i] = i;
    }
    
    for(int i = 0; i < tableSize; i++){
        int j = randomSeed->Next() % tableSize;
        //std::cout<<"i: "<<i<<"j: "<<j<<std::endl;
        std::swap(tempTable[i],tempTable[j]);
    }

    //for(int i = 0;i<tableSize;i++){
    //    std::cout<<tempTable[i]<<std::endl;
    //}

    for(int i = 0; i < tableSize; i++){
        permutationTable[i] = tempTable[i];
        permutationTable[tableSize + i] = tempTable[i];
    }
    //for(int i =0;i<permutationTable.size();i++){
    //    std::cout<<"i: "<<permutationTable[i]<<std::endl;
    //}
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
    //std::cout<<"3";
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise::noise(float x, float y, float z){
    int X = static_cast<int>(std::floor(x)) & tableSizeMask;
    int Y = static_cast<int>(std::floor(y)) & tableSizeMask;
    int Z = static_cast<int>(std::floor(z)) & tableSizeMask;

    //std::cout<<"x: " << X << "y: " << Y << "z: " << Z << std::endl;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    //std::cout<<u<<" "<<v<<" "<<" "<<w<<std::endl;

    int A = permutationTable[X] + Y;
    int AA = permutationTable[A] + Z;
    int AB = permutationTable[A+1] + Z;
    int B = permutationTable[X+1] + Y;
    int BA = permutationTable[B] + Z;
    int BB = permutationTable[B+1] + Z;
    //std::cout<<"1";

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
    //std::cout<<res;
    //std::cout<<"2";
    //std::cout<<"2";
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
    //std::cout<<total<<std::endl;
    return total / maxValue;
}

ProceduralGenerator::ProceduralGenerator(){
    //int s = 123456;
    //int64_t a = 48271;
    //int64_t c = 0;
    //int64_t  m = 2147483647;
    //int64_t test = (a * s + c);
    //std::cout << "long max: " << std::numeric_limits<long long>::max() << std::endl;
    m_noiseGenerator = new PerlinNoise(s);
}

float ProceduralGenerator::generate(float x, float y, float z){
    return m_noiseGenerator->fractalNoise(x*0.3,y*0.3,z*0.3,octaves,persistence,lacunarity);
}