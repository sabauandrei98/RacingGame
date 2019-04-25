//-------------------------------------------------------------------------------
//-- TestHelper.cpp -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "TestHelper.hpp"
TestHelper::TestHelper()
{
    meshManager=new MeshManager();
    
    boxCreated=false;
    sphereCreated=false;
    quadCreated=false;

    camera=std::make_shared<Camera>(45.0,0.1,35.0,1280,720);
    cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    camera->setPosition({0,-25,0});
    camera->setLookAt({0,0,0});
    camera->setRotation({0,0,1});
    
}
void
TestHelper::Update(float dt)
{
    if(boxCreated)
        box->updateScene(dt);
    if(quadCreated)
        quad->updateScene(dt);
    if(sphereCreated)
        sphere->updateScene(dt);
}
TestHelper::~TestHelper()
{
    delete meshManager;
}
void
TestHelper::DrawBox()
{
    if(!boxCreated)
    {
        std::shared_ptr<SceneNode> boxNode=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager->GetMesh("box")),true);
        box=std::make_shared<SceneGraph>();
        
        boxCreated=true;
    
        box->setRoot(boxNode);
        box->getRoot()->setLocalPosition({0,0,0});
        box->setCamera(camera);
        
        box->getRoot()->addChild(cameraSceneNode);
        
        std::shared_ptr<SceneNode> boxNode2=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager->GetMesh("box")));
        boxNode2->setLocalTransform(IvVector3(1,1,1), IvVector3(0,0,0), IvVector3(2,2,2));
    
        box->getRoot()->addChild(boxNode2);
        
    }
    box->drawScene() ;
}

void
TestHelper::DrawQuad()
{
    if(!quadCreated)
    {
        std::shared_ptr<SceneNode> quadNode=HelperManager::BuildQuad(HelperManager::CreateMeshInstance(meshManager->GetMesh("quad")));

        quad=std::make_shared<SceneGraph>();
        quad->setRoot(quadNode);
        quad->setCamera(camera);
        
        quad->getRoot()->setLocalPosition({0,0,0});
        quad->getRoot()->addChild(cameraSceneNode);
        
        quadCreated=true;

        std::vector<std::string > uniforms;
        uniforms.push_back("myTexture");
        std::shared_ptr<SceneNode> quadNode2=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager->GetMesh("quad"),uniforms),"cross.tga");
    
        quad->getRoot()->addChild(quadNode2);
        
    }
    quad->drawScene();
}

void TestHelper::DrawSphere()
{
    if(!sphereCreated)
    {
        std::shared_ptr<SceneNode> sphereNode=HelperManager::BuildSphere(HelperManager::CreateMeshInstance(meshManager->GetMesh("sphere")));
        
        IvVector3 rotation=IvVector3(0,0,0);
        IvVector3 position=IvVector3(0,0,0);
        IvVector3 scale=IvVector3(1,1,1);

    
        sphereNode->setLocalTransform(position, rotation, scale);
        
        sphere=std::make_shared<SceneGraph>();
    
        sphere->setRoot(sphereNode);
        sphere->setCamera(camera);
        
        sphereCreated=true;
        
        std::shared_ptr<SceneNode> sphereNode2=HelperManager::BuildSphere(HelperManager::CreateMeshInstance(meshManager->GetMesh("sphere")),true);
        sphereNode2->setLocalTransform(IvVector3(1,1,1), IvVector3(0,0,0), IvVector3(2,2,2));

        sphere->getRoot()->addChild(cameraSceneNode);
        sphere->getRoot()->addChild(sphereNode2);
        
    }
    sphere->drawScene();
    
}

