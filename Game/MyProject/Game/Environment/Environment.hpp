//-------------------------------------------------------------------------------
//-- Environment.hpp ------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Mesh.hpp"
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include "SkyBox.hpp"
#include "Terrain.hpp"
#include "../RoadGenerator/RoadEditor.hpp"
#include <stdio.h>
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class Environment:std::enable_shared_from_this<Environment>,public SceneNode
{
public:
    Environment(const char* name,const std::vector<std::pair<IvVector3,IvVector3>>& marginPoints);
    ~Environment(){}
    
private:
};


