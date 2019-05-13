#pragma once

#include "BasicMenu/StartMenu.hpp"
#include "BasicMenu/TrackMenu.hpp"
#include "Player/Player.hpp"
#include "Test/TestRayBoxIntersection/TestCollision.hpp"
#include "Test/TestHelper/TestHelper.hpp"
#include <stdio.h>
#include <iostream>
#include <IvGame.h>
#include <IvRendererHelp.h>
#include <IvBezier.h>
#include <IvVector3.h>
#include <IvVertexFormats.h>
#include <IvRendererOGL.h>
#include "CameraTestControler.hpp"
#include "SceneManagement/SceneGraph.hpp"
#include "SceneManagement/CameraSceneNode.hpp"
#include "ModelLoader/ModelLoader.hpp"
#include "SceneManagement/CarAnimator.hpp"
#include "SceneManagement/CameraFollowAnimator.hpp"
#include "GameStates/StateController.hpp"
#include "RoadGenerator/RoadEditor.hpp"
#include "SceneManagement/CarController.hpp"

class CameraTestControler;
class StateController;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();

protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );
    
    std::unique_ptr<SceneGraph>         _scene_graph;
    std::shared_ptr<SceneNode>          _root;
    std::shared_ptr<SceneNode>          _child1;
    std::shared_ptr<SceneNode>          _child2;
    std::shared_ptr<SceneNode>          _child3;
    std::shared_ptr<Camera>             _camera;
    std::shared_ptr<CameraSceneNode>    _camera_scene_node;
    std::shared_ptr<NodeAnimator>       _controller;
};
