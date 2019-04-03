//
//  RenderPacket.hpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#pragma once

#include "MeshInstance.hpp"

class RenderPacket : std::enable_shared_from_this<RenderPacket> {
protected:
    // protected variable(s)
    std::shared_ptr<MeshInstance>   _mesh_instance;
    IvMatrix44                      _world_view_projection_matrix;
    
    // protected function(s) and method(s)
    void setUpDrawing();
    
public:
    // constructor(s) and destructor
    RenderPacket();
    RenderPacket(std::shared_ptr<MeshInstance>);
    RenderPacket(std::shared_ptr<MeshInstance>, const IvMatrix44&);
    virtual ~RenderPacket();
    
    // public function(s) and method(s)
    void setMeshInstance(std::shared_ptr<MeshInstance>);
    void setWorldViewProjectionMatrix(const IvMatrix44&);
    
    std::shared_ptr<MeshInstance> getMeshInstance();
    IvMatrix44 getWorldViewProjectionMatrix();
    
    virtual void Draw();
};
