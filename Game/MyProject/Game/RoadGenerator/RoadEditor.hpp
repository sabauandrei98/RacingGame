#pragma once

#include "../SceneManagement/SceneGraph.hpp"
#include "../SceneManagement/CameraSceneNode.hpp"
#include "../SceneManagement/RoadNode.hpp"
#include "../Helper/HelperSceneNode.hpp"
#include "RoadGeneratorControler.hpp"
#include "RoadImporterExporter.hpp"
#include <IvImage.h>

class RoadEditor{
    
public:
    RoadEditor(SceneGraph* sGraph);
    ~RoadEditor();
    
    void Update(float dt);
    void generateTexturedRoad();
    std::shared_ptr<RoadGeneratorControler> getRoadGenerator(){return roadGenerator;}
   
private:
    RenderPacket render;
    std::shared_ptr<RoadNode> roadNode;
    
    //information
    std::vector<IvVector3> bezierPoints;
    std::vector<IvVector3> rMiddlePoints;
    std::vector<std::pair<IvVector3,IvVector3>> rMarginPoints;
    
    //scene points
    std::vector<std::shared_ptr<SceneNode>> bezierScenePoints;
    std::vector<std::shared_ptr<SceneNode>> bezierMiddlePoints;
    std::vector<std::pair<std::shared_ptr<SceneNode>, std::shared_ptr<SceneNode>>> bezierMarginPoints;
    
    //only for editing details
    std::shared_ptr<MeshInstance> meshInstanceRed;
    std::shared_ptr<MeshInstance> meshInstanceBlue;
    std::shared_ptr<MeshInstance> meshInstanceGreen;
    std::shared_ptr<MeshInstance> meshInstanceYellow;
    
    std::shared_ptr<RoadGeneratorControler> roadGenerator;
    SceneGraph* sceneGraph;
    RoadImporterExporter* roadIE;
    
    void setupPoints();
    void setupMeshes();
    
    void updateSceneRoadMeshColors();
    void updateSceneRoadPositions();
    void updateSceneRoadSize();
};
