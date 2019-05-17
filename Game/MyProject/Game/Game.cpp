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
    // Set up base class
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    menu=std::make_shared<StateController>();
    
    ::IvSetDefaultLighting();
  
    return true;
}

void
Game::UpdateObjects( float dt )
{
    menu->update(dt);
}
void
Game::Render()
{
<<<<<<< HEAD
    _state_controller->render();
    //IvDrawLine({50,20,20}, {40,40,40},kRed);
=======
    menu->render();
>>>>>>> master
}

 
