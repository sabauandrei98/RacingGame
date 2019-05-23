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
    _states.push_back(std::make_unique<PauseState>(this));
    _states.push_back(std::make_unique<GameOverState>(this));
    _states.push_back(std::make_unique<TestState>(this));
    _states.push_back(std::make_unique<FirstState>(this));
    _states.push_back(std::make_unique<InfoState>(this));
    
    _current_state = First;
    _states[_current_state]->onEnter();
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

void StateController::update(float dt) {
    if (_state_changed) {
        if(_old_state==Race)
            _states[Info]->onExit();
        
        _states[_old_state]->onExit();
        _states[_current_state]->onEnter();
        _state_changed = false;
    }
    //scene update
    _main_scene->updateScene(dt);
   _states[_current_state]->Update(dt);
    
    //!!hack
    if(_current_state==Race && _gotInfoScene)
    {
        _info->updateScene(dt);
        _states[Info]->Update(dt);
    }
}

void StateController::render()
{
    _states[_current_state]->Render(_main_scene.get());
    
    //!
    IvRenderer::mRenderer->SetClearDepth(1.0);
    IvRenderer::mRenderer->ClearBuffers(kDepthClear);
    
    if(_current_state==Race && !_state_changed)
    {
        if(!_gotInfoScene)
        {
            auto keepScene=_main_scene;
            _states[Info]->onEnter();
            _gotInfoScene=true;
            _info= _main_scene;
            _main_scene=keepScene;
        }
        _states[Info]->Render(_info.get());
    }
}

void StateController::requestChange(State state) {
    _old_state = _current_state;
    _current_state = state;
    _state_changed = true;
}
