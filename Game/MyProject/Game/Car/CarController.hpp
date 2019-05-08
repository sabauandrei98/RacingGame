#pragma once

#include "IvGame.h"
#include <IvEventHandler.h>
#include <IvVector2.h>
#include <IvVector3.h>
#include "../SceneManagement/SceneNode.hpp"

class CarController : public NodeAnimator{
    
public:
    CarController(std::shared_ptr<SceneNode> car);
    ~CarController(){};
    
private:
    std::shared_ptr<SceneNode> car;
    
    //increments
    float carSpeedIncrement = 0.045f;
    float angleSpeedIncrement = 0.005f;
    float nitroIncrement = 30.0f;
    float turbineBoostIncrement = 0.25f;
    float directionChangeIncrement = 0.25f;
    
    //coef
    float frictionCoefficient = 0.05f;
    float brakeCoefficient = 0.060f;
    
    
    //velocity
    float velocity = 0;
    float turbineBoostSpeedLimit = 50.0f;
    float maxSpeed = 100.0f;
    
    //angle
    float wheelAngle = 0;

    
    void animateNode(float dt, SceneNode* car) override;
};
