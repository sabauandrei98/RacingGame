
//
//  RoadMargins.cpp
//  Game
//
//  Created by Andrei Sabu - (p) on 4/10/19.
//

#include "RoadMargins.hpp"

const std::pair<IvVector3, IvVector3> RoadMargins::calculateNormalOnPoint(const IvVector3& a, const IvVector3& b, const IvVector3& p)
{
    float x0, y0;
    float x1, y1;
    
    x0 = a.x;
    y0 = a.z;
    x1 = b.x;
    y1 = b.z;

    //parallel points with axes
    if (abs(y0-y1) < error)
    {
        IvVector3 final0, final1;
        final0 = {p.x, 0, p.z + roadWidth};
        final1 = {p.x, 0, p.z - roadWidth};

        return std::make_pair(final0, final1);
    }

    //parallel points with axes
    if (abs(x0-x1) < error)
    {
        IvVector3 final0, final1;
        final0 = {p.x + roadWidth, 0, p.z};
        final1 = {p.x - roadWidth, 0, p.z};

        return std::make_pair(final0, final1);
    }
    
    float m = (y1 - y0)/(x1-x0);
    
    float px = p.x;
    float py = p.z;
    
    float X0, X1, Y0, Y1;
    
    X0 = -10;
    X1 = 10;
    
    Y0 = -1/m * (X0 - px) + py;
    Y1 = -1/m * (X1 - px) + py;
    
    float dist0, dist1;
    dist0 = sqrt((X0 - px)*(X0 - px) + (Y0 - py)*(Y0 - py));
    dist1 = sqrt((X1 - px)*(X1 - px) + (Y1 - py)*(Y1 - py));
    
    float lerp0, lerp1;
    lerp0 = roadWidth / dist0;
    lerp1 = roadWidth / dist1;
    
    IvVector3 final0, final1;
    IvVector3 point0, point1;
    point0 = {X0, 0, Y0};
    point1 = {X1, 0, Y1};
    final0 = BezierCurve::lerp(p, point0, lerp0);
    final1 = BezierCurve::lerp(p, point1, lerp1);
    final0.y = 0;
    final1.y = 0;

    
    return std::make_pair(final0, final1);
}

void RoadMargins::fixPoints(std::vector<std::pair<IvVector3, IvVector3>>& roadMarginPoints)
{
    for(int i = 1; i < roadMarginPoints.size(); i++)
    {
        float p0x = roadMarginPoints[i].first.x;
        float p0y = roadMarginPoints[i].first.z;
        
        float p1x = roadMarginPoints[i-1].first.x;
        float p1y = roadMarginPoints[i-1].first.z;
        float p2x = roadMarginPoints[i-1].second.x;
        float p2y = roadMarginPoints[i-1].second.z;
        
        float dist1 = sqrt((p0x-p1x)*(p0x-p1x) + (p0y-p1y)*(p0y-p1y));
        float dist2 = sqrt((p0x-p2x)*(p0x-p2x) + (p0y-p2y)*(p0y-p2y));
        if(dist1 > dist2)
            std::swap(roadMarginPoints[i].first, roadMarginPoints[i].second);
    }
}

const std::vector<std::pair<IvVector3, IvVector3>> RoadMargins::findTrackPoints(const std::vector<IvVector3>& roadPoints)
{
    std::vector<std::pair<IvVector3, IvVector3>> roadMarginPoints;

    for(int i = 0; i < roadPoints.size() - 1; i++)
    {
        const std::pair<IvVector3, IvVector3>& normal = calculateNormalOnPoint(roadPoints[i], roadPoints[i+1], roadPoints[i]);
        roadMarginPoints.push_back(normal);
    }

    //last point
    int roadSize = (int)roadPoints.size() - 2;
    const std::pair<IvVector3, IvVector3>& normal = calculateNormalOnPoint(roadPoints[roadSize], roadPoints[roadSize + 1], roadPoints[roadSize + 1]);
    roadMarginPoints.push_back(normal);
    
    fixPoints(roadMarginPoints);
    
    return roadMarginPoints;
}

