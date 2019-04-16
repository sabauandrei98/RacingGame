//
//  CameraSceneNode.hpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#pragma once

#include "SceneNode.hpp"
#include "../Camera.hpp"

class CameraSceneNode : std::enable_shared_from_this<CameraSceneNode>, public SceneNode {
public:
    // constructor(s) and destructor
    CameraSceneNode(const std::string&);
    const IvMatrix44& getView() const;
    const IvMatrix44& getProjection() const;
    
private:
    // private variable(s)
    IvMatrix44  _view;
    IvMatrix44  _projection;
    
    // TODO
};
