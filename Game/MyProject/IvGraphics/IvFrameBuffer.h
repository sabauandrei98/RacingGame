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
    IvFrameBuffer()=default;
    virtual ~IvFrameBuffer() {}
    
    virtual void Bind(int width=1280,int height=720)=0;
    virtual bool Unbind()=0;
    virtual std::vector<IvRenderTarget*> GetTextures() const =0  ;
    
protected:

private:

};
