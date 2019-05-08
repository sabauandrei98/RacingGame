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
    _parent(nullptr), _name(name) {
    }

SceneNode::~SceneNode() {
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// finds the first node with the given name, if it doesn't exists returns nullptr
SceneNode* SceneNode::findFirstNodeWithName(const std::string& name) const {
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
void SceneNode::findAllNodesWithName(const std::string& name, std::vector<SceneNode*>& scene_nodes) const {
    for (auto& i : _children)
        if (i->_name == name)
            scene_nodes.push_back(i.get());
    
    for (auto& i : _children)
        i->findAllNodesWithName(name, scene_nodes);
}

// adds a child
void SceneNode::addChild(const std::shared_ptr<SceneNode>& child) {
    child->_parent = this;
    _children.push_back(child);
}

// returns a pointer to the child
SceneNode* SceneNode::getChild(unsigned int index) {
    return _children[index].get();
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

const  IvVector3& SceneNode::getLocalPosition() const {
    return _transform.getPosition();
}

const  IvVector3& SceneNode::getLocalScale() const {
    return _transform.getScale();
}

void SceneNode::setParent(const std::shared_ptr<SceneNode>& parent){
    this->_parent = parent.get();
}

// returns the absolute transformation of the node
const IvMatrix44& SceneNode::getAbsoluteTransform() const {
    return _absolute_transform;
}

// returns the absolute position of the node
IvVector3 SceneNode::getAbsolutePosition() const {
    return IvVector3(_absolute_transform(0, 3), _absolute_transform(1, 3), _absolute_transform(2, 3));
}

// returns the bounding box
const BoundingBox& SceneNode::getBoundingBox() const {
    return _bounding_box;
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
    
    //updates the bounding box of this node
    if (_needs_bounding_box) {
        if (_rendarable && _rendarable->getMesh())
            _bounding_box.calculate(_rendarable->getMesh()->getMinVertices(), _rendarable->getMesh()->getMaxVertices(), _absolute_transform);
        else
            _bounding_box.invalidate();
        
        for (const auto& i : _children) {
            if (!i->_needs_bounding_box)
                continue;
            
            _bounding_box.expand(i->_bounding_box.getMin());
            _bounding_box.expand(i->_bounding_box.getMax());
        }
    }
}

// collects the rendering packets
void SceneNode::collectRenderingPackets(const Camera* camera, std::vector<RenderPacket>& render_packets) {
    if (!_enabled)
        return;
    
    //TODO: perform visibility testing here
    
    if (_rendarable) {
        RenderPacket packet;
        packet._mesh_instance = _rendarable.get();

        packet._use_depth = true;

        packet._world_view_projection_matrix = camera->getProjectionMatrix() * camera->getViewMatrix() * _absolute_transform;
        
        render_packets.push_back(packet);
    }
    
    for (auto& i : _children)
        i->collectRenderingPackets(camera, render_packets);
}

// sets the node animator
void SceneNode::setAnimator(const std::shared_ptr<NodeAnimator>& animator) {
    _animator = animator;
}

// sets the mesh instance
void SceneNode::setRenderable(const std::shared_ptr<MeshInstance>& renderable) {
    _rendarable = renderable;
}


