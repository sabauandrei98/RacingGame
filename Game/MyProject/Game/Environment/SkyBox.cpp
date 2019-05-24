//-------------------------------------------------------------------------------
//-- SkyBox.cpp -----------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "SkyBox.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//  @SkyBox::SkyBox()
//-------------------------------------------------------------------------------
SkyBox::SkyBox(const char* name):SceneNode(name)
{
    MeshManager meshManager;
    
    std::vector<std::string> uniforms;
    uniforms.push_back("TEXTURE");
    
    std::shared_ptr<SceneNode> frontQuad=HelperManager::BuildTexturedQuad("frontQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Shaders/first_pass_shader"), "../../Game/Environment/Resources/front.tga",IvVector3::zAxis);
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Shaders/first_pass_shader"), "../../Game/Environment/Resources/back.tga",IvVector3::zAxis);
    std::shared_ptr<SceneNode> upQuad=HelperManager::BuildTexturedQuad("upQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Shaders/first_pass_shader"), "../../Game/Environment/Resources/up.tga",IvVector3::xAxis);
    std::shared_ptr<SceneNode> downQuad=HelperManager::BuildTexturedQuad("downQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Shaders/first_pass_shader"), "../../Game/Environment/Resources/down.tga",IvVector3::xAxis);
    std::shared_ptr<SceneNode> rightQuad=HelperManager::BuildTexturedQuad("rightQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Shaders/first_pass_shader"), "../../Game/Environment/Resources/left.tga",IvVector3::yAxis);
    std::shared_ptr<SceneNode> leftQuad=HelperManager::BuildTexturedQuad("leftQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Shaders/first_pass_shader"), "../../Game/Environment/Resources/right.tga",IvVector3::yAxis);

    frontQuad->setLocalTransform({0,4.97,0},    {0,4.72,6.3/4},            {10,10,10});
    backQuad->setLocalTransform({0,-4.97,0},    {4.71*2,4.71*3,6.29/4},    {10,10,10});
    upQuad->setLocalTransform(  {0,0,4.97},     {0,4.72,6.28},             {10,10,10});
    downQuad->setLocalTransform({0,0,-4.97},    {0,4.72,6.28/2},           {10,10,10});
    rightQuad->setLocalTransform({4.97,0,0},    {-7.855,0,6.29},           {10,10,10});
    leftQuad->setLocalTransform({-4.97,0,0},    {7.855,0,6.268/2},         {10,10,10});

    this->addChild(frontQuad);
    this->addChild(backQuad);
    this->addChild(upQuad);
    this->addChild(downQuad);
    this->addChild(rightQuad);
    this->addChild(leftQuad);

}

