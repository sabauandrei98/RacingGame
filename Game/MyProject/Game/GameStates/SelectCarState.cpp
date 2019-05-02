//
//  SelectCarState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

SelectCarState::SelectCarState(StateController* state_controller) :
GameState(state_controller) {
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void SelectCarState::onEnter() {
    std::cout << "SelectCarState enters" << std::endl;
    std::cout << "Play: p\nBack: x" << std::endl;
}

void SelectCarState::onExit() {
    std::cout << "SelectCarState exits" << std::endl;
}

void SelectCarState::Update() {
    if (isPlayTriggered())
        state_controller->requestChange(Race);
    
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool SelectCarState::isPlayTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('p');
}

bool SelectCarState::isBackTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('x');
}
