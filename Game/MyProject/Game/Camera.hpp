#pragma once
#include <stdio.h>
#include <IvVector3.h>
#include <IvMatrix44.h>
#include <IvMatrix33.h>
#include <IvMath.h>

class Camera{

private:
    
    IvMatrix44 transform;
    
    IvVector3 position;
    IvVector3 lookAt;
    IvVector3 orientation;
    
    float fieldOfView;
    float near;
    float far;
    float aspectRatio;
    int width;
    int height;

    
public:
    Camera(){};
    Camera(float FOV, float nearPlane, float farPlane, int width, int height);
    ~Camera();
    
    void setPosition(IvVector3 newPos);
    void setLookAt(IvVector3 newLookAt);
    void setOrientation(IvVector3 newOrientation);
    void setFieldOfView(float newFOV);
    void setNear(float newNear);
    void setFar(float newFar);
    
    float getFieldOfView() { return fieldOfView; }
    float getNearPlane() { return near; }
    float getFarPlane() { return far; }
    float getHeight() { return height; }
    float getWidth() { return width; }
    float getAspectRatio() { return aspectRatio; }
    
    IvMatrix44 getViewMatrix();
    IvMatrix44 getProjectionMatrix();
    
    //last transform matrix (may not be updated)
    IvMatrix44 getTransformMatrix() { return transform;}
    

///-------------------------------------------------------------------------------
//--FUNCTIONALITIES---------------------------------------------------------------
//--------------------------------------------------------------------------------

    //base step value = 5.0f
    void zoom(float step);
    void panUp(float step);
    void panRight(float step);
};
