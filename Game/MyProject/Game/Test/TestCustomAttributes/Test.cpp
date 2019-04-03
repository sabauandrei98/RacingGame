//
//  Test.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/3/19.
//

#include "Test.hpp"

Test::Test()
{
    
}

Test::~Test()
{
    
}
struct test_vertex
{
    IvVector3 pos;
};

void Test::setup(const char*shaderName)
{

    VertexDescription vertex_description;
    vertex_description.addAttribute("IvPos",3);
    
    test_vertex* vertex_data = (test_vertex*)IvStackAllocator::mScratchAllocator->Allocate(vertex_description.getVertexSize());
    
    IvVector3* position_ptr = vertex_description.getAttribute<IvVector3>(0,"IvPos",vertex_data);
    
    *position_ptr = IvVector3(-1.0f,-1.0f,0.0f);
    
    position_ptr = vertex_description.nextVertexAttribute(position_ptr);
    
    *position_ptr = IvVector3(0.0f,0.0f,0.0f);
    
    position_ptr = vertex_description.nextVertexAttribute(position_ptr);
    
    *position_ptr = IvVector3(1.0f,-1.0f,0.0f);
   
    
    for(int i=0;i<3;i++)
    {
        indices.push_back(i);
    }
    
    unsigned int numIndices =(unsigned int) indices.size();
    UInt32* indexPtr = (UInt32*)IvStackAllocator::mScratchAllocator->Allocate(sizeof(UInt32)* numIndices);
    
    for ( unsigned int i = 0; i < numIndices; ++i )
        indexPtr[i] = indices[i];
    IvVertexShader* vs =IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(shaderName);
    IvFragmentShader*vf=IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shaderName);
    mShader=IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(vs,vf);
    
    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(vertex_description,3*vertex_description.getVertexSize(), vertex_data,kImmutableUsage);
     indexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer(
        3*vertex_description.getVertexSize(),indexPtr,kImmutableUsage);

}


void Test::Draw()
{
    IvRenderer::mRenderer->Draw(kTriangleListPrim, vertexBuffer, indexBuffer,
        3,mShader);
}
