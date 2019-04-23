#include "CameraSceneNode.hpp"


const IvMatrix44 CameraSceneNode::getViewMatrix() const
{
    IvVector3 view = lookAt - position;
    view.Normalize();
    IvVector3 right =  view.Cross( rotation );
    IvVector3 viewUp =  right.Cross( view );
    IvMatrix33 rotate;
    
    rotate.SetRows( right, viewUp, -view );
    IvVector3 xlate = - (rotate * position);
    IvMatrix44 matrix(rotate);
    
    matrix *= rotMatrix;
    
    matrix(0,3) = xlate.x;
    matrix(1,3) = xlate.y;
    matrix(2,3) = xlate.z;
    
    return matrix;
}

const IvMatrix44 CameraSceneNode::getProjectionMatrix() const
{
    IvMatrix44 perspective;
    float aspectRatio = (float) screenWidth / screenHeight;
    float d = 1.0f / IvTan(fieldOfView / 180.0f * kPI * 0.5f);
    
    perspective(0,0) = d / aspectRatio;
    perspective(1,1) = d ;
    perspective(2,2) = (nearPlane + farPlane) / (nearPlane - farPlane);
    perspective(2,3) = (2 * nearPlane * farPlane) / (nearPlane - farPlane);
    perspective(3,2) = -1.0f;
    perspective(3,3) = 0.0f;
    
    return perspective;
}

void CameraSceneNode::zoom(float step)
{
    IvVector3 direction = lookAt - position;
    direction.Normalize();
    
    position += direction * step;
}

void CameraSceneNode::pan(const IvVector2& offset)
{
    IvVector3 view = lookAt - position;
    view.Normalize();
    IvVector3 right =  view.Cross( rotation );
    right.Normalize();
    IvVector3 viewUp =  right.Cross( view );
    viewUp.Normalize();
    
    position += right * offset.x + viewUp * offset.y;
    lookAt += right * offset.x + viewUp * offset.y;
}

const IvMatrix44 CameraSceneNode::rotateX(const float angle) const
{
    IvMatrix44 x;
    x[0] = 1;
    x[5] = cos(-angle);
    x[6] = -sin(-angle);
    x[9] = sin(-angle);
    x[10] = cos(-angle);
    x[15] = 1;
    
    return x;
}

const IvMatrix44 CameraSceneNode::rotateY(const float angle) const
{
    IvMatrix44 y;
    y[0] = cos(-angle);
    y[2] = sin(-angle);
    y[5] = 1;
    y[8] = -sin(-angle);
    y[10] = cos(-angle);
    y[15] = 1;
    
    return y;
}

const IvMatrix44 CameraSceneNode::rotateZ(const float angle) const
{
    IvMatrix44 z;
    z[0] = cos(-angle);
    z[1] = -sin(-angle);
    z[4] = sin(-angle);
    z[5] = cos(-angle);
    z[10] = 1;
    z[15] = 1;
    
    return z;
}

void CameraSceneNode::rotate(const IvVector3& offsetAngles)
{
    rotOffsets += offsetAngles;
    IvMatrix44 x = rotateX(rotOffsets.x);
    IvMatrix44 y = rotateY(rotOffsets.y);
    IvMatrix44 z = rotateZ(rotOffsets.z);
    rotMatrix = z * y * x;
}

void CameraSceneNode::setPosition(const IvVector3& newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
}

void CameraSceneNode::setRotation(const IvVector3& newRotation)
{
    rotation.x = newRotation.x;
    rotation.y = newRotation.y;
    rotation.z = newRotation.z;
}

void CameraSceneNode::setLookAt(const IvVector3& newLookAt)
{
    lookAt.x = newLookAt.x;
    lookAt.y = newLookAt.y;
    lookAt.z = newLookAt.z;
}

void CameraSceneNode::setFieldOfView(float newFOV)
{
    fieldOfView = newFOV;
}

void CameraSceneNode::setNear(float newNear)
{
    nearPlane = newNear;
}

void CameraSceneNode::setFar(float newFar)
{
    farPlane = newFar;
}

void CameraSceneNode::setScreenWidth(float newWidth)
{
    screenWidth = newWidth;
}

void CameraSceneNode::setScreenHeight(float newHeight)
{
    screenHeight = newHeight;
}


CameraSceneNode::~CameraSceneNode(){}
