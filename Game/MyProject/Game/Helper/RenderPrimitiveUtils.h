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

namespace RenderPrimitiveUtils
{
    void DrawBox(const std::shared_ptr<MeshInstance>&,
                IvVector3 position=IvVector3{0,0,0},
                IvVector3 rotation=IvVector3{0,0,0},
                IvVector3 scale=IvVector3{1,1,1},
                bool wireframe=false);
    
    void DrawQuad(const std::shared_ptr<MeshInstance>&,
                IvVector3 axis,
                IvVector3 position=IvVector3{0,0,0},
                IvVector3 rotation=IvVector3{0,0,0},
                IvVector3 scale=IvVector3{1,1,1},
                bool wireframe=false);
    
    void DrawTexturedQuad(const std::shared_ptr<MeshInstance>&,
                        const char* textureName,
                        IvVector3 axis=IvVector3::zAxis,
                        IvVector3 position=IvVector3{0,0,0},
                        IvVector3 rotation=IvVector3{0,0,0},
                        IvVector3 scale=IvVector3{1,1,1},
                        bool wireframe=false);
    
    void DrawSphere(const std::shared_ptr<MeshInstance>&,
                    IvVector3 position=IvVector3{0,0,0},
                    IvVector3 rotation=IvVector3{0,0,0},
                    IvVector3 scale=IvVector3{1,1,1},
                    bool wireframe=false);
    

    std::shared_ptr<SceneGraph> BuildBox(const std::shared_ptr<MeshInstance>&,bool wireframeValue);
    std::shared_ptr<SceneGraph> BuildQuad(const std::shared_ptr<MeshInstance>&,bool wireframeValue);
    std::shared_ptr<SceneGraph> BuildSphere(const std::shared_ptr<MeshInstance>&,bool wireframeValue);
};
