//-------------------------------------------------------------------------------
//-- PauseState.cpp -------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

PauseState::PauseState(StateController* state_controller) :
GameState(state_controller) {
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void PauseState::onEnter() {
    std::cout << "PauseState enters" << std::endl;
    
    std::shared_ptr<PauseMenu> pauseMenu=std::make_shared<PauseMenu>();
    state_controller->_main_scene=pauseMenu->getScene();
}

void PauseState::onExit() {
    std::cout << "PauseState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void PauseState::Update() {
    if(isResumeTriggered())
        state_controller->requestChange(Race);
}

bool PauseState::isResumeTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("resumePause", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}


