//
//  DeferredRenderer.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 14/05/2019.
//

#include "DeferredRenderer.hpp"

#include <IvRenderer.h>

void DeferredRenderer::setUpGBuffer() {
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::vector<IvPVertex>  vertices;
    
    vertices.resize(4);
    
    vertices[0].position = {-1.f, 1.f, 0.f};
    vertices[1].position = {-1.f, -1.f, 0.f};
    vertices[2].position = {1.f, 1.f, 0.f};
    vertices[3].position = {1.f, -1.f, 0.f};
    
    mesh->setVertexBuffer(vertices, kPFormat);
    
    _renderable.setMesh(mesh);
    
    _shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile("../../Shaders/example_shader"), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile("../../Shaders/example_shader"));
    
    IvRenderer::mRenderer->SetShaderProgram(_shader);
    glUniform1i(glGetUniformLocation(_shader->GetProgramID(), "TEXTURE"), 0);
    
    std::vector<IvRenderTarget*> _render_targets;
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // position
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // normal
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // diffuse color
    _render_targets.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::DEPTH));    // depth
    
    _g_buffer = IvRenderer::mRenderer->GetResourceManager()->CreateFrameBuffer(_render_targets, 1280, 720);
}

void DeferredRenderer::setUpPreviousBuffer() {
    _copy_shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile("../../Shaders/position_shader"), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile("../../Shaders/position_shader"));
    
    IvRenderer::mRenderer->SetShaderProgram(_copy_shader);
    glUniform1i(glGetUniformLocation(_copy_shader->GetProgramID(), "POS"), 0);
    
    std::vector<IvRenderTarget*> _render_target;
    _render_target.push_back(IvRenderer::mRenderer->GetResourceManager()->CreateRenderTarget(RenderTargetType::COLOR));    // position
    
    _previous_position = IvRenderer::mRenderer->GetResourceManager()->CreateFrameBuffer(_render_target, 1280, 720);
}

void DeferredRenderer::setUpMotionBlur() {
    _blur_shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile("../../Shaders/blur_shader"), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile("../../Shaders/blur_shader"));
    
    IvRenderer::mRenderer->SetShaderProgram(_blur_shader);
    glUniform1i(glGetUniformLocation(_blur_shader->GetProgramID(), "PREVIOUS_POSITION"), 0);
    glUniform1i(glGetUniformLocation(_blur_shader->GetProgramID(), "CURRENT_POSITION"), 1);
    glUniform1i(glGetUniformLocation(_blur_shader->GetProgramID(), "COLOR"), 2);
}

void DeferredRenderer::setUpDebugScreen() {
    std::shared_ptr<Mesh> mesh1 = std::make_shared<Mesh>();
    std::shared_ptr<Mesh> mesh2 = std::make_shared<Mesh>();
    std::shared_ptr<Mesh> mesh3 = std::make_shared<Mesh>();
    std::vector<IvTCPVertex>  vertices;
    
    vertices.resize(4);
    
    vertices[0].position = {-1.f, 1.f, -0.001f};
    vertices[1].position = {-1.f, 0.35f, -0.001f};
    vertices[2].position = {-0.3333f, 1.f, -0.001f};
    vertices[3].position = {-0.33333f, 0.35f, -0.001f};
    
    vertices[0].texturecoord = {0.f, 1.f};
    vertices[1].texturecoord = {0.f, 0.f};
    vertices[2].texturecoord = {1.f, 1.f};
    vertices[3].texturecoord = {1.f, 0.f};
    
    mesh1->setVertexBuffer(vertices, kTCPFormat);
    _screen1.setMesh(mesh1);
    
    vertices[0].position = {-0.3333f, 1.f, -0.001f};
    vertices[1].position = {-0.3333f, 0.35f, -0.001f};
    vertices[2].position = {0.3333f, 1.f, -0.001f};
    vertices[3].position = {0.33333f, 0.35f, -0.001f};
    
    mesh2->setVertexBuffer(vertices, kTCPFormat);
    _screen2.setMesh(mesh2);
    
    vertices[0].position = {0.3333f, 1.f, -0.001f};
    vertices[1].position = {0.3333f, 0.35f, -0.001f};
    vertices[2].position = {1.f, 1.f, -0.001f};
    vertices[3].position = {1.f, 0.35f, -0.001f};
    
    mesh3->setVertexBuffer(vertices, kTCPFormat);
    _screen3.setMesh(mesh3);
    
    _debug_shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile("../../Shaders/debug_shader"), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile("../../Shaders/debug_shader"));
    
    IvRenderer::mRenderer->SetShaderProgram(_debug_shader);
    glUniform1i(glGetUniformLocation(_debug_shader->GetProgramID(), "TEXTURE"), 0);
}

void DeferredRenderer::renderNoEffect() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[2]->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _renderable.getMesh()->getVertexBuffer(), 4, _shader);
}

void DeferredRenderer::renderMotionBlur() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _previous_position->GetTextures()[0]->GetReference());
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[0]->GetReference());
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[2]->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _renderable.getMesh()->getVertexBuffer(), 4, _blur_shader);
    
    _previous_position->Bind();
    IvRenderer::mRenderer->ClearBuffers(kColorDepthClear);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[0]->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _renderable.getMesh()->getVertexBuffer(), 4, _copy_shader);
    _previous_position->BindToDefault();
}

void DeferredRenderer::showDebugScreen() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[0]->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _screen1.getMesh()->getVertexBuffer(), 4, _debug_shader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[1]->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _screen2.getMesh()->getVertexBuffer(), 4, _debug_shader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _g_buffer->GetTextures()[2]->GetReference());
    
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, _screen3.getMesh()->getVertexBuffer(), 4, _debug_shader);
}

DeferredRenderer::DeferredRenderer() {
    setUpGBuffer();
    setUpPreviousBuffer();
    setUpMotionBlur();
    setUpDebugScreen();
}

void DeferredRenderer::Render(SceneGraph* scene_graph) {
    _g_buffer->Bind();
    IvRenderer::mRenderer->ClearBuffers(kColorDepthClear);
    scene_graph->drawScene();

    _g_buffer->BindToDefault();
    IvRenderer::mRenderer->ClearBuffers(kColorDepthClear);
    
    if (_needs_motion_blur)
        renderMotionBlur();
    else
        renderNoEffect();
    
    if (_needs_debug_screen)
        showDebugScreen();
}
