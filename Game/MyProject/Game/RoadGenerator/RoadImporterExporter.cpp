#include "RoadImporterExporter.hpp"

std::vector<std::string> RoadImporterExporter::split(const std::string& line, const char c)
{
    std::vector<std::string> result;
    
    std::string aux = "";
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == c || i + 1 == line.size())
        {
            if(i + 1 == line.size())
                aux += line[i];
            
            result.push_back(aux);
            aux = "";
        }
        else
            aux += line[i];
    }
    
    return result;
}

void RoadImporterExporter::importFrom(const std::string& fileName){
    std::ifstream f(fileName);
    
    //get road size
    std::string m;
    getline(f, m);
    std::string::size_type sz;
    int midSize = std::stoi(m);

    //get the margin points
    for(int i = 0; i < midSize; i++)
    {
        std::string line;
        getline(f, line);

        std::vector<std::string> result = split(line, ' ');

        float fx1 = std::stof (result[0],&sz);
        float fy1 = std::stof (result[1],&sz);
        float fz1 = std::stof (result[2],&sz);
        float fx2 = std::stof (result[3],&sz);
        float fy2 = std::stof (result[4],&sz);
        float fz2 = std::stof (result[5],&sz);
        rMarginPoints.push_back(std::make_pair(IvVector3{fx1,fy1,fz1}, IvVector3{fx2,fy2,fz2}));
    }
    
}


void RoadImporterExporter::exportTo(const std::string& fileName){
    
    std::ofstream g(fileName);
    
    g << rMarginPoints.size() << '\n';
    
    //print the margin points
    for(int i = 0; i < rMarginPoints.size(); i++)
    {
        g << rMarginPoints[i].first.x << " " << rMarginPoints[i].first.y << " " << rMarginPoints[i].first.z << " ";
        g << rMarginPoints[i].second.x << " " << rMarginPoints[i].second.y << " " << rMarginPoints[i].second.z;
        
        if (i + 1 != rMarginPoints.size())
            g << '\n';
    }
    
}
