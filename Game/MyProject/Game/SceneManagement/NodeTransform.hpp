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
    // constructor(s) and destructor
    NodeTransform();
    
    // public function(s) and method(s)
    void set(const IvVector3&, const IvVector3&, const IvVector3&);
    void set(const IvVector3&);
    
    const IvMatrix44& getMatrix() const;
    const IvVector3& getPosition() const;
    const IvVector3& getScale() const;
    
    IvVector3   _position;
    IvVector3   _rotation;
    IvVector3   _scale;
    
    IvMatrix44  _transform_matrix;
    
    void calculate();
};
