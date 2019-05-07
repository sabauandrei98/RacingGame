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
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;

    _scene_graph = std::make_unique<SceneGraph>();
    _root = std::make_shared<SceneNode>("root");
    _child1 = std::make_shared<SceneNode>("child1");
    _child2 = std::make_shared<SceneNode>("child2");
    _child3 = std::make_shared<SceneNode>("child3");
    _camera = std::make_shared<Camera>(45.0, 0.1, 65.0, 1280, 720);
    _camera_scene_node = std::make_shared<CameraSceneNode>("camera", _camera);

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

    mesh->setVertexBuffer(vertices, kTCPFormat);
    mesh->setIndexBuffer({0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 0, 3, 4});

    mesh_instance->setMesh(mesh);
    mesh_instance->setShader("../../Game/shaders/example_shader");

    std::shared_ptr<SceneNode> model1=ModelLoader::loadModel("jeep.fbx", "example_shader");
    model1->setLocalTransform(IvVector3{2,0,10}, IvVector3{0,2,0}, IvVector3{4,4,4});
    carController = std::make_shared<CarController>(model1);
    model1->setAnimator(carController);
    
    _scene_graph->setRoot(_root);
    _scene_graph->setCamera(_camera);

    _root->addChild(_camera_scene_node);
    _root->addChild(_child1);
    _root->addChild(_child2);
    _root->addChild(model1);
    _root->setRenderable(mesh_instance);

    _child1->setRenderable(mesh_instance);
    _child2->setRenderable(mesh_instance);
    _child3->setRenderable(mesh_instance);
    _child2->addChild(_child3);
    _child1->setLocalPosition({5., 0., 0.});
    _child2->setLocalTransform({0., 5., 0.}, {2., 1., 1.}, {1., 1., 1.});
    _child3->setLocalTransform({0., 2., -4.}, {0., 0., 1.5}, {2., 0.5, 1.});

    _camera->setPosition({0.f, 50.0f, 0.0f });
    _camera->setLookAt({0.0f, 0.0f, 0.0f});
    _camera->setRotation({0, 0.0, 1.0f});
  
    testCollision=new TestCollision();
    testCollision->TestRayBox();
    
    _state_controller = std::make_unique<StateController>();
    
    ::IvSetDefaultLighting();
   
  
    return true;
}

void
Game::UpdateObjects( float dt )
{
    _state_controller->update();
    _scene_graph->updateScene(dt);
    testCollision->Update(dt);
}
void
Game::Render()
{
   _scene_graph->drawScene();

   //  it's ugly but is only for testing
    IvSetWorldIdentity();
    IvSetViewMatrix(_camera->getViewMatrix());
    IvSetProjectionMatrix(_camera->getProjectionMatrix());

    BoundingBox box;
    Mesh* mesh = new Mesh();
    std::vector<IvTCPVertex> vertices;
    
    vertices.resize(8);

    box = _root->getBoundingBox();
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);
    mesh->setIndexBuffer({0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7});

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());

    box = _child1->getBoundingBox();
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());

    box = _child2->getBoundingBox();
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());

    box = _child3->getBoundingBox();
    for (int i = 0; i < 8; i++) {
        vertices[i].position = box.getPoints()[i];
        vertices[i].color = {255, 255, 255, 255};
    }

    mesh->setVertexBuffer(vertices, kTCPFormat);

    IvRenderer::mRenderer->Draw(kLineListPrim, mesh->getVertexBuffer(), mesh->getIndexBuffer());


    delete mesh;
  
    testCollision->Render();
}

 
