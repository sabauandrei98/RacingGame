//
//  SceneGraph.cpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#include "SceneGraph.hpp"

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// updates all the nodes starting with root
void SceneGraph::updateScene(float dt) {
    _root->updateNode(dt);
}

// draws all the nodes starting with root
void SceneGraph::drawScene() {
    _render_cache.clear();
    _root->collectRenderingPackets(_camera.get(), _render_cache);
    
    // TODO: sort _render_cache
    
    for (const auto& i : _render_cache)
        i.draw();
}

// sets the root of the graph
void SceneGraph::setRoot(const std::shared_ptr<SceneNode>& root) {
    _root = root;
}

// returns the root of the graph
const std::shared_ptr<SceneNode>& SceneGraph::getRoot() const {
    return _root;
}

// adds a camera to the graph
void SceneGraph::setCamera(const std::shared_ptr<Camera>& camera) {
    _camera = camera;
}
