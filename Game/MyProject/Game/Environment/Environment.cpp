//-------------------------------------------------------------------------------
//-- Environment.cpp ------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Environment.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//  @Environment::Environment()
//-------------------------------------------------------------------------------
Environment::Environment(const char* name,const  std::vector<std::pair<IvVector3,IvVector3>>& marginPoints):SceneNode(name)
{
    std::shared_ptr<SceneNode> sky=std::make_shared<SkyBox>("skyBox");
    
    RenderPacket renderPacket;
    renderPacket._prim_type=kTriangleListPrim;
    renderPacket._use_blend=true;
    renderPacket._use_depth=true;
    renderPacket._use_wireframe=false;
    
    terrain=std::make_shared<Terrain>("terrain",renderPacket,50,50,marginPoints);
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootEnvironment");

    sky->setLocalTransform({0,0,30}, {0,0,0}, {30,30,30});
    terrain->setLocalTransform({0,-6,0},{1.57*3,1.57,1.57},{20,20,20});
    
    root->addChild(sky);
    root->addChild(terrain);
    this->addChild(root);
}

//-------------------------------------------------------------------------------
//  @Environment::updateTerrain()
//-------------------------------------------------------------------------------
void
Environment::updateTerrain(const std::vector<std::pair<IvVector3,IvVector3>> & marginPoints)
{
    std::vector<IvTNPVertex> vertices=((Terrain*)terrain.get())->getVertices();
    
    for(auto point:marginPoints)
    {
        verifyPoint(point,vertices);
    }
    
    ((Terrain*)terrain.get())->setVertices(vertices);
    
}

//-------------------------------------------------------------------------------
//  @Environment::verifyPoint()
//-------------------------------------------------------------------------------
void
Environment::verifyPoint(const std::pair<IvVector3, IvVector3> &point, std::vector<IvTNPVertex> &vertices)
{
    auto keep=vertices;
    for(int i=0;i<vertices.size();i++)
    {
        auto aux=point;
        aux.first.x+=2;
        aux.first.y+=2;
        aux.first.z+=2;
        
        aux.second.x+=2;
        aux.second.y+=2;
        aux.second.z+=2;
        
       
        auto vertex=vertices[i];
        if(distance(aux.first, aux.second) > distance(aux.first, vertex.position) ||
           distance(aux.first, aux.second) > distance(aux.second, vertex.position))
            vertices[i].position.y=-0.1;
    }

    for(int i=0;i<vertices.size();i++)
        if(keep[i].position.y !=vertices[i].position.y)
        std::cout<<keep[i].position.y<<" "<<vertices[i].position.y<<std::endl;
}

//-------------------------------------------------------------------------------
//  @Environment::distance()
//-------------------------------------------------------------------------------
float
Environment::distance(const IvVector3& point1,const IvVector3& point2)
{
    return sqrt(
            (point2.x-point1.x)*(point2.x-point1.x) +
            (point2.y-point1.y)*(point2.y-point1.y) +
            (point2.z-point1.z)*(point2.z-point1.z));
}
