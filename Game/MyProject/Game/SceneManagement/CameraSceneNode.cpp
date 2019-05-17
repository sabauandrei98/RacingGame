#include "CameraSceneNode.hpp"
#include "CarAnimator.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

CameraSceneNode::CameraSceneNode(const std::string& name, const CameraSceneNode::CameraPtr& camera) :
    SceneNode(name), _camera(camera) {
        _needs_bounding_box = false;
    }

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------


//void CameraSceneNode::updateNode(float dt) {
//    float translationSpeed = 3.0f;
//
//    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
//    {
//        _camera->pan({0, dt * translationSpeed});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
//    {
//        _camera->pan({0, -dt * translationSpeed});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
//    {
//        _camera->pan({-dt * translationSpeed, 0});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
//    {
//        _camera->pan({dt * translationSpeed, 0});
//    }
//    
//    // set up rotation
//    IvVector3 point = {0, 0, 0};
//    float rotationSpeed = 1.0f;
//    float x = 0, y = 0, z = 0;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('t'))
//    {
//        x += dt * rotationSpeed;
//        _camera->rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('g'))
//    {
//        x -= dt * rotationSpeed;
//        _camera->rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('y'))
//    {
//        y += dt * rotationSpeed;
//        _camera->rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('h'))
//    {
//        y -= dt * rotationSpeed;
//        _camera->rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('u'))
//    {
//        z += dt * rotationSpeed;
//        _camera->rotate({x, y, z});
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('j'))
//    {
//        z -= dt * rotationSpeed;
//        _camera->rotate({x, y, z});
//    }
//    
//    // set up scaling
//    float scalingSpeed = 1.0f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('q'))
//    {
//        _camera->zoom(dt * scalingSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('e'))
//    {
//        _camera->zoom(-dt * scalingSpeed);
//    }
//    
//    // set up FOV
//    float fovSpeed = 0.5f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('['))
//    {
//        _camera->setFieldOfView(_camera->getFieldOfView() + dt * fovSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown(']'))
//    {
//        _camera->setFieldOfView(_camera->getFieldOfView() - dt * fovSpeed);
//    }
//    
//    // set up NEAR
//    float nearSpeed = 3.0f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown(','))
//    {
//        _camera->setNear(_camera->getNearPlane() + dt * nearSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('.'))
//    {
//        _camera->setNear(_camera->getNearPlane() - dt * nearSpeed);
//    }
//    
//    
//    // set up FAR
//    float farSpeed = 3.0f;
//    if (IvGame::mGame->mEventHandler->IsKeyDown('\''))
//    {
//        _camera->setFar(_camera->getFarPlane() + dt * farSpeed);
//    }
//    if (IvGame::mGame->mEventHandler->IsKeyDown('\\'))
//    {
//        _camera->setFar(_camera->getFarPlane() - dt * farSpeed);
//    }
//    
//    if (_camera->getNearPlane() > _camera->getFarPlane())
//        throw "NEAR > FAR";
//}

IvVector3 CameraSceneNode::screenToWorld(unsigned int mouseX, unsigned int mouseY)
{
    return _camera->screenToWorld(mouseX, mouseY);
}

IvRay3 CameraSceneNode::getRay(unsigned int mouseX, unsigned int mouseY)
{
    return _camera->getRay(mouseX, mouseY);
}

