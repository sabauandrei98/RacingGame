//
//  GameState.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#pragma once

#include <iostream>

#include "../Game.hpp"
#include "../RayBoxIntersection/RayBoxIntersection.hpp"
#include "../BasicMenu/Menu.hpp"
#include "../BasicMenu/StartMenu.hpp"
#include "../BasicMenu/TrackMenu.hpp"
#include "../BasicMenu/ChooseTrackMenu.hpp"
#include "../BasicMenu/BuildTrackMenu.hpp"
#include "../BasicMenu/CreditsMenu.hpp"
#include "../BasicMenu/RaceMenu.hpp"
#include "../BasicMenu/CarMenu.hpp"
#include "../BasicMenu/HighscoresMenu.hpp"
#include "../BasicMenu/PauseMenu.hpp"

class StateController;

// ----------
// BASE CLASS
// ----------

class GameState {
public:
    // public function(s) and method(s)
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void Update() = 0;
    
    virtual void Render(SceneGraph* main_scene)
    {
        main_scene->drawScene();
    }
    
    // constructor
    GameState(StateController* state_controller) :
        state_controller(state_controller) {
        }
    virtual ~GameState(){}
    
protected:
    // protected variable(s)
    StateController*    state_controller;
};

// ---------------
// DERIVED CLASSES
// ---------------

class MenuState : public GameState {
public:
    // constructor
    MenuState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
    
private:
    // private function(s)
    bool isPlayTriggered();
    bool isHighScoreTriggered();
    bool isCreditsTriggered();
    bool isExitTriggered();
};

class TrackState : public GameState {
public:
    // constructor
    TrackState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isSelectTriggered();
    bool isBuildTriggered();
    bool isBackTriggered();
};

class SelectTrackState : public GameState {
public:
    // constructor
    SelectTrackState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isNextTriggered();
    bool isBackTriggered();
};

class BuildTrackState : public GameState {
public:
    // constructor
    BuildTrackState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isAddTriggered();
    bool isRemoveTriggered();
    bool isPlayTriggered();
    bool isSaveTriggered();
    bool isBackTriggered();
};

class SelectCarState : public GameState {
public:
    // constructor
    SelectCarState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isPlayTriggered();
    bool isBackTriggered();
};

class RaceState : public GameState {
public:
    // constructor
    RaceState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isPauseTriggered();
    
    
    std::shared_ptr<RaceMenu>           raceMenu;
};

class HighScoreState : public GameState {
public:
    // constructor
    HighScoreState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isBackTriggered();
};

class CreditsState : public GameState {
public:
    // constructor
    CreditsState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isBackTriggered();
};


class PauseState : public GameState{
public:
    // constructor
    PauseState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update();
    
private:
    // private function(s)
    bool isResumeTriggered();
    bool isQuitTriggered();
};

