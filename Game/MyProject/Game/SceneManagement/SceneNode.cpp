//
//  SceneNode.cpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#include "SceneNode.hpp"
#include "CameraSceneNode.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

SceneNode::SceneNode(const std::string& name) :
    _name(name) {
    }

SceneNode::~SceneNode() {
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// finds the first node with the given name, if it doesn't exists returns nullptr
SceneNode* SceneNode::findFirstNodeWithName(std::string name) const {
    for (auto& i : _children)
        if (i->_name == name)
            return i.get();
    
    for (auto& i : _children) {
        SceneNode* scene_node = i->findFirstNodeWithName(name);
        if (scene_node)
            return scene_node;
    }
    
    return nullptr;
}

// finds all the nodes with the given name
void SceneNode::findAllNodesWithName(std::string name, std::vector<SceneNode*>& scene_nodes) const {
    for (auto& i : _children)
        if (i->_name == name)
            scene_nodes.push_back(i.get());
    
    for (auto& i : _children)
        i->findAllNodesWithName(name, scene_nodes);
}

// adds a child
void SceneNode::addChild(const SceneNode& child) {
    _children.push_back(std::make_shared<SceneNode>(std::move(child)));
}

// removes this node and all its children from the graph
void SceneNode::remove()
{
    auto it = find_if(_parent->_children.begin(), _parent->_children.end(),
                      [this] (const auto& child) {
                          return child.get() == this;
                      });
    
    _parent->_children.erase(it);
}

// sets the local transform
void SceneNode::setLocalTransform(const IvVector3& position, const IvVector3& rotation, const IvVector3& scale) {
    _transform.set(position, rotation, scale);
}

// sets the local transforms position
void SceneNode::setLocalPosition(const IvVector3& position) {
    _transform.set(position);
}

// returns the absolute transformation of the node
const IvMatrix44& SceneNode::getAbsoluteTransform() const {
    return _absolute_transform;
}

// returns the absolute position of the node
IvVector3 SceneNode::getAbsolutePosition() const {
    return IvVector3(_absolute_transform(0, 3), _absolute_transform(1, 3), _absolute_transform(2, 3));
}

// updates the absolute transform matrix
void SceneNode::updateAbsoluteTransform() {
    _absolute_transform = _transform.getMatrix();
    if (_parent)
        _absolute_transform = _parent->getAbsoluteTransform() * _absolute_transform;
}

// updates/animates the current node and child nodes
void SceneNode::updateNode(float dt) {
    if (!_enabled)
        return;
    
    if (_animator)
        _animator->animateNode(dt, this);
    
    updateAbsoluteTransform();
    
    for (auto& i : _children)
        i->updateNode(dt);
    
    //TODO: update the bounding box of this node
}

void SceneNode::collectRenderingPackets(CameraSceneNode* camera, std::vector<RenderPacket>& render_packets) {
    if (!_enabled)
        return;
    
    //TODO: perform visibility testing here
    
    if (_rendarable) {
        //TODO: calculate world view projection and other uniforms
        
        RenderPacket packet;
        packet._mesh_instance = _rendarable;
        
        render_packets.push_back(packet);
    }
    
    for (auto& i : _children)
        i->collectRenderingPackets(camera, render_packets);
}



