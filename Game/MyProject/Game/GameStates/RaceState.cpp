//
//  RaceState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

RaceState::RaceState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void RaceState::onEnter() {
    std::cout << "RaceState enters" << std::endl;
    std::cout << "Quit: q" << std::endl;
}

void RaceState::onExit() {
    std::cout << "RaceState exits" << std::endl;
}

void RaceState::Update() {
    if (isQuitTriggered())
        state_controller->requestChange(Menu);
}

bool RaceState::isQuitTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('q');
}
