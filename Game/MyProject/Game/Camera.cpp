#include "Camera.hpp"


IvMatrix44 Camera::getViewMatrix()
{
    
    IvVector3 view = lookAt - position;
    view.Normalize();
    IvVector3 right =  view.Cross( orientation );
    IvVector3 viewUp =  right.Cross( view );
    IvMatrix33 rotate;
    rotate.SetRows( right, viewUp, -view );
    IvVector3 xlate = - (rotate * position);
    IvMatrix44 matrix(rotate);
    
    matrix(0,3) = xlate.x;
    matrix(1,3) = xlate.y;
    matrix(2,3) = xlate.z;
    
    return matrix;
}

IvMatrix44 Camera::getProjectionMatrix()
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
    position += (lookAt - position) * step;
}

void Camera::pan(const IvVector2& offset)
{
    IvVector3 view = lookAt - position;
    IvVector3 right =  view.Cross( orientation );
    right.Normalize();
    IvVector3 viewUp =  right.Cross( view );
    viewUp.Normalize();
    
    position -= right * offset.x - viewUp * offset.y;
    lookAt -= right * offset.x - viewUp * offset.y;
}

void Camera::rotate(const IvVector2& offset, IvVector3 point)
{
    IvVector3 view = point - position;
    IvVector3 right =  view.Cross( orientation );
    right.Normalize();
    IvVector3 viewUp =  right.Cross( view );
    viewUp.Normalize();
    
    position -= right * offset.x - viewUp * offset.y;
}

void Camera::setPosition(const IvVector3& newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
}

void Camera::setOrientation(const IvVector3& newOrientation)
{
    orientation.x = newOrientation.x;
    orientation.y = newOrientation.y;
    orientation.z = newOrientation.z;
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

