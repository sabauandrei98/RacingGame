//
//  CameraSceneNode.cpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#include "CameraSceneNode.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

CameraSceneNode::CameraSceneNode(const std::string& name, const Camera& camera) :
    SceneNode(name), Camera(camera) {
    }

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

void CameraSceneNode::updateNode(float dt) {
//    float translationSpeed = 3.0f;
//    
//    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
//    {
//        pan({0, dt * translationSpeed});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
//    {
//        pan({0, -dt * translationSpeed});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
//    {
//        pan({-dt * translationSpeed, 0});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
//    {
//        pan({dt * translationSpeed, 0});
//    }
//    
//    // set up rotation
//    IvVector3 point = {0, 0, 0};
//    float rotationSpeed = 1.0f;
//    float x = 0, y = 0, z = 0;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('t'))
//    {
//        x += dt * rotationSpeed;
//        rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('g'))
//    {
//        x -= dt * rotationSpeed;
//        rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('y'))
//    {
//        y += dt * rotationSpeed;
//        rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('h'))
//    {
//        y -= dt * rotationSpeed;
//        rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('u'))
//    {
//        z += dt * rotationSpeed;
//        rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('j'))
//    {
//        z -= dt * rotationSpeed;
//        rotate({x, y, z});
//    }
//    
//    // set up scaling
//    float scalingSpeed = 1.0f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('q'))
//    {
//        zoom(dt * scalingSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('e'))
//    {
//        zoom(-dt * scalingSpeed);
//    }
//    
//    // set up FOV
//    float fovSpeed = 0.5f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('['))
//    {
//        setFieldOfView(getFieldOfView() + dt * fovSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown(']'))
//    {
//        setFieldOfView(getFieldOfView() - dt * fovSpeed);
//    }
//    
//    // set up NEAR
//    float nearSpeed = 3.0f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown(','))
//    {
//        setNear(getNearPlane() + dt * nearSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('.'))
//    {
//        setNear(getNearPlane() - dt * nearSpeed);
//    }
//    
//    
//    // set up FAR
//    float farSpeed = 3.0f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('\''))
//    {
//        setFar(getFarPlane() + dt * farSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('\\'))
//    {
//        setFar(getFarPlane() - dt * farSpeed);
//    }
//    
//    if (getNearPlane() > getFarPlane())
//        throw "NEAR > FAR";
//    
//   
    
    
}
