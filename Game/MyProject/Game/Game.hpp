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
    
    std::shared_ptr<Mesh>           _mesh;
    std::shared_ptr<MeshInstance>   _mesh_instance;
};
