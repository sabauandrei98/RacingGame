//
//  IvFrameBufferOGL.cpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#include "IvFrameBufferOGL.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::IvFrameBufferOGL()
//-------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------
IvFrameBufferOGL::IvFrameBufferOGL():fbo(0)
{
    
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::IvFrameBufferOGL()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
IvFrameBufferOGL::IvFrameBufferOGL(const std::vector<IvRenderTarget*>& renderTargets,uint32_t width,uint32_t height)
{
    this->width=width;
    this->height=height;
    glGenFramebuffers(1,&fbo);
    this->renderTargets=renderTargets;
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::~IvFrameBufferOGL()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
IvFrameBufferOGL::~IvFrameBufferOGL()
{
   
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::Destroy()
//-------------------------------------------------------------------------------
// Clean up
//-------------------------------------------------------------------------------
void
IvFrameBufferOGL::Destroy()
{
    glDeleteFramebuffers(1,&fbo);
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::Create()
//-------------------------------------------------------------------------------
// Create framebuffer
//-------------------------------------------------------------------------------
void
IvFrameBufferOGL::Create(uint32_t width,uint32_t height)
{
    unsigned int colorIndex = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    for(int i=0;i<renderTargets.size();i++)
    {
        renderTargets[i]->Setup(width,height);
        if(renderTargets[i]->GetRenderTargetType()==RenderTargetType::COLOR)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0 + colorIndex++,
                                   GL_TEXTURE_2D,
                                   renderTargets[i]->GetReference(),
                                   0);
        }
        else if(renderTargets[i]->GetRenderTargetType()==RenderTargetType::DEPTH)
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                      GL_DEPTH_ATTACHMENT,
                                      GL_RENDERBUFFER,
                                      renderTargets[i]->GetReference());
        }
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::Bind()
//-------------------------------------------------------------------------------
// Bind framebuffer
//-------------------------------------------------------------------------------
void
IvFrameBufferOGL::Bind()
{
    if(this->created==false)
    {
        this->created=true;
        this->Create(this->width,this->height);
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::BindToDefault()
//-------------------------------------------------------------------------------
// Bind to default framebuffer
//-------------------------------------------------------------------------------
bool IvFrameBufferOGL::BindToDefault()
{
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0, 0, IvRenderer::mRenderer->GetWidth(), IvRenderer::mRenderer->GetHeight());
    return true;
}

//-------------------------------------------------------------------------------
// @ IvFrameBufferOGL::GetTextures()
//-------------------------------------------------------------------------------
// Get textures for every render target
//-------------------------------------------------------------------------------
const std::vector<IvRenderTarget*>& IvFrameBufferOGL::GetTextures() const
{
    return renderTargets;
}
