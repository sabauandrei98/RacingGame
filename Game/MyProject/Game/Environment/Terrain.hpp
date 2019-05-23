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
    std::vector<std::vector<float>>  elevation;
    
    std::vector<IvVector3>           normals;
    std::vector<IvTNPVertex>         vertices;
    std::vector<unsigned int>        indices;
    
    std::shared_ptr<Mesh>            grid;
    std::shared_ptr<MeshInstance>    meshInstance;
    
public:
    Terrain(const char*,RenderPacket,uint32_t width,uint32_t height,const std::vector<std::pair<IvVector3,IvVector3>>& marginPoints);
    ~Terrain(){}
    
    void setVertices(const std::vector<IvTNPVertex>& vertices);
    
    void build();
    
private:
    double noise1(double nx,double ny);
    
    int isPointRayIntersectLines(const IvVector3& point,const std::vector<std::pair<IvVector3,IvVector3>>& lines);
    bool pointIntersectsLine(IvVector3 point,IvVector3 start,IvVector3 end);
};


