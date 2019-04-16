//-------------------------------------------------------------------------------
//-- MySceneNodeHelper.cpp ------------------------------------------------------
//-------------------------------------------------------------------------------
#include "MyHelperSceneNode.h"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ MySceneNodeHelper::MySceneNodeHelper()
//-------------------------------------------------------------------------------
MyHelperSceneNode::MyHelperSceneNode(const std::string& name,RenderPacket renderPacket):SceneNode(name)
{
    myRenderPacket=renderPacket;
}
//-------------------------------------------------------------------------------
// @ MySceneNodeHelper::collectRenderPacket()
//-------------------------------------------------------------------------------
void
MyHelperSceneNode::collectRenderingPackets(CameraSceneNode * camera, std::vector<RenderPacket> & renderPackets)
{
    if (SceneNode::_rendarable) {
        myRenderPacket._mesh_instance = SceneNode::_rendarable.get();
        myRenderPacket._world_view_projection_matrix = SceneNode::_absolute_transform * camera->getView() * camera->getProjection();
       
        renderPackets.push_back(myRenderPacket);
    }
    for (auto& i : _children)
        i->collectRenderingPackets(camera, renderPackets);
}
