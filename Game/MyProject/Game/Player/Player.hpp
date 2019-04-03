//
//  Player.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/2/19.
//

#pragma once
#include <stdio.h>
#include <IvMatrix44.h>

class Player
{
public:
    Player();
    ~Player();
    
    void Update( float dt );
    void Render();
    
private:
    IvMatrix44  mTransform;
    
};

