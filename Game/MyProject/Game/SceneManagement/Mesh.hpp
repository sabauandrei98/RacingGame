//
//  Mesh.hpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//
//  Mesh class stores and manages the vertex and index buffers.
//  It needs std::vector input for both buffers.

#pragma once

#include <memory>
#include <vector>

#include <IvVertexBuffer.h>
#include <IvIndexBuffer.h>
#include <IvStackAllocator.h>
#include <IvRenderer.h>
#include <IvResourceManager.h>

class Mesh : std::enable_shared_from_this<Mesh> {
public:
    // constructor(s) and destructor
    Mesh();
    ~Mesh();
    
    // public functions and methods
    
    // sets the vertex buffer 
    template <class T>
    void setVertexBuffer(const std::vector<T>& vertices, const IvVertexFormat& vertex_format) {
        size_t  current_offset;
        
        destroyVertexBuffer();
        current_offset = IvStackAllocator::mScratchAllocator->GetCurrentOffset();
        _buffer_size = (unsigned int)vertices.size();
        
        _vertex_buffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(vertex_format, (unsigned int)vertices.size(), (void*)vertices.data(), kImmutableUsage);
        
        IvStackAllocator::mScratchAllocator->Reset(current_offset);
    }
    
    void setIndexBuffer(const std::vector<unsigned int>&);
    
    IvVertexBuffer* getVertexBuffer();
    IvIndexBuffer* getIndexBuffer();
    const unsigned int& getBufferSize() const;
    
private:
    // private variable(s)
    IvVertexBuffer* _vertex_buffer;
    IvIndexBuffer*  _index_buffer;
    unsigned int    _buffer_size;
    
    // private function(s) and method(s)
    void destroyVertexBuffer();
    void destroyIndexBuffer();
};
