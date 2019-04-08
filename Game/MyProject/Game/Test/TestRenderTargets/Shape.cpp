//
//  Shape.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/8/19.
//

#include "Shape.hpp"

Shape::Shape()
{
    
}

Shape::~Shape()
{
    
}

void Shape::SetVertexData(void *vertexData)
{
    this->vertexData=vertexData;
}

void Shape::SetVertexDescription(VertexDescription vertexDescription)
{
    this->vertexDescription=vertexDescription;
}

void Shape::Setup(const char *shaderName,const char* textureName)
{

    std::vector<unsigned int> indices;
    for(int i=0;i<noVertices;i++)
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
    
    IvFragmentShader* vf=IvRenderer::mRenderer->GetResourceManager()
    ->CreateFragmentShaderFromFile(shaderName);
    
    mShader=IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(vs,vf);
    
    
    vertexBuffer = IvRenderer::mRenderer->GetResourceManager()
    ->CreateVertexBuffer(vertexDescription,noVertices,vertexData,kImmutableUsage);
    
    indexBuffer = IvRenderer::mRenderer->GetResourceManager()
    ->CreateIndexBuffer(noVertices,indexPtr,kImmutableUsage);
    
    IvImage *image=IvImage::CreateFromFile(textureName);
    if(image)
    {
        mTexture=IvRenderer::mRenderer->GetResourceManager()
        ->CreateTexture((image->GetBytesPerPixel()==4) ? kRGBA32TexFmt : kRGB24TexFmt,image
                        ->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
    }
    
    
}

void Shape::SetNoVertices(unsigned int noVertices)
{
    this->noVertices=noVertices;
}

void Shape::SetTexture(const char *name, unsigned int reference)
{
    mShader->SetUniform(name,reference);
}

void Shape::SetTexture()
{
    textureUniform=mShader->GetUniform("Texture");
    if(textureUniform)
        textureUniform->SetValue(mTexture);
}

void Shape::Draw()
{
    IvRenderer::mRenderer->Draw(kTriangleStripPrim,
                                vertexBuffer,
                                indexBuffer,
                                noVertices,
                                mShader);
    
  
    //   mShader->SetUniform("MyColor",IvVector4{0.1,0.5,0.1,0.6});
    //   IvRenderer::mRenderer->Draw(kTriangleListPrim,
    //                                    vertexBuffer,
    //                                    indexBuffer,
    //                                    3,
    //                                    mShader);
    
    
 
}

