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
Terrain::Terrain(const char* name, RenderPacket render,uint32_t width,uint32_t height,const std::vector<std::pair<IvVector3,IvVector3>>& marginPoints):HelperSceneNode(name,render),width(width),height(height),rows(height*7),columns(width*7)
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
           // height=remainder(height,4);
    
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
    IvVector3 p1,p2,p3;
    
    std::vector<std::pair<IvVector3,IvVector3>> lines;
    for(int i=0;i<marginPoints.size()-1;i++)
    {
        std::pair<IvVector3,IvVector3> aux = marginPoints[i];
        aux.first *= 10.0f;
        aux.second *= 10.0f;
        lines.push_back(std::make_pair(aux.first, aux.second));
    }
    
    int i=0;
    
    auto keep=vertices;
    
    for(int i = 0; i < vertices.size(); i+=3)
    {
        //vertices[i].position.y = 0;
        if(isPointRayIntersectLines(vertices[i].position, lines)==1)
        {
            vertices[i].position.y=0;
        }
        
    }
    
    while(i<indices.size()-3)
    {
        
//        if(isPointRayIntersectLines(vertices[indices[i]].position, lines)==1)
//        {
//            std::cout<<vertices[indices[i]].position<<std::endl;
//            if(i%3==0)
//            {
//                vertices[indices[i]].position.y   = 0.;
//                vertices[indices[i+1]].position.y = 0.;
//                vertices[indices[i+2]].position.y = 0.;
//            }
//            else if(i%3==1)
//            {
//                vertices[indices[i-1]].position.y = 0.;
//                vertices[indices[i]].position.y   = 0.;
//                vertices[indices[i+1]].position.y = 0.;
//            }
//            else if(i%3==2)
//            {
//                vertices[indices[i-2]].position.y = 0.;
//                vertices[indices[i-1]].position.y = 0.;
//                vertices[indices[i]].position.y  = 0.;
//            }
//        }
//
        
       
            p1=vertices[indices[i]].position;
            p2=vertices[indices[i+1]].position;
            p3=vertices[indices[i+2]].position;
    
            auto u=p2-p1;
            auto v=p2-p3;
            
            IvVector3 normal = v.Cross(u);
    
            vertices[indices[i]].normal += normal;
            vertices[indices[i + 1]].normal += normal;
            vertices[indices[i + 2]].normal += normal;
             
        
        i+=3;
    }
    
//    for (int i=0;i<vertices.size();i++)
//       // if(vertices[i].position.y!=keep[i].position.y)
//            std::cout<<vertices[i].position<<" changed from: "<<keep[i].position<<std::endl;
    
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
   // PerlinNoise pn(rand()%256);
    PerlinNoise pn(66);
    return pn.noise(nx,1,ny);
}
//-------------------------------------------------------------------------------
//  @Terrain::noise1()
//-------------------------------------------------------------------------------
int
Terrain::isPointRayIntersectLines(const IvVector3& point,const std::vector<std::pair<IvVector3,IvVector3>>& lines)
{
    IvVector3 startP=point;
    IvVector3 endP=point-IvVector3(-10000,0,0);
    
    startP.y=0;
    endP.y=0;
    
    float min= 30;
  
    for(auto& line:lines)
    {
        IvVector3 start=line.first;
        IvVector3 end=line.second;

        auto p=point;
        p.y=0;
        start.y=0;
        end.y=0;
        float a = Distance(p, start);
        float b = Distance(p, end);
        
        if (a < min || b < min)
        {
            //std::cout<<"ok"<<a<<" "<<b<< " "<<point<<" "<<start << " " <<end<<std::endl;

            return 1;
        }
       // else
         //std::cout<<a<<" "<<b<< " "<<start<<" "<<end<<std::endl;
        //if(index==20)
            // break;
        //index++;
        
    }
    return 0;
}
bool Terrain::pointIntersectsLine(IvVector3 point, IvVector3 start, IvVector3 end)
{
    auto sPoint=point;
    auto ePoint=point-IvVector3(10000,0,0);
    
    auto d1=direction(start,end,sPoint);
    auto d2=direction(start,end,ePoint);
    auto d3=direction(sPoint,ePoint,start);
    auto d4=direction(sPoint,ePoint,end);
    
    if( ((d1>0 && d2<0) || (d1<0 && d2>0))  &&
        ((d3>0 && d4<0) || (d3<0 && d4>0)))
        return true;
    else if( d1==0 && isOnSegment(sPoint,start,end))
        return true;
    else if( d2==0 && isOnSegment(ePoint,start,end))
        return true;
    else if( d3==0 && isOnSegment(start,sPoint,ePoint))
        return true;
    else if( d4==0 && isOnSegment(end,sPoint,ePoint))
        return true;
    else return false;
}

bool Terrain::isOnSegment(IvVector3 point,IvVector3 start, IvVector3 end)
{
    if(std::min(start.x,end.x) <= point.x &&
       std::max(start.x,end.x) >= point.x &&
       std::min(start.z,end.z) <= point.z &&
       std::max(start.z,end.z) >=point.z)
        return true;
    return false;
}

int Terrain::direction(IvVector3 p1, IvVector3 p2, IvVector3 p3)
{
    auto a=p3-p1;
    auto b=p2-p1;
    return (a.x* b.z - a.z * b.x);
}
