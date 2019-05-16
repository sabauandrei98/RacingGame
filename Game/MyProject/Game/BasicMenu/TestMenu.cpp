//-------------------------------------------------------------------------------
//-- TestMenu.cpp ------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @TestMenu::TestMenu()
//-------------------------------------------------------------------------------
TestMenu::TestMenu()
{
    MeshManager meshManager;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 100.0, 1280, 720);
    camera->setLookAt({0.f, 0.f, 0.f });
    camera->setPosition({0,-25,0});
    camera->setRotation({0,1,0});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootTestMenu");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTest",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_back.tga");
    
    
    std::shared_ptr<SceneNode> _child1 = HelperManager::BuildSphere("sphere", HelperManager::CreateMeshInstance( meshManager.GetMesh("sphere")));
    std::shared_ptr<SceneNode>  _child3 = HelperManager::BuildTexturedQuad("quad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"), "../../Game/Helper/Shaders/TextureShader"), "../../Textures/large.tga");
    std::shared_ptr<SceneNode>  _child2 = ModelLoader::loadModel("jeep.fbx", "example_shader");

    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;
    
    std::shared_ptr<CarController> _controller = std::make_shared<CarController>();
    _child2->setAnimator(_controller);
    
    menu->setRoot(root);
    menu->getRoot()->addChild(_child2);
    menu->getRoot()->addChild(_child3);
    
    _child3->setLocalTransform({0., 0., 0.}, {0., 0., -kPI/2.}, {300., 300., 300.});
    backQuad->setLocalTransform(IvVector3{14,0,-8}, IvVector3{0,4.72,1}, IvVector3{4,4,4});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(_child2.get(), IvVector2(3.f, 10.f), true));
    cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    
    menu->getRoot()->addChild(backQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @TestMenu::~TestMenu()
//-------------------------------------------------------------------------------
TestMenu::~TestMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------




