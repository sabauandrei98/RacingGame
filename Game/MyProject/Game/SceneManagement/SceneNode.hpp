//
//  SceneNode.hpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#pragma once

#include <algorithm>

#include "RenderPacket.hpp"
#include "NodeTransform.hpp"
#include "NodeAnimator.hpp"
#include "BoundingBox.hpp"

class NodeAnimator;
class CameraSceneNode;

class SceneNode : std::enable_shared_from_this<SceneNode> {
public:
    // public function(s) and method(s)
    SceneNode(const std::string&);
    virtual ~SceneNode();
    
    SceneNode* findFirstNodeWithName(const std::string&) const;
    void findAllNodesWithName(const std::string&, std::vector<SceneNode*>&) const;
    
    void addChild(const std::shared_ptr<SceneNode>&);
    void remove();
    
    void setLocalTransform(const IvVector3&, const IvVector3&, const IvVector3&);
    void setLocalPosition(const IvVector3&);
    const IvMatrix44& getAbsoluteTransform() const;
    IvVector3 getAbsolutePosition() const;
    const BoundingBox& getBoundingBox() const;
    
    void setAnimator(const std::shared_ptr<NodeAnimator>&);
    void setRenderable(const std::shared_ptr<MeshInstance>&);
    
    virtual void updateAbsoluteTransform();
    virtual void updateNode(float);
    virtual void collectRenderingPackets(CameraSceneNode*, std::vector<RenderPacket>&);
    
protected:
    // protected variable(s)
    SceneNode*                              _parent;
    std::vector<std::shared_ptr<SceneNode>> _children;
    
    bool                                    _enabled = true;
    std::string                             _name;
    
    NodeTransform                           _transform;
    IvMatrix44                              _absolute_transform;
    BoundingBox                             _bounding_box;
    
    std::shared_ptr<NodeAnimator>           _animator;
    std::shared_ptr<MeshInstance>           _rendarable;
};
