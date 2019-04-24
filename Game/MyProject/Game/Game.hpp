#pragma once

<<<<<<< HEAD
#include"Player/Player.hpp"
#include"Test/TestCustomAttributes/Test.hpp"
#include"Test/TestRenderTargets/TestRT.hpp"
#include"Test/TestHelper/TestHelper.hpp"
=======
#include "Player/Player.hpp"
#include "Test/TestCustomAttributes/Test.hpp"
#include "Test/TestRenderTargets/TestRT.hpp"
>>>>>>> master

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

class CameraTestControler;

class Game : public IvGame
{
public:
    Game();
    ~Game();
    bool PostRendererInitialize();
    
    TestHelper*                  test;
    CameraTestControler*         cameraTest;

    std::unique_ptr<SceneGraph>         _scene_graph;
    std::shared_ptr<SceneNode>          _root;
    std::shared_ptr<SceneNode>          _child1;
    std::shared_ptr<SceneNode>          _child2;
    std::shared_ptr<SceneNode>          _child3;
    std::shared_ptr<Camera>             _camera;
    std::shared_ptr<CameraSceneNode>    _camera_scene_node;


protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};
