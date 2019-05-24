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
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(80.0, 0.1, 700.0, 1280, 720);
    camera->setLookAt({0,-25,0});
    camera->setPosition({0,0,0});
    camera->setRotation({0,1,0});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootRace");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    uniforms.push_back("row");
    uniforms.push_back("column");
    uniforms.push_back("noRows");
    uniforms.push_back("noColumns");
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    std::shared_ptr<SceneNode> carNode = ModelLoader::loadModel("jeep.fbx", "first_pass_shader", true);
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;
    
    std::shared_ptr<CarController> _controller = std::make_shared<CarController>();
    carNode->setAnimator(_controller);
    carNode->setName("Car");
    
    RoadImporterExporter roadIE;
    roadIE.importFrom("roadData.txt");
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("roadNode", roadIE.getMarginPoints(), 10.0f);
    roadNode->setLocalTransform(IvVector3{0,-0.49,0}, IvVector3{0,0,0}, IvVector3{1,1,1});
    
    std::shared_ptr<SceneNode> environment=std::make_shared<Environment>("environment",roadIE.getMarginPoints());
    
    environment->setLocalTransform({0,0,0}, {0,0,0}, {1,1,1});
    cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    
    cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(carNode.get(), IvVector2(3.f, 10.f), true));
    
    IvVector3 pos = roadIE.getMarginPoints()[0].first + roadIE.getMarginPoints()[0].second;
    pos *= 10.0;
    pos /= 2.0;
    
    carNode->setLocalPosition(pos);
    
    std::shared_ptr<Camera> map_camera;
    std::shared_ptr<CameraSceneNode> map_cameraSceneNode;
    
    map_camera = std::make_shared<Camera>(70.0, 0.1, 200.0, 1280, 720);
    map_camera->setLookAt({0.f, 0.f, 0.f });
    map_camera->setPosition({0,25,0});
    map_camera->setRotation({0,1,0});
    
    map_cameraSceneNode = std::make_shared<CameraSceneNode>("map_camera",map_camera);
    
    map_cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(carNode.get(), IvVector2(80.f, 1.f), false));
    map_cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 80.f, -1.f));
    
    menu->setRoot(root);
    menu->getRoot()->addChild(roadNode);
    menu->getRoot()->addChild(environment);
    menu->getRoot()->addChild(carNode);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->getRoot()->addChild(map_cameraSceneNode);
    menu->setCamera(camera);
    menu->setMapCamera(map_camera);

}
//-------------------------------------------------------------------------------
// @RaceMenu::~RaceMenu()
//-------------------------------------------------------------------------------
RaceMenu::~RaceMenu()
{
    
}
