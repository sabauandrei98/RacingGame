//
//  CameraSceneNode.hpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#pragma once

#include <IvGame.h>
#include <IvEventHandler.h>

#include "SceneNode.hpp"
#include "../Camera.hpp"

class CameraSceneNode : std::enable_shared_from_this<CameraSceneNode>, public SceneNode, public Camera {
public:
    // constructor(s) and destructor
    CameraSceneNode(const std::string&, const Camera&);
    
    // public function(s) and method(s)
    void updateNode(float);
};
