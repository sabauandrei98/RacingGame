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
SkyBox::SkyBox()
{
    MeshManager meshManager;
    
    sky=std::make_shared<SceneNode>("skyRoot");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    
    std::shared_ptr<SceneNode> frontQuad=HelperManager::BuildTexturedQuad("frontQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "../../Game/Environment/Resources/hills2_ft.tga",IvVector3::zAxis);
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "../../Game/Environment/Resources/hills2_bk.tga",IvVector3::zAxis);
    std::shared_ptr<SceneNode> upQuad=HelperManager::BuildTexturedQuad("upQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "../../Game/Environment/Resources/hills2_up.tga",IvVector3::xAxis);
    std::shared_ptr<SceneNode> downQuad=HelperManager::BuildTexturedQuad("downQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "../../Game/Environment/Resources/hills2_dn.tga",IvVector3::xAxis);
    std::shared_ptr<SceneNode> rightQuad=HelperManager::BuildTexturedQuad("rightQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "../../Game/Environment/Resources/hills2_lf.tga",IvVector3::yAxis);
    std::shared_ptr<SceneNode> leftQuad=HelperManager::BuildTexturedQuad("leftQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "../../Game/Environment/Resources/hills2_rt.tga",IvVector3::yAxis);


    frontQuad->setLocalTransform({0,4.97,0},    {0,4.72,6.3/4},            {10,10,10});
    backQuad->setLocalTransform({0,-4.97,0},    {4.71*2,4.71*3,6.29/4},    {10,10,10});
    upQuad->setLocalTransform(  {0,0,4.97},     {0,4.72,6.28},             {10,10,10});
    downQuad->setLocalTransform({0,0,-4.97},    {0,4.72,6.28/2},           {10,10,10});
    rightQuad->setLocalTransform({4.97,0,0},    {-7.855,0,6.28},           {10,10,10});
    leftQuad->setLocalTransform({-4.97,0,0},    {7.855,0,6.268/2},         {10,10,10});

    sky->addChild(frontQuad);
    sky->addChild(backQuad);
    sky->addChild(upQuad);
    sky->addChild(downQuad);
    sky->addChild(rightQuad);
    sky->addChild(leftQuad);
    
   

}

//-------------------------------------------------------------------------------
//  @SkyBox::getSky()
//-------------------------------------------------------------------------------
std::shared_ptr<SceneNode>
SkyBox::getSky()
{
    return sky;
}
