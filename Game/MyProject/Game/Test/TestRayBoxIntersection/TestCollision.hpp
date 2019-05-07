//-------------------------------------------------------------------------------
//-- TestCollision.hpp -------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once

#include "RayBoxIntersection.hpp"
#include "Camera.hpp"
#include "Helper/HelperManager.hpp"
#include "Helper/MeshManager.hpp"
#include "IvRendererHelp.h"
#include <iostream>

class TestCollision
{
public:

	void TestRayBox();
    void Update(float t);
    void Render();
private:
    std::shared_ptr<SceneGraph>         box;
    std::shared_ptr<SceneGraph>         sphere;
    std::shared_ptr<Camera>             camera;
    std::shared_ptr<CameraSceneNode>    cameraSceneNode;
    
    bool            is_mouse_released;
    unsigned int    mouseX;
    unsigned int    mouseY;
};
