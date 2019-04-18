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
    
    // public function(s) and method(s)
    void setAttributes(const MeshPtr&, const IvMatrix44&);
    
    const IvVector3& getMax() const;
    const IvVector3& getMin() const;
    const IvVector3& getCenter() const;
    
private:
    // private variable(s)
    MeshPtr     _mesh;
    IvMatrix44  _transform;
    
    IvVector3   _max;
    IvVector3   _min;
    IvVector3   _center;
    
    Bounds      _points;
    
    // private function(s) and method(s)
    void Calculate();
};
