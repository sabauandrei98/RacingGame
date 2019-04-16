#include "Game.hpp"

bool
IvGame::Create() 
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}

Game::Game() : IvGame()
{
    test=new TestRT(); 
}

Game::~Game()
{
    delete test;
    delete cameraTest;
}


bool 
Game::PostRendererInitialize()
{
    test->Create();
    
    IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);
    IvRendererOGL::mRenderer->SetDepthWrite(true);
    IvRendererOGL::mRenderer->SetDepthTest(kLessEqualDepthTest);
 
    test->Setup();
    
    _scene_graph = std::make_unique<SceneGraph>();
    _root = std::make_shared<SceneNode>("root");
    _camera = std::make_shared<CameraSceneNode>("camera");
    
    _scene_graph->setRoot(_root);
    _scene_graph->setCamera(_camera);
    
    ModelLoader::loadModel("../../Models/jeep/jeep.fbx", "../../Game/shaders/example_shader", _root.get());
    ModelLoader::loadModel("../../Models/van/van.FBX", "../../Game/shaders/example_shader", _root.get());
    _root->getChild(1)->setLocalPosition({5.0, 0., 0.});
    _root->setLocalPosition({0.0, 5.0, 0.0});

    // Set up base class 
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    cameraTest = new CameraTestControler();
    if (!cameraTest)
        return false;

    ::IvSetDefaultLighting();

    return true;
}

void
Game::UpdateObjects( float dt )
{
    cameraTest->Update( dt );
    _scene_graph->updateScene(dt);
}
void
Game::Render()
{
        cameraTest->Render();
    _scene_graph->drawScene();
}

