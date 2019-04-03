#include "CameraTestControler.hpp"

CameraTestControler::CameraTestControler() : cam(45.0, 0.1, 35.0, 1280, 720)
{
    //SETTING CAMERA
    cam.setPosition({-15.f, 0.0f, 5.0f });
    cam.setLookAt({0.0f, 0.0f, 0.0f});
    cam.setOrientation({0.0f, 0.0f, 1.0f});
}


void
CameraTestControler::Update( float dt )
{
    
    // set up translation
    if (IvGame::mGame->mEventHandler->IsKeyDown('w'))
    {
        cam.panUp(5 * dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('s'))
    {
        cam.panUp(-5 * dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
    {
       cam.panRight(5 * dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
    {
      cam.panRight(-5 * dt);
    }
    
    
    // set up scaling
    if (IvGame::mGame->mEventHandler->IsKeyDown('q'))
    {
        cam.zoom(5 * dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('e'))
    {
        cam.zoom(-5 * dt);
    }
    
    // set up FOV
    if (IvGame::mGame->mEventHandler->IsKeyDown('['))
    {
        cam.setFieldOfView(cam.getFieldOfView() + dt * 3);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown(']'))
    {
        cam.setFieldOfView(cam.getFieldOfView() - dt * 3);
    }
    
    // set up NEAR
    if (IvGame::mGame->mEventHandler->IsKeyDown(','))
    {
        cam.setNear(cam.getNearPlane() + dt * 3);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('.'))
    {
        cam.setNear(cam.getNearPlane() - dt * 3);
    }
    
    
    // set up FAR
    if (IvGame::mGame->mEventHandler->IsKeyDown('\''))
    {
        cam.setFar(cam.getFarPlane() + dt * 3);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('\\'))
    {
        cam.setFar(cam.getFarPlane() - dt * 3);
    }
    
    
    if (cam.getNearPlane() > cam.getFarPlane())
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
    IvRenderer::mRenderer->SetViewMatrix(cam.getViewMatrix());
    
    //PROJECTION MATRIX
    IvRenderer::mRenderer->SetProjectionMatrix(cam.getProjectionMatrix());
}

CameraTestControler::~CameraTestControler(){}
