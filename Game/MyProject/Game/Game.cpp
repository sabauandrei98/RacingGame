bool IvGame::Create()
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
    
}
Game::Game()
{
    //mPlayer=new Player();
    test=new Test();
}
Game::~Game()
{
    //delete mPlayer;
    delete test;
}
bool Game::PostRendererInitialize()
{
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    test->Setup("testShader");
    
    ::IvSetDefaultLighting();
    
    return true;
}

void Game::UpdateObjects( float dt )
{
    
}

void Game::Render()
{
    test->Draw();
}
