//
//  DeferredRenderer.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 14/05/2019.
//

#pragma once

#include "../Game/SceneManagement/SceneGraph.hpp"
#include <IvFrameBufferOGL.h>

class DeferredRenderer {
public:
    DeferredRenderer();
    
    void Render(SceneGraph*);
    
private:
    IvFrameBuffer*                  _g_buffer;
    MeshInstance                    _renderable;
    
    IvShaderProgram*                _shader;
    
    bool                            _needs_motion_blur = false;
};
