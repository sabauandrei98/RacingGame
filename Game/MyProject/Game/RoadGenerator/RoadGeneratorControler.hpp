#pragma once
#include <algorithm>
#include <IvEventHandler.h>
#include <IvVector3.h>
#include <vector>
#include <IvGame.h>
#include "BezierCurve.hpp"
#include "RoadMargins.hpp"
#include "../SceneManagement/SceneGraph.hpp"
#include <iostream>


class RoadGeneratorControler : std::enable_shared_from_this<RoadGeneratorControler>
{
public:
    RoadGeneratorControler(std::vector<IvVector3>& bPoints, std::vector<IvVector3>& rMiddle, std::vector<std::pair<IvVector3,IvVector3>>& rMargin, float editSpeed, float tStep):
    editSpeed(editSpeed), tStep(tStep), bezierPoints(bPoints), rMiddlePoints(rMiddle), rMarginPoints(rMargin){};
    ~RoadGeneratorControler(){};
    
    bool Update(float dt);
    
    const std::vector<IvVector3>& getMiddlePoints() const {return rMiddlePoints;};
    const std::vector<std::pair<IvVector3,IvVector3>>& getMarginPoints() const { return rMarginPoints;};
    const int getEditIndex() const {return editIndex;};
    
    void previousPoint();
    void nextPoint();
    void addPoint();
    void removePoint();
    void generateTrack();
    
private:
    bool needsUpdate=false;
    bool hasUpdate=false;
    float editSpeed;
    float tStep;
    int editIndex = 0;
    
    std::vector<IvVector3>& bezierPoints;
    std::vector<IvVector3>& rMiddlePoints;
    std::vector<std::pair<IvVector3,IvVector3>>& rMarginPoints;
    
    void updateControlPointsPosition(int index);
    void mergeHeadTail();
};
