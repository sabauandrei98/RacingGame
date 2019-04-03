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
    std::string                 shader;
    
    vertices.resize(4);
    vertices[0].position = {0.0, 0.0, 0.0};
    vertices[1].position = {3.0, 3.0, 3.0};
    vertices[2].position = {-2.0, 0.0, 3.0};
    vertices[3].position = {0.0, 5.0, 0.0};
    
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(0);
    
    shader = "shaders/exampleShader";
    
    _mesh = std::make_shared<Mesh>(vertices, indices);
    _mesh_instance = std::make_shared<MeshInstance>(_mesh, shader, std::vector<std::string>());
    _render_packet = std::make_shared<RenderPacket>(_mesh_instance);
    
    ::IvSetDefaultLighting();
    return true;
}

void Game::UpdateObjects(float dt) {
    
}

void Game::Render() {
    IvSetDefaultViewer(-10.0f, -10.0f, -10.0f);
    IvDrawAxes();
    _render_packet->Draw();
}
