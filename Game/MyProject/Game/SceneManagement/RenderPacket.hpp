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
    // public variable(s)d
    MeshInstance*   _mesh_instance;
    IvMatrix44      _world_view_projection_matrix;
    IvMatrix44      _world_matrix;
    IvPrimType      _prim_type = kTriangleStripPrim;
    
    bool            _use_depth = true;
    bool            _use_blend = true;
    bool            _use_wireframe = false;

    // public function(s) and method(s)
    void draw() const;
};
