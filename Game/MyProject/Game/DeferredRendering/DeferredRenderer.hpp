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
    
    bool    needs_debug_screen = false;
    bool    needs_motion_blur = false;
    
    float   exposure = 2.1f;
    float   gamma = 0.8f;
    float   vignette_intensity = 30.0f;
    float   vignette_size = 0.5f;
    
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
