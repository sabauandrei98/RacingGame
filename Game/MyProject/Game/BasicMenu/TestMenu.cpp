//-------------------------------------------------------------------------------
//-- TestMenu.cpp ------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @TestMenu::TestMenu()
//-------------------------------------------------------------------------------
TestMenu::TestMenu()
{
    MeshManager meshManager;
    SkyBox skyBox;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(75.0, 0.1, 450.0, 1280, 720);
    camera->setLookAt({0,-30,0});
    camera->setPosition({0,0,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootTestMenu");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTest",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_back.tga");
    
    std::shared_ptr<SceneNode> box=HelperManager::BuildBox("box", HelperManager::CreateMeshInstance(meshManager.GetMesh("box")));
    std::shared_ptr<SceneNode> sky=skyBox.getSky();
    
    box->setLocalTransform({0,0,1}, {0,0,0}, {2,2,2});
    backQuad->setLocalTransform({14,0,-8}, {0,4.72,1}, {4,4,4});
    sky->setLocalTransform({0,0,0}, {0,0,0}, {50,50,50});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    menu->setRoot(root);

   // menu->getRoot()->addChild(box);
   // menu->getRoot()->addChild(backQuad);
    menu->getRoot()->addChild(sky);
    
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @TestMenu::~TestMenu()
//-------------------------------------------------------------------------------
TestMenu::~TestMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------




