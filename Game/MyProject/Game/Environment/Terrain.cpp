//-------------------------------------------------------------------------------
//-- Terrain.cpp ----------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Terrain.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//  @Terrain::Terrain()
//-------------------------------------------------------------------------------
Terrain::Terrain(const char* name, RenderPacket render,uint32_t width,uint32_t height,const std::vector<std::pair<IvVector3,IvVector3>>& marginPoints):HelperSceneNode(name,render),width(width),height(height),rows(height),columns(width)
{
    srand(time(0));
    
    elevation.resize(rows);
    for(int i=0;i<elevation.size();i++)
        elevation[i].resize(columns);
    
    build();

    grid=std::make_shared<Mesh>();
    
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    std::vector<IvTNPVertex> vertices;
    std::vector<unsigned int> indices;
    
    BoundingBox box;
    for(const auto & p : marginPoints)
    {
        box.expand(10.0f * p.first + IvVector3(0.0,1.0,0.0));
        box.expand(10.0f * p.second - IvVector3(0.0,1.0,0.0));
    }
    
    auto _box_min = box.getMin();
    auto _box_max = box.getMax();
    box.expand(  0.1f * (_box_max - _box_min) + _box_max);
    box.expand(  _box_min - 0.1f * (_box_max - _box_min));
    
    std::vector<std::pair<IvVector3,IvVector3> > line_segments;
    for(std::size_t i = 0 ; i < marginPoints.size() - 1; i++)
    {
        auto p0 = std::make_pair(marginPoints[i].first, marginPoints[i + 1].first);
        if (p0.first.x > p0.second.x)
            std::swap(p0.first,p0.second);
        line_segments.push_back(p0);
        auto p1 = std::make_pair(marginPoints[i].second, marginPoints[i + 1].second);
        if (p1.first.x > p1.second.x)
            std::swap(p1.first,p1.second);
        line_segments.push_back(p1);
    }
    
    for(int i = 0 ; i < rows;i++)
    {
        for(int j = 0 ; j < columns; j++)
        {
            IvTNPVertex vertex;
            float height=std::abs(elevation[(int)i][(int)j]) * 50000.000f;
            height=remainder(height,24);
            float x = (float)i / (float)(rows - 1);
            float y = (float)j / (float)(columns - 1);
            x = x * 3.0 - 1.0;
            y = y * 3.0 - 1.0;
            vertex.position = box.getMin() + (box.getMax() - box.getMin()) * IvVector3{x,0.0f,y};
            vertex.position.y = 0;

            if(box.contains(vertex.position))
                vertex.position.y = 0.0f;
            else
                vertex.position.y = height;
            
            vertex.position.y -= 0.5;
            vertex.normal = {0.0f,0.0f,0.0f};
            vertices.push_back(vertex);
        }
    }
    
    for(int i = 0 ; i < (rows - 1);i++)
    {
        for(int j = 0 ; j < (columns - 1); j++)
        {
            indices.push_back(i * columns + j);
            indices.push_back(i * columns + j + 1);
            indices.push_back((i + 1) * columns + j);
            
            indices.push_back(i * columns + j + 1);
            indices.push_back((i + 1) * columns + j + 1);
            indices.push_back((i + 1) * columns + j);

        }
    }
   
    std::size_t i =0;
    while(i<indices.size()-3)
    {
            auto& p1=vertices[indices[i]].position;
            auto& p2=vertices[indices[i+1]].position;
            auto& p3=vertices[indices[i+2]].position;
        
            auto u=p2-p1;
            auto v=p2-p3;
            
            IvVector3 normal = v.Cross(u);
    
            vertices[indices[i]].normal += normal;
            vertices[indices[i + 1]].normal += normal;
            vertices[indices[i + 2]].normal += normal;
             
        
        i+=3;
    }
    
    for(auto & v : vertices)
    {
        v.normal.Normalize();
    }

    grid->setVertexBuffer(vertices, format);
    grid->setIndexBuffer(indices);
    
    meshInstance=std::make_shared<MeshInstance>();
    meshInstance->setMesh(grid);
    meshInstance->setShader("../../Game/Environment/Shaders/TerrainShader");
    
    this->setRenderable(meshInstance);
    
    this->vertices=vertices;
    this->indices=indices;
    
}
//-------------------------------------------------------------------------------
//  @Terrain::build()
//-------------------------------------------------------------------------------
void Terrain::build()
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
        {
            double nx=(float)j/(float)width-0.5;
            double ny=(float)i/(float)height-0.5;
            
            auto e=(0.94 * noise1( 1 * nx,  1 * ny) +
                    0.86 * noise1( 2 * nx,  2 * ny) +
                    0.98 * noise1( 4 * nx,  4 * ny) +
                    0.96 * noise1( 8 * nx,  8 * ny) +
                    0.90 * noise1(16 * nx, 16 * ny) +
                    0.98 * noise1(32 * nx, 32 * ny));
            e /= (0.94+0.86+0.98+0.96+0.90+0.98);
            e = pow(e, 5.00);
            elevation[i][j]=e;
        }
}
//-------------------------------------------------------------------------------
//  @Terrain::setVertices()
//-------------------------------------------------------------------------------
void
Terrain::setVertices(const std::vector<IvTNPVertex> &vertices)
{
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    
    this->vertices=vertices;
    grid->setVertexBuffer(vertices, format);
    meshInstance->setMesh(grid);
    this->setRenderable(meshInstance);
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//  @Terrain::noise1()
//-------------------------------------------------------------------------------
double
Terrain::noise1(double nx,double ny)
{
    PerlinNoise pn(rand()%256);
    return pn.noise(nx,1,ny);
}
//-------------------------------------------------------------------------------
//  @Terrain::noise1()
//-------------------------------------------------------------------------------
int
Terrain::isPointRayIntersectLines(const IvVector3& point,const std::vector<std::pair<IvVector3,IvVector3>>& lines)
{
    std::size_t count = 0;
    for(const auto & l : lines)
    {
        if(pointIntersectsLine(point, l.first,l.second))
            count ++;
    }
    return count;
}
bool Terrain::pointIntersectsLine(IvVector3 point, IvVector3 start, IvVector3 end)
{
    
    if(start.x < point.x && point.x < end.x)
    {
        return ( (point - start).Cross(end - start).y < 0.0f);
    }
    
}
