//-------------------------------------------------------------------------------
//-- HelperManager.h ------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include "SceneGraph.hpp"
#include "CameraSceneNode.hpp"
//-------------------------------------------------------------------------------
//-- Typedefs,Static ------------------------------------------------------------
//-------------------------------------------------------------------------------
namespace HelperManager
{
    std::shared_ptr<Mesh> CreateBoxMesh();
    std::shared_ptr<Mesh> CreateQuadMesh();
    std::shared_ptr<Mesh> CreateSphereMesh();
    
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const char* shaderName="BasicShader");
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const std::vector<std::string>& uniforms,const char* shaderName="BasicShader");
    
    IvVector3 GetMiddlePoint(IvVector3 p1,IvVector3 p2);
    void RefineTriangles(std::vector<IvTNPVertex>& vertices,std::vector<unsigned int>& indices,int recursionLevel);
    float CalculateLength(IvVector3 point);
};

