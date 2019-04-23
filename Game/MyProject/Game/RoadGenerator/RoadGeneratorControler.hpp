
#pragma once
#include <algorithm>
#include <IvEventHandler.h>
#include <IvVector3.h>
#include <vector>
#include <IvGame.h>
#include "BezierCurve.hpp"
#include "RoadGenerator.hpp"
#include "../SceneManagement/SceneGraph.hpp"
#include <iostream>


class RoadGeneratorControler
{
public:
    RoadGeneratorControler(std::vector<IvVector3>& bPoints, std::vector<IvVector3>& rMiddle, std::vector<std::pair<IvVector3,IvVector3>>& rMargin):
    bezierPoints(bPoints), rMiddlePoints(rMiddle), rMarginPoints(rMargin){};
    ~RoadGeneratorControler(){};
    
    void Update(float dt);
    
    const std::vector<IvVector3>& getMiddlePoints() const {return rMiddlePoints;};
    const std::vector<std::pair<IvVector3,IvVector3>>& getMarginPoints() const { return rMarginPoints;};
    const int getEditIndex() const {return editIndex;};
    
private:
    const float editSpeed = 4.0f;
    const float tStep = 0.05f;
    int editIndex = 0;
    
    std::vector<IvVector3>& bezierPoints;
    std::vector<IvVector3>& rMiddlePoints;
    std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints;
    
    void updateControlPointsPosition(int index);
    void mergeHeadTail();
};
