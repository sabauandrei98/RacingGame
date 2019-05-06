//-------------------------------------------------------------------------------
//-- Menu.hpp -------------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "SceneManagement/SceneGraph.hpp"
#include <stdio.h>
#include <map>
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class Menu
{
public:
    //constructor/destructor
    Menu();
    ~Menu();
    
    virtual std::shared_ptr<SceneGraph> GetScene()
    {
        return menu;
    }
    
protected:
    std::shared_ptr<SceneGraph> menu;
};
