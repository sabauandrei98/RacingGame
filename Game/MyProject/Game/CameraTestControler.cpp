#include "CameraTestControler.hpp"

CameraTestControler::CameraTestControler() : camera(45.0, 0.1, 35.0, 1280, 720)
{
    //SETTING CAMERA
    camera.setPosition({-15.f, 0.0f, 5.0f });
    camera.setLookAt({0.0f, 0.0f, 0.0f});
    camera.setOrientation({0.0f, 0.0f, 1.0f});
}


void
CameraTestControler::Update( float dt )
{
    
    // set up translation
    float translationSpeed = 3.0f;
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        camera.pan({0, dt * translationSpeed});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        camera.pan({0, -dt * translationSpeed});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
    {
        camera.pan({dt * translationSpeed, 0});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
    {
        camera.pan({-dt * translationSpeed, 0});
    }
    
    // set up rotation
    IvVector3 point = {0, 0, 0};
    float rotationSpeed = 3.0f;
    if (IvGame::mGame->mEventHandler->IsKeyDown('y'))
    {
        camera.rotate({0, dt * rotationSpeed}, point);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('h'))
    {
        camera.rotate({0, -dt * rotationSpeed}, point);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('g'))
    {
        camera.rotate({dt * rotationSpeed, 0}, point);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('j'))
    {
        camera.rotate({-dt * rotationSpeed, 0}, point);
    }
    
    
    // set up scaling
    float scalingSpeed = 1.0f;
    if (IvGame::mGame->mEventHandler->IsKeyDown('q'))
    {
        camera.zoom(dt * scalingSpeed);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('e'))
    {
        camera.zoom(-dt * scalingSpeed);
    }
    
    // set up FOV
    float fovSpeed = 0.5f;
    if (IvGame::mGame->mEventHandler->IsKeyDown('['))
    {
        camera.setFieldOfView(camera.getFieldOfView() + dt * fovSpeed);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown(']'))
    {
        camera.setFieldOfView(camera.getFieldOfView() - dt * fovSpeed);
    }
    
    // set up NEAR
    float nearSpeed = 3.0f;
    if (IvGame::mGame->mEventHandler->IsKeyDown(','))
    {
        camera.setNear(camera.getNearPlane() + dt * nearSpeed);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('.'))
    {
        camera.setNear(camera.getNearPlane() - dt * nearSpeed);
    }
    
    
    // set up FAR
    float farSpeed = 3.0f;
    if (IvGame::mGame->mEventHandler->IsKeyDown('\''))
    {
        camera.setFar(camera.getFarPlane() + dt * farSpeed);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('\\'))
    {
        camera.setFar(camera.getFarPlane() - dt * farSpeed);
    }
    
    
    if (camera.getNearPlane() > camera.getFarPlane())
        throw "NEAR > FAR";
    
}


void 
CameraTestControler::Render()                                    
{
    
    //DRAW AXES
    IvDrawAxes();
    
    IvDrawFloor();
    
    //DRAW AN OBJECT
    IvDrawTeapot();
    
    //VIEW MATRIX
    IvRenderer::mRenderer->SetViewMatrix(camera.getViewMatrix());
    
    //PROJECTION MATRIX
    IvRenderer::mRenderer->SetProjectionMatrix(camera.getProjectionMatrix());
}

CameraTestControler::~CameraTestControler(){}
