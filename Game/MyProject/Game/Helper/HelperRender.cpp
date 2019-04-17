//-------------------------------------------------------------------------------
//-- HelperRender.h -------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "HelperRender.h"


namespace HelperRender
{
    //---------------------------------------------------------------------------
    // @HelperRender::DrawBox()
    //---------------------------------------------------------------------------
    void DrawBox(IvVector3 position,
                 IvVector3 rotation,
                 IvVector3 scale)
    {
        std::shared_ptr<Mesh> boxMesh=HelperManager::CreateBoxMesh();
        std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(boxMesh);

        RenderPrimitiveUtils::DrawBox(meshInstance,position,rotation,scale);
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawQuad()
    //---------------------------------------------------------------------------
    void DrawQuad(IvVector3 axis,
                  IvVector3 position,
                  IvVector3 rotation,
                  IvVector3 scale)
    {
         std::shared_ptr<Mesh> quadMesh=HelperManager::CreateQuadMesh();

         RenderPrimitiveUtils::DrawQuad(HelperManager::CreateMeshInstance(quadMesh),axis,position,rotation,scale);
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawTexturedQuad()
    //---------------------------------------------------------------------------
    void DrawTexturedQuad(const char* textureName,
                          const char* uniformName,
                          const char* shaderName,
                          IvVector3 axis,
                          IvVector3 position,
                          IvVector3 rotation,
                          IvVector3 scale)
    {
        std::shared_ptr<Mesh> texturedQuadMesh=HelperManager::CreateQuadMesh();

        if(!textureName|| !uniformName || ! shaderName)
        {

            std::vector<std::string> uniforms;
            uniforms.push_back("myTexture");
            std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(texturedQuadMesh,uniforms);
            RenderPrimitiveUtils::DrawTexturedQuad(meshInstance,"TextureShader",axis,position,rotation,scale);

        }
        else
        {

            std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(texturedQuadMesh,uniformName);
            RenderPrimitiveUtils::DrawTexturedQuad(meshInstance,textureName,axis,position,rotation,scale);

        }
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawCrossTexturedQuad()
    //---------------------------------------------------------------------------
    void DrawCrossTexturedQuad(IvVector3 axis,
                               IvVector3 position,
                               IvVector3 rotation,
                               IvVector3 scale)
    {
        std::shared_ptr<Mesh> texturedQuadMesh=HelperManager::CreateQuadMesh();

        std::vector<std::string> uniforms;
        uniforms.push_back("myTexture");

        std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(texturedQuadMesh,uniforms,"TextureShader");

        RenderPrimitiveUtils::DrawTexturedQuad(meshInstance,"cross.tga",axis,position,rotation,scale);
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawSphere()
    //---------------------------------------------------------------------------
    void DrawSphere(IvVector3 position,
                    IvVector3 rotation,
                    IvVector3 scale)
    {
         std::shared_ptr<Mesh> sphereMesh=HelperManager::CreateSphereMesh();
         std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(sphereMesh);

         RenderPrimitiveUtils::DrawSphere(meshInstance,position,rotation,scale);
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawWireframeBox()
    //---------------------------------------------------------------------------
    void DrawWireframeBox(IvVector3 position,
                          IvVector3 rotation,
                          IvVector3 scale)
    {
        std::shared_ptr<Mesh> boxMesh=HelperManager::CreateBoxMesh();
        std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(boxMesh);

        RenderPrimitiveUtils::DrawBox(meshInstance,position,rotation,scale,true);
    }
    //-------------------------------------------------------------------------------
    // @HelperRender::DrawWireframeQuad()
    //-------------------------------------------------------------------------------
    void DrawWireframeQuad(IvVector3 axis,
                           IvVector3 position,
                           IvVector3 rotation,
                           IvVector3 scale)
    {
        
        std::shared_ptr<Mesh> quadMesh=HelperManager::CreateQuadMesh();
        std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(quadMesh);

        RenderPrimitiveUtils::DrawQuad(meshInstance,axis,position,rotation,scale,true);
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawWireframeTexturedQuad()
    //---------------------------------------------------------------------------
    void DrawWireframeTexturedQuad(const char* textureName,
                                   const char* uniformName,
                                   const char* shaderName,
                                   IvVector3 axis,
                                   IvVector3 position,
                                   IvVector3 rotation,
                                   IvVector3 scale)
    {
        std::shared_ptr<Mesh> texturedQuadMesh=HelperManager::CreateQuadMesh();

        if(!textureName|| !uniformName || ! shaderName)
        {
            std::vector<std::string> uniforms;
            uniforms.push_back("myTexture");
            std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(texturedQuadMesh,uniforms);

            RenderPrimitiveUtils::DrawTexturedQuad(meshInstance,"TextureShader",axis,position,rotation,scale,true);

        }
        else
        {
            std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(texturedQuadMesh,uniformName);

            RenderPrimitiveUtils::DrawTexturedQuad(meshInstance,textureName,axis,position,rotation,scale,true);

        }
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawWireframeCrossTexturedQuad()
    //---------------------------------------------------------------------------
    void DrawWireframeCrossTexturedQuad(IvVector3 axis,
                                        IvVector3 position,
                                        IvVector3 rotation,
                                        IvVector3 scale)
    {
        std::shared_ptr<Mesh> texturedQuadMesh=HelperManager::CreateQuadMesh();

        std::vector<std::string> uniforms;
        uniforms.push_back("myTexture");

        std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(texturedQuadMesh,uniforms,"TextureShader");

        RenderPrimitiveUtils::DrawTexturedQuad(meshInstance,"cross.tga",axis,position,rotation,scale,true);
    }
    //---------------------------------------------------------------------------
    // @HelperRender::DrawWireframeSphere()
    //---------------------------------------------------------------------------
    void DrawWireframeSphere(IvVector3 position,
                             IvVector3 rotation,
                             IvVector3 scale)
    {
        std::shared_ptr<Mesh> sphereMesh=HelperManager::CreateSphereMesh();
        std::shared_ptr<MeshInstance> meshInstance=HelperManager::CreateMeshInstance(sphereMesh);
        
        RenderPrimitiveUtils::DrawSphere(meshInstance,position,rotation,scale,true);
    }
}
