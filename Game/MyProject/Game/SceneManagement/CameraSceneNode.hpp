
#pragma once

#include <IvGame.h>
#include <IvEventHandler.h>
#include "SceneNode.hpp"
#include "../Camera.hpp"


class CameraSceneNode : public SceneNode {
public:
    // typedef(s)
    typedef std::shared_ptr<Camera> CameraPtr;
    
    // constructor(s) and destructor
    CameraSceneNode(const std::string&, const CameraPtr&);
    
    // public function(s) and method(s)
    void updateNode(float);
    
    IvVector3 screenToWorld(unsigned int mouseX,unsigned int mouseY);
    
    IvRay3 getRay( unsigned int mouseX,unsigned int mouseY);
    
private:
    CameraPtr           _camera;       
};



