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
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class TestHelper
{
public:
    TestHelper();
    ~TestHelper();
    void DrawBox();
    void DrawQuad();
    void DrawSphere();
    
private:
    std::shared_ptr<SceneNode> box;
    std::vector<bool>    createdBoxes;
    std::vector<bool>    createdQuads;
    std::vector<bool>    createdSphere;
    
    std::vector<std::shared_ptr<SceneGraph>> toBeRendered;
    
    MeshManager*         meshManager;
};
