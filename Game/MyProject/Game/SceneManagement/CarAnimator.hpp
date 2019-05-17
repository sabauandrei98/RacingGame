//
//  CarAnimator.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 03/05/2019.
//

#pragma once

#include "NodeAnimator.hpp"
#include "../Game.hpp"

class CarAnimator : public NodeAnimator {
public:
    void animateNode(float, SceneNode*);
    const IvVector3& getVelocity() const;
    
    ~CarAnimator() {}
    
private:
    IvVector3 velocity;
};
