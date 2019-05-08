#pragma once

#include "IvGame.h"
#include <IvEventHandler.h>
#include <IvVector2.h>
#include <IvVector3.h>
#include "../SceneManagement/SceneNode.hpp"
#include <iostream>

//INPUT:
//W, A, S, D - directions
//SPACE - brake
//N - nitro

//disable other key bindings

class CarController : public NodeAnimator{

//TODO:

//after more types of cars are added
//constructor parameters:
//forwardMaxSpeed  (necessary)
//carSpeedIncrement (necessary)
//nitroIncrement    (necessary)
//angleSpeedIncrement  (not necessary)
//turbineBoostSpeedLimit (not necessary)
    
    
public:
    CarController(std::shared_ptr<SceneNode> car) : car(car) {};
    ~CarController(){};
    
private:
    std::shared_ptr<SceneNode> car;
    
    //increments
    float carSpeedIncrement = 0.045f;
    float angleSpeedIncrement = 0.0075f;
    float nitroIncrement = 0.20f;
    float turbineBoostIncrement = 0.25f;
    float directionChangeIncrement = 0.25f;
    
    //coef
    float frictionCoefficient = 0.05f;
    float brakeCoefficient = 0.060f;
    
    //velocity
    float velocity = 0;
    float turbineBoostSpeedLimit = 50.0f;
    float forwardMaxSpeed = 150.0f;
    float backwardMaxSpeed = 50.0f;
    
    //angle
    float wheelAngle = 0;

    void animateNode(float dt, SceneNode* car) override;
};
