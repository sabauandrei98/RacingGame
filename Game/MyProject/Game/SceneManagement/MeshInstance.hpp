//
//  MeshInstance.hpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//
//  MeshInstance class binds a shader and it's uniforms with a mesh.
//  It needs a mesh a string for the shader name/location and a vector with uniform names

#pragma once

#include "Mesh.hpp"

#include <IvUniform.h>
#include <IvShaderProgram.h>

class MeshInstance : std::enable_shared_from_this<MeshInstance> {
public:
    // constructor(s) and destructor
    MeshInstance();
    ~MeshInstance();
    
    // public function(s) and method(s)
    void setMesh(const std::shared_ptr<Mesh>&);
    void setShader(const std::string&);
    void addShaderUniforms(const std::vector<std::string>&);
    void setWorldViewProjectionMatrix(const IvMatrix44&);
    void setWorldMatrix(const IvMatrix44&);
    
    // TODO: implement different uniform setters
    void setUniformValue(unsigned int, const IvVector4&);
    void setUniformValue(unsigned int, IvTexture*);
    void setUniformValue(unsigned int, const IvVector3&);
    void setUniformValue(unsigned int, float);
    
    const std::shared_ptr<Mesh>& getMesh() const;
    const std::vector<IvUniform*>& getShaderUniforms() const;
    IvShaderProgram* getShader();
    
private:
    // private variable(s)
    std::shared_ptr<Mesh>       _mesh;
    std::vector<IvUniform*>     _shader_uniforms;
    IvShaderProgram*            _shader;
    
    // private function(s) and method(s)
    void destroyShader();
};
