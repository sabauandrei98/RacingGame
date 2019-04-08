//
//  CameraSceneNode.cpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#include "CameraSceneNode.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

CameraSceneNode::CameraSceneNode(const std::string& name) :
    SceneNode(name) {
        _view.Identity();
        _projection.Identity();
    }

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// returns the view matrix of the camera
const IvMatrix44& CameraSceneNode::getView() const {
    return _view;
}

// returns the projection matrix of the camera
const IvMatrix44& CameraSceneNode::getProjection() const {
    return _projection;
}
