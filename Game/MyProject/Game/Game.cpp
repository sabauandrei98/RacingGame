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
    //mPlayer=new Player();
    test=new TestRT();
}
Game::~Game()
{
    //delete mPlayer;
    delete test;
}
bool Game::PostRendererInitialize()
{
    
    IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);
    IvRendererOGL::mRenderer->SetDepthWrite(false);
    IvRendererOGL::mRenderer->SetDepthTest(kDisableDepthTest);
    
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    test->Create();
    test->Setup();
    
    ::IvSetDefaultLighting();
    
    return true;
}

void Game::UpdateObjects( float dt )
{
    
}

void Game::Render()
{
//    IvSetDefaultViewer(-10.0,-10.0,10.0);
//    IvDrawTeapot();
    test->Draw();
}
