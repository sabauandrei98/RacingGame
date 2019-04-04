//===============================================================================
// @ IvVertexFormats.h
// 
// Vertex format definitions
// ------------------------------------------------------------------------------
// Copyright (C) 2008-2015  James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//===============================================================================

#ifndef __IvVertexFormats__h__
#define __IvVertexFormats__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "IvVector2.h"
#include "IvVector3.h"
#include "IvVector4.h"
#include "IvColor.h"
#include <vector>
//-------------------------------------------------------------------------------
//-- Classes ----------------------------------------------------------
//-------------------------------------------------------------------------------

struct VertexAttribute
{
    std::string name;
    uint32_t    noFloats;
    std::size_t offset = 0;
};


class VertexDescription
{
    std::vector<VertexAttribute> attributes;
    uint32_t vertexSize = 0;
public:
    VertexDescription() = default;
    ~VertexDescription()=default;
    
    
    void AddAttribute(const char* name, uint32_t noFloats);
    
    uint32_t GetVertexSize() const;
    
    const std::vector<VertexAttribute> & GetAttributes() const;
    
    template <class T>
    T* GetAttribute( const char * attributeName, void * vertexData) const;
    
    template<class T>
    T* NextVertexAttribute(T * attributePtr);
    
};

//-------------------------------------------------
//---Generic methods for Vertex Description--------
//-------------------------------------------------


//-------------------------------------------------------------------------------
// @ VertexDescription::GetAttribute()
//-------------------------------------------------------------------------------
// Get the attribute after the name
//-------------------------------------------------------------------------------
template <class T>
T* VertexDescription::GetAttribute( const char * attributeName, void * vertexData) const
{
    auto itr = std::find_if(attributes.begin(),attributes.end(), [&](const VertexAttribute & v){
        if(v.name == attributeName)
            return true;
        return false;
    });
    if(itr != attributes.end())
    {
        return reinterpret_cast<T*>(reinterpret_cast<char*>(vertexData)
            + itr->offset);
    }
    return nullptr;
}

//-------------------------------------------------------------------------------
// @ VertexDescription::NextVertexAttribute()
//-------------------------------------------------------------------------------
template<class T>
T* VertexDescription::NextVertexAttribute(T * attributePtr)
{
    return reinterpret_cast<T*>(reinterpret_cast<char*>(attributePtr)
                +GetVertexSize());
}

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

// enum for requesting format
enum IvVertexFormat 
{
    kPFormat,       // position only
    kCPFormat,      // color, position
    kNPFormat,      // normal, position
    kCNPFormat,     // color, normal, position
    kTCPFormat,     // texture coord, color, position
    kTNPFormat,      // texture coord, normal, position

    kLastVertexFormat = kTNPFormat

};
const int kVertexFormatCount = kLastVertexFormat + 1;

// individual format structs
// note that in a "real" renderer some of these would make use of compressed data

// a bit silly, but consistent
struct IvPVertex
{
    IvVector3 position;
};

struct IvCPVertex
{
    IvColor color;
    IvVector3 position;
};

struct IvNPVertex
{
    IvVector3 normal;
    IvVector3 position;
};

struct IvCNPVertex
{
    IvColor color;
    IvVector3 normal;
    IvVector3 position;
};

struct IvTCPVertex
{
    IvVector2 texturecoord;
    IvColor color;
    IvVector3 position;
};

struct IvTNPVertex
{
    IvVector2 texturecoord;
    IvVector3 normal;
    IvVector3 position;
};

const size_t kIvVFSize[] =
{
    sizeof(IvPVertex),
    sizeof(IvCPVertex),
    sizeof(IvNPVertex),
    sizeof(IvCNPVertex),
    sizeof(IvTCPVertex),
    sizeof(IvTNPVertex)
};


#endif
