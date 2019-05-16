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
Terrain::Terrain(const char* name,uint32_t width,uint32_t height):SceneNode(name),width(width),height(height),rows(height),columns(width)
{
    elevation.resize(rows);
    for(int i=0;i<elevation.size();i++)
        elevation[i].resize(columns);
    
    build();
    
    RenderPacket renderPacket;
    renderPacket._prim_type=kTriangleListPrim;
    renderPacket._use_blend=true;
    renderPacket._use_depth=true;
    renderPacket._use_wireframe=false;
    
    std::shared_ptr<Mesh> grid=std::make_shared<Mesh>();
    
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    std::vector<IvTNPVertex> vertices;
    std::vector<unsigned int> indices;
    
    for(int i = 0 ; i < rows;i++)
    {
        for(int j = 0 ; j < columns; j++)
        {
            IvTNPVertex vertex;
            vertex.position={(float)i-rows/2,(float)(elevation[(int)i][(int)j]*2000),(float)j-columns/2};
            vertices.push_back(vertex);
        }
    }
    
    for(int i = 0 ; i < (rows - 1);i++)//y
    {
        for(int j = 0 ; j < (columns - 1); j++)//x
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
    
    while(i<=indices.size()-3)
    {
        p1=vertices[indices[i]].position;
        p2=vertices[indices[i+1]].position;
        p3=vertices[indices[i+2]].position;
    
        auto u=p2-p1;
        auto v=p2-p3;
    
        if(i%2==1)
        {
            u=p1-p2;
            v=p1-p3;
        }
        //cross product
        IvVector3 normal;
        normal.x=u.y*v.z-u.z*v.y;
        normal.y=u.z*v.x-u.x*v.z;
        normal.z=u.x*v.y-u.y*v.x;
    
        normalFaces.push_back(std::make_pair(normal, IvVector3{(float)indices[i],(float)indices[i+1],(float)indices[i+2]}));

        i++;
    }
    
    i=0;
    while(i<indices.size())
    {
        vertices[indices[i]].normal=calculateNormalAverage(normalFaces,indices[i]);
        i++;
    }

    grid->setVertexBuffer(vertices, format);
    grid->setIndexBuffer(indices);
    
    std::shared_ptr<MeshInstance> meshInstance=std::make_shared<MeshInstance>();
    meshInstance->setMesh(grid);
    meshInstance->setShader("../../Game/Environment/Shaders/BasicShader");
    
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
                    0.94 * noise1(32 * nx, 32 * ny));
            e /= (0.94+0.86+0.98+0.96+0.90+0.94);
            e = pow(e, 5.00);
            elevation[i][j]=e;
        }
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
    PerlinNoise pn(rand()%500);
    return pn.noise(nx,1,ny);
}

//-------------------------------------------------------------------------------
//  @Terrain::calculateNormalAverage()
//-------------------------------------------------------------------------------
IvVector3
Terrain::calculateNormalAverage(std::vector<std::pair<IvVector3,IvVector3>> normalFaces, unsigned int index)
{
    IvVector3 sum(0,0,0);
    auto count=0;
    
    for(auto face:normalFaces)
    {
        if(index==face.second.x || index==face.second.y || index==face.second.z)
        {
            sum.x+=face.first.x;
            sum.y+=face.first.y;
            sum.z+=face.first.z;
            count++;
        }
    }
    
    if(count!=0)
    {
        sum.x/=(float)count;
        sum.y/=(float)count;
        sum.z/=(float)count;
    }
    
   // sum.Normalize();
    return sum;
}
