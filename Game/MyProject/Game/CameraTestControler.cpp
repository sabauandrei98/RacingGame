#include "CameraTestControler.hpp"

CameraTestControler::CameraTestControler() : camera(45.0, 0.1, 35.0, 1280, 720)
{
    //SETTING CAMERA
    camera.setPosition({-10.f, 0.0f, 5.0f });
    camera.setLookAt({0.0f, 0.0f, 0.0f});
    camera.setRotation({0.0f, 0.0f, 1.0f});
    
    
    MeshManager* meshManager=new MeshManager();
    std::shared_ptr<SceneNode> boxNode=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager->GetMesh("box")));
    boxGraph=std::make_shared<SceneGraph>();
    boxGraph->setRoot(boxNode);
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
        camera.pan({-dt * translationSpeed, 0});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
    {
        camera.pan({dt * translationSpeed, 0});
    }
    
    // set up rotation
    IvVector3 point = {0, 0, 0};
    float rotationSpeed = 1.0f;
    float x = 0, y = 0, z = 0;
    if (IvGame::mGame->mEventHandler->IsKeyDown('t'))
    {
        x += dt * rotationSpeed;
        camera.rotate({x, y, z});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('g'))
    {
        x -= dt * rotationSpeed;
        camera.rotate({x, y, z});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('y'))
    {
        y += dt * rotationSpeed;
        camera.rotate({x, y, z});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('h'))
    {
        y -= dt * rotationSpeed;
        camera.rotate({x, y, z});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('u'))
    {
        z += dt * rotationSpeed;
        camera.rotate({x, y, z});
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('j'))
    {
        z -= dt * rotationSpeed;
        camera.rotate({x, y, z});
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
    
    unsigned int mouseX,mouseY;
    if(IvGame::mGame->mEventHandler->IsMousePressed(mouseX, mouseY))
    {
        mouseCoordinates=camera.screenToWorld(mouseX,mouseY);
    
        mousePicker=true;
        
        boxGraph->getRoot()->setLocalPosition(mouseCoordinates);
        boxGraph->updateScene(dt);
    }
   
}


void 
CameraTestControler::Render()                                    
{
    
    //DRAW AXES
    IvDrawAxes();
    
    //IvDrawFloor();
    
    if(mousePicker)
    {
        boxGraph->setCamera(std::make_shared<CameraSceneNode>("camera",camera));
        boxGraph->drawScene();
    }
    //DRAW AN OBJECT
    //IvDrawTeapot();
    
    //VIEW MATRIX
    IvRenderer::mRenderer->SetViewMatrix(camera.getViewMatrix());
    
    //PROJECTION MATRIX
    IvRenderer::mRenderer->SetProjectionMatrix(camera.getProjectionMatrix());
}

CameraTestControler::~CameraTestControler(){}
