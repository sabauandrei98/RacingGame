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
    uint32_t    numFloats;
    std::size_t offset = 0;
};


class VertexDescription
{
   
    std::vector<VertexAttribute> attributes;
    uint32_t m_size = 0;
public:
    VertexDescription() = default;
    virtual ~VertexDescription();
    
    void addAttribute(const char* name, uint32_t count);
    void removeAttribute(const char* name);
    
    uint32_t getVertexSize() const;
    const std::vector<VertexAttribute> & getAttributes() const;
    
    
    template <class T>
    T* getAttribute(std::size_t vertexInde, const char * attribute_name, void * vertex_data) const;
    template<class T>
    T* nextVertexAttribute(T * attribute_ptr);
    
};

//-------------
//generic methods for Vertex Decsription
//---------------
template <class T>
T* VertexDescription::getAttribute(std::size_t vertexInde, const char * attribute_name, void * vertex_data) const
{
    auto itr = std::find_if(attributes.begin(),attributes.end(), [&](const VertexAttribute & v){
        if(v.name == attribute_name)
            return true;
        return false;
    });
    if(itr != attributes.end())
    {
        return reinterpret_cast<T*>(reinterpret_cast<char*>(vertex_data) + itr->offset);
    }
    return nullptr;
}

template<class T>
T* VertexDescription::nextVertexAttribute(T * attribute_ptr)
{
    return reinterpret_cast<T*>(reinterpret_cast<char*>(attribute_ptr) + getVertexSize());
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
