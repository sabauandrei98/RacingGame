#pragma once

#include"Player/Player.hpp"
#include"Test/TestCustomAttributes/Test.hpp"
#include"Test/TestRenderTargets/TestRT.hpp"

#include <stdio.h>
#include<iostream>
#include<IvGame.h>
#include<IvRendererHelp.h>
#include<IvBezier.h>
#include<IvVector3.h>
#include<IvVertexFormats.h>
#include<IvRendererOGL.h>
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
    
    TestRT *test;
    CameraTestControler*            cameraTest;
    std::unique_ptr<SceneGraph>     _scene_graph;
    std::shared_ptr<SceneNode>      root;
    std::shared_ptr<SceneNode>      child1;
    std::shared_ptr<SceneNode>      child2;

protected:
    virtual void UpdateObjects(float dt);
    virtual void Render();
    
private:
    Game( const Game& other );
    Game& operator=( const Game& other );

};
