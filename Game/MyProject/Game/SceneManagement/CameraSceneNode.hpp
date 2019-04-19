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

class CameraSceneNode : std::enable_shared_from_this<CameraSceneNode>, public SceneNode {
public:
    // typedef(s)
    typedef std::shared_ptr<Camera> CameraPtr;
    
    // constructor(s) and destructor
    CameraSceneNode(const std::string&, const CameraPtr&);
    
    // public function(s) and method(s)
    void updateNode(float);
    
private:
    CameraPtr  _camera;
};
