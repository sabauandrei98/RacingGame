#pragma once

#include <vector>
#include <IvVector3.h>

class BezierCurve
{
public:
    static const std::vector<IvVector3> buildCurve(const std::vector<IvVector3>& bezierPoints, float tStep);
    static void extractPoints(std::vector<IvVector3>& line, float tStep, std::vector<IvVector3>& middlePoints);
    static const IvVector3 lerp(const IvVector3& a, const IvVector3& b, float t);
};

