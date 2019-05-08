//
//  CameraSceneNode.cpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#include "CameraSceneNode.hpp"

#include "CarAnimator.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

CameraSceneNode::CameraSceneNode(const std::string& name, const CameraSceneNode::CameraPtr& camera) :
    SceneNode(name), _camera(camera) {
        _needs_bounding_box = false;
    }

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

IvVector3 CameraSceneNode::screenToWorld(unsigned int mouseX, unsigned int mouseY)
{
    return _camera->screenToWorld(mouseX, mouseY);
}

IvRay3 CameraSceneNode::getRay(unsigned int mouseX, unsigned int mouseY)
{
    return _camera->getRay(mouseX, mouseY);
}
