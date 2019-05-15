#include "Game.hpp"
bool
IvGame::Create() 
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}

Game::Game() : IvGame()
{
}

Game::~Game()
{
    delete _infoManager;
}

bool 
Game::PostRendererInitialize()
{
    // Set up base class
    if ( !IvGame::PostRendererInitialize() )
        return false;
    

    MeshManager meshManager;
    
    _scene_graph = std::make_unique<SceneGraph>();
    _root = std::make_shared<SceneNode>("root");
    _child1 = HelperManager::BuildSphere("sphere", HelperManager::CreateMeshInstance( meshManager.GetMesh("sphere")));
    _child3 = HelperManager::BuildTexturedQuad("quad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"), "../../Game/Helper/Shaders/TextureShader"), "../../Textures/large.tga");
    _child2 = ModelLoader::loadModel("jeep.fbx", "example_shader");
    _child2->setName("Car");
    
    _camera = std::make_shared<Camera>(45.0, 0.1, 400.0, 1280, 720);
    _camera_scene_node = std::make_shared<CameraSceneNode>("camera", _camera);
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;

    _scene_graph->setRoot(_root);
    _scene_graph->setCamera(_camera);
    
    _controller = std::make_shared<CarController>();
    _child2->setAnimator(_controller);
    
    _root->addChild(_child2);
    _root->addChild(_child3);
    _root->addChild(_camera_scene_node);
    _camera_scene_node->setAnimator(std::make_shared<CameraFollowAnimator>(_child2.get(), IvVector2(3.f, 10.f), true));
    _camera_scene_node->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    _child3->setLocalTransform({0., 0., 0.}, {0., 0., -kPI/2.}, {300., 300., 300.});
    
    _camera->setRotation({0., 1., 0.});

    _infoManager = new InfoManager(_root.get());
    
    ::IvSetDefaultLighting();
  
    return true;
}

void
Game::UpdateObjects( float dt )
{
    _scene_graph->updateScene(dt);
}
void
Game::Render()
{

    _scene_graph->drawScene();

}

 
