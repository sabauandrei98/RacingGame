#pragma once

#include <IvMatrix44.h>
#include <IvRenderer.h>
#include <IvEventHandler.h>
#include <IvMath.h>
#include <IvVector3.h>
#include <IvRendererHelp.h>
#include "Game.h"
#include "Camera.hpp"


class CameraTestControler
{
public:
    CameraTestControler();
    ~CameraTestControler();

    void Update( float dt );
    void Render();
    
    Camera camera;
};
