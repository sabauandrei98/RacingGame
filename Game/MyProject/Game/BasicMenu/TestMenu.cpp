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
    
    std::shared_ptr<SceneNode>  _child2 = ModelLoader::loadModel("jeep.fbx", "example_shader", true);

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;
    
    std::shared_ptr<CarController> _controller = std::make_shared<CarController>();
    _child2->setAnimator(_controller);
    //_child2->setLocalPosition({0,-10,0});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(_child2);

    RoadImporterExporter roadIE;
    roadIE.importFrom("roadDataTest.txt");
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("Road", roadIE.getMarginPoints(), 10.0f,true);
    roadNode->setLocalTransform(IvVector3{0,-0.5,0}, IvVector3{0,0,0}, IvVector3{1,1,1});
    menu->getRoot()->addChild(roadNode);
    
    std::shared_ptr<SceneNode> environment=std::make_shared<Environment>("environment",roadIE.getMarginPoints());
   
    
    backQuad->setLocalTransform({14,0,-8}, {0,4.72,1}, {4,4,4});
    environment->setLocalTransform({0,0,0}, {0,0,0}, {1,1,1});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(_child2.get(), IvVector2(3.f, 10.f), true));
    cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    std::shared_ptr<Camera> map_camera;
    std::shared_ptr<CameraSceneNode> map_cameraSceneNode;
    
    map_camera = std::make_shared<Camera>(70.0, 0.1, 200.0, 1280, 720);
    map_camera->setLookAt({0.f, 0.f, 0.f });
    map_camera->setPosition({0,25,0});
    map_camera->setRotation({0,1,0});
    
    map_cameraSceneNode = std::make_shared<CameraSceneNode>("map_camera",map_camera);
    
    map_cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(_child2.get(), IvVector2(80.f, 1.f), false));
    map_cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 80.f, -1.f));
    
    menu->getRoot()->addChild(backQuad);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->getRoot()->addChild(map_cameraSceneNode);
    menu->setCamera(camera);
    menu->setMapCamera(map_camera);
    
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




