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
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(80.0, 0.1, 800.0, 1280, 720);
    camera->setLookAt({0.f, -25.f, 0.f });
    camera->setPosition({0,0,0});
    camera->setRotation({0,1,0});
    
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootTestMenu");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTest",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"../../Game/BasicMenu/Resources/tr_back.tga");
    
    
    std::shared_ptr<SceneNode> _child1 = HelperManager::BuildSphere("sphere", HelperManager::CreateMeshInstance( meshManager.GetMesh("sphere")));
    std::shared_ptr<SceneNode>  _child2 = ModelLoader::loadModel("jeep.fbx", "example_shader");

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;
    
    std::shared_ptr<CarController> _controller = std::make_shared<CarController>();
    _child2->setAnimator(_controller);
    //_child2->setLocalPosition({0,-10,0});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(_child2);

    RoadImporterExporter* roadIE = new RoadImporterExporter();
    roadIE->importFrom("roadDataTest.txt");
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("Road", roadIE->getMarginPoints(), 10.0f);
    roadNode->setLocalTransform(IvVector3{0,-0.5,0}, IvVector3{0,0,0}, IvVector3{1,1,1});
    menu->getRoot()->addChild(roadNode);
    
    std::shared_ptr<SceneNode> environment=std::make_shared<Environment>("environment",roadIE->getMarginPoints());
    
    delete roadIE;
    
    backQuad->setLocalTransform({14,0,-8}, {0,4.72,1}, {4,4,4});
    environment->setLocalTransform({0,0,0}, {0,0,0}, {1,1,1});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(_child2.get(), IvVector2(3.f, 10.f), true));
    cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    
    menu->setCamera(camera);
    
    menu->getRoot()->addChild(environment);
    menu->getRoot()->addChild(cameraSceneNode);
    
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




