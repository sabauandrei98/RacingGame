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



void Test::Setup(const char*shaderName)
{

    VertexDescription vertexDescription;
    vertexDescription.AddAttribute("IvPos",3);
    vertexDescription.AddAttribute("IvColor",3);
    
    void* vertexData = IvStackAllocator::mScratchAllocator->Allocate(3 * vertexDescription.GetVertexSize());
    
    
    IvVector3* positionPtr = vertexDescription.GetAttribute<IvVector3>("IvPos",vertexData);
   
    *positionPtr = IvVector3(-1.0f,-1.0f,0.0f);
    positionPtr = vertexDescription.NextVertexAttribute(positionPtr);
    
    *positionPtr = IvVector3(0.0f,0.0f,0.0f);
    positionPtr = vertexDescription.NextVertexAttribute(positionPtr);
    
    *positionPtr = IvVector3(1.0f,-1.0f,0.0f);

    IvVector3* colorPtr=vertexDescription.GetAttribute<IvVector3>("IvColor",vertexData);

    *colorPtr=IvVector3{1.,0.,0.};
    colorPtr=vertexDescription.NextVertexAttribute(colorPtr);

    *colorPtr=IvVector3{1.,1.,0.};
    colorPtr=vertexDescription.NextVertexAttribute(colorPtr);

    *colorPtr=IvVector3{1.,0.,1.};
    
    
    for(int i=0;i<3;i++)
    {
        indices.push_back(i);
    }
    
    unsigned int noIndices =(unsigned int) indices.size();
    UInt32* indexPtr = (UInt32*)IvStackAllocator::mScratchAllocator->
                        Allocate(sizeof(UInt32)* noIndices);
    
    for ( unsigned int i = 0; i < noIndices; ++i )
        indexPtr[i] = indices[i];
    
    IvVertexShader* vs =IvRenderer::mRenderer->GetResourceManager()
                        ->CreateVertexShaderFromFile(shaderName);
    
    IvFragmentShader* vf=IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(shaderName);
    
    mShader=IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(vs,vf);
    
    
    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(vertexDescription,3, vertexData,kImmutableUsage);
    
     indexBuffer = IvRenderer::mRenderer->GetResourceManager()->CreateIndexBuffer(
        3,indexPtr,kImmutableUsage);

}


void Test::Draw()
{
   // mShader->setUniform("unifColor",IvVector3{1.,0.,0.});
    IvRenderer::mRenderer->Draw(kTriangleListPrim, vertexBuffer, indexBuffer,
        3,mShader);
}
