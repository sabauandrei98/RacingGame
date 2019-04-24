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

// destructor
MeshInstance::~MeshInstance() {
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
void MeshInstance::setWorldViewProjectionMatrix(const IvMatrix44& matrix) {
    IvRenderer::mRenderer->SetWVPMat(matrix);
}

// sets the shader uniform values with vec4
void MeshInstance::setUniformValue(unsigned int index, const IvVector4& value) {
    _shader_uniforms[index]->SetValue(value, 0);
}

// sets the shader uniform values with texture
void MeshInstance::setUniformValue(unsigned int index, IvTexture* value) {
    _shader_uniforms[index]->SetValue(value);
}

// returns the mesh
const std::shared_ptr<Mesh>& MeshInstance::getMesh() const {
    return _mesh;
}

// returns the shader
IvShaderProgram* MeshInstance::getShader() {
    return _shader;
}

// returns the shader uniforms
const std::vector<IvUniform*>& MeshInstance::getShaderUniforms() const {
    return _shader_uniforms;
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

void MeshInstance::destroyShader() {
    if (_shader)
        IvRenderer::mRenderer->GetResourceManager()->Destroy(_shader);
    _shader = nullptr;
}

