//-------------------------------------------------------------------------------
//-- GameOver.cpp ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "GameOver.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @GameOver::GameOver()
//-------------------------------------------------------------------------------
GameOver::GameOver()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootGameOver");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    
    std::shared_ptr<SceneNode> retryQuad=HelperManager::BuildTexturedQuad("retryGameOver",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/race_retry.tga");
    
    std::shared_ptr<SceneNode> quitQuad=HelperManager::BuildTexturedQuad("backGameOver",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/race_quit.tga");
    
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    retryQuad->setLocalTransform(IvVector3{-4,0,0}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    quitQuad->setLocalTransform(IvVector3{4,0,0}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(retryQuad);
    menu->getRoot()->addChild(quitQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @GameOver::~GameOver()
//-------------------------------------------------------------------------------
GameOver::~GameOver()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
