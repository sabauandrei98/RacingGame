#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "IvVector3.h"

//FILE FORMAT

//n - size of the road
//x1 y1 z1 x2 y2 z2 (n times for pairs of margin points)

class RoadImporterExporter{

public:
    
    RoadImporterExporter(){};
    ~RoadImporterExporter(){};
    
    void importFrom(const std::string& fileName);
    
    //can export without any import
    void exportTo(std::vector<std::pair<IvVector3,IvVector3>>& marginPoints, const std::string& fileName);
   
    const std::vector<std::pair<IvVector3,IvVector3>>& getMarginPoints() const { return rMarginPoints;};
    
private:
    std::vector<std::pair<IvVector3,IvVector3>> rMarginPoints;
    std::vector<std::string> split(const std::string& line, const char c);
};
