#include "Camera.hpp"


IvMatrix44 Camera::getViewMatrix() const
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

IvMatrix44 Camera::getProjectionMatrix() const
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

void Camera::zoom(float step)
{
    IvVector3 direction = lookAt - position;
    direction.Normalize();
    
    position += direction * step;
}

void Camera::pan(const IvVector2& offset)
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

const IvMatrix44 Camera::rotateX(const float angle) const
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

const IvMatrix44 Camera::rotateY(const float angle) const
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

const IvMatrix44 Camera::rotateZ(const float angle) const
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

void Camera::rotate(const IvVector3& offsetAngles)
{
    rotOffsets += offsetAngles;
    IvMatrix44 x = rotateX(rotOffsets.x);
    IvMatrix44 y = rotateY(rotOffsets.y);
    IvMatrix44 z = rotateZ(rotOffsets.z);
    rotMatrix = z * y * x;
}

void Camera::setPosition(const IvVector3& newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
}

void Camera::setRotation(const IvVector3& newRotation)
{
    rotation.x = newRotation.x;
    rotation.y = newRotation.y;
    rotation.z = newRotation.z;
}

void Camera::setLookAt(const IvVector3& newLookAt)
{
    lookAt.x = newLookAt.x;
    lookAt.y = newLookAt.y;
    lookAt.z = newLookAt.z;
}

void Camera::setFieldOfView(float newFOV)
{
    fieldOfView = newFOV;
}

void Camera::setNear(float newNear)
{
    nearPlane = newNear;
}

void Camera::setFar(float newFar)
{
    farPlane = newFar;
}

void Camera::setScreenWidth(float newWidth)
{
    screenWidth = newWidth;
}

void Camera::setScreenHeight(float newHeight)
{
    screenHeight = newHeight;
}


Camera::~Camera(){}

