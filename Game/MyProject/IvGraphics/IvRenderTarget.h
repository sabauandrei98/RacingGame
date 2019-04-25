//
//  IvRenderTarget.h
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include<iostream>
#include<vector>
//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------
enum RenderTargetType
{
    COLOR,
    DEPTH
};
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class IvRenderTarget
{
public:
    //constructor/destructor
    IvRenderTarget(){}
    virtual ~IvRenderTarget(){}
    
    virtual unsigned int GetReference() const = 0 ;
    virtual RenderTargetType GetRenderTargetType() const = 0;
    virtual void Destroy()=0;
    
    friend class IvFrameBufferOGL;
    
protected:
    virtual void Setup(uint32_t width,uint32_t height) = 0;
    
private:
    
};
