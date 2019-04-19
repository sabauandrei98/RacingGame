//
//  BoundingBox.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 18/04/2019.
//

#pragma once

#include <IvVector3.h>

#include "Mesh.hpp"

class BoundingBox {
public:
    // typedefs
    typedef std::shared_ptr<Mesh>   MeshPtr;
    typedef std::vector<IvVector3>  Bounds;
    typedef std::vector<IvVector2>  BorderPoint;
    
    // public function(s) and method(s)
    void calculate(const MeshPtr&, const IvMatrix44&);
    void calculate(const Bounds&);
    
    const IvVector3& getMax() const;
    const IvVector3& getMin() const;
    const IvVector3& getCenter() const;
    const Bounds& getPoints() const;
    
private:
    // needed for intersection calculations
    IvVector3   _max;
    IvVector3   _min;
    IvVector3   _center;
    
    Bounds      _points;
    
    // private function(s) and method(s)
    void calculatePoints(const BorderPoint&, const IvMatrix44&);
};
