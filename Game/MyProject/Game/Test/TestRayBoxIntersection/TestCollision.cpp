//-------------------------------------------------------------------------------
//-- TestCollision.cpp -----------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestCollision.hpp"

void 
TestCollision::TestRayBox()
{
    
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 35.0, 1280, 720);
    camera->setPosition({0.f, 0.f, 0.f });
    camera->setLookAt({2.7f, 1.5f, 1.5f});
    
    MeshManager meshManager;
    std::shared_ptr<SceneNode> boxNode=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager.GetMesh("box")),true);
    box=std::make_shared<SceneGraph>();
    
    BoundingBox boound=boxNode->getBoundingBox();
    
    boxNode->setLocalTransform(IvVector3(0.5,0.5,0.5),IvVector3(0,0,0),IvVector3(1,1,1));
    
    box->setRoot(boxNode);
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    box->getRoot()->addChild(cameraSceneNode);
    box->setCamera(camera);
    
    boundingBox.center=IvVector3(0.5,0.5,0.5);
    boundingBox.max=IvVector3(1,1,1);
    boundingBox.min=IvVector3(0.,0.,0.);
    
    cameraPosition=IvVector3(-1,-0.1,-1);
    cameraLookAt=IvVector3(1.2,1.1,1.5);
    IvRay3 ray2(cameraPosition,cameraLookAt);
    
    ray=IvRay3(ray2);
    
   
}

void TestCollision::Update(float t)
{
    box->updateScene(t);
    
}
void TestCollision::Render()
{
    box->drawScene();
    
    IvDrawLine(boundingBox.min, boundingBox.center,kGreen);
    
    RayBoxIntersection raybox;
    if(raybox.IsRayIntersectingBox(ray, boundingBox))
        IvDrawLine(ray.GetOrigin(), ray.GetDirection(),kRed);

}
