//
//  HighScoreState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

HighScoreState::HighScoreState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void HighScoreState::onEnter() {
    std::cout << "HighScoreState enters" << std::endl;
    
    std::shared_ptr<HighscoresMenu> highscoresMenu=std::make_shared<HighscoresMenu>();
    state_controller->_main_scene=highscoresMenu->getScene();
}

void HighScoreState::onExit() {
    std::cout << "HighScoreState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void HighScoreState::Update() {
    if (isBackTriggered())
        state_controller->requestChange(Menu);
}

bool HighScoreState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey))
    {
        RayBoxIntersection raybox(state_controller->_main_scene->getCamera()->getRay(mousex,mousey));
        if(raybox.IsRayIntersectingBox(state_controller->_main_scene->getRoot()->getChild(0)->getBoundingBox()))
            return true;
    }
    return false;
}
