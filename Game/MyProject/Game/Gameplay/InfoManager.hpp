#pragma once

#include <stdio.h>
#include <IvVector3.h>
#include <IvVector2.h>
#include <map>
#include "../SceneManagement/SceneNode.hpp"
#include "../Car/CarController.hpp"

//Manager supports more than one player

class InfoManager{
    
public:
    InfoManager(SceneNode* root);
    ~InfoManager();
    
    void Update(float dt);
    
private:
    
    float sinceStartTimer = 0.0f;
    
    //range to trigger next checkpoint
    float checkpointTriggerDistance = 0.5f;
    
    //the root (good to search for objects)
    SceneNode* root;
    
    std::vector<SceneNode*> carsList;
    std::vector<IvVector3> roadMiddlePoints;
    
    //data tables
    std::map<std::string, int> laps;
    std::map<std::string, int> checkpoints;
    std::map<std::string, int> score;
    std::map<std::string, float> lapTime;
    
    void setLap(const std::string& carName, int lap);
    void setScore(const std::string& carName, int score);
    void setCheckpoint(const std::string& carName, int checkpoint);
    
    const int getLap(const std::string& carName) const;
    const int getCheckpoint(const std::string& carName) const;
    const int getScore(const std::string& carName) const;
    const float getCarSpeed(const std::string& carName) const;
    const float getTime() const;
    
    void updateCarStats();
};
