#pragma once

#include <stdio.h>
#include <IvVector3.h>
#include <IvVector2.h>
#include <unordered_map>
#include "../SceneManagement/SceneNode.hpp"
#include "../SceneManagement/RoadNode.hpp"
#include "../Car/CarController.hpp"

//Manager supports more than one player

class InfoManager{
    
public:
    InfoManager(SceneNode* root);
    ~InfoManager();
    
    void Update(float dt);
    
    const int getLap(const std::string& carName) const;
    const int getCheckpoint(const std::string& carName) const;
    const int getScore(const std::string& carName) const;
    const float getLapTime(const std::string& carName, int lap) const;
    const float getCarSpeed(const std::string& carName) const;
    const float getTime() const;
private:
    
    float sinceStartTimer = 0.0f;
    
    //range to trigger next checkpoint
    float checkpointTriggerDistance = 3.0f;
    
    //the root (good to search for objects)
    SceneNode* root;
    
    std::vector<SceneNode*> carsList;
    std::vector<IvVector3> roadMiddlePoints;
    
    struct CarProps {
        int laps;
        int checkpoints;
        int score;
        std::vector<float> lapTime;
    };
    std::unordered_map<std::string, CarProps> carsData;
    
    void setLap(const std::string& carName, int lap);
    void setScore(const std::string& carName, int score);
    void setCheckpoint(const std::string& carName, int checkpoint);
    void setLapTime(const std::string& carName, int lap, float time);
    
    void updateCarStats();
};
