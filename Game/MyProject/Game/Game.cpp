//
//  Game.cpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/2/19.
//

#include "Game.hpp"

bool IvGame::Create() {
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}

Game::Game() : IvGame() {
    
}

Game::~Game() {
    
}

bool Game::PostRendererInitialize() {
    if (!IvGame::PostRendererInitialize())
        return false;
    
    ::IvSetDefaultLighting();
    return true;
}

void Game::UpdateObjects(float dt) {
    
}

void Game::Render() {
    IvSetDefaultViewer(10.0f, 10.0f, 10.0f);
    IvDrawAxes();
}
