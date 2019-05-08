//
//  CameraAnimator.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 07/05/2019.
//

#include "CameraFollowAnimator.hpp"

#include "CameraSceneNode.hpp"
#include "CarAnimator.hpp"

CameraFollowAnimator::CameraFollowAnimator(const SceneNode* target, const IvVector2& camera_circle, bool needs_smoothing) :
    _target(target), _camera_circle(camera_circle), _needs_smoothing(needs_smoothing) {
        // setting default values
        if (needs_smoothing) {
            _min_distance = 10.;
            _max_distance = 25.;
            _smoothing_speed = 7.;
        }
    }

void CameraFollowAnimator::animateNode(float dt, SceneNode* node_to_animate) {
    CameraSceneNode*    camera_node = (CameraSceneNode*)node_to_animate;
    
    IvVector3   distance;           // distance between the camera and the target
    IvVector3   velocity;           // velocity of the target car
    IvVector3   camera_position;    // the desires position of the camera
    
    distance = camera_node->getAbsolutePosition() - _target->getAbsolutePosition();
    velocity = ((CarAnimator*)_target->getAnimator())->getVelocity();
    
    // the desired postition of the camera has to be a vector with length equals the radius of the circle and with orientation equals negative orientation of the velocity
    if (velocity.IsZero())
        camera_position = {0., _camera_circle.x, -_camera_circle.y};
    else {
        camera_position = -velocity;
        camera_position *= _camera_circle.y / camera_position.Length();
        camera_position.y = _camera_circle.x;
    }
    
    if (_needs_smoothing) {
        if (distance.Length() < _max_distance && distance.Length() > _min_distance) {
            IvVector3   n1 = velocity - (distance - camera_position) * (_smoothing_speed * _smoothing_speed * dt);
            float       n2 = 1 + _smoothing_speed * dt;
            velocity = n1 / (n2 * n2);
        }
        
        camera_node->setAbsolutePosition(camera_node->getAbsolutePosition() + velocity * dt);
    }
    else
        camera_node->setAbsolutePosition(_target->getAbsolutePosition() + camera_position);
    
    camera_node->_camera->setPosition(camera_node->getAbsolutePosition());
    camera_node->_camera->setLookAt(_target->getAbsolutePosition());
    
    //std::cout << camera_node->_camera->getPosition() << " -------------------- " << _target->getAbsolutePosition() << std::endl;
}

void CameraFollowAnimator::setMinMaxDistance(float min, float max) {
    _min_distance = min;
    _max_distance = max;
}

void CameraFollowAnimator::setSmoothingSpeed(float value) {
    _smoothing_speed = value;
}
