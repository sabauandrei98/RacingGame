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
    
    startMenu=std::make_shared<Start>();
    //trackMenu=std::make_shared<Track>();
    
    ::IvSetDefaultLighting();
   
  
    return true;
}

void
Game::UpdateObjects( float dt )
{
    startMenu->Update(dt);
   //trackMenu->Update(dt);
}
void
Game::Render()
{
    startMenu->Render();
 //   trackMenu->Render();
}

 
