//
//  DeferredRenderer.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 14/05/2019.
//

#include "DeferredRenderer.hpp"

#include <IvRenderer.h>

DeferredRenderer::DeferredRenderer() {
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::vector<IvPVertex>  vertices;
    
    vertices.resize(4);
    
    vertices[0].position = {-1.f, 1.f, 0.f};
    vertices[1].position = {-1.f, -1.f, 0.f};
    vertices[2].position = {1.f, 1.f, 0.f};
    vertices[3].position = {1.f, -1.f, 0.f};
    
    mesh->setVertexBuffer(vertices, kPFormat);
    
    _renderable.setMesh(mesh);

    _shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile("../../Shaders/second_pass_shader"), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile("../../Shaders/second_pass_shader"));
    
    std::vector<IvRenderTarget*> _render_targets;
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // position
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // normal
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // diffuse color
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::DEPTH));    // depth
    
    _g_buffer = IvRenderer::mRenderer->GetResourceManager()->CreateFrameBuffer(_render_targets, 1280 * 2, 720 * 2);
}

void DeferredRenderer::Render(SceneGraph* scene_graph) {
    _g_buffer->Bind();
    IvRenderer::mRenderer->SetClearDepth(1.0);
    IvRenderer::mRenderer->ClearBuffers(kColorDepthClear);
    
    scene_graph->drawScene();
    
    _g_buffer->BindToDefault();
    IvRenderer::mRenderer->SetClearDepth(1.0);
    IvRenderer::mRenderer->ClearBuffers(kColorDepthClear);
    
    IvRenderTarget* render = _g_buffer->GetTextures()[1];
    _shader->SetUniform("TEXTURE", render->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _renderable.getMesh()->getVertexBuffer(), 4, _shader);
}
