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
    
    std::shared_ptr<SceneNode> car;
    
    float carSpeedIncrement = 0.045f;
    float angleSpeedIncrement = 0.005f;
    float fricitonCoefficient = 0.008f;
    float maxSpeed = 20.0f;
    float length = 0;
    float angle = 0;
    
    void animateNode(float dt, SceneNode* car) override;
};
