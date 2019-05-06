
#pragma once

#include <IvMatrix33.h>
#include <IvMath.h>
#include <IvImage.h>
#include "SceneNode.hpp"

class RoadNode : std::enable_shared_from_this<RoadNode>, public SceneNode {

public:
    RoadNode(const std::string& name, std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints);
    
private:
    void buildMesh(std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints);
};
