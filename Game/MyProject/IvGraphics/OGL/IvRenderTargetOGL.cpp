//
//  IvRenderTargetOGL.cpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#include "IvRenderTargetOGL.h"

IvRenderTargetOGL::IvRenderTargetOGL():renderTargetType(RenderTargetType::COLOR),reference(0)
{
    
}
IvRenderTargetOGL::IvRenderTargetOGL(const RenderTargetType& renderTargetType)
{
    this->renderTargetType=renderTargetType;
}

IvRenderTargetOGL::~IvRenderTargetOGL()
{
    if(renderTargetType==RenderTargetType::COLOR)
        glDeleteTextures(1,&reference);
    else if(renderTargetType==RenderTargetType::DEPTH)
        glDeleteRenderbuffers(1,&reference);
}

unsigned int IvRenderTargetOGL::GetReference()
{
    return reference;
}

RenderTargetType IvRenderTargetOGL::GetRenderTargetType()
{
    return renderTargetType;
}

void IvRenderTargetOGL::Setup(int width,int height)
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
    
       // glBindTexture(GL_TEXTURE_2D,0);
    }
    else if(renderTargetType==RenderTargetType::DEPTH)
    {
        glGenRenderbuffers(2,&reference);
        glBindRenderbuffer(GL_RENDERBUFFER,reference);
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH_COMPONENT,
                              width,
                              height);
        
     //   glBindRenderbuffer(GL_RENDERBUFFER,0);
    }
    else if(renderTargetType==RenderTargetType::DEPTH_STENCIL)
    {
        glGenRenderbuffers(3, &reference);
        glBindRenderbuffer(GL_RENDERBUFFER,reference);
        glRenderbufferStorage(GL_RENDERBUFFER,
                              GL_DEPTH24_STENCIL8,
                              width,
                              height);
    }
}



