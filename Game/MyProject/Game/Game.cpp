//
//  Game.cpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/2/19.
//

#include "Game.hpp"

bool IvGame::Create() {
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );
}

Game::Game() : IvGame() {
}

Game::~Game() {
}

bool Game::PostRendererInitialize() {
    if (!IvGame::PostRendererInitialize())
        return false;
    
    std::vector<IvTNPVertex>    vertices;
    std::vector<unsigned int>   indices;
    
    vertices.resize(4);
    vertices[0].position = {0.0, 0.0, 0.0};
    vertices[1].position = {0.0, 5.0, 0.0};
    vertices[2].position = {5.0, 0.0, 0.0};
    vertices[3].position = {5.0, 5.0, 0.0};
    
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    
    _mesh = std::make_shared<Mesh>();
    _mesh->setVertexBuffer(vertices, kTNPFormat);
    _mesh->setIndexBuffer(indices);
    
    _mesh_instance_1 = std::make_shared<MeshInstance>();
    _mesh_instance_1->setMesh(_mesh);
    _mesh_instance_1->setShader("shaders/example_shader");
    _mesh_instance_1->addShaderUniforms(std::vector<std::string>{"color"});
    _mesh_instance_1->setUniformValue(0, {1.0, 0.0, 0.0, 1.0});
    
    _mesh_instance_2 = std::make_shared<MeshInstance>();
    _mesh_instance_2->setMesh(_mesh);
    _mesh_instance_2->setShader("shaders/example_shader");
    _mesh_instance_2->addShaderUniforms(std::vector<std::string>{"color"});
    _mesh_instance_2->setUniformValue(0, {0.0, 1.0, 0.0, 1.0});
    
    _scene_node_0 = std::make_shared<SceneNode>("root");
    _scene_node_1 = std::make_shared<SceneNode>("scene_node_1");
    _scene_node_2 = std::make_shared<SceneNode>("scene_node_2");
    _camera_scene_node = std::make_shared<CameraSceneNode>("camera");
    _scene_node_1->setRenderable(_mesh_instance_1);
    _scene_node_2->setRenderable(_mesh_instance_2);
    _scene_node_1->setLocalPosition({1.0, 2.0, 3.0});
    _scene_node_2->setLocalPosition({-1.0, -2.0, 3.0});
    
    _scene_graph = std::make_unique<SceneGraph>();
    _scene_graph->setRoot(_scene_node_0);
    _scene_node_0->addChild(_scene_node_1);
    _scene_node_1->addChild(_scene_node_2);
    _scene_graph->setCamera(_camera_scene_node);
    
    ::IvSetDefaultLighting();
    return true;
}

void Game::UpdateObjects(float dt) {
    _scene_graph->updateScene(dt);
}

void Game::Render() {
    _scene_graph->drawScene();
    
    IvSetDefaultViewer(10.0f, 10.0f, 10.0f);
    IvDrawAxes();
}
