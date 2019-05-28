
#include "PerlinNoise.hpp"

PerlinNoise::PerlinNoise(unsigned int seed)
{	
	p.resize(256);

	std::iota(p.begin(), p.end(), 0);

	std::default_random_engine engine(seed);

	std::shuffle(p.begin(), p.end(), engine);

	p.insert(p.end(), p.begin(), p.end());
}

double
PerlinNoise::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double
PerlinNoise::gradient(int hash, double x, double y, double z)
{
    int h = hash & 15; //convert 4 bits of has code
    double u = h<8 ? x : y;
    double v = h<4 ? y : h==12 || h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

double
PerlinNoise::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double
PerlinNoise::noise(double x, double y, double z)
{
    //find units cube that contains the points
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    
    //relative x,y,z
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    
    //compute fade curves
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    
    //hash coordinates for the 8 cube corners
    int A  = p[X]+Y;
    int AA = p[A]+Z;
    int AB = p[A+1]+Z;
    int B  = p[X+1]+Y;
    int BA = p[B]+Z;
    int BB = p[B+1]+Z;
    
    return lerp(w,
                lerp(v,
                     lerp(u,
                          gradient(p[AA], x  , y  , z   ),
                          gradient(p[BA], x-1, y  , z   )),
                     lerp(u,
                          gradient(p[AB], x  , y-1, z   ),
                          gradient(p[BB], x-1, y-1, z   ))
                     ),
                lerp(v,
                     lerp(u, gradient(p[AA+1], x  , y  , z-1 ),gradient(p[BA+1], x-1, y  , z-1 )),
                     lerp(u, gradient(p[AB+1], x  , y-1, z-1 ),gradient(p[BB+1], x-1, y-1, z-1 ))
                     )
                );
}
