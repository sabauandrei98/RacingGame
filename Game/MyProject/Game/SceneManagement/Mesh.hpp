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
        
        // sets the starting values
        _min_max_vertices.resize(3);
        _min_max_vertices[0].x = vertices[0].position.x;
        _min_max_vertices[0].y = vertices[0].position.x;
        _min_max_vertices[1].x = vertices[0].position.y;
        _min_max_vertices[1].y = vertices[0].position.y;
        _min_max_vertices[2].x = vertices[0].position.z;
        _min_max_vertices[2].y = vertices[0].position.z;
        
        // calculates the min and max for each axe
        for (T i : vertices) {
            if (i.position.x < _min_max_vertices[0].x)
                _min_max_vertices[0].x = i.position.x;
            if (i.position.x > _min_max_vertices[0].y)
                _min_max_vertices[0].y = i.position.x;
            
            if (i.position.y < _min_max_vertices[1].x)
                _min_max_vertices[1].x = i.position.y;
            if (i.position.y > _min_max_vertices[1].y)
                _min_max_vertices[1].y = i.position.y;
            
            if (i.position.z < _min_max_vertices[2].x)
                _min_max_vertices[2].x = i.position.z;
            if (i.position.z > _min_max_vertices[2].y)
                _min_max_vertices[2].y = i.position.z;
        }
    }
    
    void setIndexBuffer(const std::vector<unsigned int>&);
    
    IvVertexBuffer* getVertexBuffer();
    IvIndexBuffer* getIndexBuffer();
    const unsigned int& getBufferSize() const;
    const std::vector<IvVector2>& getMinMaxVertices() const;
    
private:
    // private variable(s)
    IvVertexBuffer*         _vertex_buffer;
    IvIndexBuffer*          _index_buffer;
    std::vector<IvVector2>  _min_max_vertices;
    unsigned int            _buffer_size;
    
    // private function(s) and method(s)
    void destroyVertexBuffer();
    void destroyIndexBuffer();
};
