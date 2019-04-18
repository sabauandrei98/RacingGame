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
    // Set up base class
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
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
    
    _root->addChild(ModelLoader::loadModel("jeep.fbx", "example_shader"));
    _root->addChild(ModelLoader::loadModel("van.FBX", "example_shader"));
    _root->addChild(ModelLoader::loadModel("jeep.fbx", "example_shader"));
    _root->getChild(0)->setLocalPosition({5., 0., 0.});
    _root->getChild(1)->setLocalPosition({0., 5., 0.});
    
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

