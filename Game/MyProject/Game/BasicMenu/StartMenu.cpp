//-------------------------------------------------------------------------------
//-- StartMenu.cpp --------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "StartMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @StartMenu::StartMenu()
//-------------------------------------------------------------------------------
StartMenu::StartMenu()
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
    std::shared_ptr<SceneNode> playQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"roadTexture.tga");
    
    std::shared_ptr<SceneNode> highscoresQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"highscore.tga");
    
    std::shared_ptr<SceneNode> creditsQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"credits.tga");
    
    std::shared_ptr<SceneNode> exitQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"exit.tga");
    
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    playQuad->setLocalTransform(IvVector3{-7,0,0}, IvVector3{0,4.75,1}, IvVector3{4,4,5});
    highscoresQuad->setLocalTransform(IvVector3{-1,0,0}, IvVector3{0,4.72,1}, IvVector3{7,6,5});
    creditsQuad->setLocalTransform(IvVector3{4,0,0}, IvVector3{0,4.68,1}, IvVector3{10,6,5});
    exitQuad->setLocalTransform(IvVector3{10,0,-7}, IvVector3{0,4.72,1}, IvVector3{4,5,4});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(playQuad);
    menu->getRoot()->addChild(highscoresQuad);
    menu->getRoot()->addChild(creditsQuad);
    menu->getRoot()->addChild(exitQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @StartMenu::~StartMenu()
//-------------------------------------------------------------------------------
StartMenu::~StartMenu()
{
    
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
