//
//  IvRenderTarget.h
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/4/19.
//

#pragma once

class IvRenderTarget
{
public:
    virtual bool Create()=0;
    
protected:
    IvRenderTarget(unsigned int texture);
    virtual ~IvRenderTarget(){}
    
private:
    unsigned int texture;
    
};
