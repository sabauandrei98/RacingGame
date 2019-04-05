//
//  NodeTransform.hpp
//  Game
//
//  Created by Tamas Both - (p) on 04/04/2019.
//
//  NodeTransform class manages the transformations.

#pragma once

#include <IvVector3.h>
#include <IvMatrix44.h>

class NodeTransform {
public:
    // public function(s) and method(s)
    void set(const IvVector3&, const IvVector3&, const IvVector3&);
    void set(const IvVector3&);
    
    const IvMatrix44& getMatrix();
    
private:
    // private variable(s)
    IvVector3   _position;
    IvVector3   _rotation;
    IvVector3   _scale;
    
    IvMatrix44  _transform_matrix;
    bool        _is_dirty = true;
    
    void calculate();
};