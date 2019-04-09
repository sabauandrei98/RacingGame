//
//  IvRenderTarget.h
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#pragma once

#include<iostream>
#include<vector>

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

enum RenderTargetType
{
    COLOR,
    DEPTH,
    DEPTH_STENCIL
};

enum StencilStatementsFunc
{
    NEVER,
    ALWAYS,
    LESS,
    LEQUAL,
    EQUAL,
    GEQUAL,
    GREATER,
    GNOTEQUAL
};

enum StencilAction
{
    KEEP,
    ZERO,
    REPLACE,
    INVERT
};

struct StencilOpParams
{
    StencilAction sfail;
    StencilAction dpfail;
    StencilAction ddpass;
};

struct StencilStatements
{
    StencilStatementsFunc stencilFunc;
    StencilOpParams stencilOp;
};

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvRenderTarget
{
public:
    virtual unsigned int GetReference() const = 0 ;
    virtual RenderTargetType GetRenderTargetType() const = 0;
    
    virtual void SetStencilStatements(const std::vector<StencilStatements>& stencilStatements) =0;
    virtual std::vector<StencilStatements> GetStencilStatements() const =0;
    
    friend class IvFrameBufferOGL;
    
protected:
    //constructor/destructor
    IvRenderTarget(){}
    virtual ~IvRenderTarget(){}
    
    virtual void Setup(int width,int height) = 0;
    

private:
    
};
