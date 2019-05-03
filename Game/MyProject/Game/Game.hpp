#pragma once

#include "BasicMenu/Menu.hpp"
#include "BasicMenu/Start.hpp"
#include "BasicMenu/Track.hpp"
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

    std::shared_ptr<Start>          startMenu;
    std::shared_ptr<Track>          trackMenu;


protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};
