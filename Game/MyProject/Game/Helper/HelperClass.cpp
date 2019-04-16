//-------------------------------------------------------------------------------
//-- HelperClass.cpp ------------------------------------------------------------
//-------------------------------------------------------------------------------

#include"HelperClass.h"

//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ HelperClass::DrawBox()
//-------------------------------------------------------------------------------
void
HelperClass::DrawBox(const std::shared_ptr<MeshInstance>& meshInstance,
                     IvVector3 position,
                     IvVector3 rotation,
                     IvVector3 scale)
{
    if(!builtBox)
    {
        BuildBox(meshInstance);
        builtBox=true;
    }
    box->updateScene(0.01);
    box->getRoot()->setLocalTransform(position, rotation, scale);
    box->drawScene();
}

//-------------------------------------------------------------------------------
// @ HelperClass::DrawQuad()
//-------------------------------------------------------------------------------
void
HelperClass::DrawQuad(const std::shared_ptr<MeshInstance>& meshInstance,
                      IvVector3 axis,
                      IvVector3 position,
                      IvVector3 rotation,
                      IvVector3 scale)
{
    if(!builtQuad)
    {
        BuildQuad(meshInstance);
        builtQuad=true;
    }
    
    if(axis==IvVector3::xAxis)
    {
         rotation+=IvVector3(0,0,1.5);
    }
    else if(axis==IvVector3::yAxis)
    {
        rotation+=IvVector3(1.5,0,0);
    }
    else if(axis==IvVector3::zAxis)
    {
        rotation+=IvVector3(0,1.5,0);
    }
    quad->updateScene(0.01);
    quad->getRoot()->setLocalTransform(position, rotation, scale);
    quad->drawScene();
    
}

//-------------------------------------------------------------------------------
// @ HelperClass::DrawTexturedQuad()
//-------------------------------------------------------------------------------
void
HelperClass::DrawTexturedQuad(const std::shared_ptr<MeshInstance> &meshInstance,
                              const char *textureName,
                              IvVector3 axis,
                              IvVector3 position,
                              IvVector3 rotation,
                              IvVector3 scale)
{
    if(!builtQuad)
    {
        BuildQuad(meshInstance);
        builtQuad=true;
        
        IvImage *image=IvImage::CreateFromFile(textureName);
        if(image)
        {
            quadTexture=IvRenderer::mRenderer->GetResourceManager()
            ->CreateTexture((image->GetBytesPerPixel()==4) ? kRGBA32TexFmt : kRGB24TexFmt,image
                            ->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
            delete image;
            image = 0;
        }
    }
    IvShaderProgram* shader=meshInstance->getShader();
    IvUniform* unif=shader->GetUniform("myTexture");
    if(unif)
        unif->SetValue(quadTexture);
    
    quad->updateScene(0.01);
    quad->getRoot()->setLocalTransform(position, rotation, scale);
    quad->drawScene();
   
}
//-------------------------------------------------------------------------------
// @ HelperClass::DrawCrossQuad()
//-------------------------------------------------------------------------------
void
HelperClass::DrawCrossQuad(const std::shared_ptr<MeshInstance> & meshInstance,
                           IvVector3 axis,
                           IvVector3 position,
                           IvVector3 rotation,
                           IvVector3 scale)
{
    
    DrawTexturedQuad(meshInstance, "cross.tga",axis,position,rotation,scale);
    
}
//-------------------------------------------------------------------------------
// @ HelperClass::DrawSphere()
//-------------------------------------------------------------------------------
void
HelperClass::DrawSphere(const std::shared_ptr<MeshInstance> & meshInstance,
                           IvVector3 position,
                           IvVector3 rotation,
                           IvVector3 scale)
{
    if(!builtSphere)
    {
        BuildSphere(meshInstance);
        builtSphere=true;
    }
    sphere->updateScene(0.01);
    sphere->getRoot()->setLocalTransform(position, rotation, scale);
    sphere->drawScene();
}
//-------------------------------------------------------------------------------
// @ HelperClass::SetWireframeState()
//-------------------------------------------------------------------------------
void
HelperClass::SetWireframeState(bool wireframeValue)
{
    this->wireframeValue=wireframeValue;
}
//------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ HelperClass::BuildBox()
//-------------------------------------------------------------------------------
void
HelperClass::BuildBox(const std::shared_ptr<MeshInstance>& squareInstance)
{
    //  setting sceneNode
    RenderPacket myRenderPacket;
    myRenderPacket._use_blend=true;
    myRenderPacket._use_depth=true;
    myRenderPacket._use_wireframe=wireframeValue;
    myRenderPacket._prim_type=kTriangleStripPrim;

    std::shared_ptr<MyHelperSceneNode> squareNode=std::make_shared<MyHelperSceneNode>("box",myRenderPacket);
    squareNode->setRenderable(squareInstance);


    // adding children to scene graph
    std::shared_ptr<MyHelperSceneNode> root=std::make_shared<MyHelperSceneNode>("boxRoot",myRenderPacket);
    root->addChild(squareNode);
    
    // build box
    box=std::make_shared<SceneGraph>();
    box->setRoot(root);
    box->setCamera(std::make_shared<CameraSceneNode>("camera"));
    
}
//-------------------------------------------------------------------------------
// @ HelperClass::BuildQuad()
//-------------------------------------------------------------------------------
void
HelperClass::BuildQuad(const std::shared_ptr<MeshInstance>&meshInstance)
{
    //setting sceneNode
    RenderPacket myRenderPacket;
    myRenderPacket._use_blend=true;
    myRenderPacket._use_depth=true;
    myRenderPacket._use_wireframe=wireframeValue;
    myRenderPacket._prim_type=kTriangleStripPrim;

    std::shared_ptr<MyHelperSceneNode> quadNode=std::make_shared<MyHelperSceneNode>("quad",myRenderPacket);
    quadNode->setRenderable(meshInstance);


    //adding children to scene graph
    std::shared_ptr<MyHelperSceneNode> root=std::make_shared<MyHelperSceneNode>("quadRoot",myRenderPacket);
    root->addChild(quadNode);

    
    //build quad
    quad=std::make_shared<SceneGraph>();
    quad->setRoot(root);
    quad->setCamera(std::make_shared<CameraSceneNode>("camera"));
    
}

//-------------------------------------------------------------------------------
// @ HelperClass::BuildSphere()
//-------------------------------------------------------------------------------
void
HelperClass::BuildSphere(const std::shared_ptr<MeshInstance>& meshInstance)
{
    //setting sceneNode
    RenderPacket myRenderPacket;
    myRenderPacket._use_blend=true;
    myRenderPacket._use_depth=true;
    myRenderPacket._use_wireframe=wireframeValue;
    myRenderPacket._prim_type=kTriangleListPrim;
    
    std::shared_ptr<MyHelperSceneNode> sphereNode=std::make_shared<MyHelperSceneNode>("sphere",myRenderPacket);
    sphereNode->setRenderable(meshInstance);
    
    
    //adding children to scene graph
    std::shared_ptr<MyHelperSceneNode> root=std::make_shared<MyHelperSceneNode>("sphereRoot",myRenderPacket);
    root->addChild(sphereNode);
    
    
    //build quad
    sphere=std::make_shared<SceneGraph>();
    sphere->setRoot(root);
    sphere->setCamera(std::make_shared<CameraSceneNode>("camera"));
}


