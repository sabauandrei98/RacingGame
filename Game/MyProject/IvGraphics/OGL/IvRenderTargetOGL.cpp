//
//  IvRenderTargetOGL.cpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#include "IvRenderTargetOGL.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::IvRenderTargetOGL()
//-------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------
IvRenderTargetOGL::IvRenderTargetOGL()
{
    
}

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::IvRenderTargetOGL()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
IvRenderTargetOGL::IvRenderTargetOGL(const RenderTargetType& renderTargetType)
{
    this->renderTargetType=renderTargetType;
}

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::~IvRenderTargetOGL()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
IvRenderTargetOGL::~IvRenderTargetOGL()
{
}

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::Destroy()
//-------------------------------------------------------------------------------
// Clean up
//-------------------------------------------------------------------------------
void
IvRenderTargetOGL::Destroy()
{
    if(renderTargetType==RenderTargetType::COLOR)
        glDeleteTextures(1,&reference);
    else if(renderTargetType==RenderTargetType::DEPTH)
        glDeleteRenderbuffers(1,&reference);
}

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::GetReference()
//-------------------------------------------------------------------------------
// Get attachement reference
//-------------------------------------------------------------------------------
unsigned int IvRenderTargetOGL::GetReference() const
{
    return reference;
}

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::GetRenderTargetType()
//-------------------------------------------------------------------------------
RenderTargetType IvRenderTargetOGL::GetRenderTargetType() const
{
    return renderTargetType;
}

//-------------------------------------------------------------------------------
// @ IvRenderTargetOGL::Setup()
//-------------------------------------------------------------------------------
void IvRenderTargetOGL::Setup(uint32_t width,uint32_t height)
{
    if(renderTargetType==RenderTargetType::COLOR)
    {
        glGenTextures(1,&reference);
        glBindTexture(GL_TEXTURE_2D,reference);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     nullptr);
        
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR);
        
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER,
                        GL_LINEAR);
    }
    else if(renderTargetType==RenderTargetType::DEPTH)
    {
        glGenRenderbuffers(1,&reference);
        glBindRenderbuffer(GL_RENDERBUFFER,reference);
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH_COMPONENT,
                              width,
                              height);
    }
}


