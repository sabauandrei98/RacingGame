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

    
    std::shared_ptr<SceneNode> frontQuad=HelperManager::BuildTexturedQuad("frontQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "hills2_ft.tga",IvVector3::zAxis);
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "hills2_bk.tga",IvVector3::zAxis);
    std::shared_ptr<SceneNode> upQuad=HelperManager::BuildTexturedQuad("upQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "hills2_up.tga",IvVector3::xAxis);
    std::shared_ptr<SceneNode> downQuad=HelperManager::BuildTexturedQuad("downQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "hill2s_up.tga",IvVector3::xAxis);
    std::shared_ptr<SceneNode> rightQuad=HelperManager::BuildTexturedQuad("rightQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "hills2_lf.tga",IvVector3::yAxis);
    std::shared_ptr<SceneNode> leftQuad=HelperManager::BuildTexturedQuad("leftQuad", HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/Environment/Shaders/TextureShader"), "hills2_rt.tga",IvVector3::yAxis);

    frontQuad->setLocalTransform(IvVector3{0,4.97,0}, IvVector3{0,4.72,6.3/4}, IvVector3{10,10,10});
    backQuad->setLocalTransform(IvVector3{0,-4.97,0}, IvVector3{0,4.72,6.3/4}, IvVector3{10,10,10});
    upQuad->setLocalTransform(IvVector3{0,0,4.97}, IvVector3{0,4.72,6.28}, IvVector3{10,10,10});
    downQuad->setLocalTransform(IvVector3{0,0,-4.97}, IvVector3{0,4.72,6.28/2}, IvVector3{10,10,10});
    rightQuad->setLocalTransform(IvVector3{4.97,0,0}, IvVector3{-7.855,0,6.29}, IvVector3{10,10,10});
    leftQuad->setLocalTransform(IvVector3(-4.97,0,0), IvVector3{7.855,0,6.26855/2.0}, IvVector3{10,10,10});


    sky->addChild(frontQuad);
    sky->addChild(backQuad);
    sky->addChild(upQuad);
    //sky->addChild(downQuad);
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
