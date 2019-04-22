#include "Game.hpp"
bool
IvGame::Create() 
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}

Game::Game() : IvGame()
{
    test=new TestHelper();
    testCollision=new TestCollision();
}

Game::~Game()
{
    delete test;
    delete testCollision;
    delete cameraTest;
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
    
    cameraTest = new CameraTestControler();
    if (!cameraTest)
        return false;

    ::IvSetDefaultLighting();

    testCollision->TestRayBox();
    
    
    return true;
}

void
Game::UpdateObjects( float dt )
{
    cameraTest->Update( dt );
    testCollision->Update(dt);

    
}
void
Game::Render()
{
    cameraTest->Render();
    //test->DrawBox();
    //testCollision->Render();
}

