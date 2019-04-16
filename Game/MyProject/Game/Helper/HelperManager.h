//-------------------------------------------------------------------------------
//-- HelperManager.h ------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "SceneGraph.hpp"
#include "CameraSceneNode.hpp"
#include <math.h>
#include <stdio.h>
//-------------------------------------------------------------------------------
//-- Typedefs,Static ------------------------------------------------------------
//-------------------------------------------------------------------------------
static std::vector<std::string> DEFAULT_UNIFORMS_VECTOR;
//-------------------------------------------------------------------------------
//-- Clases ---------------------------------------------------------------------
//-------------------------------------------------------------------------------
class HelperManager
{
public:
    
    std::shared_ptr<Mesh> CreateBoxMesh();
    std::shared_ptr<Mesh> CreateQuadMesh();
    std::shared_ptr<Mesh> CreateSphereMesh();
    
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh>&,const char* shaderName="BasicShader",const std::vector<std::string>& uniforms=DEFAULT_UNIFORMS_VECTOR);
   
private:
    //---for sphere
    IvVector3 GetMiddlePoint(IvVector3 p1,IvVector3 p2);
    std::vector<IvTNPVertex> RefineTriangles(std::vector<IvTNPVertex> vertices,int recursionLevel);
    float CalculateLength(IvVector3 point);
    //----
};
