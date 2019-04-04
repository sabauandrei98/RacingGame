//
//  IvCustomVertexFormat.cpp
//  IvGraphics
//
//  Created by Monica Olanescu - (p) on 4/3/19.
//

#include"IvVertexFormats.h"
#include <stdio.h>


//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
// @ VertexDescription::AddAttribute()
//-------------------------------------------------------------------------------
// Add a new attribute,by giving its name and the number of floats
//-------------------------------------------------------------------------------
void VertexDescription::AddAttribute(const char *name,  uint32_t noFloats)
{
    std::size_t newOffset = 0;
    for(const auto & atr : attributes)
    {
        newOffset += sizeof(float) * atr.noFloats;
    }
    VertexAttribute vertex;
    vertex.name=name;
    vertex.noFloats=noFloats;
    vertex.offset=newOffset;
    attributes.push_back(vertex);
    vertexSize += (sizeof(float) * noFloats);
}


//-------------------------------------------------------------------------------
// @ VertexDescription::GetVertexSize()
//-------------------------------------------------------------------------------
uint32_t VertexDescription::GetVertexSize() const
{
    return vertexSize;
}


//-------------------------------------------------------------------------------
// @ VertexDescription::GetAttributes()
//-------------------------------------------------------------------------------
const std::vector<VertexAttribute>& VertexDescription::GetAttributes() const
{
    return attributes;
}


