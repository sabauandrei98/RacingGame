//-------------------------------------------------------------------------------
//-- CarMenu.cpp ----------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "CarMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @CarMenu::CarMenu()
//-------------------------------------------------------------------------------
CarMenu::CarMenu()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootCar");
    
    std::shared_ptr<SceneNode> model1=ModelLoader::loadModel("jeep.fbx", "example_shader");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backCar",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_back.tga");
    
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    model1->setLocalTransform(IvVector3{0,0,0}, IvVector3{1,1.5,1}, IvVector3{4,4,4});
    backQuad->setLocalTransform(IvVector3{14,0,-8}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(model1);
    menu->getRoot()->addChild(backQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @CarMenu::~CarMenu()
//-------------------------------------------------------------------------------
CarMenu::~CarMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

