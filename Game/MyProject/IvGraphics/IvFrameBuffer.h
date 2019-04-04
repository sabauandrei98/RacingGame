//
//  IvFrameBuffer.h
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//
#pragma once

#include"IvRenderTarget.h"

#include<iostream>
#include<vector>

class IvFrameBuffer
{
private:
    std::vector<IvRenderTarget*> renderTarget;
protected:
    //constructor/destructor
    IvFrameBuffer()=default;
    virtual ~IvFrameBuffer() {}
    
public:
    virtual bool Create()=0;
    virtual void AddRenderTarget(const IvRenderTarget& renderTarget);
    virtual void Draw();
    virtual void Draw(const IvRenderTarget& renderTarget)=0;
};
