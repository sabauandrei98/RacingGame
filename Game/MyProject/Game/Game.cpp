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
   
}


bool 
Game::PostRendererInitialize()
{
    IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);
    IvRendererOGL::mRenderer->SetDepthWrite(true);
    IvRendererOGL::mRenderer->SetDepthTest(kLessEqualDepthTest);

    // Set up base class 
    if ( !IvGame::PostRendererInitialize() )
        return false;
    

    ::IvSetDefaultLighting();
    
    sceneGraph = new SceneGraph();
    
    std::shared_ptr<SceneNode> root = std::make_shared<SceneNode>("root");
    std::shared_ptr<CameraSceneNode> camera = std::make_shared<CameraSceneNode>("camera", 45.0, 0.1, 35.0, 1280, 720);
    camera->setPosition({0.f, -25.0f, 0.0f });
    camera->setRotation({0,0,1});
    camera->setLookAt({0.0f, 0.0f, 0.0f});
    
    sceneGraph->setRoot(root);
    sceneGraph->setCamera(camera);
    
    roadEditor = new RoadEditor(sceneGraph);

    return true;
}

void
Game::UpdateObjects( float dt )
{
    roadEditor->Update(dt);
}
void
Game::Render()
{
    sceneGraph->drawScene();
}

