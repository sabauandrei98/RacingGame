//
//  Mesh.cpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#include "Mesh.hpp"

// -----------------------------
// CONSTRUCTOR(S) AND DESTRUCTOR
// -----------------------------

// default constructor
Mesh::Mesh() :
    _vertex_buffer(nullptr), _index_buffer(nullptr) {
    }

// destructor
Mesh::~Mesh() {
    destroyVertexBuffer();
    destroyIndexBuffer();
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

// destroys the vertex buffer
void Mesh::destroyVertexBuffer() {
    if (_vertex_buffer)
        IvRenderer::mRenderer->GetResourceManager()->Destroy(_vertex_buffer);
    _vertex_buffer = nullptr;
}

// destroys the index buffer
void Mesh::destroyIndexBuffer() {
    if (_index_buffer)
        IvRenderer::mRenderer->GetResourceManager()->Destroy(_index_buffer);
    _index_buffer = nullptr;
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// sets up the index buffer with a given vector of indexes
void Mesh::setIndexBuffer(const std::vector<unsigned int>& indices) {
    size_t      current_offset;
    
    destroyIndexBuffer();
    current_offset = IvStackAllocator::mScratchAllocator->GetCurrentOffset();
    
    _index_buffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer((unsigned int)indices.size(), (void*)indices.data(), kImmutableUsage);
    
    IvStackAllocator::mScratchAllocator->Reset(current_offset);
}

// returns the vertex buffer
IvVertexBuffer* Mesh::getVertexBuffer() {
    return _vertex_buffer;
}

// returns the index buffer
IvIndexBuffer* Mesh::getIndexBuffer() {
    return _index_buffer;
}

// returns the size of the buffer
const unsigned int& Mesh::getBufferSize() const {
    return _buffer_size;
}
