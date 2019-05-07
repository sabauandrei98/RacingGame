#include "CarController.hpp"

void CarController::animateNode(float dt, SceneNode* car)
{
    bool hasAcceleration = false;
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        velocity += carSpeedIncrement;
        
        if (velocity < 0)
            velocity += carSpeedIncrement;
        
        hasAcceleration = true;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        velocity -= carSpeedIncrement;
        
        if (velocity > 0)
            velocity -= carSpeedIncrement;
        
        hasAcceleration = true;
    }
    
    
    float coef = abs(velocity/maxSpeed);
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            angle += angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            angle -= angleSpeedIncrement * coef;
        }
    }
    else
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            angle -= angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            angle += angleSpeedIncrement * coef;
        }
    }
    else
    if (velocity < 0)
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            angle -= angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            angle += angleSpeedIncrement * coef;
        }
    }
    else
    if (velocity > 0)
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            angle += angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            angle -= angleSpeedIncrement * coef;
        }
    }
    
 
    if (IvGame::mGame->mEventHandler->IsKeyDown(' '))
    {
        if (velocity < 0)
        {
            velocity += brakeCoefficient;
        }
        else
            if (velocity > 0)
            {
                velocity -= brakeCoefficient;
            }
    }
        
    
    if (velocity > maxSpeed)
        velocity = maxSpeed;
    
    if (velocity < -maxSpeed)
        velocity = -maxSpeed;
    
    if (!hasAcceleration)
    {
        if(velocity > 0)
            velocity -= fricitonCoefficient;
        else
            velocity += fricitonCoefficient;
    }
    
    
    
    IvVector2 carVelocity;
    carVelocity.x = velocity * (sin(angle)) * coef;
    carVelocity.y = velocity * (cos(angle)) * coef;
    
    
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

