//
//  Shape.hpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/8/19.
//

#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>

#include"IvFrameBuffer.h"
#include"IvVertexFormats.h"
#include"IvStackAllocator.h"
#include"IvShaderProgram.h"
#include"IvRenderer.h"
#include"IvRendererHelp.h"
#include"IvResourceManager.h"
#include"IvRenderTarget.h"
#include"IvImage.h"
#include"IvUniform.h"
#include"IvTexture.h"

class Shape
{
public:
    IvFrameBuffer* frameBuffer;
    
    unsigned int noVertices;
    
    IvShaderProgram* mShader;
    IvVertexBuffer* vertexBuffer;
    IvIndexBuffer* indexBuffer;
    
    IvUniform* textureUniform;
    IvTexture* mTexture;
    
    void* vertexData;
    VertexDescription vertexDescription;
    
public:
    Shape();
    ~Shape();
    void Setup(const char *shaderName,const char* textureName);
    
    void Draw();
    
    void SetVertexData(void* vertexData);
    void SetVertexDescription(VertexDescription vertexDescription);
    void SetNoVertices(unsigned int noVertices);
    
    void SetUniforms();
    void SetTexture(const char* name,unsigned int reference);
    
    void LoadTexture(const char* textureName);
    
};


