#pragma once

#include <stdio.h>
#include <vector>
#include <numeric>
#include <random>
#include <math.h>


class PerlinNoise
{
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    ~PerlinNoise(){}
    
    double noise(double x,double y,double z);
    
private:
    std::vector<int> p;
    double fade(double t);
    double gradient(int hash,double x,double y,double z);
    double lerp(double t,double a,double b);
};
