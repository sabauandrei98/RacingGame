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
    
    std::shared_ptr<HelperSceneNode>  terrain=std::make_shared<Terrain>("terrain",renderPacket,50,50,marginPoints);
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootEnvironment");

    sky->setLocalTransform({0,0,30}, {0,0,0}, {30,30,30});
    terrain->setLocalTransform({0,-6,0},{1.57*3,1.57,1.57},{20,20,20});
    
    root->addChild(sky);
    root->addChild(terrain);
    this->addChild(root);
}
