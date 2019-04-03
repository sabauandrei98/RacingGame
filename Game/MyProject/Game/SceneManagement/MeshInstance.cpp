//
//  MeshInstance.cpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#include "MeshInstance.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

MeshInstance::MeshInstance() :
    _mesh(nullptr), _shader(nullptr) {
        
    }

MeshInstance::MeshInstance(const std::vector<IvTNPVertex>& vertices, const std::vector<unsigned int>& indices, const std::string& shader_name, const std::vector<std::string>& shader_uniforms) {
        setMesh(vertices, indices);
        setShader(shader_name);
        setShaderUniforms(shader_uniforms);
    }

MeshInstance::~MeshInstance() {
    if (_mesh)
        delete _mesh;
    destroyShader();
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

void MeshInstance::destroyShader() {
    IvRenderer::mRenderer->GetResourceManager()->Destroy(_shader);
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

void MeshInstance::setMesh(const std::vector<IvTNPVertex>& vertices, const std::vector<unsigned int>& indices) {
    if (_mesh)
        delete _mesh;
    
    _mesh = new Mesh(vertices, indices);
}

void MeshInstance::setShader(const std::string& shader_name) {
    if (_shader)
        destroyShader();
    
    _shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(shader_name.c_str()), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shader_name.c_str()));
}

void MeshInstance::setShaderUniforms(const std::vector<std::string>& shader_uniforms) {
    for (std::string i : shader_uniforms)
        _shader_uniforms.push_back(_shader->GetUniform(i.c_str()));
}

void MeshInstance::setWorldViewProjectionMatrix(const IvMatrix44& transform_matrix) {
    IvRenderer::mRenderer->SetWorldMatrix(transform_matrix);
}
