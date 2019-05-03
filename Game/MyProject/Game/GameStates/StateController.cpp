//
//  StateController.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "StateController.hpp"

// -----------
// CONSTRUCTOR
// -----------

StateController::StateController() {
    _states.push_back(std::make_unique<MenuState>(this));
    _states.push_back(std::make_unique<TrackState>(this));
    _states.push_back(std::make_unique<SelectTrackState>(this));
    _states.push_back(std::make_unique<BuildTrackState>(this));
    _states.push_back(std::make_unique<SelectCarState>(this));
    _states.push_back(std::make_unique<RaceState>(this));
    _states.push_back(std::make_unique<HighScoreState>(this));
    _states.push_back(std::make_unique<CreditsState>(this));
    
    _current_state = Menu;
    _states[_current_state]->onEnter();
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

void StateController::update() {
    if (_state_changed) {
        _states[_old_state]->onExit();
        _states[_current_state]->onEnter();
        _state_changed = false;
    }
    
    _states[_current_state]->Update();
}

void StateController::requestChange(State state) {
    _old_state = _current_state;
    _current_state = state;
    _state_changed = true;
}
