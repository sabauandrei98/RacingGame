//
//  StateController.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#pragma once

#include "GameStates.hpp"
#include "../BasicMenu/InfoMenu.hpp"

class GameState;

// enumeration for states
enum State {
    Menu, Track, SelectTrack, BuildTrack, SelectCar, Race, HighScore, Credits,Pause,GOver,Tests,First,Info
};

// state controller class
class StateController {
public:
    // constructor
    StateController();
    
    // public function(s) and method(s)
    void requestChange(State);
    void update(float dt);
    void render();
    
    friend class MenuState;
    friend class TrackState;
    friend class SelectTrackState;
    friend class BuildTrackState;
    friend class CreditsState;
    friend class HighScoreState;
    friend class SelectCarState;
    friend class RaceState;
    friend class PauseState;
    friend class GameOverState;
    friend class TestState;
    friend class FirstState;
    friend class GameState;
    friend class InfoState;
    
private:
    // private variable(s)
    std::vector<std::unique_ptr<GameState>> _states;
    State                                   _current_state;
    State                                   _old_state;
    bool                                    _state_changed = false;
    
    std::shared_ptr<SceneGraph>             _info;
    bool                                    _gotInfoScene = false;
    
protected:
    std::shared_ptr<SceneGraph>             _main_scene;
};
