#pragma once

#include <IvGame.h>
#include <IvRendererHelp.h>
#include "CameraTestControler.hpp"


class CameraTestControler;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

    CameraTestControler*         cameraTest;

protected:
    virtual void UpdateObjects( float dt );
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};