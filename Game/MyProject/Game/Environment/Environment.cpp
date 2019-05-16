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
Environment::Environment(const char* name):SceneNode(name)
{
    std::shared_ptr<SceneNode> sky=std::make_shared<SkyBox>("skyBox");
    std::shared_ptr<SceneNode> terrain=std::make_shared<Terrain>("terrain",46,20);
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootEnvironment");

    sky->setLocalTransform({0,0,30}, {0,0,0}, {30,30,30});
    terrain->setLocalTransform({0,0,0},{0,1.57,1.57},{2,2,2});
    
    root->addChild(sky);
    root->addChild(terrain);
    this->addChild(root);
}

