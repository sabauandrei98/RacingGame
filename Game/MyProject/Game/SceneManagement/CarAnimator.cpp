//
//  CarAnimator.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 03/05/2019.
//

#include "CarAnimator.hpp"

// hardcoded now for simple car driving
void CarAnimator::animateNode(float dt, SceneNode* scene_node) {
    velocity = {0., 0., 0.};
    
    if (IvGame::mGame->mEventHandler->IsKeyDown('w')) {
        velocity = {0., 0., 25.};
        
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
            velocity = {-10., 0, velocity.z};
        
        else if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
            velocity = {10., 0, velocity.z};
    }
    
    else if (IvGame::mGame->mEventHandler->IsKeyDown('s')) {
        velocity = {0., 0., -15.};
        
        if (IvGame::mGame->mEventHandler->IsKeyDown('d'))
            velocity = {-10., 0, velocity.z};
        
        else if (IvGame::mGame->mEventHandler->IsKeyDown('a'))
            velocity = {10., 0, velocity.z};
    }
    
    scene_node->setLocalPosition(scene_node->getLocalPositon() + velocity * dt);
}

const IvVector3& CarAnimator::getVelocity() const {
    return velocity;
}
