//-------------------------------------------------------------------------------
//-- Car.cpp --------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Car.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// @Car::Car()
//---------------------------------------------------------------------------
Car::Car()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    car=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("root");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad(HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_back.tga");
    
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    backQuad->setLocalTransform(IvVector3{10,0,-4}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    car->setRoot(root);
    car->getRoot()->addChild(backQuad);
    car->getRoot()->addChild(cameraSceneNode);
    car->setCamera(camera);
    
}
//---------------------------------------------------------------------------
// @Car::~Car()
//---------------------------------------------------------------------------
Car::~Car()
{
    
}
//---------------------------------------------------------------------------
// @Car::Update()
//---------------------------------------------------------------------------
void
Car::Update(float dt)
{
    car->updateScene(dt);
}
//---------------------------------------------------------------------------
// @Car::Render()
//---------------------------------------------------------------------------
void
Car::Render()
{
    car->drawScene();
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

