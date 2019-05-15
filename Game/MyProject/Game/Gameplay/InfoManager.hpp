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
    ~InfoManager(){};
    
    void Update(float dt);
    
private:
    
    //the root to search for everything
    SceneNode* root;
    
    //data tables
    std::map<std::string, int> laps;
    std::map<std::string, int> checkpoints;
    std::map<std::string, int> score;
    
    //road middle points
    std::vector<IvVector3> roadMiddlePoints;
    
    float time = 0.0f;
    float maxDistanceToCheckPoint = 0.01f;
    
    //setters for tables
    void setLap(const std::string& carName, int lap);
    void setScore(const std::string& carName, int score);
    void setCheckpoint(const std::string& carName, int checkpoint);
    
    //getters for tables
    const int getLap(const std::string& carName) const;
    const int getCheckpoint(const std::string& carName) const;
    const int getScore(const std::string& carName) const;
    
    
    const IvVector3& getCarSpeed(const std::string& carName) const;
    const float getTime() const;
};
