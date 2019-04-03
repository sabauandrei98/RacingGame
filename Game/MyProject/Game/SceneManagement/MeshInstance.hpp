//
//  MeshInstance.hpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#pragma once

#include "Mesh.hpp"

#include <IvUniform.h>
#include <IvShaderProgram.h>

class MeshInstance : std::enable_shared_from_this<MeshInstance> {
private:
    // private variable(s)
    std::shared_ptr<Mesh>   _mesh;
    IvShaderProgram*        _shader;
    std::vector<IvUniform*> _shader_uniforms;
    
    // private function(s) and method(s)
    void destroyShader();
    
public:
    // constructor(s) and destructor
    MeshInstance();
    MeshInstance(const std::shared_ptr<Mesh>&, const std::string&, const std::vector<std::string>&);
    ~MeshInstance();
    
    // public function(s) and method(s)
    void setMesh(const std::shared_ptr<Mesh>&);
    void setShader(const std::string&);
    void addShaderUniforms(const std::vector<std::string>&);
    void setWorldViewProjectionMatrix(const IvMatrix44&);
    
    // TODO: implement uniform setters
    
    std::shared_ptr<Mesh> getMesh();
    IvShaderProgram* getShader();
    std::vector<IvUniform*> getShaderUniforms();
};
