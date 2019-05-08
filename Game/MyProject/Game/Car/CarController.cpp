#include "CarController.hpp"

void CarController::animateNode(float dt, SceneNode* car)
{
    bool hasAcceleration = false;
    
    //FORWARD
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        velocity += carSpeedIncrement;
        
        //APPLY SOME INITIAL TURBINE BOOST
        if (velocity > 0 && velocity < turbineBoostSpeedLimit)
            velocity += turbineBoostIncrement;
        
        //APPLY SOME BOOST WHEN CHANGING DIRECTION
        if (velocity < 0)
            velocity += directionChangeIncrement;
        
        hasAcceleration = true;
    }
    
    //BACKWARD
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        velocity -= carSpeedIncrement;
        
        //APPLY SOME INITIAL TURBINE BOOST
        if (velocity < 0 && velocity > -turbineBoostSpeedLimit)
            velocity -= turbineBoostIncrement;
        
        //APPLY SOME BOOST WHEN CHANGING DIRECTION
        if (velocity > 0)
            velocity -= directionChangeIncrement;
        
        hasAcceleration = true;
    }
    
    //BRAKE
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
    
    //NITRO
    if (IvGame::mGame->mEventHandler->IsKeyPressed('n'))
    {
        if (velocity > 0)
            velocity += nitroIncrement;
        else
        if (velocity < 0)
            velocity -= nitroIncrement;
        
        hasAcceleration = true;
    }
    
    //LIMIT THE VELOCITY
    if (velocity > maxSpeed)
        velocity = maxSpeed;
    
    if (velocity < -maxSpeed)
        velocity = -maxSpeed;
    
    //APPLY SOME FRICTION
    if (!hasAcceleration)
    {
        if(velocity > 0)
            velocity -= frictionCoefficient;
        else
            velocity += frictionCoefficient;
    }
    
    //APPLY A STEERING COEFFICIENT CONSIDERING THE CURRENT VELOCITY
    float coef = abs(velocity/maxSpeed);
    
    //LEFT & RIGHT STEERING CONSIDERING THE CURRENT VELOCITY
    //IF WE WANT TO MOVE FORWARD, IGNORING CURRENT VELOCITY
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            wheelAngle += angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            wheelAngle -= angleSpeedIncrement * coef;
        }
    }
    else
    //IF WE WANT TO MOVE BACKWARD, IGNORING CURRENT VELOCITY
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            wheelAngle -= angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            wheelAngle += angleSpeedIncrement * coef;
        }
    }
    else
    //IF THE CAR IS MOVING BACKWARDS, CONSIDERING CURRENT VELOCITY AND NO ACCELERATION
    if (velocity < 0)
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            wheelAngle -= angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            wheelAngle += angleSpeedIncrement * coef;
        }
    }
    else
    //IF THE CAR IS MOVING FORWARD, CONSIDERING CURRENT VELOCITY AND NO ACCELERATION
    if (velocity > 0)
    {
        if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
        {
            wheelAngle += angleSpeedIncrement * coef;
        }
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
        {
            wheelAngle -= angleSpeedIncrement * coef;
        }
    }
    
    
    IvVector2 carVelocity;
    carVelocity.x = velocity * (sin(wheelAngle)) * coef;
    carVelocity.y = velocity * (cos(wheelAngle)) * coef;
    
    
    IvVector2 carPosition;
    carPosition.x += carVelocity.x * dt;
    carPosition.y += carVelocity.y * dt;
    
    IvVector3 carPos = car->getLocalPosition();
    carPos.x += carPosition.x;
    carPos.z += carPosition.y;
    
    
    car->setLocalTransform(carPos, {0, wheelAngle, 0}, car->getLocalScale());
}

CarController::CarController(std::shared_ptr<SceneNode> car) : car(car) {
    
}
