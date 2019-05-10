//
//  SelectCarState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

SelectCarState::SelectCarState(StateController* state_controller) :
GameState(state_controller) {
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void SelectCarState::onEnter() {
    std::cout << "SelectCarState enters" << std::endl;
    
    std::shared_ptr<CarMenu> carMenu=std::make_shared<CarMenu>();
    state_controller->_main_scene=carMenu->getScene();
}

void SelectCarState::onExit() {
    std::cout << "SelectCarState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void SelectCarState::Update() {
    if (isPlayTriggered())
        state_controller->requestChange(Race);
    
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool SelectCarState::isPlayTriggered() {    
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->getChild(0)->getBoundingBox()))
            return true;
    }
    return false;
}

bool SelectCarState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("backCar", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}
