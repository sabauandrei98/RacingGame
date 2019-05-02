//
//  CreditsState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

CreditsState::CreditsState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void CreditsState::onEnter() {
    std::cout << "CreditsState enters" << std::endl;
    std::cout << "Back: x" << std::endl;
}

void CreditsState::onExit() {
    std::cout << "CreditsState exits" << std::endl;
}

void CreditsState::Update() {
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool CreditsState::isBackTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('x');
}
