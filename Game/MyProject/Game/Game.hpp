//
//  Game.hpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/2/19.
//

#pragma once

#include <vector>

#include <IvGame.h>
#include <IvRendererHelp.h>
#include "RenderPacket.hpp"
#include "SceneGraph.hpp"
#include "CameraSceneNode.hpp"

class Game : public IvGame {
public:
    Game();
    ~Game();
    bool PostRendererInitialize();
    
protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game(const Game& other);
    Game& operator =(const Game& other);
    
    std::shared_ptr<Mesh>               _mesh;
    std::shared_ptr<MeshInstance>       _mesh_instance_1;
    std::shared_ptr<MeshInstance>       _mesh_instance_2;
    
    std::shared_ptr<SceneNode>          _scene_node_0;
    std::shared_ptr<SceneNode>          _scene_node_1;
    std::shared_ptr<SceneNode>          _scene_node_2;
    std::shared_ptr<CameraSceneNode>    _camera_scene_node;
    
    std::unique_ptr<SceneGraph>         _scene_graph;
};
