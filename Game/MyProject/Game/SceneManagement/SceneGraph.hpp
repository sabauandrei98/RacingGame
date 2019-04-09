//
//  SceneGraph.hpp
//  Game
//
//  Created by Tamas Both - (p) on 05/04/2019.
//

#pragma once

#include "SceneNode.hpp"

class SceneGraph {
public:
    // public function(s) and method(s)
    void updateScene(float);
    void drawScene();
    
    void setRoot(const std::shared_ptr<SceneNode>&);
    const std::shared_ptr<SceneNode>& getRoot() const;
    
    void setCamera(const std::shared_ptr<CameraSceneNode>&);
    
private:
    // private variable(s)
    std::shared_ptr<SceneNode>          _root;
    std::vector<RenderPacket>           _render_cache;
    
    std::shared_ptr<CameraSceneNode>    _camera;
};
