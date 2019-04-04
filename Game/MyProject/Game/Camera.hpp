#pragma once
#include <stdio.h>
#include <IvVector3.h>
#include <IvVector2.h>
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
    float nearPlane;
    float farPlane;
    int screenWidth;
    int screenHeight;

public:
    Camera(){};
    Camera(const float fieldOfView, const float nearPlane, const float farPlane, const int screenWidth, const int screenHeight) :
        fieldOfView(fieldOfView),
        nearPlane(nearPlane),
        farPlane(farPlane),
        screenWidth(screenWidth),
        screenHeight(screenHeight)
        {};
    
    ~Camera();
    
    void setPosition(const IvVector3& newPos);
    void setLookAt(const IvVector3& newLookAt);
    void setOrientation(const IvVector3& newOrientation);
    void setFieldOfView(float newFOV);
    void setNear(float newNear);
    void setFar(float newFar);
    void setScreenWidth(float newWidth);
    void setScreenHeight(float newHeight);
    
    const float getFieldOfView() { return fieldOfView; }
    const float getNearPlane() { return nearPlane; }
    const float getFarPlane() { return farPlane; }
    const float getHeight() { return screenHeight; }
    const float getWidth() { return screenWidth; }
    const IvVector3& getPosition() { return position; }
    const IvVector3& getLookAt() { return lookAt; }
    const IvVector3& getOrientation() { return orientation; }
    const IvMatrix44& getTransformMatrix() { return transform;}
    
    IvMatrix44 getViewMatrix();
    IvMatrix44 getProjectionMatrix();
    
    
///-------------------------------------------------------------------------------
//--FUNCTIONALITIES---------------------------------------------------------------
//--------------------------------------------------------------------------------

    void zoom(float step);
    void pan(const IvVector2& offset);
    void rotate(const IvVector2& offset, IvVector3 point);
};
