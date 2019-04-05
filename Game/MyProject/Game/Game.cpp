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
    
    _mesh_instance = std::make_shared<MeshInstance>();
    _mesh_instance->setMesh(_mesh);
    _mesh_instance->setShader("shaders/example_shader");
    _mesh_instance->addShaderUniforms(std::vector<std::string>{"color"});
    _mesh_instance->setUniformValue(0, {1.0, 0.0, 0.0, 1.0});
    
    ::IvSetDefaultLighting();
    return true;
}

void Game::UpdateObjects(float dt) {
}

void Game::Render() {
    RenderPacket    render_packet;
    render_packet._mesh_instance = _mesh_instance;
    render_packet.draw();

    IvSetDefaultViewer(10.0f, 10.0f, 10.0f);
    IvDrawAxes();
}
