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
void BoundingBox::calculate(const MeshPtr& mesh, const IvMatrix44& transform) {
    calculatePoints(mesh->getMinMaxVertices(), transform);
}

// calculates the bounding box with given bounding boxes
void BoundingBox::calculate(const BoundingBox::Bounds& points) {
    BorderPoint borders;
    IvMatrix44  transform;
    
    // sets the starting values
    borders.resize(3);
    borders[0].x = points[0].x;
    borders[0].y = points[0].x;
    borders[1].x = points[0].y;
    borders[1].y = points[0].y;
    borders[2].x = points[0].z;
    borders[2].y = points[0].z;
    
    // calculates the min and max for each axe
    for (IvVector3 i : points) {
        if (i.x < borders[0].x)
            borders[0].x = i.x;
        if (i.x > borders[0].y)
            borders[0].y = i.x;
        
        if (i.y < borders[1].x)
            borders[1].x = i.y;
        if (i.y > borders[1].y)
            borders[1].y = i.y;
        
        if (i.z < borders[2].x)
            borders[2].x = i.z;
        if (i.z > borders[2].y)
            borders[2].y = i.z;
    }
    
    calculatePoints(borders, transform);
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

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// --------------------------------

void BoundingBox::calculatePoints(const BorderPoint& points, const IvMatrix44& transform) {
    _points.resize(8);
    
    // sets the points absolute positions
    _points[0] = {points[0].x, points[1].x, points[2].x};
    _points[1] = {points[0].x, points[1].x, points[2].y};
    _points[2] = {points[0].x, points[1].y, points[2].x};
    _points[3] = {points[0].x, points[1].y, points[2].y};
    _points[4] = {points[0].y, points[1].x, points[2].x};
    _points[5] = {points[0].y, points[1].x, points[2].y};
    _points[6] = {points[0].y, points[1].y, points[2].x};
    _points[7] = {points[0].y, points[1].y, points[2].y};
    
    for (IvVector3& i : _points) {
        IvVector4 vector = {i.x, i.y, i.z, 1.};
        vector = transform * vector;
        i = {vector.x, vector.y, vector.z};
    }
    
    _min = _points[0];
    _max = _points[7];
    _center = (_min + _max) / 2;
}
