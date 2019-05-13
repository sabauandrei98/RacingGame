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
#include "../Camera.hpp"

class NodeAnimator;
class CameraSceneNode;

class SceneNode : std::enable_shared_from_this<SceneNode> {
public:
    // public function(s) and method(s)
    SceneNode(const std::string&);
    virtual ~SceneNode();
    
    SceneNode* findFirstNodeWithName(const std::string&) const;
    void findAllNodesWithName(const std::string&, std::vector<std::shared_ptr<SceneNode>>&) const;
    void findAllNodesContainingName(const std::string& name, std::vector<std::shared_ptr<SceneNode>>& scene_nodes) const;
    
    void addChild(const std::shared_ptr<SceneNode>&);
    SceneNode* getChild(unsigned int);
    void remove();
    
    void setLocalTransform(const IvVector3&, const IvVector3&, const IvVector3&);
    void setLocalPosition(const IvVector3&);
    
    const IvVector3& getLocalPosition() const;
    const IvMatrix44& getAbsoluteTransform() const;
    IvVector3 getAbsolutePosition() const;
    void setAbsolutePosition(const IvVector3&);
    const BoundingBox& getBoundingBox() const;
    IvVector3 getLocalPositon() const;
    IvVector3 getLocalScale() const;
    
    void setAnimator(const std::shared_ptr<NodeAnimator>&);
    void setRenderable(const std::shared_ptr<MeshInstance>&);
    const std::shared_ptr<MeshInstance>& getRenderable() const;
    
    const NodeAnimator* getAnimator() const;
    
    virtual void updateAbsoluteTransform();
    virtual void updateNode(float);
    virtual void collectRenderingPackets(const Camera*, std::vector<RenderPacket>&);
    
protected:
    // protected variable(s)
    SceneNode*                              _parent;
    std::vector<std::shared_ptr<SceneNode>> _children;
    
    bool                                    _enabled = true;
    bool                                    _needs_bounding_box = true;
    std::string                             _name;
    
    NodeTransform                           _transform;
    IvMatrix44                              _absolute_transform;
    BoundingBox                             _bounding_box;
    
    std::shared_ptr<NodeAnimator>           _animator;
    std::shared_ptr<MeshInstance>           _rendarable;
};
