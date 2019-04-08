//
//  IvFrameBufferOGL.hpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//
#pragma once

#include"IvFrameBuffer.h"

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
class IvFrameBufferOGL:private IvFrameBuffer
{
public:
    friend class IvResourceManagerOGL;
    
    void Bind(int width=1280,int height=720);
    bool Unbind();
    std::vector<IvRenderTarget*> GetTextures();
    void AttachToCurrentlyFBO();

protected:
    IvFrameBufferOGL();
    IvFrameBufferOGL(const std::vector<IvRenderTarget*>& renderTargets);
    ~IvFrameBufferOGL();
    
private:
    unsigned int fbo;
    std::vector<IvRenderTarget*> renderTargets;
};

