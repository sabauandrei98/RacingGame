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
    
    for(int i = 0 ; i < rows;i++)
    {
        for(int j = 0 ; j < columns; j++)
        {
            IvTNPVertex vertex;
            float height=elevation[(int)i][(int)j]*2000.0f;
            height=remainder(height,2);
    
            vertex.position={(float)i-rows/2,height,(float)j-columns/2};
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
    
    //keep the normals and the indices for the current face
    std::vector<std::pair<IvVector3,IvVector3>> normalFaces;
    IvVector3 p1,p2,p3;
    int i=0;
    
    std::vector<std::pair<IvVector3,IvVector3>> lines;
    for(int i=0;i<marginPoints.size();i++)
    {
        lines.push_back(std::make_pair(marginPoints[i].first, marginPoints[i+1].first));
        lines.push_back(std::make_pair(marginPoints[i].second, marginPoints[i+1].second));
    }
    
    while(i<indices.size()-3)
    {
//        if(isPointOnRoad(vertices[i].position, marginPoints) || isPointOnRoad(vertices[i+1].position, marginPoints) || isPointOnRoad(vertices[i+2].position, marginPoints))
//        {
//            vertices[i].position.y   = -0.1;
//            vertices[i+1].position.y = -0.1;
//            vertices[i+2].position.y = -0.1;
//        }
        
        if(isPointRayIntersectLines(vertices[i].position, lines))
        {
            vertices[i].position.y   = -0.1;
            vertices[i+1].position.y = -0.1;
            vertices[i+2].position.y = -0.1;
        }
        
        p1=vertices[indices[i]].position;
        p2=vertices[indices[i+1]].position;
        p3=vertices[indices[i+2]].position;
    
        auto u=p2-p1;
        auto v=p2-p3;
        
        //cross product
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
    for(auto val:normalFaces)
        normals.push_back(val.first);
    
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
bool
Terrain::isPointRayIntersectLines(const IvVector3& point,const std::vector<std::pair<IvVector3,IvVector3>>& lines)
{
    for(auto& line:lines)
    {
        IvVector3 start=line.first;
        IvVector3 end=line.second;
        
        float ax = end.x - start.x;
        float ay = end.y - start.y;
        float az = end.z - start.z;
        
        auto startP=point;
        auto endP=point+IvVector3{-100000.0,0.0,0.0};
        
        float bx = startP.x-endP.x;
        float by = 0;
        float bz = 0;
        
        float dx = startP.x - start.x;
        float dy = startP.y - start.y;
        float dz = startP.z - start.z;
        
        float det = ax * bz - az * bx;
        
        if (det == 0) return false;
        
        float r = (dx * bz - dz * bx) / det;
        float s = (ax * dz - az * dx) / det;
        
        if( !(r < 0 || r > 1 || s < 0 || s > 1))
            return true;
    }
    return false;
}

