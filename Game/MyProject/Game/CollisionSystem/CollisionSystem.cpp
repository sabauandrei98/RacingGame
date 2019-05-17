//
//  CollisionSystem.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 09/05/2019.
//

#include "CollisionSystem.hpp"
#include "../SceneManagement/SceneNode.hpp"

#include <IvVector3.h>

// returns reference to the already existing static object
CollisionSystem& CollisionSystem::getCollisionSystem() {
    static CollisionSystem system;
    return system;
}

void CollisionSystem::addStaticNode(const SceneNode* node) {
    _static_nodes.push_back(node);
}

void CollisionSystem::addStaticNodes(const std::vector<SceneNode*>& nodes) {
    for (const auto& i : nodes)
        _static_nodes.push_back(i);
}

void CollisionSystem::removeStaticNode(const SceneNode* node) {
    _static_nodes.erase(std::find(_static_nodes.begin(), _static_nodes.end(), node));
}

void CollisionSystem::removeStaticNodes(const std::vector<SceneNode*>& nodes) {
    for (const auto& i : nodes)
        _static_nodes.erase(std::find(_static_nodes.begin(), _static_nodes.end(), i));
}

void CollisionSystem::addDinamicNode(const SceneNode* node) {
    _dinamic_nodes.push_back(node);
}

void CollisionSystem::addDinamicNodes(const std::vector<SceneNode*>& nodes) {
    for (const auto& i : nodes)
        _dinamic_nodes.push_back(i);
}

void CollisionSystem::removeDinamicNode(const SceneNode* node) {
    _dinamic_nodes.erase(std::find(_dinamic_nodes.begin(), _dinamic_nodes.end(), node));
}

void CollisionSystem::removeDinamicNodes(const std::vector<SceneNode*>& nodes) {
    for (const auto& i : nodes)
        _dinamic_nodes.erase(std::find(_dinamic_nodes.begin(), _dinamic_nodes.end(), i));
}

bool CollisionSystem::isCollision() {
    for (std::vector<const SceneNode*>::iterator current_node = _dinamic_nodes.begin(); current_node < _dinamic_nodes.end(); current_node++) {
        for (std::vector<const SceneNode*>::iterator node = _static_nodes.begin(); node < _static_nodes.end(); node++)
            if (areColliding(*current_node, *node))
                return true;
        
        for (std::vector<const SceneNode*>::iterator node = current_node + 1; node < _dinamic_nodes.end(); node++)
            if (areColliding(*current_node, *node))
                return true;
    }
    
    return false;
}

bool CollisionSystem::isColliding(const SceneNode* current_node) {
    for (const auto& node : _static_nodes)
        if (areColliding(current_node, node))
            return true;
    
    for (const auto& node : _dinamic_nodes)
        if (areColliding(current_node, node) && current_node != node)
            return true;
    
    return false;
}

bool CollisionSystem::areColliding(const SceneNode* node1, const SceneNode* node2) {
    IvVector3 min1 = node1->getBoundingBox().getMin();
    IvVector3 max1 = node1->getBoundingBox().getMax();
    IvVector3 min2 = node2->getBoundingBox().getMin();
    IvVector3 max2 = node2->getBoundingBox().getMax();
    
    bool x_intersection = (min2.x < max1.x && min2.x > min1.x) || (min1.x < max2.x && min1.x > min2.x);
    bool y_intersection = (min2.y < max1.y && min2.y > min1.y) || (min1.y < max2.y && min1.y > min2.y);
    bool z_intersection = (min2.z < max1.z && min2.z > min1.z) || (min1.z < max2.z && min1.z > min2.z);
    
    return x_intersection && y_intersection && z_intersection;
}
