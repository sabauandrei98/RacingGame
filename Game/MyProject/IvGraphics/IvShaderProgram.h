//===============================================================================
// @ IvShaderProgram.h
// 
// Base class for combined vertex and fragment/pixel shader
// ------------------------------------------------------------------------------
// Copyright (C) 2008-2015  James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//===============================================================================

#ifndef __IvShaderProgram__h__
#define __IvShaderProgram__h__

#include<IvVector3.h>
#include<IvVector2.h>
#include<IvVector4.h>
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

class IvUniform;

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvShaderProgram
{
public:
    // interface routines
    virtual IvUniform* GetUniform(char const* name) = 0;
    
    virtual void setFloat(const char* name,float value)=0;
    virtual void setVec2(const char* name,IvVector2 value)=0;
    virtual void setVec3(const char* name,IvVector3 value)=0;
    virtual void setVec4(const char* name,IvVector4 value)=0;
    
    unsigned int getProgramID() { return programID; }
    void setProgramID(unsigned pID) { programID = pID; }
    
protected:
    // constructor/destructor
    IvShaderProgram() {}
    virtual ~IvShaderProgram() {}

private:
    // copy operations (unimplemented so we can't copy)
    IvShaderProgram(const IvShaderProgram& other);
    IvShaderProgram& operator=(const IvShaderProgram& other);
    
protected:
    unsigned int programID;
}; 

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
