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

Mesh::Mesh() :
    _vertex_buffer(nullptr), _index_buffer(nullptr) {
        
    }

Mesh::Mesh(const std::vector<IvTNPVertex>& vertices, const std::vector<unsigned int>& indices) {
    setVertexBuffer(vertices);
    setIndexBuffer(indices);
}

Mesh::~Mesh() {
    destroyVertexBuffer();
    destroyIndexBuffer();
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

void Mesh::destroyVertexBuffer() {
    IvRenderer::mRenderer->GetResourceManager()->Destroy(_vertex_buffer);
    _vertex_buffer = nullptr;
}

void Mesh::destroyIndexBuffer() {
    IvRenderer::mRenderer->GetResourceManager()->Destroy(_index_buffer);
    _index_buffer = nullptr;
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

void Mesh::setVertexBuffer(const std::vector<IvTNPVertex>& vertices) {
    size_t          current_offset;
    IvTNPVertex*    data_ptr;
    
    if (_vertex_buffer)
        destroyVertexBuffer();
    
    current_offset = IvStackAllocator::mScratchAllocator->GetCurrentOffset();
    data_ptr = (IvTNPVertex*)IvStackAllocator::mScratchAllocator->Allocate(kIvVFSize[kTNPFormat] * vertices.size());
    
    for (unsigned int i = 0; i < vertices.size(); i++) {
        data_ptr[i].texturecoord = vertices[i].texturecoord;
        data_ptr[i].normal = vertices[i].normal;
        data_ptr[i].position = vertices[i].position;
    }
    
    _vertex_buffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(kTNPFormat, (unsigned int)vertices.size(), data_ptr, kImmutableUsage);
    
    IvStackAllocator::mScratchAllocator->Reset(current_offset);
}

void Mesh::setIndexBuffer(const std::vector<unsigned int>& indices) {
    size_t      current_offset;
    UInt32*     index_ptr;
    
    if (_vertex_buffer)
        destroyVertexBuffer();
    
    current_offset = IvStackAllocator::mScratchAllocator->GetCurrentOffset();
    index_ptr = (UInt32*)IvStackAllocator::mScratchAllocator->Allocate(sizeof(UInt32)* indices.size());
    
    for (unsigned int i = 0; i < indices.size(); i++)
        index_ptr[i] = indices[i];
    
    _index_buffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer((unsigned int)indices.size(), index_ptr, kImmutableUsage);
    
    IvStackAllocator::mScratchAllocator->Reset(current_offset);
}

IvVertexBuffer* Mesh::getVertexBuffer() {
    return _vertex_buffer;
}

IvIndexBuffer* Mesh::getIndexBuffer() {
    return _index_buffer;
}
