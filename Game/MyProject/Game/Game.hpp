//
//  Game.hpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/2/19.
//

#pragma once

#include"Player/Player.hpp"
#include"Test/TestCustomAttributes/Test.hpp"

#include <stdio.h>
#include<iostream>
#include<IvGame.h>
#include<IvRendererHelp.h>
#include<IvBezier.h>
#include<IvVector3.h>
#include<IvVertexFormats.h>

class Game:public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();
    
   // Player*         mPlayer;
    
    Test *test;
    
protected:
    virtual void UpdateObjects( float dt );
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );
};

