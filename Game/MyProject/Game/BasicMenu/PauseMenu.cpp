//-------------------------------------------------------------------------------
//-- PauseMenu ------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "PauseMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @PauseMenu::PauseMenu()
//-------------------------------------------------------------------------------
PauseMenu::PauseMenu()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("root");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> resumeQuad=HelperManager::BuildTexturedQuad("resumePause",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"race_resume.tga");
    std::shared_ptr<SceneNode> quitQuad=HelperManager::BuildTexturedQuad("quitPause",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"race_quit.tga");
    
    resumeQuad->setLocalTransform(IvVector3{-4,0,0}, IvVector3{0,4.75,1}, IvVector3{4,4,5});
    quitQuad->setLocalTransform(IvVector3{4,0,0}, IvVector3{0,4.75,1}, IvVector3{4,4,5});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    menu->setRoot(root);
    menu->getRoot()->addChild(resumeQuad);
    menu->getRoot()->addChild(quitQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @PauseMenu::~PauseMenu()
//-------------------------------------------------------------------------------
PauseMenu::~PauseMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------


