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

// default constructor
MeshInstance::MeshInstance() :
    _mesh(nullptr), _shader(nullptr) {
    }

// special constructor
MeshInstance::MeshInstance(const std::shared_ptr<Mesh>& mesh, const std::string& shader_name, const std::vector<std::string>& shader_uniforms) :
    _mesh(mesh) {
        setShader(shader_name);
        addShaderUniforms(shader_uniforms);
    }

// destructor
MeshInstance::~MeshInstance() {
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

void MeshInstance::destroyShader() {
    if (_shader)
        IvRenderer::mRenderer->GetResourceManager()->Destroy(_shader);
    _shader = nullptr;
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// sets a new mesh
void MeshInstance::setMesh(const std::shared_ptr<Mesh>& mesh) {
    _mesh = mesh;
}

// sets a new shader
void MeshInstance::setShader(const std::string& shader_name) {
    _shader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(shader_name.c_str()), IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shader_name.c_str()));
}

// adds shader uniforms
void MeshInstance::addShaderUniforms(const std::vector<std::string>& shader_uniforms) {
    for (std::string i : shader_uniforms)
        _shader_uniforms.push_back(_shader->GetUniform(i.c_str()));
}

// sets the world view projection matrix
void MeshInstance::setWorldViewProjectionMatrix(const IvMatrix44& transform_matrix) {
    IvRenderer::mRenderer->SetWorldMatrix(transform_matrix);
}

// returns the mesh
std::shared_ptr<Mesh> MeshInstance::getMesh() {
    return _mesh;
}

IvShaderProgram* MeshInstance::getShader() {
    return _shader;
}

// returns the shader uniforms
std::vector<IvUniform*> MeshInstance::getShaderUniforms() {
    return _shader_uniforms;
}
