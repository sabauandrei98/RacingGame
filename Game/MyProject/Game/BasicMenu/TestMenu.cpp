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
    //SkyBox skyBox;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(80.0, 0.1, 700.0, 1280, 720);
    camera->setLookAt({0,-25,0});
    camera->setPosition({0,0,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootTestMenu");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTest",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_back.tga");
    
    std::shared_ptr<SceneNode> environment=std::make_shared<Environment>("environment");
    
    backQuad->setLocalTransform({14,0,-8}, {0,4.72,1}, {4,4,4});
    environment->setLocalTransform({0,10,0}, {0,0,0}, {2,2,2});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    menu->setRoot(root);
    menu->setCamera(camera);
    
    menu->getRoot()->addChild(environment);
    menu->getRoot()->addChild(cameraSceneNode);
    
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




