//-------------------------------------------------------------------------------
//-- TrackMenu.cpp --------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "TrackMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @TrackMenu::TrackMenu()
//-------------------------------------------------------------------------------
TrackMenu::TrackMenu()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootTrack");

    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    
    std::shared_ptr<SceneNode> chooseQuad=HelperManager::BuildTexturedQuad("chooseTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_choose.tga");
    
    std::shared_ptr<SceneNode> buildQuad=HelperManager::BuildTexturedQuad("buildTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_build.tga");
    
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_back.tga");
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    chooseQuad->setLocalTransform(IvVector3{0,0,4}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    buildQuad->setLocalTransform(IvVector3{0,0,0}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    backQuad->setLocalTransform(IvVector3{14,0,-8}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(chooseQuad);
    menu->getRoot()->addChild(buildQuad);
    menu->getRoot()->addChild(backQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @TrackMenu::~TrackMenu()
//-------------------------------------------------------------------------------
TrackMenu::~TrackMenu()
{
    
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
