//
//  HighScoreState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

HighScoreState::HighScoreState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void HighScoreState::onEnter() {
    std::cout << "HighScoreState enters" << std::endl;
    std::cout << "Back: x" << std::endl;
}

void HighScoreState::onExit() {
    std::cout << "HighScoreState exits" << std::endl;
}

void HighScoreState::Update() {
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool HighScoreState::isBackTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('x');
}
