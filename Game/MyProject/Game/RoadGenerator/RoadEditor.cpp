
#include "RoadEditor.hpp"


RoadEditor::RoadEditor(SceneGraph* sGraph) : sceneGraph(sGraph)
{
    setupMeshes();
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
}

RoadEditor::~RoadEditor()
{
    delete roadGenerator;
}

void RoadEditor::generateTexturedRoad()
{
    RoadNode* roadNode = new RoadNode("roadNode", rMarginPoints, sceneGraph->getRoot());
}

void RoadEditor::Update(float dt)
{
    sceneGraph->updateScene(dt);
    roadGenerator->Update(dt);
    buildRoadEditor();
    
    if (IvGame::mGame->mEventHandler->IsKeyReleased('g'))
    {
        generateTexturedRoad();
    }
}

void RoadEditor::setupMeshes()
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

