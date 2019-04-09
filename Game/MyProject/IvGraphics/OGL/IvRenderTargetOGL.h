//
//  IvRenderTargetOGL.hpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//
#pragma once
#include "IvRenderTarget.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif


//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvRenderTargetOGL:private IvRenderTarget
{
public:
    friend class IvResourceManagerOGL;
    
    unsigned int GetReference() const;
    RenderTargetType GetRenderTargetType() const;
    
    void SetStencilStatements(const std::vector<StencilStatements>& stencilStatements);
    std::vector<StencilStatements> GetStencilStatements() const;
    
protected:
    //constructor/desctructor
    IvRenderTargetOGL();
    IvRenderTargetOGL(const RenderTargetType& renderTargetType);
    ~IvRenderTargetOGL();
    
    void Setup(int width,int height);
    
private:
    unsigned int reference;
    RenderTargetType renderTargetType;
    std::vector<StencilStatements> stencilStamentes;
};
