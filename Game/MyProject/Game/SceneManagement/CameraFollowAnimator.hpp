//
//  CameraAnimator.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 07/05/2019.
//

#pragma once

#include "NodeAnimator.hpp"

class CameraFollowAnimator : public NodeAnimator {
public:
    CameraFollowAnimator(const SceneNode*, const IvVector2&, bool);
    
    void animateNode(float, SceneNode*);
    
    void setMinMaxDistance(float, float);
    void setSmoothingSpeed(float);
    
private:
    const SceneNode*    _target;            // the target that needs to be followed
    const IvVector2     _camera_circle;     // contains the circle which defines all of the posible
                                            // desired positions of the camera around the car
    const bool          _needs_smoothing;   // defines if the camera needs smoothing during follow
    
    float               _smoothing_speed;
    
    // distances between the camera and the target if the camera needs smoothing
    float               _min_distance;
    float               _max_distance;
};
