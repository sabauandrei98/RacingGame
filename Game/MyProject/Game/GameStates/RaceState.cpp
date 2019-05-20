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
        score=0;
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

    RoadImporterExporter* roadImpExp=new RoadImporterExporter();
    roadImpExp->importFrom("roadDataTest.txt");
    
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("Road", roadImpExp->getMarginPoints());
    roadNode->setLocalTransform(IvVector3{0,-0.5,0}, IvVector3{3.144,0,0}, IvVector3{12,12,12});
    raceMenu->getScene()->getRoot()->addChild(roadNode);
    delete roadImpExp;
    
}

void RaceState::onExit() {
    std::cout << "RaceState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void RaceState::Update(float dt) {
    
//   roadEditor->Update(dt);
    if(isPauseTriggered())
        state_controller->requestChange(Pause);
    else
        if(isGameOverTriggered())
        {
            frames=0;
            score=0;
            state_controller->requestChange(GOver);
        }
        else
        {
            frames++;
            if(frames==10)
            {
                frames=0;
                raceMenu->renderNo(score);
                score++;
             }
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

