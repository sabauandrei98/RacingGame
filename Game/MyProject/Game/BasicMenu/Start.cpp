//-------------------------------------------------------------------------------
//-- Start.cpp -------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Start.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// @Start::Start()
//---------------------------------------------------------------------------
Start::Start()
{
    this->time=0.0f;
    
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    start=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("root");
    
//    std::vector<std::string> back_uniforms;
//    back_uniforms.push_back("u_time");
//
//    std::shared_ptr<SceneNode> background1=HelperManager::BuildQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),back_uniforms,"../../Game/BasicMenu/Shaders/Clouds"));
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> playQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"roadTexture.tga");
    
    std::shared_ptr<SceneNode> highscoresQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"highscore.tga");
    
    std::shared_ptr<SceneNode> creditsQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"credits.tga");
    
    std::shared_ptr<SceneNode> exitQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"exit.tga");
    
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
   // background1->setLocalTransform(IvVector3{-7,0,0}, IvVector3{0,4.75,1}, IvVector3{4,4,5});
    playQuad->setLocalTransform(IvVector3{-7,0,0}, IvVector3{0,4.75,1}, IvVector3{4,4,5});
    highscoresQuad->setLocalTransform(IvVector3{-1,0,0}, IvVector3{0,4.72,1}, IvVector3{7,6,5});
    creditsQuad->setLocalTransform(IvVector3{4,0,0}, IvVector3{0,4.68,1}, IvVector3{10,6,5});
    exitQuad->setLocalTransform(IvVector3{10,0,-7}, IvVector3{0,4.72,1}, IvVector3{4,5,4});
    
    start->setRoot(root);
  //  start->getRoot()->addChild(background1);
    start->getRoot()->addChild(playQuad);
    start->getRoot()->addChild(highscoresQuad);
    start->getRoot()->addChild(creditsQuad);
    start->getRoot()->addChild(exitQuad);
    start->getRoot()->addChild(cameraSceneNode);
    start->setCamera(camera);
    
}
//---------------------------------------------------------------------------
// @StartMenu::~StartMenu()
//---------------------------------------------------------------------------
Start::~Start()
{
    
}
//---------------------------------------------------------------------------
// @Menu::Update()
//---------------------------------------------------------------------------
void
Start::Update(float dt)
{
    this->time+=0.004f;
    start->updateScene(dt);
}
//---------------------------------------------------------------------------
// @Menu::Render()
//---------------------------------------------------------------------------
void
Start::Render()
{
    start->drawScene();
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
