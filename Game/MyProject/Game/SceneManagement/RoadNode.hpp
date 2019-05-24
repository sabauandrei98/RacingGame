
#pragma once

#include <IvMatrix33.h>
#include <IvMath.h>
#include <IvImage.h>
#include "SceneNode.hpp"

class RoadNode : std::enable_shared_from_this<RoadNode>, public SceneNode {

public:
    RoadNode(const std::string& name, const std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints, float scaleFactor,bool reversedNormals);
    const std::vector<IvVector3>& getMiddlePoints() {return rMiddlePoints;}
private:
    float vectorScaleFactor;
    std::vector<IvVector3> rMiddlePoints;
    void buildMesh(const std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints,bool reversedNormals);
};
