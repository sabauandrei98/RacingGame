//
//  TrackState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

TrackState::TrackState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void TrackState::onEnter() {
    std::cout << "TrackState enters" << std::endl;
    std::cout << "Select: s\nBuild: b\nBack: x" << std::endl;
}

void TrackState::onExit() {
    std::cout << "TrackState exits" << std::endl;
}

void TrackState::Update() {
    if (isSelectTriggered())
        state_controller->requestChange(SelectTrack);
    
    if (isBuildTriggered())
        state_controller->requestChange(BuildTrack);
    
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool TrackState::isSelectTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('s');
}

bool TrackState::isBuildTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('b');
}

bool TrackState::isBackTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('x');
}

