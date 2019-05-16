#pragma once

#include <stdio.h>
#include <IvVector3.h>
#include <IvVector2.h>
#include <map>
#include "../SceneManagement/SceneNode.hpp"
#include "../Car/CarController.hpp"

class InfoManager{
    
public:
    InfoManager(SceneNode* root);
    ~InfoManager();
    
    void Update(float dt);
    
private:
    
    //the root (good to search for objects)
    SceneNode* root;
    
    //the list of the cars
    std::vector<std::shared_ptr<SceneNode>> carsList;
    
    //data tables
    std::map<std::string, int> laps;
    std::map<std::string, int> checkpoints;
    std::map<std::string, int> score;
    std::map<std::string, float> lapTime;
    
    //road middle points
    std::vector<IvVector3> roadMiddlePoints;
    
    //timer
    float sinceStartTimer = 0.0f;
    
    //max distance to trigger the next checkpoint
    float checkpointTriggerDistance = 0.1f;
    
    //setters for tables
    void setLap(const std::string& carName, int lap);
    void setScore(const std::string& carName, int score);
    void setCheckpoint(const std::string& carName, int checkpoint);
    
    //getters for tables
    const int getLap(const std::string& carName) const;
    const int getCheckpoint(const std::string& carName) const;
    const int getScore(const std::string& carName) const;
    
    const float getCarSpeed(const std::string& carName) const;
    const float getTime() const;
    
    void updateCarStats();
};
