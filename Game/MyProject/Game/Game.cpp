#include "Game.hpp"
#include "Helper/HelperRender.h"
bool
IvGame::Create() 
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}

Game::Game() : IvGame()
{
  
}

Game::~Game()
{
    delete cameraTest;
}


bool 
Game::PostRendererInitialize()
{
    IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);
    IvRendererOGL::mRenderer->SetDepthWrite(true);
    IvRendererOGL::mRenderer->SetDepthTest(kLessEqualDepthTest);
    
    // Set up base class 
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    cameraTest = new CameraTestControler();
    if (!cameraTest)
        return false;

    ::IvSetDefaultLighting();

    return true;
}

void
Game::UpdateObjects( float dt )
{
    cameraTest->Update( dt );
}
void
Game::Render()
{
    cameraTest->Render();
    HelperRender::DrawBox();
}

