//-------------------------------------------------------------------------------
//-- TestCollision.cpp -----------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestCollision.hpp"

void 
TestCollision::TestRayBox()
{
    camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({5,-35,15});
    camera->setRotation({0,0,1});
    
    MeshManager meshManager;
    std::shared_ptr<SceneNode> boxNode=HelperManager::BuildBox("boxNode",HelperManager::CreateMeshInstance(meshManager.GetMesh("box")),true,true,true);
    box=std::make_shared<SceneGraph>();
    
    boxNode->setLocalTransform({0,0,0},{0,0,0},{4,4,4});
    box->setRoot(boxNode);
    
    cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    box->getRoot()->addChild(cameraSceneNode);
    box->setCamera(camera);

}

void TestCollision::Update(float dt)
{
    box->updateScene(dt);
    
    is_mouse_released = (IvGame::mGame->mEventHandler->IsMousePressed(mouseX, mouseY));
        
}
void TestCollision::Render()
{
    box->drawScene();
    static int index=0;
    if(is_mouse_released)
    {
        RayBoxIntersection raybox(cameraSceneNode->getRay(mouseX,mouseY));
        if(raybox.IsRayIntersectingBox(box->getRoot()->getBoundingBox()))
        {
            std::cout<<"ok "<<index++<<std::endl;
        }
    }
    
}
