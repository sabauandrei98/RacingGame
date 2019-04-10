//
//  Test.cpp
//  Game
//
//  Created by Monica Olanescu - (p) on 4/5/19.
//

#include "TestRT.hpp"

TestRT::TestRT()
{
}

void TestRT::Create()
{
    VertexDescription vertexDescription;
    vertexDescription.AddAttribute("IvPos",3);
    vertexDescription.AddAttribute("IvCoord",2);
    
    void* vertexData = IvStackAllocator::mScratchAllocator->Allocate(4 * vertexDescription.GetVertexSize());
    
    IvVector3* positionPtr = vertexDescription.GetAttribute<IvVector3>("IvPos",vertexData);
    
    *positionPtr = IvVector3(-1.0f,-1.0f,0.0f);
    positionPtr = vertexDescription.NextVertexAttribute(positionPtr);
    
    *positionPtr = IvVector3(-1.0f,1.0f,0.0f);
    positionPtr = vertexDescription.NextVertexAttribute(positionPtr);
    
    *positionPtr = IvVector3(1.0f,-1.0f,0.0f);
    positionPtr = vertexDescription.NextVertexAttribute(positionPtr);
    
    *positionPtr = IvVector3(1.0f,1.0f,0.0f);
    
    IvVector2* uvPtr=vertexDescription.GetAttribute<IvVector2>("IvCoord",vertexData);
    
    *uvPtr=IvVector2{1.,0.};
    uvPtr=vertexDescription.NextVertexAttribute(uvPtr);
    
    *uvPtr=IvVector2{1.,1.};
    uvPtr=vertexDescription.NextVertexAttribute(uvPtr);
    
    *uvPtr=IvVector2{0.,0.};
    uvPtr=vertexDescription.NextVertexAttribute(uvPtr);
    
    *uvPtr=IvVector2{0.,1.};
    
    Shape* shape=new Shape();
    shape->SetNoVertices(4);
    shape->SetVertexData(vertexData);
    shape->SetVertexDescription(vertexDescription);
    
    shapes.push_back(shape);
    
    
    VertexDescription vertexDescription2;
    vertexDescription2.AddAttribute("IvPos",3);
    vertexDescription2.AddAttribute("IvCoord",2);
    
    void* vertexData2 = IvStackAllocator::mScratchAllocator->Allocate(3 * vertexDescription2.GetVertexSize());
    
    IvVector3* positionPtr2 = vertexDescription2.GetAttribute<IvVector3>("IvPos",vertexData2);
    
    *positionPtr2 = IvVector3(-0.3f,-0.3f,0.2f);
    positionPtr2 = vertexDescription2.NextVertexAttribute(positionPtr2);
    
    *positionPtr2 = IvVector3(-0.3f,0.3f,0.2f);
    positionPtr2 = vertexDescription2.NextVertexAttribute(positionPtr2);
    
    *positionPtr2 = IvVector3(0.3f,-0.3f,0.2f);
    
    IvVector2* uvPtr2=vertexDescription2.GetAttribute<IvVector2>("IvCoord",vertexData2);
    
    *uvPtr2=IvVector2{1.,0.};
    uvPtr2=vertexDescription2.NextVertexAttribute(uvPtr2);
    
    *uvPtr2=IvVector2{1.,1.};
    uvPtr2=vertexDescription2.NextVertexAttribute(uvPtr2);
    
    *uvPtr2=IvVector2{0.,0.};
    
    
    Shape* shape2=new Shape();
    shape2->SetNoVertices(3);
    shape2->SetVertexData(vertexData2);
    shape2->SetVertexDescription(vertexDescription2);
    
    shapes.push_back(shape2);
    
    
    VertexDescription vertexDescription3;
    vertexDescription3.AddAttribute("IvPos",3);
    vertexDescription3.AddAttribute("IvCoord",2);
    
    void* vertexData3 = IvStackAllocator::mScratchAllocator->Allocate(3 * vertexDescription3.GetVertexSize());
    
    
    IvVector3* positionPtr3 = vertexDescription3.GetAttribute<IvVector3>("IvPos",vertexData3);
    
    *positionPtr3 = IvVector3(-0.4f,-0.4f,0.1f);
    positionPtr3 = vertexDescription3.NextVertexAttribute(positionPtr3);
    
    *positionPtr3 = IvVector3(-0.4f,0.4f,0.1f);
    positionPtr3 = vertexDescription3.NextVertexAttribute(positionPtr3);
    
    *positionPtr3 = IvVector3(0.4f,-0.4f,0.1f);
    
    IvVector2* uvPtr3=vertexDescription3.GetAttribute<IvVector2>("IvCoord",vertexData3);
    
    *uvPtr3=IvVector2{1.,0.};
    uvPtr3=vertexDescription3.NextVertexAttribute(uvPtr3);
    
    *uvPtr3=IvVector2{1.,1.};
    uvPtr3=vertexDescription3.NextVertexAttribute(uvPtr3);
    
    *uvPtr3=IvVector2{0.,0.};
    
    
    Shape* shape3=new Shape();
    shape3->SetNoVertices(3);
    shape3->SetVertexData(vertexData3);
    shape3->SetVertexDescription(vertexDescription3);
    
    shapes.push_back(shape3);
    
    //------ create framebuffer  -------//
    IvRenderTarget* renderTarget=IvRenderer::mRenderer->GetResourceManager()
    ->CreateRenderTarget(RenderTargetType::COLOR);
    
    IvRenderTarget* renderTarget2=IvRenderer::mRenderer->GetResourceManager()
    ->CreateRenderTarget(RenderTargetType::DEPTH);

    std::vector<IvRenderTarget*> renderTargets;
    renderTargets.push_back(renderTarget);
    renderTargets.push_back(renderTarget2);
    
    frameBuffer=IvRenderer::mRenderer->GetResourceManager()
    ->CreateFrameBuffer(renderTargets,1024,768);
    
}

TestRT::~TestRT()
{
    for(int i=0;i<shapes.size();i++)
        delete shapes[i];
}

void TestRT::Setup()
{
    shapes[0]->Setup("testShaderRT","b1.tga");
    shapes[1]->Setup("testBlurShader","b1.tga");
}

void TestRT::Draw()
{
    
    frameBuffer->Bind();
 
    shapes[0]->SetUniforms();
    shapes[0]->Draw();
    
    shapes[1]->SetUniforms();
    shapes[1]->Draw();
    
    if(!frameBuffer->Unbind())
    {
        std::cout<<"Cannot unbind framebuffer!"<<std::endl;
    
        IvRenderTarget* render=frameBuffer->GetTextures()[0];
        shapes[0]->SetTexture("Texture",render->GetReference());
        shapes[0]->Draw();
    
        IvRenderTarget* render2=frameBuffer->GetTextures()[1];
        shapes[1]->SetTexture("Texture",render2->GetReference());
        shapes[1]->Draw();
    }
    
}
