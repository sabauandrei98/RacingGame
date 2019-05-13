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
Terrain::Terrain(uint32_t width,uint32_t height,uint32_t rows,uint32_t columns):width(width),height(height),rows(rows),columns(columns)
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
            currentC=(width/columns) * index;
            
            if(currentC==columns && direction==1)
            {
                direction=-1;
                stop=true;
            }
            else if(currentC == -1 && direction==-1)
            {
                direction=1;
                stop=true;
            }
            else
            {
                IvTNPVertex vertex;
                vertex.position={currentR,currentC,elevation[currentR][currentC]};
                vertices.push_back(vertex);
            }
            index+=direction;
            
            
        }
        indexx++;
        currentR=(height/rows)*indexx;
    }
    auto val=columns*2;
    for(int i=0;i<vertices.size()-width*2;i++)
    {
        if(val-1!=i+1)
        {
            indices.push_back(i);
            indices.push_back(val-1);
            indices.push_back(i+1);
            indices.push_back(val-2);
        }
        val--;
        if(val==i+1)
            val=i+1+columns*2;
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
}
//-------------------------------------------------------------------------------
//  @Terrain::build()
//-------------------------------------------------------------------------------
void Terrain::build()
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
        {
            double nx=j/(width)-0.5;
            double ny=i/(height)-0.5;
            
            auto e=(0.94 * noise1( 1 * nx,  1 * ny) +
                    0.86 * noise1( 2 * nx,  2 * ny) +
                    0.38 * noise1( 4 * nx,  4 * ny) +
                    0.06 * noise1( 8 * nx,  8 * ny) +
                    0.00 * noise1(16 * nx, 16 * ny) +
                    0.04 * noise1(32 * nx, 32 * ny));
            e /= (0.94+0.86+0.38+0.06+0.00+0.04);
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
    return pn.noise(nx,ny,1);
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
