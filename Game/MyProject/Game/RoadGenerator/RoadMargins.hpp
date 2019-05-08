#pragma once

#include <vector>
#include <IvMath.h>
#include "BezierCurve.hpp"

class RoadMargins
{
public:
    static constexpr float error = 0.05f;
    static constexpr float roadWidth = 0.75f;
    static const std::vector<std::pair<IvVector3, IvVector3>> findTrackPoints(const std::vector<IvVector3>& roadPoints);
    static const std::pair<IvVector3, IvVector3> calculateNormalOnPoint(const IvVector3& a, const IvVector3& b, const IvVector3& p);
    static void fixPoints(std::vector<std::pair<IvVector3, IvVector3>>& roadMarginPoints);
};