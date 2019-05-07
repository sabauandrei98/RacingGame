#include "CarController.hpp"

void CarController::animateNode(float dt, SceneNode* car)
{
    bool hasAcceleration = false;
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        length += carSpeedIncrement;
        hasAcceleration = true;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        length -= carSpeedIncrement;
        hasAcceleration = true;
    }
    
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            angle += angleSpeedIncrement;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            angle -= angleSpeedIncrement;
        }
    }
    else
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            angle -= angleSpeedIncrement;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            angle += angleSpeedIncrement;
        }
    }
   
        
    
    if (length > maxSpeed)
        length = maxSpeed;
    
    if (length < -maxSpeed)
        length = -maxSpeed;
    
    if (!hasAcceleration)
    {
        if(length > 0)
            length -= fricitonCoefficient;
        else
            length += fricitonCoefficient;
    }
    
    IvVector2 carVelocity;
    carVelocity.x = length * (sin(angle));
    carVelocity.y = length * (cos(angle));
    
    
    IvVector2 carPosition;
    carPosition.x += carVelocity.x * dt;
    carPosition.y += carVelocity.y * dt;
    
    IvVector3 carPos = car->getLocalPosition();
    carPos.x += carPosition.x;
    carPos.z += carPosition.y;
    car->setLocalTransform(carPos, {0,angle,0}, {4,4,4});

    
}

CarController::CarController(std::shared_ptr<SceneNode> car) : car(car) {
    
}

