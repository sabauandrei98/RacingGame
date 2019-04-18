//-------------------------------------------------------------------------------
//-- TestHelper.cpp -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "TestHelper.h"
TestHelper::TestHelper()
{
    meshManager=new MeshManager();
    createdBoxes.push_back(false);
    createdBoxes.push_back(false);
    
    createdQuads.push_back(false);
    createdQuads.push_back(false);
    
    createdSphere.push_back(false);
    createdSphere.push_back(false);

}
void
TestHelper::DrawBox()
{
    if(!createdBoxes[0])
    {
        std::shared_ptr<SceneNode> boxNode=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager->GetMesh("box")),true);
        toBeRendered.push_back(std::make_shared<SceneGraph>());
        
        createdBoxes[0]=true;
    
        toBeRendered[0]->setRoot(boxNode);
        toBeRendered[0]->setCamera(std::make_shared<CameraSceneNode>("camera"));
        toBeRendered[0]->updateScene(0.01);
    }
    toBeRendered[0]->drawScene();
    
    if(!createdBoxes[1])
    {
        std::shared_ptr<SceneNode> boxNode2=HelperManager::BuildBox(HelperManager::CreateMeshInstance(meshManager->GetMesh("box")));
        boxNode2->setLocalTransform(IvVector3(1,1,1), IvVector3(0,0,0), IvVector3(2,2,2));
        toBeRendered.push_back(std::make_shared<SceneGraph>());
        
        createdBoxes[1]=true;
    
        toBeRendered[1]->setRoot(boxNode2);
        toBeRendered[1]->setCamera(std::make_shared<CameraSceneNode>("camera"));
        toBeRendered[1]->updateScene(0.01);
    }
    toBeRendered[1]->drawScene();
}

void
TestHelper::DrawQuad()
{
    if(!createdQuads[0])
    {
        std::shared_ptr<SceneNode> quadNode=HelperManager::BuildQuad(HelperManager::CreateMeshInstance(meshManager->GetMesh("quad")));
        toBeRendered.push_back(std::make_shared<SceneGraph>());
        toBeRendered[0]->setRoot(quadNode);
        toBeRendered[0]->setCamera(std::make_shared<CameraSceneNode>("camera"));
        toBeRendered[0]->updateScene(0.01);
        
        createdQuads[0]=true;
    }
    toBeRendered[0]->drawScene();
    
    if(!createdQuads[1])
    {
        std::vector<std::string > uniforms;
        uniforms.push_back("myTexture");
        std::shared_ptr<SceneNode> quadNode2=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager->GetMesh("quad"),uniforms),"cross.tga");
        toBeRendered.push_back(std::make_shared<SceneGraph>());
    
        toBeRendered[1]->setRoot(quadNode2);
        toBeRendered[1]->setCamera(std::make_shared<CameraSceneNode>("camera"));
        toBeRendered[1]->updateScene(0.01);
        
        createdQuads[1]=true;
    }
    toBeRendered[1]->drawScene();
}

void TestHelper::DrawSphere()
{
    if(!createdSphere[0])
    {
        std::shared_ptr<SceneNode> sphereNode=HelperManager::BuildSphere(HelperManager::CreateMeshInstance(meshManager->GetMesh("sphere")));
        toBeRendered.push_back(std::make_shared<SceneGraph>());
    
        IvVector3 rotation=IvVector3(0,0,0);
        IvVector3 position=IvVector3(0,0,0);
        IvVector3 scale=IvVector3(1,1,1);
  
    
        toBeRendered[0]->setRoot(sphereNode);
        toBeRendered[0]->setCamera(std::make_shared<CameraSceneNode>("camera"));
        toBeRendered[0]->getRoot()->setLocalTransform(position, rotation, scale);
        toBeRendered[0]->updateScene(0.01);
        
        createdSphere[0]=true;
    }
    toBeRendered[0]->drawScene();
    
    if(!createdSphere[1])
    {
        std::shared_ptr<SceneNode> sphereNode2=HelperManager::BuildSphere(HelperManager::CreateMeshInstance(meshManager->GetMesh("sphere")),true);
        sphereNode2->setLocalTransform(IvVector3(1,1,1), IvVector3(0,0,0), IvVector3(2,2,2));
        toBeRendered.push_back(std::make_shared<SceneGraph>());
    
        toBeRendered[1]->setRoot(sphereNode2);
        toBeRendered[1]->setCamera(std::make_shared<CameraSceneNode>("camera"));
        toBeRendered[1]->updateScene(0.01);
        
        createdSphere[1]=true;
    }
    toBeRendered[1]->drawScene();
}

