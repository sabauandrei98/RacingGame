//
//  IvCustomVertexFormat.cpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/3/19.
//

#include"IvVertexFormats.h"
#include <stdio.h>

VertexDescription::~VertexDescription()
{
    
}

void VertexDescription::addAttribute(const char *name,  uint32_t count)
{
    std::size_t new_offset = 0;
    for(const auto & atr : attributes)
    {
        new_offset += sizeof(float) * atr.numFloats;
    }
    VertexAttribute vertex;
    vertex.name=name;
    vertex.numFloats=count;
    vertex.offset=new_offset;
    attributes.push_back(vertex);
    m_size += (sizeof(float) * count);
}



uint32_t VertexDescription::getVertexSize() const
{
    return m_size;
}


const std::vector<VertexAttribute>& VertexDescription::getAttributes() const
{
    return attributes;
}


