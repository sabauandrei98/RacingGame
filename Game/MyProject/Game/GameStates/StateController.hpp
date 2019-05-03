//
//  StateController.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#pragma once

#include "GameStates.hpp"

class GameState;

// enumeration for states
enum State {
    Menu, Track, SelectTrack, BuildTrack, SelectCar, Race, HighScore, Credits
};

// state controller class
class StateController {
public:
    // constructor
    StateController();
    
    // public function(s) and method(s)
    void requestChange(State);
    void update();
    
private:
    // private variable(s)
    std::vector<std::unique_ptr<GameState>> _states;
    State                                   _current_state;
    State                                   _old_state;
    bool                                    _state_changed = false;
};
