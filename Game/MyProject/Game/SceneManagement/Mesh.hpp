//
//  Mesh.hpp
//  Game
//
//  Created by Tamas Both - (p) on 03/04/2019.
//

#pragma once

#include <memory>
#include <vector>

#include <IvVertexBuffer.h>
#include <IvIndexBuffer.h>
#include <IvStackAllocator.h>
#include <IvRenderer.h>
#include <IvResourceManager.h>

class Mesh : std::enable_shared_from_this<Mesh> {
private:
    // private variable(s)
    IvVertexBuffer* _vertex_buffer;
    IvIndexBuffer*  _index_buffer;
    
    // private function(s) and method(s)
    void destroyVertexBuffer();
    void destroyIndexBuffer();
    
public:
    // constructor(s) and destructor
    Mesh();
    Mesh(const std::vector<IvTNPVertex>&, const std::vector<unsigned int>&);
    ~Mesh();
    
    // public functions and methods
    void setVertexBuffer(const std::vector<IvTNPVertex>&);
    void setIndexBuffer(const std::vector<unsigned int>&);
    
    IvVertexBuffer* getVertexBuffer();
    IvIndexBuffer* getIndexBuffer();
};
