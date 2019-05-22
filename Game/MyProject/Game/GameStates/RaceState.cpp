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
 
    roadEditor=std::make_unique<RoadEditor>(raceMenu->getScene().get());
    infoManager=std::make_unique<InfoManager>(raceMenu->getScene()->getRoot().get());
    
    RoadImporterExporter* roadImpExp=new RoadImporterExporter();
    roadImpExp->importFrom("roadDataTest.txt");
    
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("Road", roadImpExp->getMarginPoints(), 10);
    roadNode->setLocalTransform(IvVector3{0,-0.5,0}, IvVector3{3.144,0,0}, IvVector3{1,1,1});
    raceMenu->getScene()->getRoot()->addChild(roadNode);
    delete roadImpExp;
    
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
            int time=infoManager->getTime();
            raceMenu->renderText("timeTextRoot", "TIME");
            raceMenu->renderDigit("timeRoot",time);
            raceMenu->renderDigit("lapRoot",infoManager->getLap("Car"));
            raceMenu->renderDigit("lapTimeRoot",infoManager->getLapTime("Car", infoManager->getLap("Car")));

            raceMenu->renderDigit("scoreRoot",infoManager->getScore("Car"));
            raceMenu->renderDigit("checkpointRoot",infoManager->getCheckpoint("Car"));
            raceMenu->renderDigit("carSpeedRoot", infoManager->getCarSpeed("Car"));
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

