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
    std::shared_ptr<SceneGraph> box;
    BoundingBox boundingBox;
    IvVector3 cameraPosition;
    IvVector3 cameraLookAt;
    IvRay3 ray;
    IvVector3 mouseCoordinates;
};
