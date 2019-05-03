//
//  GameState.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#pragma once

#include <iostream>

#include "../Game.hpp"

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
    
    // constructor
    GameState(StateController* state_controller) :
        state_controller(state_controller) {
        }
    
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
    bool isNextTriggered();
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
    bool isQuitTriggered();
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
