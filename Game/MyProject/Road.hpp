#pragma once

#include "../../SceneManagement/SceneGraph.hpp"
#include "../../SceneManagement/CameraSceneNode.hpp"
#include ""
#include <IvImage.h>

class Road{
    
public:
    Road();
    ~Road();
    
    void Update(float dt);
    void Render();
    
private:
    //information
    std::vector<IvVector3> bezierPoints;
    std::vector<IvVector3> rMiddlePoints;
    std::vector<std::pair<IvVector3,IvVector3>> rMarginPoints;
    
    //scene points
    std::vector<std::shared_ptr<SceneNode>> bezierScenePoints;
    std::vector<std::shared_ptr<SceneNode>> bezierMiddlePoints;
    std::vector<std::pair<std::shared_ptr<SceneNode>, std::shared_ptr<SceneNode>>> bezierMarginPoints;
    
    std::shared_ptr<MeshInstance> meshInstanceRed;
    std::shared_ptr<MeshInstance> meshInstanceBlue;
    std::shared_ptr<MeshInstance> meshInstanceGreen;
    std::shared_ptr<MeshInstance> meshInstanceYellow;
    
    RoadGeneratorControler* roadGenerator;
    SceneGraph* sceneGraph;
    
    void setupPoints();
    void setupMeshes();
    void setupGraph();
    
    void getPointsFromScene();
    void buildRoad();
    void resizeRoad();
    
    void generateRoadWithTexture();
};