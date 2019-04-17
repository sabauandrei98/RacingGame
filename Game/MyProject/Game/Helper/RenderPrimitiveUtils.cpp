//-------------------------------------------------------------------------------
//-- RenderPrimitiveUtils.cpp ------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "RenderPrimitiveUtils.h"

namespace RenderPrimitiveUtils
{
    //-------------------------------------------------------------------------------
    // @ RenderPrimitiveUtils::DrawBox()
    //-------------------------------------------------------------------------------
    void DrawBox(const std::shared_ptr<MeshInstance>& meshInstance,
                IvVector3 position,
                IvVector3 rotation,
                IvVector3 scale,
                bool wireframe)
    {
  
        std::shared_ptr<SceneGraph> box=BuildBox(meshInstance,wireframe);
        box->getRoot()->setLocalTransform(position, rotation, scale);
        box->updateScene(0.01);
        box->drawScene();
    }

    //-------------------------------------------------------------------------------
    // @ RenderPrimitiveUtils::DrawQuad()
    //-------------------------------------------------------------------------------
    void DrawQuad(const std::shared_ptr<MeshInstance>& meshInstance,
                IvVector3 axis,
                IvVector3 position,
                IvVector3 rotation,
                IvVector3 scale,
                bool wireframe)
    {
        std::shared_ptr<SceneGraph> quad =BuildQuad(meshInstance,wireframe);
    
        if (axis == IvVector3::xAxis)
            rotation += IvVector3(0, 1.5, 0);
        else if (axis == IvVector3::yAxis)
            rotation += IvVector3(1.5, 0, 0);
        else if (axis == IvVector3::zAxis)
            rotation += IvVector3(0, 0, 1.5);
    
        quad->getRoot()->setLocalTransform(position, rotation, scale);
        quad->updateScene(0.01);
        quad->drawScene();
    }

//-------------------------------------------------------------------------------
// @ RenderPrimitiveUtils::DrawTexturedQuad()
//-------------------------------------------------------------------------------
void
DrawTexturedQuad(const std::shared_ptr<MeshInstance>& meshInstance,
                const char* textureName,
                IvVector3 axis,
                IvVector3 position,
                IvVector3 rotation,
                IvVector3 scale,
                bool wireframe )
{
    std::shared_ptr<SceneGraph> quad=BuildQuad(meshInstance,wireframe);
    
    IvImage* image = IvImage::CreateFromFile(textureName);
    IvTexture* quadTexture;

    if (image)
    {
        quadTexture = IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt, image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
        delete image;
        image = 0;
    }
    
    IvUniform* unif = meshInstance->getShaderUniforms()[0];
    if (unif)
        unif->SetValue(quadTexture);


    quad->getRoot()->setLocalTransform(position, rotation, scale);
    quad->updateScene(0.01);
    quad->drawScene();
}
//-------------------------------------------------------------------------------
// @ RenderPrimitiveUtils::DrawSphere()
//-------------------------------------------------------------------------------
void
DrawSphere(const std::shared_ptr<MeshInstance>& meshInstance,
        IvVector3 position,
        IvVector3 rotation,
        IvVector3 scale,
        bool wireframe)
{
   
    std::shared_ptr<SceneGraph> sphere=BuildSphere(meshInstance,wireframe);

    sphere->getRoot()->setLocalTransform(position, rotation, scale);
    sphere->updateScene(0.01);
    sphere->drawScene();
}
//-------------------------------------------------------------------------------
// @ RenderPrimitiveUtils::BuildBox()
//-------------------------------------------------------------------------------
std::shared_ptr<SceneGraph>
BuildBox(const std::shared_ptr<MeshInstance>& squareInstance,bool wireframeValue)
{
    //  setting sceneNode
    RenderPacket myRenderPacket;
    myRenderPacket._use_blend = true;
    myRenderPacket._use_depth = true;
    myRenderPacket._use_wireframe = wireframeValue;
    myRenderPacket._prim_type = kTriangleStripPrim;
    
    std::shared_ptr<MyHelperSceneNode> squareNode = std::make_shared<MyHelperSceneNode>("box", myRenderPacket);
    squareNode->setRenderable(squareInstance);
    
    // adding children to scene graph
    std::shared_ptr<MyHelperSceneNode> root = std::make_shared<MyHelperSceneNode>("boxRoot", myRenderPacket);
    root->addChild(squareNode);
    
    // build box
    std::shared_ptr<SceneGraph> box = std::make_shared<SceneGraph>();
    box->setRoot(root);
    box->setCamera(std::make_shared<CameraSceneNode>("camera"));
    return box;
}
//-------------------------------------------------------------------------------
// @ RenderPrimitiveUtils::BuildQuad()
//-------------------------------------------------------------------------------
std::shared_ptr<SceneGraph>
BuildQuad(const std::shared_ptr<MeshInstance>& meshInstance,bool wireframeValue)
{
    //setting sceneNode
    RenderPacket myRenderPacket;
    myRenderPacket._use_blend = true;
    myRenderPacket._use_depth = true;
    myRenderPacket._use_wireframe = wireframeValue;
    myRenderPacket._prim_type = kTriangleStripPrim;
    
    std::shared_ptr<MyHelperSceneNode> quadNode = std::make_shared<MyHelperSceneNode>("quad", myRenderPacket);
    quadNode->setRenderable(meshInstance);
    
    //adding children to scene graph
    std::shared_ptr<MyHelperSceneNode> root = std::make_shared<MyHelperSceneNode>("quadRoot", myRenderPacket);
    root->addChild(quadNode);
    
    //build quad
     std::shared_ptr<SceneGraph> quad = std::make_shared<SceneGraph>();
    quad->setRoot(root);
    quad->setCamera(std::make_shared<CameraSceneNode>("camera"));
    return quad;
}

//-------------------------------------------------------------------------------
// @ RenderPrimitiveUtils::BuildSphere()
//-------------------------------------------------------------------------------
std::shared_ptr<SceneGraph>
BuildSphere(const std::shared_ptr<MeshInstance>& meshInstance,bool wireframeValue)
{
    //setting sceneNode
    RenderPacket myRenderPacket;
    myRenderPacket._use_blend = true;
    myRenderPacket._use_depth = true;
    myRenderPacket._use_wireframe = wireframeValue;
    myRenderPacket._prim_type = kTriangleListPrim;
    
    std::shared_ptr<MyHelperSceneNode> sphereNode = std::make_shared<MyHelperSceneNode>("sphere", myRenderPacket);
    sphereNode->setRenderable(meshInstance);
    
    //adding children to scene graph
    std::shared_ptr<MyHelperSceneNode> root = std::make_shared<MyHelperSceneNode>("sphereRoot", myRenderPacket);
    root->addChild(sphereNode);
    
    //build sphere
    std::shared_ptr<SceneGraph> sphere = std::make_shared<SceneGraph>();
    sphere->setRoot(root);
    sphere->setCamera(std::make_shared<CameraSceneNode>("camera"));
    return sphere;
}
};
