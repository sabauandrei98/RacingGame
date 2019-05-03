//-------------------------------------------------------------------------------
//-- BuildTrack.hpp -------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include <stdio.h>
#include <map>
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class BuildTrack
{
public:
    //constructor/destructor
    BuildTrack();
    ~BuildTrack();
    
    void Update(float dt);
    void Render();
    
private:
    std::shared_ptr<SceneGraph> buildTrack;
};
