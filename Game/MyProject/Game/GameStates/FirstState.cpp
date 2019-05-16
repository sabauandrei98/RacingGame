//-------------------------------------------------------------------------------
//-- FirstState.cpp -------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

FirstState::FirstState(StateController* state_controller) :
GameState(state_controller) {
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void FirstState::onEnter() {
    std::cout << "FirstState enters" << std::endl;
    
    std::shared_ptr<FirstMenu> first=std::make_shared<FirstMenu>();
    state_controller->_main_scene=first->getScene();
}

void FirstState::onExit() {
    std::cout << "FirstState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void FirstState::Update(float dt) {
    if (isTestTriggered())
        state_controller->requestChange(Tests);
    
    if (isGameTriggered())
        state_controller->requestChange(Menu);
    
    if(isExitTriggered())
    {
        ResourceManager::resetResourceManager();
        IvGame::mGame->Quit();
    }
}

bool FirstState::isTestTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("test", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool FirstState::isGameTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("game", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool FirstState::isExitTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("exitFirst", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}


