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
#include <limits>

#include <IvVertexBuffer.h>
#include <IvIndexBuffer.h>
#include <IvStackAllocator.h>
#include <IvRenderer.h>
#include <IvResourceManager.h>
#include <IvVector3.h>

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
        
        _min_vertices = IvVector3(std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity(),
                                  std::numeric_limits<float>::infinity());
        _max_vertices = IvVector3(-std::numeric_limits<float>::infinity(),
                                  -std::numeric_limits<float>::infinity(),
                                  -std::numeric_limits<float>::infinity());
        
        for (const auto& vertex : vertices) {
            _min_vertices = IvVector3(std::min(_min_vertices.x, vertex.position.x),
                                      std::min(_min_vertices.y, vertex.position.y),
                                      std::min(_min_vertices.z, vertex.position.z));
            
            _max_vertices = IvVector3(std::max(_max_vertices.x, vertex.position.x),
                                      std::max(_max_vertices.y, vertex.position.y),
                                      std::max(_max_vertices.z, vertex.position.z));
        }

    }
    
    void setIndexBuffer(const std::vector<unsigned int>&);
    
    IvVertexBuffer* getVertexBuffer();
    IvIndexBuffer* getIndexBuffer();
    const unsigned int& getBufferSize() const;
    const IvVector3& getMinVertices() const;
    const IvVector3& getMaxVertices() const;
    
private:
    // private variable(s)
    IvVertexBuffer* _vertex_buffer;
    IvIndexBuffer*  _index_buffer;
    IvVector3       _min_vertices;
    IvVector3       _max_vertices;
    unsigned int    _buffer_size;
    
    // private function(s) and method(s)
    void destroyVertexBuffer();
    void destroyIndexBuffer();
};
