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
Terrain::Terrain(uint32_t width,uint32_t height):width(width),height(height),rows(height),columns(width)
{
    elevation.resize(rows);
    for(int i=0;i<elevation.size();i++)
        elevation[i].resize(columns);
    
    build();
    
    RenderPacket renderPacket;
    renderPacket._prim_type=kTriangleStripPrim;
    renderPacket._use_blend=true;
    renderPacket._use_depth=true;
    renderPacket._use_wireframe=true;
    
    terrain=std::make_shared<HelperSceneNode>("terrain",renderPacket);
    
    std::shared_ptr<Mesh> grid=std::make_shared<Mesh>();
    
    float currentR=0;
    float currentC=0;
    
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    std::vector<IvTNPVertex> vertices;
    std::vector<unsigned int> indices;
    
    int indexx=0;
    float index=0;
    float direction=1;
    while(currentR<rows)
    {
        bool stop=false;
        while(!stop)
        {
            currentC=((float)width/columns) * index;
            
            if(currentC>=columns && direction==1)
            {
                direction=-1;
                stop=true;
            }
            else if(currentC <= -1 && direction==-1)
            {
                direction=1;
                stop=true;
            }
            else
            {
                IvTNPVertex vertex;
                vertex.position={currentR,(float)elevation[(int)currentR][(int)currentC]*2000,currentC};
                vertices.push_back(vertex);
            }
            index+=direction;
            
        }
        indexx++;
        currentR=((float)height/(float)rows)*indexx;
    }
    auto val=columns*2;
    for(int i=0;i<vertices.size()-width;i++)
    {
        if(val!=i+1)
        {
            if(i==4)
                std::cout<<std::endl;
            indices.push_back(i);
            indices.push_back(val-1);
        }
        val--;
        if(val==i+1)
            val=i+1+columns*2;
    }
    
    //calculate the normal for the first triangle
    std::vector<std::pair<IvVector3,IvVector3>> normalFaces; //keep the normal and the indices for the current face
    IvVector3 p1,p2,p3;
    int i=0;
    
    while(i<indices.size()-3)
    {
        p1=vertices[indices[i]].position;
        p2=vertices[indices[i+1]].position;
        p3=vertices[indices[i+2]].position;
    
        auto u=p2-p1;
        auto v=p3-p1;
    
        //cross product
        IvVector3 normal;
        normal.x=u.y*v.z-u.z*v.y;
        normal.y=u.z*v.x-u.x*v.z;
        normal.z=u.x*v.y-u.y*v.x;
    
        normal.Normalize();
        normalFaces.push_back(std::make_pair(normal, IvVector3{(float)indices[i],(float)indices[i+1],(float)indices[i+2]}));
        
        i++;
    }
    
    //calculate normals only for the interior vertices of the grid
    i=1;
    while(i<indices.size())
    {
        vertices[indices[i]].normal=calculateNormalAverage(normalFaces,indices[i]);
        i++;
    }
    
    for(int i=0;i<indices.size();i+=4)
    {
        std::cout<<indices[i]<<" "<<indices[i+1]<<" "<<indices[i+2]<<" "<<indices[i+3]<<std::endl<<std::endl;
        std::cout<<vertices[indices[i]].position<<" "<<vertices[indices[i+1]].position<<" "<<vertices[indices[i+2]].position<<" "<<vertices[indices[i+3]].position<<std::endl<<std::endl;
    }
    grid->setVertexBuffer(vertices, format);
    grid->setIndexBuffer(indices);
    
    std::shared_ptr<MeshInstance> meshInstance=std::make_shared<MeshInstance>();
    meshInstance->setMesh(grid);
    meshInstance->setShader("BasicShader");
    
    terrain->setRenderable(meshInstance);
    
    terrain->setLocalTransform({0,0,0}, {0,0,1}, {4,4,4});
    
    
    for(auto val:normalFaces)
        normals.push_back(val.first);
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
    PerlinNoise pn(256);
    return pn.noise(nx,1,ny);
}
//-------------------------------------------------------------------------------
//  @Terrain::noise2()
//-------------------------------------------------------------------------------
double
Terrain::noise2(double nx,double ny)
{
    PerlinNoise pn(100);
    return pn.noise(nx,ny,1);
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
    
    sum.x/=count;
    sum.y/=count;
    sum.z/=count;
    
    return sum;
}
