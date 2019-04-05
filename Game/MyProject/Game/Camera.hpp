#pragma once
#include <stdio.h>
#include <IvVector3.h>
#include <IvVector2.h>
#include <IvVector4.h>
#include <IvMatrix44.h>
#include <IvMatrix33.h>
#include <IvMath.h>
#include <iostream>

class Camera{

private:
    
    IvMatrix44 transform;
    IvMatrix44 rotMatrix;
    
    IvVector3 position;
    IvVector3 lookAt;
    IvVector3 rotation;
    IvVector3 rotOffsets;
    
    float fieldOfView;
    float nearPlane;
    float farPlane;
    int screenWidth;
    int screenHeight;

public:
    Camera(){};
    Camera(const float fieldOfView, const float nearPlane, const float farPlane, const int screenWidth, const int screenHeight) :
        rotOffsets(0.0f, 0.0f, 0.0f),
        fieldOfView(fieldOfView),
        nearPlane(nearPlane),
        farPlane(farPlane),
        screenWidth(screenWidth),
        screenHeight(screenHeight)
        {};
    
    ~Camera();
    
    void setPosition(const IvVector3& newPos);
    void setLookAt(const IvVector3& newLookAt);
    void setRotation(const IvVector3& newRotation);
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
    const IvVector3& getRotation() { return rotation; }
    const IvMatrix44& getTransformMatrix() { return transform;}
    
    
    IvMatrix44 getViewMatrix();
    IvMatrix44 getProjectionMatrix();
    
    const IvMatrix44 rotateX(const float angle);
    const IvMatrix44 rotateY(const float angle);
    const IvMatrix44 rotateZ(const float angle);
    
    
    
///-------------------------------------------------------------------------------
//--FUNCTIONALITIES---------------------------------------------------------------
//--------------------------------------------------------------------------------

    void zoom(float step);
    void pan(const IvVector2& offset);
    void rotate(const IvVector3& offset);
    
    
};
