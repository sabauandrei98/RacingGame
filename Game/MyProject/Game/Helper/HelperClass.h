//-------------------------------------------------------------------------------
//-- HelperClass.h -------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "SceneGraph.hpp"
#include "CameraSceneNode.hpp"
#include "HelperManager.h"
#include "IvImage.h"
#include "MyHelperSceneNode.h"
//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class HelperClass
{
public:
    void DrawBox(const std::shared_ptr<MeshInstance>&,
                 IvVector3 position=IvVector3{0,0,0},
                 IvVector3 rotation=IvVector3{0,0,0},
                 IvVector3 scale=IvVector3{1,1,1});
    
    void DrawQuad(const std::shared_ptr<MeshInstance>&,
                  IvVector3 axis,
                  IvVector3 position=IvVector3{0,0,0},
                  IvVector3 rotation=IvVector3{0,0,0},
                  IvVector3 scale=IvVector3{1,1,1});
    
    void DrawTexturedQuad(const std::shared_ptr<MeshInstance>&,
                          const char* textureName,
                          IvVector3 axis=IvVector3::zAxis,
                          IvVector3 position=IvVector3{0,0,0},
                          IvVector3 rotation=IvVector3{0,0,0},
                          IvVector3 scale=IvVector3{1,1,1});
    
    void DrawCrossQuad(const std::shared_ptr<MeshInstance>&,
                       IvVector3 axis=IvVector3::zAxis,
                       IvVector3 position=IvVector3{0,0,0},
                       IvVector3 rotation=IvVector3{0,0,0},
                       IvVector3 scale=IvVector3{1,1,1});
    
    void DrawSphere(const std::shared_ptr<MeshInstance>&,
                    IvVector3 position=IvVector3{0,0,0},
                    IvVector3 rotation=IvVector3{0,0,0},
                    IvVector3 scale=IvVector3{1,1,1});
    
    void SetWireframeState(bool wireframeValue);
    
private:
    void BuildBox(const std::shared_ptr<MeshInstance>&);
    void BuildQuad(const std::shared_ptr<MeshInstance>&);
    void BuildSphere(const std::shared_ptr<MeshInstance>&);

    bool                            builtBox        =    false;
    bool                            builtQuad       =    false;
    bool                            builtSphere     =    false;
    
    bool                            wireframeValue  =    false;
    
    std::shared_ptr<SceneGraph>     box;
    std::shared_ptr<SceneGraph>     quad;
    std::shared_ptr<SceneGraph>     sphere;
    
    IvTexture*                      quadTexture;
    
};
