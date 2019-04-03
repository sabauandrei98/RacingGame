//
//  RenderPacket.cpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#include "RenderPacket.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

// default constructor
RenderPacket::RenderPacket() :
    _mesh_instance(nullptr) {
        _world_view_projection_matrix.Identity();
    }

// special constructor
RenderPacket::RenderPacket(std::shared_ptr<MeshInstance> instace_pointer) :
    _mesh_instance(instace_pointer) {
        _world_view_projection_matrix.Identity();
    }

// special constructor
RenderPacket::RenderPacket(std::shared_ptr<MeshInstance> instace_pointer, const IvMatrix44& matrix) :
    _mesh_instance(instace_pointer), _world_view_projection_matrix(matrix) {

    }

// destructor
RenderPacket::~RenderPacket() {
    
}

// -----------------------------------
// PROTECTED FUNCTION(S) AND METHOD(S)
// -----------------------------------

// sets up the environment for drawing
void RenderPacket::setUpDrawing() {
    IvRenderer::mRenderer->SetShaderProgram(_mesh_instance->getShader());
    _mesh_instance->setWorldViewProjectionMatrix(_world_view_projection_matrix);
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// sets the mesh instance
void RenderPacket::setMeshInstance(std::shared_ptr<MeshInstance> instace_pointer) {
    _mesh_instance = instace_pointer;
}

// sets the world view projection matrix
void RenderPacket::setWorldViewProjectionMatrix(const IvMatrix44& matrix) {
    _world_view_projection_matrix = matrix;
}

// returns the mesh instance
std::shared_ptr<MeshInstance> RenderPacket::getMeshInstance() {
    return _mesh_instance;
}

// returns the world view projection matrix
IvMatrix44 RenderPacket::getWorldViewProjectionMatrix() {
    return _world_view_projection_matrix;
}

// draws the geometry
void RenderPacket::Draw() {
    setUpDrawing();
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _mesh_instance->getMesh()->getVertexBuffer(), _mesh_instance->getMesh()->getIndexBuffer());
}
