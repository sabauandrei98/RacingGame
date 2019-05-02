//
//  MenuState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

MenuState::MenuState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void MenuState::onEnter() {
    std::cout << "MenuState enters" << std::endl;
    std::cout << "Play: p\nHighScore: h\nCredits: c\nExit: e" << std::endl;
}

void MenuState::onExit() {
    std::cout << "MenuState exits" << std::endl;
}

void MenuState::Update() {
    if (isPlayTriggered())
        state_controller->requestChange(Track);
    
    if (isHighScoreTriggered())
        state_controller->requestChange(HighScore);
    
    if (isCreditsTriggered())
        state_controller->requestChange(Credits);
    
    if (isExitTriggered())
        IvGame::mGame->Quit();
}

bool MenuState::isPlayTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('p');
}

bool MenuState::isHighScoreTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('h');
}

bool MenuState::isCreditsTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('c');
}

bool MenuState::isExitTriggered() {
    return IvGame::mGame->mEventHandler->IsKeyDown('e');
}
