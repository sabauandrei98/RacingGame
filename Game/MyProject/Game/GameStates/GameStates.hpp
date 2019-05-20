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
#include "../BasicMenu/GameOver.hpp"
#include "../BasicMenu/FirstMenu.hpp"
#include "../BasicMenu/TestMenu.hpp"
#include "../RoadGenerator/RoadEditor.hpp"
#include "../RoadGenerator/RoadImporterExporter.hpp"

class StateController;

// ----------
// BASE CLASS
// ----------

class GameState {
public:
    // public function(s) and method(s)
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void Update(float dt) = 0;
    
    virtual void Render(SceneGraph* mainScene)
    {
        mainScene->drawScene();
    }
    
    bool rayIntersectsSceneNode(const char* name,unsigned int mousex,unsigned int mousey,const std::shared_ptr<SceneGraph>& mainScene)
    {
        RayBoxIntersection raybox(mainScene->getCamera()->getRay(mousex,mousey));
        auto nd = mainScene->getRoot()->findFirstNodeWithName(name);
        if(nd != nullptr && raybox.IsRayIntersectingBox(nd->getBoundingBox()))
            return true;
        return false;
    }
    
    bool rayIntersectsSceneNode(const std::shared_ptr<SceneNode>& node,unsigned int mousex,unsigned int mousey,const std::shared_ptr<SceneGraph>& mainScene)
    {
        RayBoxIntersection raybox(mainScene->getCamera()->getRay(mousex,mousey));
        if(node != nullptr && raybox.IsRayIntersectingBox(node->getBoundingBox()))
            return true;
        return false;
    }
    // constructor
    GameState(StateController* state_controller) :
        state_controller(state_controller) {
        }
    
    void saveFile(std::string configurerFile,std::string fileName)
    {
        std::ifstream fin(fileName);
        int noFiles;
        fin>>noFiles;
        
        std::vector<std::string> files;
        for(int i=0;i<noFiles;i++)
        {
            std::string fileName;
            fin>>fileName;
            files.push_back(fileName);
        }
        fin.close();
        
        noFiles++;
        std::ofstream fout(fileName);
        fout<<noFiles<<'\n';
        for(int i=0;i<files.size();i++)
            fout<<files[i]<<'\n';
        fout<<fileName<<'\n';
        
        fout.close();
    }
    std::vector<std::string> getFilesName(const std::string& configurerFile)
    {
        std::ifstream fin(configurerFile);
        int noFiles;
        fin>>noFiles;
        
        std::vector<std::string> files;
        for(int i=0;i<noFiles;i++)
        {
            std::string fileName;
            fin>>fileName;
            files.push_back(fileName);
        }
        fin.close();
        
        return files;
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
    void Update(float dt);
    
    
private:
    // private function(s)
    bool isPlayTriggered();
    bool isHighScoreTriggered();
    bool isCreditsTriggered();
    bool isExitTriggered();
    bool isBackTriggered();
};

class TrackState : public GameState {
public:
    // constructor
    TrackState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update(float dt);
    
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
    void Update(float dt);
    
private:
    std::unique_ptr<RoadEditor> roadEditor;
    
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
    void Update(float dt);
    
private:
    std::unique_ptr<RoadEditor> roadEditor;
    
    // private function(s)
    bool isPreviousTriggered();
    bool isNextTriggered();
    bool isGenerateTriggered();
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
    void Update(float dt);
    
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
    void Update(float dt);
    
private:
    // private function(s)
    bool isPauseTriggered();
    bool isGameOverTriggered();

    uint32_t score                  =   0;
    uint32_t frames                 =   0;
    
    std::shared_ptr<RaceMenu>           raceMenu;
    MeshManager                         meshManager;
    std::unique_ptr<RoadEditor>         roadEditor;
};

class HighScoreState : public GameState {
public:
    // constructor
    HighScoreState(StateController*);
    
    // public function(s) and method(s)
    void onEnter();
    void onExit();
    void Update(float dt);
    
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
    void Update(float dt);
    
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
    void Update(float dt);
    
private:
    // private function(s)
    bool isResumeTriggered();
};

class GameOverState:public GameState{
  
public:
    //constructor
    GameOverState(StateController*);
    
    //public functio(s) and method(s)
    void onEnter();
    void onExit();
    void Update(float dt);
    
private:
    //private function(s)
    bool isRetryTriggered();
    bool isQuitTriggered();
    
};

class FirstState:public GameState{
    
public:
    //constructor
    FirstState(StateController*);
    
    //public functio(s) and method(s)
    void onEnter();
    void onExit();
    void Update(float dt);
    
private:
    //private function(s)
    bool isTestTriggered();
    bool isGameTriggered();
    bool isExitTriggered();
    
};

class TestState:public GameState{
    
public:
    //constructor
    TestState(StateController*);
    
    //public functio(s) and method(s)
    void onEnter();
    void onExit();
    void Update(float dt);
    
private:
    //private function(s)
    bool isBackTriggered();
};

