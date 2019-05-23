//-------------------------------------------------------------------------------
//-- RaceMenu.hpp ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Menu.hpp"
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include "../RoadGenerator/RoadImporterExporter.hpp"
#include "../SceneManagement/RoadNode.hpp"
#include "../Car/CarController.hpp"
#include "../Environment/Environment.hpp"
#include "../ModelLoader/ModelLoader.hpp"
#include "../SceneManagement/CameraFollowAnimator.hpp"
#include "../Gameplay/InfoManager.hpp"
#include <stdio.h>
#include <map>
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class RaceMenu:public Menu
{
public:
    //constructor/destructor
    RaceMenu();
    ~RaceMenu();
     
private:
    MeshManager             meshManager;
};


