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



void Test::setup(const char*shaderName)
{

    VertexDescription vertex_description;
    vertex_description.addAttribute("IvPos",3);
    vertex_description.addAttribute("IvColor",3);
    
    void* vertex_data = IvStackAllocator::mScratchAllocator->Allocate(3 * vertex_description.getVertexSize());
    
    IvVector3* position_ptr = vertex_description.getAttribute<IvVector3>("IvPos",vertex_data);
    
    *position_ptr = IvVector3(-1.0f,-1.0f,0.0f);
    
    position_ptr = vertex_description.nextVertexAttribute(position_ptr);
    
    *position_ptr = IvVector3(0.0f,0.0f,0.0f);
    
    position_ptr = vertex_description.nextVertexAttribute(position_ptr);
    
    *position_ptr = IvVector3(1.0f,-1.0f,0.0f);

    IvVector3* color_ptr=vertex_description.getAttribute<IvVector3>("IvColor",vertex_data);

    *color_ptr=IvVector3{1.,0.,0.};

    color_ptr=vertex_description.nextVertexAttribute(color_ptr);

    *color_ptr=IvVector3{1.,1.,0.};

    color_ptr=vertex_description.nextVertexAttribute(color_ptr);

    *color_ptr=IvVector3{1.,0.,1.};
    
    
    for(int i=0;i<3;i++)
    {
        indices.push_back(i);
    }
    
    unsigned int numIndices =(unsigned int) indices.size();
    UInt32* indexPtr = (UInt32*)IvStackAllocator::mScratchAllocator->Allocate(sizeof(UInt32)* numIndices);
    
    for ( unsigned int i = 0; i < numIndices; ++i )
        indexPtr[i] = indices[i];
    
    IvVertexShader* vs =IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(shaderName);
    
    IvFragmentShader* vf=IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shaderName);
    
    mShader=IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(vs,vf);
    
    
    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(vertex_description,3, vertex_data,kImmutableUsage);
    
     indexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer(
        3,indexPtr,kImmutableUsage);

}


void Test::Draw()
{
    mShader->setUniform("unifColor",IvVector3{1.,0.,0.});
    IvRenderer::mRenderer->Draw(kTriangleListPrim, vertexBuffer, indexBuffer,
        3,mShader);
}
