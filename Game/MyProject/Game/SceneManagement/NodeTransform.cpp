//
//  NodeTransform.cpp
//  Game
//
//  Created by Tamas Both - (p) on 04/04/2019.
//

#include "NodeTransform.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

NodeTransform::NodeTransform() {
    _transform_matrix.Identity();
    _position = {0., 0., 0.};
    _rotation = {0., 0., 0.};
    _scale = {1., 1., 1.};
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// sets the position, the rotation and the scala
void NodeTransform::set(const IvVector3& position, const IvVector3& rotation, const IvVector3& scale) {
    _position = position;
    _rotation = rotation;
    _scale = scale;
    
    calculate();
}

// sets the position
void NodeTransform::set(const IvVector3& position) {
    _position = position;
    
    calculate();
}

// returns the transform matrix
const IvMatrix44& NodeTransform::getMatrix() {
    return _transform_matrix;
}

const IvVector3& NodeTransform::getPosition() const{
    return _position;
    
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
    position.Translation(_position);
    rotation.Rotation(_rotation[2], rotation[1], rotation[0]);
    scale.Scaling(_scale);
    
    _transform_matrix = position * rotation * scale * _transform_matrix;
}
