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
 
    test->Setup();

    // Set up base class 
    if ( !IvGame::PostRendererInitialize() )
        return false;
    
    cameraTest = new CameraTestControler();
    if (!cameraTest)
        return false;
    
    std::vector<IvTCPVertex> vertices;
    vertices.resize(5);
    
    vertices[0].position = {-2., -2., 0.};
    vertices[1].position = {2., -2., 0.};
    vertices[2].position = {2., 2., 0.};
    vertices[3].position = {-2., 2., 0.};
    vertices[4].position = {0., 0., 3.};
    
    vertices[0].color = {255, 0, 0, 255};
    vertices[1].color = {0, 255, 0, 255};
    vertices[2].color = {0, 0, 255, 255};
    vertices[3].color = {255, 255, 0, 255};
    vertices[4].color = {255, 0, 255, 255};
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    mesh->setVertexBuffer(vertices, kTCPFormat);
    mesh->setIndexBuffer({0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 0, 3, 4});
    
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    mesh_instance->setMesh(mesh);
    mesh_instance->setShader("../../Game/shaders/example_shader");
    
    root = std::make_shared<SceneNode>("root");
    child1 = std::make_shared<SceneNode>("child1");
    child2 = std::make_shared<SceneNode>("child2");
    root->setRenderable(mesh_instance);
    child1->setRenderable(mesh_instance);
    child2->setRenderable(mesh_instance);
    
    child1->setLocalPosition({5., 0., 0.});
    child2->setLocalTransform({0., 5., 0.}, {2., 1., 1.}, {1., 1., 1.});
    
    root->addChild(child1);
    root->addChild(child2);
    
    _scene_graph = std::make_unique<SceneGraph>();
    _scene_graph->setRoot(root);
    _scene_graph->setCamera(std::make_shared<CameraSceneNode>("camera"));

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
    
    IvSetWorldIdentity();
    
    // bad drawing just for test the bounging box
    BoundingBox box;
    Mesh* mesh = new Mesh();
    std::vector<IvTCPVertex> vertices;
    
    box = root->getBoundingBox();
    vertices.resize(8);
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);
    mesh->setIndexBuffer({0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7});

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());

    box = child1->getBoundingBox();
    vertices.resize(8);
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);
    mesh->setIndexBuffer({0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7});

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());

    box = child2->getBoundingBox();
    vertices.resize(8);
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);
    mesh->setIndexBuffer({0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7});

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());

    delete mesh;
}

