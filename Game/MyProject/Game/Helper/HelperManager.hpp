//-------------------------------------------------------------------------------
//-- HelperManager.hpp ------------------------------------------------------------
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
#include "HelperSceneNode.hpp"

//-------------------------------------------------------------------------------
//-- Typedefs,Static ------------------------------------------------------------
//-------------------------------------------------------------------------------
namespace HelperManager
{
    std::shared_ptr<Mesh> CreateBoxMesh();
    std::shared_ptr<Mesh> CreateQuadMesh();
    std::shared_ptr<Mesh> CreateSphereMesh();
    
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const char* shaderName="../../Game/Helper/Shaders/BasicShader");
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const std::vector<std::string>& uniforms,const char* shaderName="../../Game/Helper/Shaders/TextureShader");
    
    std::shared_ptr<SceneNode> BuildBox(const char* name,const std::shared_ptr<MeshInstance>&,bool depth=true,bool blend=true,bool wireframeValue=false);
    std::shared_ptr<SceneNode> BuildSphere(const char* name,const std::shared_ptr<MeshInstance>&,bool depth=true,bool blend=true,bool wireframeValue=false);
    std::shared_ptr<SceneNode> BuildQuad(const char* name,const std::shared_ptr<MeshInstance>&,IvVector3 axis=IvVector3::zAxis,bool depth=true,bool blend=true, bool wireframeValue=false);
    std::shared_ptr<SceneNode> BuildTexturedQuad(const char* name,const std::shared_ptr<MeshInstance>&,const char* textureName,IvVector3 axis=IvVector3::zAxis,bool depth=true,bool blend=true, bool wireframeValue=false);
    
};

namespace Utils
{
    IvVector3 GetMiddlePoint(const IvVector3& point1,const IvVector3& point2);
    void RefineTriangles(std::vector<IvTNPVertex>& vertices,std::vector<unsigned int>& indices,int recursionLevel);
    float CalculateLength(const IvVector3& point);
};


