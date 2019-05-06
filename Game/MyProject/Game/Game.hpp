#pragma once

#include "BasicMenu/StartMenu.hpp"
#include "BasicMenu/TrackMenu.hpp"
#include "Player/Player.hpp"
#include "Test/TestRayBoxIntersection/TestCollision.hpp"
#include "GameStates/StateController.hpp"

class CameraTestControler;
class StateController;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

    std::shared_ptr<StartMenu>          startMenu;
    //std::shared_ptr<TrackMenu>          trackMenu;

    std::unique_ptr<StateController>    _state_controller;

protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};
