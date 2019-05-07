//-------------------------------------------------------------------------------
//-- BuildTrackMenu.cpp ---------------------------------------------------------
//-------------------------------------------------------------------------------
#include "BuildTrackMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @BuildTrackMenu::BuildTrackMenu()
//-------------------------------------------------------------------------------
BuildTrackMenu::BuildTrackMenu()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootBuildTrack");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    
    std::shared_ptr<SceneNode> previousQuad=HelperManager::BuildTexturedQuad("previousTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_previous.tga");

    std::shared_ptr<SceneNode> nextQuad=HelperManager::BuildTexturedQuad("nextTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_next.tga");
    
    std::shared_ptr<SceneNode> addQuad=HelperManager::BuildTexturedQuad("addTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_add.tga");
    
    std::shared_ptr<SceneNode> removeQuad=HelperManager::BuildTexturedQuad("removeTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_remove.tga");
    
    std::shared_ptr<SceneNode> playQuad=HelperManager::BuildTexturedQuad("playTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_play.tga");
    
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTrack",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_back.tga");
    
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    previousQuad->setLocalTransform(IvVector3{-10,0,-8}, IvVector3{0,4.72,1}, IvVector3{1,2,4});
    nextQuad->setLocalTransform(IvVector3{-5,0,-8}, IvVector3{0,4.72,1}, IvVector3{1,2,4});
    addQuad->setLocalTransform(IvVector3{14,0,6}, IvVector3{0,4.72,1}, IvVector3{1,2,4});
    removeQuad->setLocalTransform(IvVector3{14,0,3}, IvVector3{0,4.72,1}, IvVector3{2,2,4});
    playQuad->setLocalTransform(IvVector3{14,0,0}, IvVector3{0,4.72,1}, IvVector3{1,2,4});
    backQuad->setLocalTransform(IvVector3{14,0,-8}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(previousQuad);
    menu->getRoot()->addChild(nextQuad);
    menu->getRoot()->addChild(addQuad);
    menu->getRoot()->addChild(removeQuad);
    menu->getRoot()->addChild(playQuad);
    menu->getRoot()->addChild(backQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @BuildTrackMenu::~BuildTrackMenu()
//-------------------------------------------------------------------------------
BuildTrackMenu::~BuildTrackMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------


