//-------------------------------------------------------------------------------
//-- FirstMenu.cpp --------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "FirstMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @FirstMenu::FirstMenu()
//-------------------------------------------------------------------------------
FirstMenu::FirstMenu()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootFirstMenu");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> testQuad=HelperManager::BuildTexturedQuad("test",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/test.tga");
    std::shared_ptr<SceneNode> gameQuad=HelperManager::BuildTexturedQuad("game",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/game.tga");
    std::shared_ptr<SceneNode> exitQuad=HelperManager::BuildTexturedQuad("exitFirst",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/exit.tga");
    
    testQuad->setLocalTransform(IvVector3{-4,0,0}, IvVector3{0,4.72,1}, IvVector3{4,4,5});
    gameQuad->setLocalTransform(IvVector3{4,0,0}, IvVector3{0,4.72,1}, IvVector3{4,4,5});
    exitQuad->setLocalTransform(IvVector3{14,0,-5}, IvVector3{0,4.72,1}, IvVector3{4,5,4});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    menu->setRoot(root);
    
    menu->getRoot()->addChild(testQuad);
    menu->getRoot()->addChild(gameQuad);
    menu->getRoot()->addChild(exitQuad);
    
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @FirstMenu::~FirstMenu()
//-------------------------------------------------------------------------------
FirstMenu::~FirstMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------



