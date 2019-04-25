//-------------------------------------------------------------------------------
//-- TestCollision.cpp -----------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestCollision.hpp"

void 
TestCollision::TestRayBox()
{
    
    camera=std::make_shared<Camera>(45.0, 0.1, 35.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    MeshManager meshManager;
    std::shared_ptr<SceneNode> boxNode=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager.GetMesh("box")),true,true,true);
    box=std::make_shared<SceneGraph>();
    
    boxNode->setLocalTransform({0,0,0},{0,0,0},{4,4,4});
    box->setRoot(boxNode);
    
    cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    box->getRoot()->addChild(cameraSceneNode);
    box->setCamera(camera);
    
    
//    //testing boundingg box for a sphere
//    std::shared_ptr<SceneNode> sphereNode=HelperManager::BuildSphere(HelperManager::CreateMeshInstance(meshManager.GetMesh("sphere")));
//    sphere=std::make_shared<SceneGraph>();
//
//    sphereNode->setLocalTransform({0,0,0},{0,0,0},{4,4,4});
//    sphere->setRoot(sphereNode);
//    sphere->getRoot()->addChild(cameraSceneNode);
//    sphere->setCamera(camera);
    
   
}

void TestCollision::Update(float dt)
{
    box->updateScene(dt);
  //  sphere->updateScene(dt);
    
}
void TestCollision::Render()
{
    box->drawScene();
    static int index=0;
    
    if(cameraSceneNode->getMousePressed())
    {
        IvRay3 ray2(camera->getPosition(),cameraSceneNode->getMouseCoordinates());
        
        ray=IvRay3(ray2);
        RayBoxIntersection raybox;
        if(raybox.IsRayIntersectingBox(ray, box->getRoot()->getBoundingBox()))
        {
            IvVector3 auxOrigin;
            auxOrigin.x=ray.GetOrigin().x;
            auxOrigin.x=ray.GetOrigin().y;
            auxOrigin.x=ray.GetOrigin().z;
            
            IvDrawLine(auxOrigin, ray.GetDirection(),kRed);
            
            std::cout<<index++<<":"<<cameraSceneNode->getMouseCoordinates().x<<" "<<cameraSceneNode->getMouseCoordinates().y<<" "<<cameraSceneNode->getMouseCoordinates().z<<std::endl;
        }
    }
    
    // //testing bounding box for sphere
    //sphere->drawScene();
//    IvSetWorldIdentity();
//    IvSetViewMatrix(camera->getViewMatrix());
//    IvSetProjectionMatrix(camera->getProjectionMatrix());
//
//    BoundingBox boundingBox;
//    Mesh* mesh = new Mesh();
//    std::vector<IvTCPVertex> vertices;
//
//    boundingBox =sphere->getRoot()->getBoundingBox();
//    vertices.resize(8);
//    for (int i = 0; i < 8; i++) {
//        vertices[i].position = boundingBox.getPoints()[i];
//        vertices[i].color = {255, 255, 255, 255};
//    }
//
//    mesh->setVertexBuffer(vertices, kTCPFormat);
//    mesh->setIndexBuffer({0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7});
//
//    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());
//
//    delete mesh;
    
    //IvDrawLine(boundingBox.min, boundingBox.center,kGreen);

   
}
