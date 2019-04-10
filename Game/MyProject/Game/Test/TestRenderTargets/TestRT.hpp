//
//  Test.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/5/19.
//

#pragma once
#include"Shape.hpp"
#include<IvRendererOGL.h>

class TestRT
{    
    std::vector<Shape*> shapes;
    
    IvFrameBuffer* frameBuffer;
public:
    TestRT();
    ~TestRT();
    void Create();
    
    void Setup();
    void Draw();
};
