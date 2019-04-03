#include "Camera.hpp"

Camera::Camera(float FOV, float nearPlane, float farPlane, int w, int h)
{
    fieldOfView = FOV;
    near = nearPlane;
    far = farPlane;
    width = w;
    height = h;
    aspectRatio = (float) w / h;
}


IvMatrix44 Camera::getViewMatrix()
{
    
    IvVector3 view = lookAt - position;
    view.Normalize();
    
    IvVector3 right =  view.Cross( orientation );
    right.Normalize();
    
    IvVector3 viewUp =  right.Cross( view );
    viewUp.Normalize();
    
    // now set up matrices
    // world->view rotation
    
    IvMatrix33 rotate;
    rotate.SetRows( right, viewUp, -view );
    
    // world->view translation
    IvVector3 xlate = - (rotate * position);
    
    // build 4x4 matrix
    IvMatrix44 matrix(rotate);
    
    matrix(0,3) = xlate.x;
    matrix(1,3) = xlate.y;
    matrix(2,3) = xlate.z;
    
    return matrix;
}

IvMatrix44 Camera::getProjectionMatrix()
{
    IvMatrix44 perspective;
    
    float d = 1.0f/IvTan(fieldOfView/180.0f*kPI*0.5f);
    
    perspective(0,0) = d / aspectRatio;
    perspective(1,1) = d ;
    perspective(2,2) = (near+far) / (near-far);
    perspective(2,3) = (2*near*far) / (near-far);
    perspective(3,2) = -1.0f;
    perspective(3,3) = 0.0f;
    
    return perspective;
}


void Camera::setPosition(IvVector3 newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
}

void Camera::setOrientation(IvVector3 newOrientation)
{
    orientation.x = newOrientation.x;
    orientation.y = newOrientation.y;
    orientation.z = newOrientation.z;
}

void Camera::setLookAt(IvVector3 newLookAt)
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
    near = newNear;
}

void Camera::setFar(float newFar)
{
    far = newFar;
}

void Camera::zoom(float step)
{
    IvVector3 view = lookAt - position;
    view.Normalize();
    
    IvVector3 s = view * step + position;
    
    if(s.x * s.x + s.y * s.y + s.z * s.z > 10.0f)
        position += view * step;
}

void Camera::panRight(float step)
{
    IvVector3 right = {0.0, 1.0, 0.0};
    position += right * step;
    lookAt += right * step;
}

void Camera::panUp(float step)
{
    IvVector3 up = {0.0, 0.0, 1.0};
    position += up * step;
    lookAt += up * step;
}

Camera::~Camera(){}

