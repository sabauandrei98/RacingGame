
#include "RoadEditor.hpp"


RoadEditor::RoadEditor(SceneGraph* sGraph) : sceneGraph(sGraph)
{
    setupPoints();
    getPointsFromScene();
    roadGenerator = new RoadGeneratorControler(bezierPoints, rMiddlePoints, rMarginPoints);
}


void RoadEditor::setupPoints()
{
    std::shared_ptr<SceneNode> root = sceneGraph->getRoot();
    std::vector<IvVector3> positions = {{-5, 0, -5}, {-10, 0, 2}, {-5, 0, 7}, {-2, 0, 5}, {1, 0, 1},
        {-3, 0, -5}, {0, 0, -5},  {4, 0, -3}, {3, 0, 4}, {-5, 0, -5}};
    
    for(int i = 0; i < positions.size(); i++)
    {
        std::shared_ptr<SceneNode> point = std::make_shared<SceneNode>("bezierPoint" + std::to_string(i));
        root->addChild(point);
        point->setLocalPosition(positions[i]);
        
        if (i % 3 == 0)
            point->setRenderable(meshInstanceRed);
        else
            point->setRenderable(meshInstanceRed);
    }
}


void RoadEditor::getPointsFromScene()
{
    sceneGraph->getRoot()->findAllNodesContainingName("bezierPoint", bezierScenePoints);
    
    for(int i = 0; i < bezierScenePoints.size(); i++)
        bezierPoints.push_back(bezierScenePoints[i]->getLocalPosition());
}

void RoadEditor::resizeRoadEditor()
{
    if(bezierPoints.size() != bezierScenePoints.size() || bezierMiddlePoints.size() == 0)
    {
        
        for(int i = 0; i < bezierScenePoints.size(); i++)
        {
            bezierScenePoints[i]->remove();
        }
        bezierScenePoints.clear();
        
        
        for(int i = 0; i < bezierMiddlePoints.size(); i++)
        {
            bezierMiddlePoints[i]->remove();
        }
        bezierMiddlePoints.clear();
        
        for(int i = 0; i < bezierMarginPoints.size(); i++)
        {
            bezierMarginPoints[i].first->remove();
            bezierMarginPoints[i].second->remove();
        }
        bezierMarginPoints.clear();
        
        
        for(int i = 0; i < rMiddlePoints.size(); i++)
        {
            std::shared_ptr<SceneNode> point = std::make_shared<SceneNode>("bezierMiddlePoint" + std::to_string(i));
            sceneGraph->getRoot()->addChild(point);
            point->setLocalPosition(rMiddlePoints[i]);
            point->setRenderable(meshInstanceBlue);
            bezierMiddlePoints.push_back(point);
        }
        
        for(int i = 0; i < rMarginPoints.size(); i++)
        {
            std::shared_ptr<SceneNode> pointL = std::make_shared<SceneNode>("bezierMarginLPoint" + std::to_string(i));
            sceneGraph->getRoot()->addChild(pointL);
            pointL->setLocalPosition(rMarginPoints[i].first);
            pointL->setRenderable(meshInstanceBlue);
            
            std::shared_ptr<SceneNode> pointR = std::make_shared<SceneNode>("bezierMarginRPoint" + std::to_string(i));
            sceneGraph->getRoot()->addChild(pointR);
            pointR->setLocalPosition(rMarginPoints[i].second);
            pointR->setRenderable(meshInstanceBlue);
            bezierMarginPoints.push_back(std::make_pair(pointL, pointR));
        }
        
        //render bezier points at final to see the color
        for(int i = 0; i < bezierPoints.size(); i++)
        {
            std::shared_ptr<SceneNode> point = std::make_shared<SceneNode>("bezierPoint" + std::to_string(i));
            sceneGraph->getRoot()->addChild(point);
            point->setLocalPosition(bezierPoints[i]);
            
            if(i % 3 == 0)
                point->setRenderable(meshInstanceRed);
            else
                point->setRenderable(meshInstanceGreen);
            
            bezierScenePoints.push_back(point);
        }
        
    }
}

void RoadEditor::buildRoadEditor()
{
    resizeRoadEditor();
    
    for(int i = 0; i < bezierPoints.size(); i++)
        bezierScenePoints[i]->setLocalPosition(bezierPoints[i]);
    
    for(int i = 0; i < rMiddlePoints.size(); i++)
        bezierMiddlePoints[i]->setLocalPosition(rMiddlePoints[i]);
    
    for(int i = 0; i < rMarginPoints.size(); i++)
    {
        bezierMarginPoints[i].first->setLocalPosition(rMarginPoints[i].first);
        bezierMarginPoints[i].second->setLocalPosition(rMarginPoints[i].second);
    }
}

RoadEditor::~RoadEditor()
{
    delete roadGenerator;
}

void RoadEditor::generateRoadEditorWithTexture()
{
    
    std::shared_ptr<SceneNode> root = sceneGraph->getRoot();
    std::shared_ptr<SceneNode> p = std::make_shared<SceneNode>("roadTextured");
    root->addChild(p);
    
    std::shared_ptr<Mesh> meshTexture = std::make_shared<Mesh>();
    
    IvTCPVertex point;
    IvVertexFormat format = IvVertexFormat::kTCPFormat;
    std::vector<IvTCPVertex> pointPosition;
    std::vector<unsigned int> indexBuffer;
    
    point.color.Set(255, 255, 255, 255);
    for(int i = 0; i < rMarginPoints.size(); i++)
    {
        point.position = rMarginPoints[i].first;
        pointPosition.push_back(point);
        point.position = rMarginPoints[i].second;
        pointPosition.push_back(point);
    }
    
    
    for(int i = 0; i < rMarginPoints.size() * 2; i += 4)
    {
        pointPosition[i].texturecoord = {1,0};
        pointPosition[i+1].texturecoord = {1,1};
        pointPosition[i+2].texturecoord = {0,0};
        pointPosition[i+3].texturecoord = {0,1};
    }
    
    for(int i = 0; i < rMarginPoints.size() * 2; i++)
    {
        indexBuffer.push_back(i);
    }
    
    meshTexture->setVertexBuffer(pointPosition, format);
    meshTexture->setIndexBuffer(indexBuffer);
    
    
    const char* shader = "roadShader";
    std::shared_ptr<MeshInstance> meshTextureInstance = std::make_shared<MeshInstance>();
    meshTextureInstance->setMesh(meshTexture);
    meshTextureInstance->setShader(shader);
    std::vector<std::string> uniforms;
    uniforms.push_back("roadTexture");
    meshTextureInstance->addShaderUniforms(uniforms);
    
    IvImage* image = IvImage::CreateFromFile("roadTexture.tga");
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
    
    root->findFirstNodeWithName("roadTextured")->setRenderable(meshTextureInstance);
    
}

void RoadEditor::Update(float dt)
{
    sceneGraph->updateScene(dt);
    roadGenerator->Update(dt);
    buildRoadEditor();
    
    //coloring stuff
    for(int i = 0; i < bezierScenePoints.size(); i++)
    {
        if(i % 3 == 0)
            bezierScenePoints[i]->setRenderable(meshInstanceRed);
        else
            bezierScenePoints[i]->setRenderable(meshInstanceGreen);
    }
    
    //set yellow the editable point
    bezierScenePoints[roadGenerator->getEditIndex()]->setRenderable(meshInstanceYellow);
    
    
    if (IvGame::mGame->mEventHandler->IsKeyReleased('g'))
    {
        generateRoadEditorWithTexture();
    }
}

