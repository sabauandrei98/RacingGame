
//
//  RoadGenerator.hpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/10/19.
//

#pragma once

#include <vector>
#include <IvMath.h>
#include "BezierCurve.hpp"

class RoadGenerator
{
public:
    static constexpr float roadWidth = 0.75f;
    static const std::vector<std::pair<IvVector3, IvVector3>> findTrackPoints(const std::vector<IvVector3>& roadPoints);
    static const std::pair<IvVector3, IvVector3> calculateNormalOnPoint(const IvVector3& a, const IvVector3& b, const IvVector3& p);

};
