//
//  IvFrameBufferOGL.cpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#include "IvFrameBufferOGL.h"

IvFrameBufferOGL::IvFrameBufferOGL():fbo(0)
{
    
}
IvFrameBufferOGL::IvFrameBufferOGL(const std::vector<IvRenderTarget*>& renderTargets)
{
    glGenFramebuffers(1,&fbo);
    this->renderTargets=renderTargets;
}

IvFrameBufferOGL::~IvFrameBufferOGL()
{
    glDeleteFramebuffers(1,&fbo);
}

void IvFrameBufferOGL::Bind(int width,int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    
    for(int i=0;i<renderTargets.size();i++)
    {
        renderTargets[i]->Setup(width,height);
        glActiveTexture(GL_TEXTURE0 + i);
        if(renderTargets[i]->GetRenderTargetType()==RenderTargetType::COLOR)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0+i,
                                   GL_TEXTURE_2D,
                                   renderTargets[i]->GetReference(),
                                   0);
        }
        if(renderTargets[i]->GetRenderTargetType()==RenderTargetType::DEPTH)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                      GL_DEPTH_ATTACHMENT,
                                      GL_RENDERBUFFER,
                                      renderTargets[i]->GetReference());
            glDisable(GL_DEPTH_TEST);
        }
        if(renderTargets[i]->GetRenderTargetType()==RenderTargetType::DEPTH_STENCIL)
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                      GL_DEPTH_STENCIL_ATTACHMENT,
                                      GL_RENDERBUFFER,
                                      renderTargets[i]->GetReference());
        }
    }
}
bool IvFrameBufferOGL::Unbind()
{
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    return true;
}

std::vector<IvRenderTarget*> IvFrameBufferOGL::GetTextures()
{
    return renderTargets;
}

void IvFrameBufferOGL::AttachToCurrentlyFBO()
{
    for(int index=0;index<renderTargets.size();index++)
    {
        if(renderTargets[index]->GetRenderTargetType()==RenderTargetType::COLOR)
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0+index,
                                   GL_TEXTURE_2D,
                                   renderTargets[index]->GetReference(),
                                   0);
        else if(renderTargets[index]->GetRenderTargetType()==RenderTargetType::DEPTH)
            glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                   GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   renderTargets[index]->GetReference());
        else if(renderTargets[index]->GetRenderTargetType()==RenderTargetType::DEPTH_STENCIL)
            glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                   GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   renderTargets[index]->GetReference());
    }
}
