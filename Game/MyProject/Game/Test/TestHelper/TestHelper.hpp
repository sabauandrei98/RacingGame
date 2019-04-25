//-------------------------------------------------------------------------------
//-- TestHelper.h  --------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "SceneGraph.hpp"
#include "Helper/HelperManager.hpp"
#include "Helper/MeshManager.hpp"
#include "IvRendererHelp.h"
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class TestHelper
{
public:
    TestHelper();
   
    void DrawBox();
    void DrawQuad();
    void DrawSphere();
    
    void Update(float dt);
    
private:
    bool                                boxCreated;
    bool                                quadCreated;
    bool                                sphereCreated;
    
    std::shared_ptr<SceneGraph>         box;
    std::shared_ptr<SceneGraph>         quad;
    std::shared_ptr<SceneGraph>         sphere;
    
    MeshManager*                        meshManager;
    
    std::shared_ptr<Camera>             camera;
    std::shared_ptr<CameraSceneNode>    cameraSceneNode;
};
