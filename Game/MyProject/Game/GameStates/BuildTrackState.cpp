//
//  BuildTrackState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

BuildTrackState::BuildTrackState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void BuildTrackState::onEnter() {
    std::cout << "BuildTrackState enters" << std::endl;
    
    std::shared_ptr<BuildTrackMenu> buildTrack=std::make_shared<BuildTrackMenu>();
    state_controller->_main_scene=buildTrack->getScene();
    
    roadEditor=std::make_unique<RoadEditor>(buildTrack->getScene().get());
}

void BuildTrackState::onExit() {
    std::cout << "BuildTrackState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void BuildTrackState::Update(float dt) {
    static int i=0;
    roadEditor->Update(dt);
    
    if (isPlayTriggered())
    {
        RoadImporterExporter roadImpExp;
        std::string name="roadData.txt";
        if(roadEditor->getMarginPoints().size()!=0)
            roadImpExp.exportTo(roadEditor->getMarginPoints(), name);
        state_controller->requestChange(SelectCar);
    }
    if (isAddTriggered())
        roadEditor->getRoadGenerator()->addPoint();
    
    if(isRemoveTriggered())
        roadEditor->getRoadGenerator()->removePoint();
    
    if(isSaveTriggered())
    {
        RoadImporterExporter roadImpExp;
        std::string name="roadData"+std::to_string(i)+".txt";
        roadImpExp.exportTo(roadEditor->getMarginPoints(), name);
        i++;
        saveFile("manageFiles.txt",name);
    }
    
    if(isPreviousTriggered())
        roadEditor->getRoadGenerator()->previousPoint();
    
    if(isNextTriggered())
        roadEditor->getRoadGenerator()->nextPoint();
    
    if(isGenerateTriggered())
        roadEditor->generateTexturedRoad();
    
    if (isBackTriggered())
        state_controller->requestChange(Track);
}

bool BuildTrackState::isNextTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("nextTrack", mousex, mousey, state_controller->_main_scene))
            return true;
    return false;
}

bool BuildTrackState::isPreviousTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("previousTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool BuildTrackState::isGenerateTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("generateTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool BuildTrackState::isAddTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("addTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool BuildTrackState::isRemoveTriggered(){
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("removeTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool BuildTrackState::isPlayTriggered(){
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("playTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool BuildTrackState::isSaveTriggered(){
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("saveTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

bool BuildTrackState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("backTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}


