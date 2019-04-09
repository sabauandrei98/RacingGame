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
    unsigned int colorIndex = 0;
    for(int i=0;i<renderTargets.size();i++)
    {
        renderTargets[i]->Setup(width,height);
        //glActiveTexture(GL_TEXTURE0 + i);
        if(renderTargets[i]->GetRenderTargetType()==RenderTargetType::COLOR)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0 + colorIndex++,
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
            glClear(GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_STENCIL_TEST);
            std::vector<StencilStatements> stencilStatements=renderTargets[i]->GetStencilStatements();
            for(int ii=0;ii<stencilStatements.size();ii++)
            {
                switch (stencilStatements[i].stencilFunc){
                    case NEVER:
                        glStencilFunc(GL_NEVER,1,0xFF);
                        break;
                    case ALWAYS:
                        glStencilFunc(GL_ALWAYS,1, 0xFF);
                        break;
                    case LESS:
                        glStencilFunc(GL_LESS,1, 0xFF);
                        break;
                    case LEQUAL:
                        glStencilFunc(GL_LEQUAL,1, 0xFF);
                        break;
                    case EQUAL:
                        glStencilFunc(GL_EQUAL,1, 0xFF);
                        break;
                    case GEQUAL:
                        glStencilFunc(GL_GEQUAL,1, 0xFF);
                        break;
                    case GREATER:
                        glStencilFunc(GL_GREATER,1, 0xFF);
                        break;
                    case GNOTEQUAL:
                        glStencilFunc(GL_NOTEQUAL,1, 0xFF);
                        break;
                    default:
                        break;
                        
                    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
                    glStencilMask(0xFF);
                }
                
            }
            glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                      GL_DEPTH_STENCIL_ATTACHMENT,
                                      GL_RENDERBUFFER,
                                      renderTargets[i]->GetReference());
            glDisable(GL_STENCIL_TEST);
            glDisable(GL_DEPTH_TEST);
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

std::vector<IvRenderTarget*> IvFrameBufferOGL::GetTextures() const
{
    return renderTargets;
}
