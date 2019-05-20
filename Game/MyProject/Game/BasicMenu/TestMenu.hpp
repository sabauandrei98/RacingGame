//-------------------------------------------------------------------------------
//-- TestMenu.hpp -------------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Menu.hpp"
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include "../Environment/SkyBox.hpp"
#include "../Environment/Terrain.hpp"
#include "../Environment/Environment.hpp"
#include "../ModelLoader/ModelLoader.hpp"
#include "../Car/CarController.hpp"
#include "../RoadGenerator/RoadImporterExporter.hpp"
#include "../SceneManagement/RoadNode.hpp"
#include "../SceneManagement/CameraFollowAnimator.hpp"
#include <stdio.h>
#include <map>

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class TestMenu:public Menu
{
public:
    //constructor/destructor
    TestMenu();
    ~TestMenu();
    
private:
};




