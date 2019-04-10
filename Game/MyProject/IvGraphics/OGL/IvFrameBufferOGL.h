//
//  IvFrameBufferOGL.hpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//
#pragma once

#include"IvFrameBuffer.h"
#include"IvRenderer.h"

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
    
    void Create(uint32_t width,uint32_t height);
    void Bind();
    bool BindToDefault();
    
    const std::vector<IvRenderTarget*>& GetTextures() const ;

protected:
    //constructor/destructor
    IvFrameBufferOGL();
    IvFrameBufferOGL(const std::vector<IvRenderTarget*>& renderTargets,uint32_t width,uint32_t height);
    ~IvFrameBufferOGL();
    void Destroy();
    
private:
    unsigned int fbo;
    std::vector<IvRenderTarget*> renderTargets;
    
    bool created=false;
    uint32_t width=1024;
    uint32_t height=768;
};

