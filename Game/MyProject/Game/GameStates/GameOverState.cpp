//-------------------------------------------------------------------------------
//-- GameOverState.cpp ----------------------------------------------------------
//-------------------------------------------------------------------------------
#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

GameOverState::GameOverState(StateController* state_controller) :
GameState(state_controller) {
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void GameOverState::onEnter() {
    std::cout << "GameOverState enters" << std::endl;
    
    std::shared_ptr<GameOver> gameover=std::make_shared<GameOver>();
    state_controller->_main_scene=gameover->getScene();
}

void GameOverState::onExit() {
    std::cout << "GameOverState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void GameOverState::Update() {
    if (isQuitTriggered())
        state_controller->requestChange(Menu);
    
    if (isRetryTriggered())
        state_controller->requestChange(Race);
}

bool GameOverState::isRetryTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->getChild(0)->getBoundingBox()))
            return true;
    }
    return false;
}

bool GameOverState::isQuitTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->getChild(1)->getBoundingBox()))
            return true;
    }
    return false;
}

