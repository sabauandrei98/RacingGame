//-------------------------------------------------------------------------------
//-- HelperManager.h ------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include "IvImage.h"
#include "SceneGraph.hpp"
#include "CameraSceneNode.hpp"
#include "MyHelperSceneNode.h"

//-------------------------------------------------------------------------------
//-- Typedefs,Static ------------------------------------------------------------
//-------------------------------------------------------------------------------
namespace HelperManager
{
    std::shared_ptr<Mesh> CreateBoxMesh();
    std::shared_ptr<Mesh> CreateQuadMesh();
    std::shared_ptr<Mesh> CreateSphereMesh();
    
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const char* shaderName="BasicShader");
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const std::vector<std::string>& uniforms,const char* shaderName="TextureShader");
    
    std::shared_ptr<SceneNode> BuildBox(const std::shared_ptr<MeshInstance>&,bool wireframeValue=false);
    std::shared_ptr<SceneNode> BuildSphere(const std::shared_ptr<MeshInstance>&,bool wireframeValue=false);
    std::shared_ptr<SceneNode> BuildQuad(const std::shared_ptr<MeshInstance>&,IvVector3 axis=IvVector3::zAxis, bool wireframeValue=false);
    std::shared_ptr<SceneNode> BuildTexturedQuad(const std::shared_ptr<MeshInstance>&,const char* textureName,const char* shaderName="TextureShader",IvVector3 axis=IvVector3::zAxis, bool wireframeValue=false);
    
    IvVector3 GetMiddlePoint(const IvVector3& point1,const IvVector3& point2);
    void RefineTriangles(std::vector<IvTNPVertex>& vertices,std::vector<unsigned int>& indices,int recursionLevel);
    float CalculateLength(const IvVector3& point);
    
};


