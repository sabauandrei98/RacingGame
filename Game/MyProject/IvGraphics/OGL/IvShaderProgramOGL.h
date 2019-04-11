//===============================================================================
// @ IvShaderProgramOGL.h
// 
// OpenGL implementation for combined vertex and fragment/pixel shader
// ------------------------------------------------------------------------------
// Copyright (C) 2008-2015   James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//===============================================================================

#ifndef __IvShaderProgramOGL__h__
#define __IvShaderProgramOGL__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <map>
#include <string>

#include "../IvShaderProgram.h"
#include "../IvVertexFormats.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

class IvResourceManagerOGL;
class IvUniformOGL;

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvShaderProgramOGL : public IvShaderProgram
{
public:
    // interface routines
    IvUniform* GetUniform(char const* name) final;
    
    void SetUniform(const char* name,float value);
<<<<<<< HEAD
    void SetUniform(const char* name,IvVector2 value);
    void SetUniform(const char* name,IvVector3 value);
    void SetUniform(const char* name,IvVector4 value);
    void SetUniform(const char* name,unsigned int texture);
=======
    void SetUniform(const char* name,const IvVector2& value);
    void SetUniform(const char* name,const IvVector3& value);
    void SetUniform(const char* name,const IvVector4& value);
>>>>>>> master
    
    friend class IvResourceManagerOGL;
    friend class IvRendererOGL;
    
private:
    // constructor/destructor
    IvShaderProgramOGL();
    ~IvShaderProgramOGL() final;
    
    // initialization
    bool Create( GLuint vertexShaderID, GLuint fragmentShaderID );
    
    // destruction
    void Destroy();
    
    // make this the active program
    bool MakeActive();
    
private:
    // copy operations
    IvShaderProgramOGL(const IvShaderProgramOGL& other);
    IvShaderProgramOGL& operator=(const IvShaderProgramOGL& other);

    GLuint              mProgramID;
    unsigned int        mNextTextureStage;
    std::map<std::string, IvUniformOGL*> mUniforms;
    
    
};


//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
