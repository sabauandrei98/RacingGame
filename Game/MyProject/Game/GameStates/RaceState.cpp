//
//  RaceState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

RaceState::RaceState(StateController* state_controller) :
    GameState(state_controller) {
        meshManager=MeshManager();
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void RaceState::onEnter() {
    std::cout << "RaceState enters" << std::endl;
    std::cout << "Pause: x" << std::endl;
    
    raceMenu=std::make_shared<RaceMenu>();
    state_controller->_main_scene=raceMenu->getScene();
    infoManager=std::make_unique<InfoManager>(raceMenu->getScene()->getRoot().get());
}

void RaceState::onExit() {
    std::cout << "RaceState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void RaceState::Update(float dt) {
    infoManager->Update(dt);
    
    if(isPauseTriggered())
        state_controller->requestChange(Pause);
    else
        if(isGameOverTriggered())
        {
            state_controller->requestChange(GOver);
        }
        else
        {
            raceMenu->renderText("timeTextRoot", "TIME");
            raceMenu->renderText("carSpeedTextRoot", "SPEED");
            raceMenu->renderText("scoreTextRoot", "SCORE");
            raceMenu->renderText("lapTimeTextRoot", "LAPTIME");
            raceMenu->renderText("checkpointTextRoot", "CHECKPOINT");
            raceMenu->renderText("lapTextRoot", "LAP");
            
            
            raceMenu->renderDigit("timeRoot",(int)infoManager->getTime());
            raceMenu->renderDigit("lapRoot",infoManager->getLap("Car"));
            raceMenu->renderDigit("lapTimeRoot",infoManager->getLapTime("Car", infoManager->getLap("Car")));
            raceMenu->renderDigit("scoreRoot",infoManager->getScore("Car"));
            raceMenu->renderDigit("checkpointRoot",infoManager->getCheckpoint("Car"));
            int speed = infoManager->getCarSpeed("Car");
            if(speed<0)
                speed*=-1;
            raceMenu->renderDigit("carSpeedRoot", speed);
        }
}   
    
bool RaceState::isPauseTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('x');
}

bool RaceState::isGameOverTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('q');
}

