//===============================================================================
// @ IvShaderProgramOGL.cpp
// 
// OpenGL implementation for combined vertex and fragment/pixel shader
// ------------------------------------------------------------------------------
// Copyright (C) 2008-2015  James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <string.h>

#include "IvShaderProgramOGL.h"
#include "IvAssert.h"
#include "IvFragmentShaderOGL.h"
#include "IvUniformOGL.h"
#include "IvVertexShaderOGL.h"
#include "IvDebugger.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::IvShaderProgramOGL()
//-------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------
IvShaderProgramOGL::IvShaderProgramOGL() : IvShaderProgram()
    , mProgramID(0)
    , mNextTextureStage(0)
{
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::~IvShaderProgramOGL()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
IvShaderProgramOGL::~IvShaderProgramOGL()
{
    ASSERT(!mProgramID);
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::CreateFromFile()
//-------------------------------------------------------------------------------
// Create a shader from a file
//-------------------------------------------------------------------------------
bool
IvShaderProgramOGL::Create( GLuint vertexShaderID, GLuint fragmentShaderID )
{
    // check for valid inputs
    if ( 0 == vertexShaderID || 0 == fragmentShaderID )
        return false;
    
    // allocate the shader id
    mProgramID = glCreateProgram();
    programID = mProgramID;
    if ( mProgramID == 0 )
        return false;
    
    // attach the shaders
    glAttachShader( mProgramID, vertexShaderID );
    glAttachShader( mProgramID, fragmentShaderID );
    
    // link it
    glLinkProgram( mProgramID );
    GLint status = 0;
    glGetProgramiv( mProgramID, GL_LINK_STATUS, &status );
    if ( 0 == status )
        return false;
    
    return true;
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::Destroy()
//-------------------------------------------------------------------------------
// Clean up before destructor
//-------------------------------------------------------------------------------
void
IvShaderProgramOGL::Destroy()
{
    glDeleteProgram(mProgramID);
    mProgramID = 0;
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::MakeActive()
//-------------------------------------------------------------------------------
// Make this the active program
//-------------------------------------------------------------------------------
bool
IvShaderProgramOGL::MakeActive()
{
    if ( mProgramID == 0 )
        return false;

    glUseProgram( mProgramID );

    std::map<std::string, IvUniformOGL*>::iterator iter = mUniforms.begin();
   
    while (iter != mUniforms.end())
    {
        iter->second->Update();
        
        iter++;
    }

    return true;
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::GetUniform()
//-------------------------------------------------------------------------------
// Queries, returns and caches a shader uniform
//-------------------------------------------------------------------------------
IvUniform*
IvShaderProgramOGL::GetUniform(char const* name)
{
    if (!name)
    {
        return nullptr;
    }

    // Did we already query the uniform?
    if (mUniforms.find(name) != mUniforms.end())
    {
        return mUniforms[name];
    }

    // First, query the location
    GLint location = glGetUniformLocation(mProgramID, name);
    if (location == -1)
        return nullptr;
    
    // now find it in the list of uniforms to get type and size
    GLint numUniforms = 0;
    glGetProgramiv( mProgramID, GL_ACTIVE_UNIFORMS, &numUniforms );
    GLint uniformMaxLength = 0;
    glGetProgramiv( mProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength );
    GLint count = -1;
    GLenum type = 0;
    GLchar* uniformName = new GLchar[uniformMaxLength];
    bool found = false;
    int maxlen = strlen(name);
    for ( GLint i = 0; i < numUniforms; ++i )
    {
        GLsizei length;
        glGetActiveUniform( mProgramID, i, uniformMaxLength, &length, &count, &type, uniformName);              
        if (strncmp(uniformName, name, maxlen) == 0)
        {
            found = true;
            break;
        }
    }
    delete [] uniformName;

    // not found
    if ( !found || count < 0 )
        return nullptr;
    
    IvUniformType ivType;
    switch (type)
    {
        case GL_FLOAT:
            ivType = kFloatUniform;
            break;
        case GL_FLOAT_VEC3:
            ivType = kFloat3Uniform;
            break;
        case GL_FLOAT_VEC4:
            ivType = kFloat4Uniform;
            break;
        case GL_FLOAT_MAT4:
            ivType = kFloatMatrix44Uniform;
            break;
        case GL_SAMPLER_2D:
            ivType = kTextureUniform;
            break;
        default:
            return nullptr;
    };

    IvUniformOGL* uniform = new IvUniformOGL(ivType, (unsigned int)count, this, location, ivType == kTextureUniform?mNextTextureStage++:0);
    mUniforms[name] = uniform;

    return uniform;
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::SetUniform()
//-------------------------------------------------------------------------------
//  float set
//-------------------------------------------------------------------------------
void IvShaderProgramOGL::SetUniform(const char*name, float value)
{
    glUniform1f(glGetUniformLocation(mProgramID,name), value);
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::SetUniform()
//-------------------------------------------------------------------------------
//  IvVector2 set
//-------------------------------------------------------------------------------
void IvShaderProgramOGL::SetUniform(const char *name,IvVector2 value)
{
    glUniform2f(glGetUniformLocation(mProgramID,name), value.x,value.y);
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::SetUniform()
//-------------------------------------------------------------------------------
//  IvVector3 set
//-------------------------------------------------------------------------------
void IvShaderProgramOGL::SetUniform(const char *name,IvVector3 value)
{
    glUniform3f(glGetUniformLocation(mProgramID,name), value.x,value.y,value.z);
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::SetUniform()
//-------------------------------------------------------------------------------
//  IvVector4 set
//-------------------------------------------------------------------------------
void IvShaderProgramOGL::SetUniform(const char *name,IvVector4 value)
{
    glUniform4f(glGetUniformLocation(mProgramID,name), value.x,value.y,value.z,value.w);
}

//-------------------------------------------------------------------------------
// @ IvShaderProgramOGL::SetUniform()
//-------------------------------------------------------------------------------
//  IvTexture set
//-------------------------------------------------------------------------------
void IvShaderProgramOGL::SetUniform(const char *name,unsigned int texture)
{
    static GLuint unit=0;
    glActiveTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(mProgramID,name), 0);
   
}



