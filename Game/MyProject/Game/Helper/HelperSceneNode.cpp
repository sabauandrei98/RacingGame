//-------------------------------------------------------------------------------
//-- MySceneNodeHelper.cpp ------------------------------------------------------
//-------------------------------------------------------------------------------
#include "HelperSceneNode.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ MySceneNodeHelper::MySceneNodeHelper()
//-------------------------------------------------------------------------------
HelperSceneNode::HelperSceneNode(const std::string& name,RenderPacket renderPacket):SceneNode(name)
{
    m_renderPacket=renderPacket;
}
//-------------------------------------------------------------------------------
// @ MySceneNodeHelper::collectRenderPacket()
//-------------------------------------------------------------------------------
void
HelperSceneNode::collectRenderingPackets(const Camera* camera, std::vector<RenderPacket> & renderPackets)
{
    if(!SceneNode::_enabled)
        return ;
    
    
    if (SceneNode::_rendarable) {
        m_renderPacket._mesh_instance = SceneNode::_rendarable.get();
        
        m_renderPacket._world_view_projection_matrix =  camera->getProjectionMatrix()*camera->getViewMatrix() *SceneNode::_absolute_transform;
       
        renderPackets.push_back(m_renderPacket);
    }
    for (auto& i : _children)
        i->collectRenderingPackets(camera, renderPackets);
}
