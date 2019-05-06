//-------------------------------------------------------------------------------
//-- RaceMenu.cpp ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "RaceMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @RaceMenu::RaceMenu()
//-------------------------------------------------------------------------------
RaceMenu::RaceMenu()
{
    meshManager=MeshManager();
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("root");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    uniforms.push_back("row");
    uniforms.push_back("column");
    
    std::shared_ptr<SceneNode> countRoot=std::make_shared<SceneNode>("countRoot");
    
    std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad("count1",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"font.tga");
    
    countScoreQuad->setLocalTransform(IvVector3{4,0,7}, IvVector3{0,4.72,1}, IvVector3{2,2,2});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    countRoot->addChild(countScoreQuad);
    
    menu->setRoot(root);
    menu->getRoot()->addChild(countRoot);
    
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @RaceMenu::~RaceMenu()
//-------------------------------------------------------------------------------
RaceMenu::~RaceMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------


