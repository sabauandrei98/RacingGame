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
    
protected:
    //constructor/desctructor
    IvRenderTargetOGL();
    IvRenderTargetOGL(const RenderTargetType& renderTargetType);
    ~IvRenderTargetOGL();
    void Destroy();
    void Setup(uint32_t width,uint32_t height);
private:
    unsigned int reference;
    RenderTargetType renderTargetType;
};
