//
//  Test.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/3/19.
//

#pragma once

#include <stdio.h>
#include<iostream>
#include<vector>
#include"IvVertexFormats.h"
#include"IvStackAllocator.h"
#include"IvShaderProgram.h"
#include"IvRenderer.h"
#include"IvRendererHelp.h"
#include"IvResourceManager.h"
#include"IvFrameBuffer.h"
#include"IvFrameBufferOGL.h"

class Test
{
    std::vector<IvTCPVertex> vertices;
    std::vector<unsigned int> indices;
    
    IvShaderProgram* mShader;
    IvVertexBuffer * vertexBuffer;
    IvIndexBuffer* indexBuffer;
public:
    Test();
    ~Test();
    void Setup(const char* shaderName);
    void Draw();
};
