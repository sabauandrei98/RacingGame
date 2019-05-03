//-------------------------------------------------------------------------------
//-- Track.cpp ------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Track.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// @Track::Track()
//---------------------------------------------------------------------------
Track::Track()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    track=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("root");

    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    
    std::shared_ptr<SceneNode> chooseQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_choose.tga");
    
    std::shared_ptr<SceneNode> buildQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_build.tga");
    
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_back.tga");
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    chooseQuad->setLocalTransform(IvVector3{0,0,4}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    buildQuad->setLocalTransform(IvVector3{0,0,0}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    backQuad->setLocalTransform(IvVector3{0,0,-4.5}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    track->setRoot(root);
    
    track->getRoot()->addChild(chooseQuad);
    track->getRoot()->addChild(buildQuad);
    track->getRoot()->addChild(backQuad);
    
    track->getRoot()->addChild(cameraSceneNode);
    track->setCamera(camera);
    
}
//---------------------------------------------------------------------------
// @Track::~Track()
//---------------------------------------------------------------------------
Track::~Track()
{
    
}
//---------------------------------------------------------------------------
// @Menu::Update()
//---------------------------------------------------------------------------
void
Track::Update(float dt)
{
    track->updateScene(dt);
}
//---------------------------------------------------------------------------
// @Menu::Render()
//---------------------------------------------------------------------------
void
Track::Render()
{
    track->drawScene();
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
