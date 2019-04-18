#pragma once

#include"Player/Player.hpp"
#include"Test/TestCustomAttributes/Test.hpp"
#include"Test/TestRenderTargets/TestRT.hpp"
#include"Test/TestHelper/TestHelper.hpp"

#include <stdio.h>
#include<iostream>
#include<IvGame.h>
#include<IvRendererHelp.h>
#include<IvBezier.h>
#include<IvVector3.h>
#include<IvVertexFormats.h>
#include<IvRendererOGL.h>
#include "CameraTestControler.hpp"


class CameraTestControler;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();
    
    TestHelper*                  test;
    CameraTestControler*         cameraTest;

protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};
