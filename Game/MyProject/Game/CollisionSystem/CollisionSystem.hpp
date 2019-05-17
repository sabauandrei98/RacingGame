//
//  CollisionSystem.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 09/05/2019.
//

#pragma once

#include <vector>

class SceneNode;

class CollisionSystem {
public:
    static CollisionSystem& getCollisionSystem();
    
    void addStaticNode(const SceneNode*);
    void addStaticNodes(const std::vector<SceneNode*>&);
    void removeStaticNode(const SceneNode*);
    void removeStaticNodes(const std::vector<SceneNode*>&);
    
    void addDinamicNode(const SceneNode*);
    void addDinamicNodes(const std::vector<SceneNode*>&);
    void removeDinamicNode(const SceneNode*);
    void removeDinamicNodes(const std::vector<SceneNode*>&);
    
    // checks if there is collision in the system
    bool isCollision();
    // checks if the given node collides
    bool isColliding(const SceneNode*);
    
private:
    // nodes which are fixed in the scene and never collide with each other
    std::vector<const SceneNode*> _static_nodes;
    // nodes which are moving in the scene and can collide with each other and with the fixed nodes
    std::vector<const SceneNode*> _dinamic_nodes;
    
    // private constructor
    CollisionSystem() {}
    // copy constructor and assignment operator are not needed
    CollisionSystem(const CollisionSystem&) = delete;
    CollisionSystem& operator =(const CollisionSystem&) = delete;
    
    // checks if the two nodes are colliding
    bool areColliding(const SceneNode*, const SceneNode*);
};
