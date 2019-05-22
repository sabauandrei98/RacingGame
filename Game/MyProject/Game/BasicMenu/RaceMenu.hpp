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
    
    void renderDigit(std::string name,uint32_t no);
    void renderText(std::string name,std::string text);
    
private:
    MeshManager             meshManager;
    
    unsigned int noDigits(uint32_t number);
    void addNewDigit(std::string name,uint32_t no);
    void checkNeedChangeDigit(uint32_t no);
    int firstDigit(uint32_t no);
    void renderNumber(std::string name,uint32_t no,const IvVector3& position);
   
};


