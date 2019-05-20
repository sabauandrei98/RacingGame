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
    
    bool    _needs_motion_blur = false;
    bool    _needs_debug_screen = false;
    
private:
    IvFrameBuffer*      _g_buffer;
    IvFrameBuffer*      _previous_position;
    MeshInstance        _renderable;
    
    MeshInstance        _screen1;
    MeshInstance        _screen2;
    MeshInstance        _screen3;
    
    IvShaderProgram*    _shader;
    IvShaderProgram*    _blur_shader;
    IvShaderProgram*    _copy_shader;
    IvShaderProgram*    _debug_shader;
    
    void setUpGBuffer();
    void setUpPreviousBuffer();
    void setUpMotionBlur();
    void setUpDebugScreen();
    
    void renderNoEffect();
    void renderMotionBlur();
    void showDebugScreen();
};
