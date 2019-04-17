//-------------------------------------------------------------------------------
//-- HelperRender.h -------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include <IvVector3.h>
#include "RenderPrimitiveUtils.h"

namespace HelperRender
{
    void DrawBox(IvVector3 position=IvVector3{0,0,0},
                 IvVector3 rotation=IvVector3{0,0,0},
                 IvVector3 scale=IvVector3{1,1,1});


    void DrawQuad(IvVector3 axis,
                  IvVector3 position=IvVector3{0,0,0},
                  IvVector3 rotation=IvVector3{0,0,0},
                  IvVector3 scale=IvVector3{1,1,1});


    void DrawTexturedQuad(const char* textureName,
                          const char* uniformName,
                          const char* shaderName,
                          IvVector3 axis=IvVector3::zAxis,
                          IvVector3 position=IvVector3{0,0,0},
                          IvVector3 rotation=IvVector3{0,0,0},
                          IvVector3 scale=IvVector3{1,1,1});


    void DrawCrossTexturedQuad(IvVector3 axis=IvVector3::zAxis,
                               IvVector3 position=IvVector3{0,0,0},
                               IvVector3 rotation=IvVector3{0,0,0},
                               IvVector3 scale=IvVector3{1,1,1});


    void DrawWireframeBox(IvVector3 position=IvVector3{0,0,0},
                          IvVector3 rotation=IvVector3{0,0,0},
                          IvVector3 scale=IvVector3{1,1,1});


    void DrawSphere(IvVector3 position=IvVector3{0,0,0},
                    IvVector3 rotation=IvVector3{0,0,0},
                    IvVector3 scale=IvVector3{1,1,1});


    // draw all of the above applying wireframe mode
    void DrawWireframeQuad(IvVector3 axis,
                  IvVector3 position=IvVector3{0,0,0},
                  IvVector3 rotation=IvVector3{0,0,0},
                  IvVector3 scale=IvVector3{1,1,1});


    void DrawWireframeTexturedQuad(const char* textureName,
                          const char* uniformName,
                          const char* shaderName,
                          IvVector3 axis=IvVector3::zAxis,
                          IvVector3 position=IvVector3{0,0,0},
                          IvVector3 rotation=IvVector3{0,0,0},
                          IvVector3 scale=IvVector3{1,1,1});


    void DrawWireframeCrossTexturedQuad(IvVector3 axis=IvVector3::zAxis,
                               IvVector3 position=IvVector3{0,0,0},
                               IvVector3 rotation=IvVector3{0,0,0},
                               IvVector3 scale=IvVector3{1,1,1});


    void DrawWireframeSphere(IvVector3 position=IvVector3{0,0,0},
                    IvVector3 rotation=IvVector3{0,0,0},
                    IvVector3 scale=IvVector3{1,1,1});
}
