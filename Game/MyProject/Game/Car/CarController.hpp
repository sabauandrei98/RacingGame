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

class CarController :  public NodeAnimator{

//TODO:

//after more types of cars are added
//constructor parameters:
//forwardMaxSpeed  (necessary)
//carSpeedIncrement (necessary)
//nitroIncrement    (necessary)
//angleSpeedIncrement  (not necessary)
//turbineBoostSpeedLimit (not necessary)
    
    
public:
    CarController(){};
    ~CarController(){};
    
    const IvVector3& getVelocity() const;
    
private:
    
    //increments
    float carSpeedIncrement = 0.045f;
    float angleSpeedIncrement = 0.0075f * 4;
    float nitroIncrement = 0.20f;
    float turbineBoostIncrement = 0.15f;
    float directionChangeIncrement = 0.25f * 3;
    
    //coef
    float frictionCoefficient = 0.05f * 5;
    float brakeCoefficient = 0.060f * 5;
    
    //velocity
    float velocity = 0;
    float turbineBoostSpeedLimit = 20.0f;
    float forwardMaxSpeed = 30.0f;
    float backwardMaxSpeed = 20.0f;
    
    //angle
    float wheelAngle = 0;
    IvVector3 velocity_vector;
    void animateNode(float dt, SceneNode* car) override;
};
