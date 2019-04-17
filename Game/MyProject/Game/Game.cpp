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
    //delete cameraTest;
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
    
    Camera cam(45.0, 0.1, 35.0, 1280, 720);
    cam.setPosition({0.f, 10.0f, 0.0f });
    cam.setLookAt({0.0f, 0.0f, 0.0f});
    cam.setRotation({0.0f, 0.0f, 1.0f});
    
    _camera = std::make_shared<CameraSceneNode>("camera", cam);
    
    _scene_graph->setRoot(_root);
    _scene_graph->setCamera(_camera);
    _root->addChild(_camera);
    
    ModelLoader::loadModel("../../Models/jeep/jeep.fbx", "../../Models/jeep/jeep.tga", "../../Game/shaders/example_shader", _root.get());
    ModelLoader::loadModel("../../Models/jeep/jeep.fbx", "../../Models/jeep/jeep.tga", "../../Game/shaders/example_shader", _root.get());
    
    _root->getChild(1)->setLocalPosition({0., 0., 0.});
    _root->getChild(2)->setLocalPosition({5., 0., 5.});

    // Set up base class 
    if ( !IvGame::PostRendererInitialize())
        return false;
    
//    cameraTest = new CameraTestControler();
//    if (!cameraTest)
//        return false;

    ::IvSetDefaultLighting();

    return true;
}

void
Game::UpdateObjects( float dt )
{
    //cameraTest->Update(dt);
    _scene_graph->updateScene(dt);
}
void
Game::Render()
{
    //cameraTest->Render();
    IvDrawAxes();
    _scene_graph->drawScene();
}

