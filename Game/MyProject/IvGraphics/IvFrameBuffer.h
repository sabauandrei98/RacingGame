//
//  IvFrameBuffer.h
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include"IvRenderTarget.h"

#include<iostream>
#include<vector>
//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class IvFrameBuffer
{
public:
    //constructor/destructor
    IvFrameBuffer(){}
    virtual ~IvFrameBuffer(){}
    virtual void Destroy()=0;
    
    virtual void Create(uint32_t width,uint32_t height)=0;
    virtual void Bind()=0;
    virtual bool BindToDefault()=0;
    virtual const std::vector<IvRenderTarget*>& GetTextures() const =0  ;
    
protected:

private:

};
