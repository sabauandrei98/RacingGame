#include "Game.hpp"

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
    delete testBezier;
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
    

    ::IvSetDefaultLighting();
    
    testBezier = new TestBezier();

    return true;
}

void
Game::UpdateObjects( float dt )
{
    testBezier->Update( dt );
}
void
Game::Render()
{
    testBezier->Render();
}

