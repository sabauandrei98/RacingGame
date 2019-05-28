
#pragma once

#include <cmath>
#include <ctime>
#include <chrono>

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
    void setTarget(SceneNode*);
    SceneNode* getTarget() const;
    
    IvVector3 screenToWorld(unsigned int mouseX,unsigned int mouseY);
    IvRay3 getRay( unsigned int mouseX,unsigned int mouseY);
    
    // void updateNode(float dt);
    // this derived function is not needed, because the camera is used only in absolute space
    void updateAbsoluteTransform() {}
    ~CameraSceneNode() {}
    
    friend class CameraFollowAnimator;
    
private:
    // private variable(s)
    CameraPtr   _camera;
};



