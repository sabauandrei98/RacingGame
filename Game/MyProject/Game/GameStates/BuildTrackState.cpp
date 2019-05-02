//
//  BuildTrackState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

BuildTrackState::BuildTrackState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void BuildTrackState::onEnter() {
    std::cout << "BuildTrackState enters" << std::endl;
    std::cout << "Next: n\nBack: x" << std::endl;
}

void BuildTrackState::onExit() {
    std::cout << "BuildTrackState exits" << std::endl;
}

void BuildTrackState::Update() {
    if (isNextTriggered())
        state_controller->requestChange(SelectCar);
    
    if (isBackTriggered())
        state_controller->requestChange(Track);
}

bool BuildTrackState::isNextTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('n');
}

bool BuildTrackState::isBackTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('x');
}
