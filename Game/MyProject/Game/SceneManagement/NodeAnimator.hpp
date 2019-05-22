//
//  NodeAnimator.hpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#pragma once

#include <memory>

#include "SceneNode.hpp"

class SceneNode;

class NodeAnimator : std::enable_shared_from_this<NodeAnimator> {
public:
    // public function(s) and method(s)
    NodeAnimator();
    virtual ~NodeAnimator();
    virtual void animateNode(float, SceneNode*);
    virtual void animateNode(SceneNode*,SceneNode*,const IvVector3&);
};
