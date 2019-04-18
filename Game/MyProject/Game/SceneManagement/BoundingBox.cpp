//
//  BoundingBox.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 18/04/2019.
//

#include "BoundingBox.hpp"

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

void BoundingBox::setAttributes(const MeshPtr& mesh, const IvMatrix44& transform) {
    _mesh = mesh;
    _transform = transform;
    Calculate();
}

const IvVector3& BoundingBox::getMax() const {
    return _max;
}

const IvVector3& BoundingBox::getMin() const {
    return _min;
}

const IvVector3& BoundingBox::getCenter() const {
    return _center;
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

void BoundingBox::Calculate() {
    
}
