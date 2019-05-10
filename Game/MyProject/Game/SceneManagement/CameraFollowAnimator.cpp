//
//  CameraAnimator.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 07/05/2019.
//

#include "CameraFollowAnimator.hpp"

#include "CameraSceneNode.hpp"
#include "CarController.hpp"

CameraFollowAnimator::CameraFollowAnimator(const SceneNode* target, const IvVector2& camera_circle, bool needs_smoothing) :
    _target(target), _camera_circle(camera_circle), _needs_smoothing(needs_smoothing) {
        // setting default values
        if (needs_smoothing)
            _smoothing_speed = 17.f;
    }

void CameraFollowAnimator::animateNode(float dt, SceneNode* node_to_animate) {
    CameraSceneNode*    camera_node = (CameraSceneNode*)node_to_animate;
    
    IvVector3   distance;           // distance between the camera and the target
    IvVector3   velocity;           // velocity of the target car
    IvVector3   camera_position;    // the desired position of the camera
    
    distance = camera_node->getAbsolutePosition() - _target->getAbsolutePosition();
    velocity = ((CarController*)_target->getAnimator())->getVelocity();
    
    // the desired postition of the camera has to be a vector with length equals the radius of the circle and with orientation equals negative orientation of the velocity
    if (velocity.IsZero() == false) {
        camera_position = -velocity;
        camera_position *= _camera_circle.y / camera_position.Length();
        camera_position.y = _camera_circle.x;
        
        if (_needs_smoothing) {
            IvVector3   n1 = velocity - (distance - camera_position) * (_smoothing_speed * _smoothing_speed * dt);
            float       n2 = 1.f + _smoothing_speed * dt;
            velocity = n1 / (n2 * n2);
            
            camera_node->setAbsolutePosition(camera_node->getAbsolutePosition() + velocity * dt);
        }
        else
            camera_node->setAbsolutePosition(_target->getAbsolutePosition() + camera_position);
    }
    
    camera_node->_camera->setPosition(camera_node->getAbsolutePosition());
    camera_node->_camera->setLookAt(_target->getAbsolutePosition());
}

void CameraFollowAnimator::setSmoothingSpeed(float value) {
    _smoothing_speed = value;
}
