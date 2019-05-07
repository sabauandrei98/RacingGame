//
//  MenuState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

MenuState::MenuState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void MenuState::onEnter() {
    std::cout << "MenuState enters" << std::endl;
    
    std::shared_ptr<StartMenu> startScene=std::make_shared<StartMenu>();
    state_controller->_main_scene=startScene->getScene();
    
}

void MenuState::onExit() {
    std::cout << "MenuState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void MenuState::Update() {
    
    if (isPlayTriggered())
        state_controller->requestChange(Track);
    
    if (isHighScoreTriggered())
        state_controller->requestChange(HighScore);
    
    if (isCreditsTriggered())
        state_controller->requestChange(Credits);
    
    if(isBackTriggered())
        state_controller->requestChange(First);
    
    if (isExitTriggered())
    {
        ResourceManager::resetResourceManager();
        IvGame::mGame->Quit();
    }
    
   
}

bool MenuState::isPlayTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->findFirstNodeWithName("playStart")->getBoundingBox()))
            return true;
    }
    return false;
}

bool MenuState::isHighScoreTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->findFirstNodeWithName("highscoreStart")->getBoundingBox()))
            return true;
    }
    return false;
}

bool MenuState::isCreditsTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->findFirstNodeWithName("creditsStart")->getBoundingBox()))
            return true;
    }
    return false;
}

bool MenuState::isExitTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->findFirstNodeWithName("exitStart")->getBoundingBox()))
            return true;
    }
    return false;
}

bool MenuState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->findFirstNodeWithName("backStart")->getBoundingBox()))
            return true;
    }
    return false;
}