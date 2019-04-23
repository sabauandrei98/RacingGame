#include "BezierCurve.hpp"

const IvVector3 BezierCurve::lerp(const IvVector3& a, const IvVector3& b, float t)
{
    float cx = (float)a.x + (float)(b.x - a.x) * t;
    float cz = (float)a.z + (float)(b.z - a.z) * t;
    return {cx, 0, cz};
}

const IvVector3 BezierCurve::getPointFromLine(float t, const std::vector<IvVector3>& line)
{
    std::vector<IvVector3> remainingPoints;
    for(int i = 0; i < line.size(); i++)
        remainingPoints.push_back(line[i]);
    
    for(int i = 0; i < remainingPoints.size() - 1; i++)
        for(int j = 0; j < remainingPoints.size() - i - 1; j++)
        {
            remainingPoints[j] = lerp(remainingPoints[j], remainingPoints[j+1], t);
            remainingPoints[j].y = 0;
        }
    
    return remainingPoints[0];
}

void BezierCurve::extractPoints(std::vector<IvVector3>& line, float tStep, std::vector<IvVector3>& middlePoints)
{
    for(float t = 0; t <= 1; t += tStep)
        middlePoints.push_back(getPointFromLine(t, line));
}

const std::vector<IvVector3> BezierCurve::buildCurve(const std::vector<IvVector3>& bezierPoints ,float tStep)
{
    int lastFixedPointIndex = 0;
    std::vector<IvVector3> curvePart, middlePoints;
    curvePart.push_back(bezierPoints[lastFixedPointIndex]);
    
    for(int i = 1; i < bezierPoints.size(); i++)
    {
        //F C C F
        if(i % 3 == 0)
        {
            lastFixedPointIndex = i;
            curvePart.push_back(bezierPoints[i]);
            extractPoints(curvePart, tStep, middlePoints);
            curvePart.clear();
            
            //put the start point
            curvePart.push_back(bezierPoints[i]);
        }
        else
            curvePart.push_back(bezierPoints[i]);
    }
    
    //put the ending point
    middlePoints.push_back(curvePart[curvePart.size() - 1]);
    
    return middlePoints;
}
