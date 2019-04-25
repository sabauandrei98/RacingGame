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
    delete testCollision;
}

bool 
Game::PostRendererInitialize()
{
    // Set up base class
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    testCollision=new TestCollision();
    testCollision->TestRayBox();

    test=new TestHelper();
    
    ::IvSetDefaultLighting();
   
    return true;
}

void
Game::UpdateObjects( float dt )
{

    cameraTest->Update( dt );
    testCollision->Update(dt);
  
    test->Update(dt);
}
void
Game::Render()
{
    cameraTest->Render();
   
    testCollision->Render();
    
}

 
