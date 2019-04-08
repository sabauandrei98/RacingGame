//
//  IvRenderTarget.h
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#pragma once


//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

enum RenderTargetType
{
    COLOR,
    DEPTH,
    DEPTH_STENCIL
};

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvRenderTarget
{
public:
    virtual void Setup(int width,int height)=0;
    virtual unsigned int GetReference()=0;
    virtual RenderTargetType GetRenderTargetType()=0;
    
protected:
    IvRenderTarget(){}
    virtual ~IvRenderTarget(){}
    
private:
    
};
