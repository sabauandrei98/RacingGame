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
    
    void Setup(int width,int height);
    unsigned int GetReference();
    RenderTargetType GetRenderTargetType();
    
protected:
    //constructor/desctructor
    IvRenderTargetOGL();
    IvRenderTargetOGL(const RenderTargetType& renderTargetType);
    ~IvRenderTargetOGL();
    
private:
    unsigned int reference;
    RenderTargetType renderTargetType;
};
