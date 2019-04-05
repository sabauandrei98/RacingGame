//
//  RenderPacket.hpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//
//  RenderPacket class binds a MeshInstance with wvp_matrix and sets the states for rendering

#pragma once

#include <IvRendererOGL.h>

#include "MeshInstance.hpp"

class RenderPacket  {
public:
    // public variable(s)
    std::shared_ptr<MeshInstance>   _mesh_instance;
    IvMatrix44                      _world_view_projection_matrix;
    IvPrimType                      _prim_type = kTriangleListPrim;
    
    bool                    _use_depth = false;
    bool                    _use_blend = false;
    
    // public function(s) and method(s)
    void draw();
};
