//
//  TrackState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

TrackState::TrackState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void TrackState::onEnter() {
    std::cout << "TrackState enters" << std::endl;
   
    std::shared_ptr<TrackMenu> trackScene=std::make_shared<TrackMenu>();
    state_controller->_main_scene=trackScene->getScene();
}

void TrackState::onExit() {
    std::cout << "TrackState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void TrackState::Update(float dt) {
    if (isSelectTriggered())
        state_controller->requestChange(SelectTrack);
    
    if (isBuildTriggered())
        state_controller->requestChange(BuildTrack);
    
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool TrackState::isSelectTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("chooseTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool TrackState::isBuildTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("buildTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool TrackState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("backTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

