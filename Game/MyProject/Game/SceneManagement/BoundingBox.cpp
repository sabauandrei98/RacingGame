
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

// calculates the bounding box with given mesh and trasform matrix
void BoundingBox::calculate(const IvVector3& min, const IvVector3& max, const IvMatrix44& transform) {
    // sets the points absolute positions
    calculatePoints(min, max);
    
    for (IvVector3& i : _points) {
        IvVector4 vector = {i.x, i.y, i.z, 1.};
        vector = transform * vector;
        i = {vector.x, vector.y, vector.z};
    }
    
    _min = _points[0];
    _max = _points[7];
    _center = (_min + _max) / 2;
}

void BoundingBox::invalidate() {
    _min = IvVector3(std::numeric_limits<float>::infinity(),
                     std::numeric_limits<float>::infinity(),
                     std::numeric_limits<float>::infinity());
    
    _max = IvVector3(-std::numeric_limits<float>::infinity(),
                     -std::numeric_limits<float>::infinity(),
                     -std::numeric_limits<float>::infinity());
    
    _center = IvVector3(0.f, 0.f, 0.f);
}

void BoundingBox::expand(const IvVector3& v) {
    _min = IvVector3(std::min(_min.x, v.x), std::min(_min.y, v.y), std::min(_min.z, v.z));
    _max = IvVector3(std::max(_max.x, v.x), std::max(_max.y, v.y), std::max(_max.z, v.z));
    _center = (_min + _max) / 2;
    
    calculatePoints(_min, _max);
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

const BoundingBox::Bounds& BoundingBox::getPoints() const {
    return _points;
}

// --------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// --------------------------------

void BoundingBox::calculatePoints(const IvVector3& min, const IvVector3& max) {
    _points[0] = {min.x, min.y, min.z};
    _points[1] = {min.x, min.y, max.z};
    _points[2] = {min.x, max.y, min.z};
    _points[3] = {min.x, max.y, max.z};
    _points[4] = {max.x, min.y, min.z};
    _points[5] = {max.x, min.y, max.z};
    _points[6] = {max.x, max.y, min.z};
    _points[7] = {max.x, max.y, max.z};
}
