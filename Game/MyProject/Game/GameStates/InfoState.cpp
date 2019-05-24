//-------------------------------------------------------------------------------
//-- InfoState.cpp --------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

InfoState::InfoState(StateController* state_controller):GameState(state_controller)
{
    //infoScene=std::make_shared<InfoMenu>();
}

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------
void InfoState::onEnter() {
    std::cout << "InfoState enters" << std::endl;
    infoMenu=std::make_shared<InfoMenu>();
    infoManager=std::make_unique<InfoManager>(state_controller->_main_scene->getRoot().get());
    state_controller->_main_scene=infoMenu->getScene();
}

void InfoState::onExit() {
    std::cout << "InfoState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void
InfoState::Update(float dt)
{
    infoManager->Update(dt);
    infoMenu->renderText("timeTextRoot", "TIME");
    infoMenu->renderText("carSpeedTextRoot", "SPEED");
    infoMenu->renderText("scoreTextRoot", "SCORE");
    infoMenu->renderText("checkpointTextRoot", "CHECKPOINT");
    infoMenu->renderText("lapTextRoot", "LAP");

    infoMenu->renderDigit("timeRoot",(int)infoManager->getTime());
    infoMenu->renderDigit("lapRoot",infoManager->getLap("Car"));
    infoMenu->renderDigit("scoreRoot",infoManager->getScore("Car"));
    infoMenu->renderDigit("checkpointRoot",infoManager->getCheckpoint("Car"));
    infoMenu->renderDigit("carSpeedRoot",infoManager->getCarSpeed("Car"));
}

