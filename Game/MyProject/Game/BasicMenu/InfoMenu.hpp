//-------------------------------------------------------------------------------
//-- InfoMenu.hpp ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "HelperManager.hpp"
#include "MeshManager.hpp"
#include "../BasicMenu/Menu.hpp"
#include "../SceneManagement/SceneGraph.hpp"
#include <stdio.h>
#include <unordered_map>
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class InfoMenu:public Menu
{
public:
    //constructor/destructor
    InfoMenu();
    ~InfoMenu();
    
    void renderDigit(std::string name,uint32_t no);
    void renderText(std::string name,std::string text);
    
private:
    MeshManager meshManager;
    std::unordered_map<char,std::pair<uint32_t,uint32_t>> characters;
    
    unsigned int noDigits(uint32_t number);
    void addNewDigit(std::string name,uint32_t no);
    void checkNeedChangeDigit(uint32_t no);
    int firstDigit(uint32_t no);
    void renderNumber(std::string name,uint32_t no,const IvVector3& position);
    std::pair<float,float> getRowCol(const char c) const;
    void setCharacters();
};
