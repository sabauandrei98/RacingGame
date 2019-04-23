
#include "TestBezier.hpp"


TestBezier::TestBezier()
{
    setupGraph();
    setupMeshes();
    setupPoints();
    getPointsFromScene();
    roadGenerator = new RoadGeneratorControler(bezierPoints, rMiddlePoints, rMarginPoints);
    
    std::shared_ptr<SceneNode> root = sceneGraph->getRoot();
    std::shared_ptr<SceneNode> p = std::make_shared<SceneNode>("roadTextured");
    root->addChild(p);

}

void TestBezier::setupMeshes()
{
    //mesh
    std::shared_ptr<Mesh> meshRed = std::make_shared<Mesh>();
    std::shared_ptr<Mesh> meshBlue = std::make_shared<Mesh>();
    std::shared_ptr<Mesh> meshGreen = std::make_shared<Mesh>();
    std::shared_ptr<Mesh> meshYellow = std::make_shared<Mesh>();
    
    IvCPVertex point;
    IvVertexFormat format = IvVertexFormat::kCPFormat;
    point.position = {0,0,0};
    std::vector<IvCPVertex> pointPosition;
    std::vector<unsigned int> indexBuffer;
    indexBuffer.push_back(0);
    
    //red
    point.color.Set(255,0, 0, 1);
    pointPosition.push_back(point);
    meshRed->setVertexBuffer(pointPosition, format);
    meshRed->setIndexBuffer(indexBuffer);
    
    //blue
    pointPosition.clear();
    point.color.Set(0,0, 255, 1);
    pointPosition.push_back(point);
    meshBlue->setVertexBuffer(pointPosition, format);
    meshBlue->setIndexBuffer(indexBuffer);
    
    //green
    pointPosition.clear();
    point.color.Set(0, 255, 0, 1);
    pointPosition.push_back(point);
    meshGreen->setVertexBuffer(pointPosition, format);
    meshGreen->setIndexBuffer(indexBuffer);
    
    //yellow
    pointPosition.clear();
    point.color.Set(255, 255, 0, 1);
    pointPosition.push_back(point);
    meshYellow->setVertexBuffer(pointPosition, format);
    meshYellow->setIndexBuffer(indexBuffer);
    
    //mesh instance
    const char* shader = "testShader";
    meshInstanceRed = std::make_shared<MeshInstance>();
    meshInstanceRed->setMesh(meshRed);
    meshInstanceRed->setShader(shader);
    
    meshInstanceBlue = std::make_shared<MeshInstance>();
    meshInstanceBlue->setMesh(meshBlue);
    meshInstanceBlue->setShader(shader);
    
    meshInstanceGreen = std::make_shared<MeshInstance>();
    meshInstanceGreen->setMesh(meshGreen);
    meshInstanceGreen->setShader(shader);
    
    meshInstanceYellow = std::make_shared<MeshInstance>();
    meshInstanceYellow->setMesh(meshYellow);
    meshInstanceYellow->setShader(shader);
}

void TestBezier::setupGraph()
{
    sceneGraph = new SceneGraph();
    
    std::shared_ptr<SceneNode> root = std::make_shared<SceneNode>("root");
    std::shared_ptr<CameraSceneNode> camera = std::make_shared<CameraSceneNode>("camera", 45.0, 0.1, 35.0, 1280, 720);
    camera->setPosition({0.f, -25.0f, 0.0f });
    camera->setRotation({0,0,1});
    camera->setLookAt({0.0f, 0.0f, 0.0f});
    
    sceneGraph->setRoot(root);
    sceneGraph->setCamera(camera);
}


void TestBezier::setupPoints()
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


void TestBezier::getPointsFromScene()
{
    sceneGraph->getRoot()->findAllNodesContainingName("bezierPoint", bezierScenePoints);
    
    for(int i = 0; i < bezierScenePoints.size(); i++)
        bezierPoints.push_back(bezierScenePoints[i]->getLocalPosition());
}

void TestBezier::resizeRoad()
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

void TestBezier::buildRoad()
{
    resizeRoad();
    
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

TestBezier::~TestBezier()
{
    delete sceneGraph;
}

void TestBezier::generateRoadWithTexture()
{
    
    std::shared_ptr<Mesh> meshTexture = std::make_shared<Mesh>();
    
    IvTCPVertex point;
    IvVertexFormat format = IvVertexFormat::kTCPFormat;
    std::vector<IvTCPVertex> pointPosition;
    std::vector<unsigned int> indexBuffer;
    
    point.color.Set(255, 255, 255, 255);
    int changed = 0;
    for(int i = 0; i < rMarginPoints.size(); i++)
    {
        if(i > 0)
        {
            float p0x = rMarginPoints[i].first.x;
            float p0y = rMarginPoints[i].first.z;
            
            float p1x = rMarginPoints[i-1].first.x;
            float p1y = rMarginPoints[i-1].first.z;
            float p2x = rMarginPoints[i-1].second.x;
            float p2y = rMarginPoints[i-1].second.z;
            
            if(sqrt((p0x-p1x)*(p0x+p1x) + (p0y-p1y)*(p0y+p1y)) > sqrt((p0x-p2x)*(p0x+p2x) + (p0y-p2y)*(p0y+p2y)))
            {
                std::swap(rMarginPoints[i].first, rMarginPoints[i].second);
                changed++;
            }
        }
        
        
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
    
    std::shared_ptr<SceneNode> root = sceneGraph->getRoot();
    root->findFirstNodeWithName("roadTextured")->setRenderable(meshTextureInstance);
    
}

void TestBezier::Update(float dt)
{
    sceneGraph->updateScene(dt);
    roadGenerator->Update(dt);
    buildRoad();
    
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
        setRoad = true;
    }
    
    if(setRoad)
        generateRoadWithTexture();
}

void TestBezier::Render()
{
     sceneGraph->drawScene();
}

