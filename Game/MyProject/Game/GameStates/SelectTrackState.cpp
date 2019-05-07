//
//  SelectTrackState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

SelectTrackState::SelectTrackState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void SelectTrackState::onEnter() {
    std::cout << "SelectTrackState enters" << std::endl;
    std::cout << "Next: n\nBack: x" << std::endl;
}

void SelectTrackState::onExit() {
    std::cout << "SelectTrackState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void SelectTrackState::Update() {
    if (isNextTriggered())
        state_controller->requestChange(SelectCar);
    
    if (isBackTriggered())
        state_controller->requestChange(Track);
}

bool SelectTrackState::isNextTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('n');
}

bool SelectTrackState::isBackTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('x');
}
