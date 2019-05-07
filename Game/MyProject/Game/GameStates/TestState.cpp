//-------------------------------------------------------------------------------
//-- TestState.cpp -------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

TestState::TestState(StateController* state_controller) :
GameState(state_controller) {
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void TestState::onEnter() {
    std::cout << "TestState enters" << std::endl;
    
    std::shared_ptr<TestMenu> gameover=std::make_shared<TestMenu>();
    state_controller->_main_scene=gameover->getScene();
}

void TestState::onExit() {
    std::cout << "TestState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void TestState::Update() {
    if (isBackTriggered())
        state_controller->requestChange(First);
    
}

bool TestState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("backTest", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}



