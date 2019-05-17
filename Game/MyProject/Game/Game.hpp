#pragma once

#include "BasicMenu/StartMenu.hpp"
#include "BasicMenu/TrackMenu.hpp"
#include "Player/Player.hpp"
#include <stdio.h>
#include <iostream>
#include <IvGame.h>
#include <IvRendererHelp.h>
#include <IvBezier.h>
#include <IvVector3.h>
#include <IvVertexFormats.h>
#include <IvRendererOGL.h>
#include "CameraTestControler.hpp"
#include "SceneManagement/SceneGraph.hpp"
#include "SceneManagement/CameraSceneNode.hpp"
#include "ModelLoader/ModelLoader.hpp"
#include "SceneManagement/CarAnimator.hpp"
#include "SceneManagement/CameraFollowAnimator.hpp"
#include "GameStates/StateController.hpp"

#include "RoadGenerator/RoadEditor.hpp"
#include "Car/CarController.hpp"


class CameraTestControler;
class StateController;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );
    
    std::shared_ptr<StateController> menu;
};
