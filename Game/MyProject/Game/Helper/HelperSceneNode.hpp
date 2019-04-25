//-------------------------------------------------------------------------------
//-- HelperSceneNode.h --------------------------------------------------------
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

class HelperSceneNode:public SceneNode
{
public:
    
    HelperSceneNode(const std::string& name,RenderPacket renderPacket);
    virtual ~HelperSceneNode(){}
    
    void collectRenderingPackets(const Camera*,std::vector<RenderPacket>&);
    
private:
    
    RenderPacket       m_renderPacket;
};

