#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "IvVector3.h"

//FILE FORMAT

//n - size of the road
//x y z   (n times for middle points)
//x1 y1 z1 x2 y2 z2 (n times for pairs of margin points)

class RoadImporterExporter{

public:
    RoadImporterExporter(){};
    ~RoadImporterExporter(){};
    
    void importFrom(const std::string& fileName);
    void exportTo(const std::string& fileName);
   
    const std::vector<IvVector3>& getMiddlePoints() const {return rMiddlePoints;};
    const std::vector<std::pair<IvVector3,IvVector3>>& getMarginPoints() const { return rMarginPoints;};
    
private:
    std::vector<IvVector3> rMiddlePoints;
    std::vector<std::pair<IvVector3,IvVector3>> rMarginPoints;
    
    std::vector<std::string> split(const std::string& line, const char c);
};
