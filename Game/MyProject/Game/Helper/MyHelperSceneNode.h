//-------------------------------------------------------------------------------
//-- MyHelperSceneNode.h --------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "SceneNode.hpp"
#include "CameraSceneNode.hpp"
//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class MyHelperSceneNode:public SceneNode
{
public:
	
    MyHelperSceneNode(const std::string& name,RenderPacket renderPacket);
    ~MyHelperSceneNode(){}
    
    void collectRenderingPackets(CameraSceneNode*,std::vector<RenderPacket>&);

private:

    RenderPacket       myRenderPacket;
};
