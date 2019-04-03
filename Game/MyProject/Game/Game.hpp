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
#include "SceneManagement/RenderPacket.hpp"

class Game : public IvGame {
private:
    Game(const Game& other);
    Game& operator =(const Game& other);
    
    std::shared_ptr<Mesh>           _mesh;
    std::shared_ptr<MeshInstance>   _mesh_instance;
    std::shared_ptr<RenderPacket>   _render_packet;
    
protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
public:
    Game();
    ~Game();
    bool PostRendererInitialize();
};
