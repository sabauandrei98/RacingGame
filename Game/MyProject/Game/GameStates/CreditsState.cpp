//
//  CreditsState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

CreditsState::CreditsState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void CreditsState::onEnter() {
    std::cout << "CreditsState enters" << std::endl;
    
    std::shared_ptr<CreditsMenu> creditsMenu=std::make_shared<CreditsMenu>();
    state_controller->_main_scene=creditsMenu->GetScene();
}

void CreditsState::onExit() {
    std::cout << "CreditsState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void CreditsState::Update() {
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool CreditsState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->getChild(0)->getBoundingBox()))
            return true;
    }
    return false;
}
