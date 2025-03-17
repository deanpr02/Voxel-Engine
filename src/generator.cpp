#include "generator.h"

/*
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

*/


/*
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
    //test();
}

void PerlinNoise::test(){
    int seed = 123456; // Example seed
    int octaves = 4;
    float persistence = 0.5;
    float lacunarity = 2.0;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            float n = fractalNoise(i*0.01,j*0.01,0,octaves,persistence,lacunarity);
            std::cout<<n<<"|";
        }
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
    //std::cout<<"3";
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlinNoise::noise(float x, float y, float z){
    //int X = static_cast<int>(std::floor(x)) & tableSizeMask;
    //int Y = static_cast<int>(std::floor(y)) & tableSizeMask;
    //int Z = static_cast<int>(std::floor(z)) & tableSizeMask;
    int X = static_cast<int>(std::floor(x));
    int Y = static_cast<int>(std::floor(y));
    int Z = static_cast<int>(std::floor(z));

// Proper modulo handling for negative values
    X = ((X % tableSize) + tableSize) % tableSize;
    Y = ((Y % tableSize) + tableSize) % tableSize;
    Z = ((Z % tableSize) + tableSize) % tableSize;

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
    //std::cout<<res<<std::endl;
    //std::cout<<"2";
    //std::cout<<"2";
    //std::cout<<(res+1.0f)/2.0f<<"|";
    return (res + 1.0f) / 2.0f;
}

float PerlinNoise::fractalNoise(float x, float y, float z, int octaves, float persistence, float lacunarity){
    float total = 0;
    float frequency = 1; // originally 1
    float amplitude = 1;
    float maxValue = 0;

    //std::cout<<"x: " << x << "y: " << y << "z: " << z << std::endl;
    for(int i = 0; i < octaves; i++){
        int offset = i * 2;
        total += noise((x+offset) * frequency,(y+offset) * frequency,z * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;
    }
    //std::cout<<total/maxValue<<std::endl;
    return total / maxValue;
}

*/

Perlin::Perlin(int s) {
	seed = s;

	p = new int[256];
	Gx = new float[256];
	Gy = new float[256];
	Gz = new float[256];

	for (int i=0; i<256; ++i) {
		p[i] = i;

		Gx[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
		Gy[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
		Gz[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
	}

	int j=0;
	int swp=0;
	for (int i=0; i<256; i++) {
		j = rand() & 255;

		swp = p[i];
		p[i] = p[j];
		p[j] = swp;
	}
}

float Perlin::noise(float sample_x, float sample_y, float sample_z)
{
	// Unit cube vertex coordinates surrounding the sample point
	int x0 = int(floorf(sample_x));
	int x1 = x0 + 1;
	int y0 = int(floorf(sample_y));
	int y1 = y0 + 1;
	int z0 = int(floorf(sample_z));
	int z1 = z0 + 1;

	// Determine sample point position within unit cube
	float px0 = sample_x - float(x0);
	float px1 = px0 - 1.0f;
	float py0 = sample_y - float(y0);
	float py1 = py0 - 1.0f;
	float pz0 = sample_z - float(z0);
	float pz1 = pz0 - 1.0f;

	// Compute dot product between gradient and sample position vector
	int gIndex = p[(x0 + p[(y0 + p[z0 & 255]) & 255]) & 255];
	float d000 = Gx[gIndex]*px0 + Gy[gIndex]*py0 + Gz[gIndex]*pz0;
	gIndex = p[(x1 + p[(y0 + p[z0 & 255]) & 255]) & 255];
	float d001 = Gx[gIndex]*px1 + Gy[gIndex]*py0 + Gz[gIndex]*pz0;
	
	gIndex = p[(x0 + p[(y1 + p[z0 & 255]) & 255]) & 255];
	float d010 = Gx[gIndex]*px0 + Gy[gIndex]*py1 + Gz[gIndex]*pz0;
	gIndex = p[(x1 + p[(y1 + p[z0 & 255]) & 255]) & 255];
	float d011 = Gx[gIndex]*px1 + Gy[gIndex]*py1 + Gz[gIndex]*pz0;
	
	gIndex = p[(x0 + p[(y0 + p[z1 & 255]) & 255]) & 255];
	float d100 = Gx[gIndex]*px0 + Gy[gIndex]*py0 + Gz[gIndex]*pz1;
	gIndex = p[(x1 + p[(y0 + p[z1 & 255]) & 255]) & 255];
	float d101 = Gx[gIndex]*px1 + Gy[gIndex]*py0 + Gz[gIndex]*pz1;

	gIndex = p[(x0 + p[(y1 + p[z1 & 255]) & 255]) & 255];
	float d110 = Gx[gIndex]*px0 + Gy[gIndex]*py1 + Gz[gIndex]*pz1;
	gIndex = p[(x1 + p[(y1 + p[z1 & 255]) & 255]) & 255];
	float d111 = Gx[gIndex]*px1 + Gy[gIndex]*py1 + Gz[gIndex]*pz1;

	// Interpolate dot product values at sample point using polynomial interpolation 6x^5 - 15x^4 + 10x^3
	float wx = ((6*px0 - 15)*px0 + 10)*px0*px0*px0;
	float wy = ((6*py0 - 15)*py0 + 10)*py0*py0*py0;
	float wz = ((6*pz0 - 15)*pz0 + 10)*pz0*pz0*pz0;

	float xa = d000 + wx*(d001 - d000);
	float xb = d010 + wx*(d011 - d010);
	float xc = d100 + wx*(d101 - d100);
	float xd = d110 + wx*(d111 - d110);
	float ya = xa + wy*(xb - xa);
	float yb = xc + wy*(xd - xc);
	float value = ya + wz*(yb - ya);

	return value;
}

FractalNoise::FractalNoise(int s){
    m_perlinSource = new Perlin(s);

	m_octaves = 8;
	m_lacunarity = 2.0f;
	m_persistence = 0.5f;
	m_baseFrequency = 1.0f;
	m_baseAmplitude = 1.0f;
}

float FractalNoise::noise(float sample_x, float sample_y, float sample_z) {
	float sum = 0;
	float freq = m_baseFrequency;
	float amp = m_baseAmplitude;

	for (int i=0; i<m_octaves; ++i) {
		sum += m_perlinSource->noise(sample_x*freq, sample_y*freq, sample_z*freq)*amp;

		freq *= m_lacunarity;
		amp *= m_persistence;
	}

	return (sum+1.0f)/2;
}


ProceduralGenerator::ProceduralGenerator(){
    int s = 123456;
    m_noiseGenerator = new FractalNoise(s);
}

float ProceduralGenerator::generate(float x, float y, float z){
    return m_noiseGenerator->noise(x*0.03,y*0.03,z*0.03);
}