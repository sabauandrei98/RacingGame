//
//  RaceState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

RaceState::RaceState(StateController* state_controller) :
    GameState(state_controller) {
        meshManager=MeshManager();
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void RaceState::onEnter() {
    std::cout << "RaceState enters" << std::endl;
    std::cout << "Pause: x" << std::endl;
    
    raceMenu=std::make_shared<RaceMenu>();
    state_controller->_main_scene=raceMenu->getScene();
}

void RaceState::onExit() {
    std::cout << "RaceState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void RaceState::Update(float dt) {
    if(isPauseTriggered())
        state_controller->requestChange(Pause);
    else
        if(isGameOverTriggered())
        {
            state_controller->requestChange(GOver);
        }
}   
    
bool RaceState::isPauseTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('x');
}

bool RaceState::isGameOverTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('q');
}

