
#include "RoadNode.hpp"

RoadNode::RoadNode(const std::string& name, std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints) :  SceneNode(name)
{
    buildMesh(rMarginPoints);
}

void RoadNode::buildMesh(std::vector<std::pair<IvVector3,IvVector3>>& roadPoints)
{
    std::shared_ptr<Mesh> meshTexture = std::make_shared<Mesh>();
    
    //BUFFERS
    IvTCPVertex point;
    IvVertexFormat format = IvVertexFormat::kTCPFormat;
    std::vector<IvTCPVertex> pointPosition;
    std::vector<unsigned int> indexBuffer;
    
    point.color.Set(255, 255, 255, 255);
    for(int i = 0; i < roadPoints.size(); i++)
    {
        point.position = roadPoints[i].first;
        pointPosition.push_back(point);
        point.position = roadPoints[i].second;
        pointPosition.push_back(point);
    }
    
    
    for(int i = 0; i < roadPoints.size() * 2; i += 4)
    {
        pointPosition[i].texturecoord = {1,0};
        pointPosition[i+1].texturecoord = {1,1};
        pointPosition[i+2].texturecoord = {0,0};
        pointPosition[i+3].texturecoord = {0,1};
    }
    
    for(int i = 0; i < roadPoints.size() * 2; i++)
    {
        indexBuffer.push_back(i);
    }
    
    meshTexture->setVertexBuffer(pointPosition, format);
    meshTexture->setIndexBuffer(indexBuffer);
    
    const char* shader = "../../Game/RoadGenerator/Shaders/roadShader";
    std::shared_ptr<MeshInstance> meshTextureInstance = std::make_shared<MeshInstance>();
    meshTextureInstance->setMesh(meshTexture);
    meshTextureInstance->setShader(shader);
    
    //UNIFORMS
    std::vector<std::string> uniforms;
    uniforms.push_back("roadTexture");
    meshTextureInstance->addShaderUniforms(uniforms);
    
    IvImage* image = IvImage::CreateFromFile("../../Game/RoadGenerator/Resources/road.tga");

    IvTexture* quadTexture;
    
    if (image)
    {
        quadTexture = IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt, image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
        delete image;
        image = 0;
    }
    
    IvUniform* unif = meshTextureInstance->getShaderUniforms()[0];
    if (unif)
        unif->SetValue(quadTexture);
    
    this->setRenderable(meshTextureInstance);
}





