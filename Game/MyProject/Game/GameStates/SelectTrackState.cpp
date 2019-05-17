//
//  SelectTrackState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

SelectTrackState::SelectTrackState(StateController* state_controller) :
    GameState(state_controller) {
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------

void SelectTrackState::onEnter() {
    std::cout << "SelectTrackState enters" << std::endl;
    
    std::shared_ptr<ChooseTrackMenu> selectTrackMenu=std::make_shared<ChooseTrackMenu>();
    state_controller->_main_scene=selectTrackMenu->getScene();
    
    RoadImporterExporter roadImpExp;
    
    std::vector<std::string> files=getFilesName("manageFiles.txt");
    
    for(int i=0;i<files.size();i++)
    {
        roadImpExp.importFrom(files[i]);
        std::vector<std::pair<IvVector3,IvVector3>> marginPoints;
        marginPoints=roadImpExp.getMarginPoints();
        
        roadEditor=std::make_unique<RoadEditor>(selectTrackMenu->getScene().get());
        roadEditor->setMarginPoints(marginPoints);
        roadEditor->generateTexturedRoad();
        roadEditor->setLocalTransform({i*9.0f,0,i*3.0f}, {0,0,0}, {0.5,0.5,0.5});
    }
}

void SelectTrackState::onExit() {
    std::cout << "SelectTrackState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void SelectTrackState::Update(float dt) {
    if (isNextTriggered())
        state_controller->requestChange(SelectCar);
    
    if (isBackTriggered())
        state_controller->requestChange(Track);
}

bool SelectTrackState::isNextTriggered() {
    std::vector<std::shared_ptr<SceneNode>> nodes;
    state_controller->_main_scene->getRoot()->findAllNodesWithName("roadNode", nodes);
    int index=0;
    unsigned int mousex,mousey;
    while(index<nodes.size())
    {
        if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode(nodes[index], mousex,  mousey,state_controller->_main_scene))
        {
            RoadImporterExporter roadImpExp;
            roadImpExp.exportTo(roadEditor->getMarginPoints(), "roadData.txt");
            return true;
        }
        index++;
    }
    return false;
}

bool SelectTrackState::isBackTriggered() {
    unsigned int mousex,mousey;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mousex,mousey) && rayIntersectsSceneNode("backChooseTrack", mousex, mousey, state_controller->_main_scene))
        return true;
    return false;
}

