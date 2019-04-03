//
//  Game.cpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/2/19.
//

#include "Game.hpp"

bool IvGame::Create()
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
    
}
Game::Game()
{
    mPlayer=new Player();
    test=new Test();
}
Game::~Game()
{
    delete mPlayer;
    delete test;
}
bool Game::PostRendererInitialize()
{
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    test->setup("testShader");
    
    ::IvSetDefaultLighting();
    
    return true;
}

void Game::UpdateObjects( float dt )
{
    mPlayer->Update(dt);
}

void Game::Render()
{
   // mPlayer->Render();
    test->Draw();
}
