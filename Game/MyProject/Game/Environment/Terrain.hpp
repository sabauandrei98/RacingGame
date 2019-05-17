//-------------------------------------------------------------------------------
//-- Terrain.hpp ----------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Mesh.hpp"
#include <IvRendererHelp.h>
#include <IvRenderer.h>
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include "PerlinNoise.hpp"
#include "../SceneManagement/SceneNode.hpp"
#include <stdio.h>
#include <numeric>
#include <random>
#include <time.h>

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class Terrain: std::enable_shared_from_this<Terrain>,public HelperSceneNode
{
    uint32_t width;
    uint32_t height;
    uint32_t rows;
    uint32_t columns;
    std::vector<std::vector<float>> elevation;
    
    std::vector<IvVector3> normals;
    std::vector<IvTNPVertex> vertices;
    std::vector<unsigned int> indices;
    
public:
    Terrain(const char*,RenderPacket,uint32_t width,uint32_t height);
    ~Terrain(){}
    
    std::vector<IvVector3> getNormal(){return normals;}
    std::vector<IvTNPVertex> getVertices(){return vertices;}
    std::vector<unsigned int> getIndices(){return indices;}
    
    void build();
    
private:
    double noise1(double nx,double ny);
   
    IvVector3 calculateNormalAverage(std::vector<std::pair<IvVector3,IvVector3>> normalFaces,unsigned int index);
};


