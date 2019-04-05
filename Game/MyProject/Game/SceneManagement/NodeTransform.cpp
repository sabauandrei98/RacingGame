//
//  NodeTransform.cpp
//  Game
//
//  Created by Tamas Both - (p) on 04/04/2019.
//

#include "NodeTransform.hpp"

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// sets the position, the rotation and the scala
void NodeTransform::set(const IvVector3& position, const IvVector3& rotation, const IvVector3& scale) {
    _position = position;
    _rotation = rotation;
    _scale = scale;
    
    _is_dirty = true;
}

// sets the position
void NodeTransform::set(const IvVector3& position) {
    _position = position;
    
    _is_dirty = true;
}

// returns the transform matrix
const IvMatrix44& NodeTransform::getMatrix() {
    if (_is_dirty) {
        calculate();
        _is_dirty = false;
    }
    
    return _transform_matrix;
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

// calculates the transform matrix
void NodeTransform::calculate() {
    IvMatrix44 position;
    IvMatrix44 rotation;
    IvMatrix44 scale;
    
    _transform_matrix.Identity();
    position.Identity();
    rotation.Identity();
    scale.Identity();
    
    position.Translation(_position);
    rotation.Rotation(_rotation[2], _rotation[1], _rotation[0]);
    scale.Scaling(_scale);
    
    _transform_matrix = position * rotation * scale * _transform_matrix;
}

