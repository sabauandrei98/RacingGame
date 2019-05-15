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
    
    SceneNode* root;
    std::map<std::string, int> laps;
    std::map<std::string, int> checkpoints;
    std::map<std::string, int> score;
    float time = 0.;
    
    void setLap(const std::string& carName, int lap);
    void setScore(const std::string& carName, int score);
    void setCheckpoint(const std::string& carName, int checkpoint);
    
    const int getLap(const std::string& carName) const;
    const int getCheckpoint(const std::string& carName) const;
    const int getScore(const std::string& carName) const;
    const IvVector3& getCarSpeed(const std::string& carName) const;
    const float getTime() const;
};
