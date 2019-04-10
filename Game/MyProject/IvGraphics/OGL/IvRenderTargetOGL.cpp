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
        glDeleteRenderbuffers(2,&reference);
    else if(renderTargetType==RenderTargetType::DEPTH_STENCIL)
        glDeleteRenderbuffers(3,&reference);
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
    
        glBindTexture(GL_TEXTURE_2D,0);
    }
    else if(renderTargetType==RenderTargetType::DEPTH)
    {
        unsigned int mReference;
        glGenRenderbuffers(2,&mReference);
        glBindRenderbuffer(GL_RENDERBUFFER,mReference);
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH_COMPONENT,
                              width,
                              height);
        reference=mReference;
        glBindRenderbuffer(GL_RENDERBUFFER,0);
    }
    else if(renderTargetType==RenderTargetType::DEPTH_STENCIL)
    {
        unsigned int mReference;
        glGenRenderbuffers(3, &mReference);
        glBindRenderbuffer(GL_RENDERBUFFER,mReference);
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH24_STENCIL8,
                              width,
                              height);
        reference=mReference;
    }
}



