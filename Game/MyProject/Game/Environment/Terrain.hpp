//-------------------------------------------------------------------------------
//-- Terrain.hpp ----------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Mesh.hpp"
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include "PerlinNoise.hpp"
#include <stdio.h>
#include <numeric>
#include <random>
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class Terrain
{
    uint32_t width;
    uint32_t height;
    uint32_t rows;
    uint32_t columns;
    std::shared_ptr<SceneNode> terrain;
    std::vector<std::vector<float>> elevation;
    
public:
    Terrain(uint32_t width,uint32_t height,uint32_t rows,uint32_t columns);
    ~Terrain(){}
    
    std::shared_ptr<SceneNode> getTerrain(){return terrain;}
    void build();
    
private:
    double noise1(double nx,double ny);
    double noise2(double nx,double ny);
   
};


