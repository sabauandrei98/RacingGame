//
//  RenderPacket.cpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#include "RenderPacket.hpp"

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// sets the states and draws the function
void RenderPacket::draw() const {
    // setting up shader and wvp_matrix
    IvRenderer::mRenderer->SetShaderProgram(_mesh_instance->getShader());
    _mesh_instance->setWorldViewProjectionMatrix(_world_view_projection_matrix);
    _mesh_instance->setWorldViewMatrix(_world_view_matrix);

    
    // setting up the states
    if (_use_depth)
        IvRendererOGL::mRenderer->SetDepthWrite(true);
    else
        IvRendererOGL::mRenderer->SetDepthWrite(false);
    
    if (_use_blend)
        IvRendererOGL::mRenderer->SetBlendFunc(kSrcAlphaBlendFunc, kOneMinusSrcAlphaBlendFunc, kAddBlendOp);
    else
        IvRendererOGL::mRenderer->SetBlendFunc(kOneBlendFunc, kZeroBlendFunc, kAddBlendOp);
    
    if(_use_wireframe)
        IvRenderer::mRenderer->SetFillMode(kWireframeFill);
    else
        IvRenderer::mRenderer->SetFillMode(kSolidFill);
    
    // drawing
    if (_mesh_instance->getMesh()->getIndexBuffer())
        IvRenderer::mRenderer->Draw(_prim_type, _mesh_instance->getMesh()->getVertexBuffer(), _mesh_instance->getMesh()->getIndexBuffer());
    else
        IvRenderer::mRenderer->Draw(_prim_type, _mesh_instance->getMesh()->getVertexBuffer(), _mesh_instance->getMesh()->getBufferSize());
}
