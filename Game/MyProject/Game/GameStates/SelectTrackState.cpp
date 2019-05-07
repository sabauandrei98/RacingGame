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
    
    std::shared_ptr<ChooseTrackMenu> selectTrackMenu=std::make_shared<ChooseTrackMenu>();
    state_controller->_main_scene=selectTrackMenu->getScene();
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
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->findFirstNodeWithName("backCar")->getBoundingBox()))
            return true;
    }
    return false;
}
