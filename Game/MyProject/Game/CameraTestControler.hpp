#pragma once

#include <IvMatrix44.h>
#include <IvRenderer.h>
#include <IvEventHandler.h>
#include <IvMath.h>
#include <IvVector3.h>
#include <IvRendererHelp.h>
#include "Game.hpp"
#include "Camera.hpp"


class CameraTestControler
{
public:
    CameraTestControler();
    ~CameraTestControler();

    void Update( float dt );
    void Render();
    
    std::shared_ptr<Camera> camera;
    std::shared_ptr<CameraSceneNode> cameraSceneNode;
    
    IvVector3 mouseCoordinates;
    bool mousePicker;
    std::shared_ptr<SceneGraph> boxGraph;
};
