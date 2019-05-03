#pragma once

#include <stdio.h>
#include <iostream>
#include <IvGame.h>
#include <IvRendererHelp.h>
#include <IvBezier.h>
#include <IvVector3.h>
#include <IvVertexFormats.h>
#include <IvRendererOGL.h>
#include "SceneManagement/SceneGraph.hpp"
#include "SceneManagement/CameraSceneNode.hpp"
#include "BasicMenu/Menu.hpp"
#include "BasicMenu/Start.hpp"
#include "BasicMenu/Track.hpp"
#include "Player/Player.hpp"
#include "Test/TestRayBoxIntersection/TestCollision.hpp"

class CameraTestControler;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

    std::shared_ptr<Start>          startMenu;
    std::shared_ptr<Track>          trackMenu;

protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};
