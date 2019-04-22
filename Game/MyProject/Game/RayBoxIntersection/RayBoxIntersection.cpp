//-------------------------------------------------------------------------------
//-- RayBoxIntersection.cpp -----------------------------------------------------
//-------------------------------------------------------------------------------
#include "RayBoxIntersection.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//  @RayBoxIntersection::IsRayIntersectingBox()
//-------------------------------------------------------------------------------
bool
RayBoxIntersection::IsRayIntersectingBox(const IvRay3 &ray, const BoundingBox &boundingBox)
{
    float minX=boundingBox.min.x;
    float minY=boundingBox.min.y;
    float minZ=boundingBox.min.z;
    
    float maxX=boundingBox.max.x;
    float maxY=boundingBox.max.y;
    float maxZ=boundingBox.max.z;
    
    IvVector3 origin=ray.GetOrigin();
    IvVector3 direction=ray.GetDirection();

    if(IsPointInsideBoundingBox(direction, boundingBox))
        return true;
    
    float mintx;
    float minty;
    float mintz;
 
    if(direction.x==0 && direction.y==0 && direction.z==0)
    {
        mintx=(minX-origin.x)*(1/direction.x);
        minty=(minY-origin.y)*(1/direction.y);
        mintz=(minZ-origin.z)*(1/direction.z);
    }
    else
    {
     mintx=(minX-origin.x)/direction.x;
     minty=(minY-origin.y)/direction.y;
     mintz=(minZ-origin.z)/direction.z;
    }
    float tmin;
    if(mintx>minty)
        tmin=mintx;
    else
        tmin=minty;

    float maxtx;
    float maxty;
    float maxtz;
    if(direction.x==0 && direction.y==0 && direction.z==0)
    {
        maxtx=(maxX-origin.x)*(1/direction.x);
        maxty=(maxY-origin.y)*(1/direction.y);
        maxtz=(maxZ-origin.z)*(1/direction.z);
    }
    else
    {
        maxtx=(maxX-origin.x)/direction.x;
        maxty=(maxY-origin.y)/direction.y;
        maxtz=(maxZ-origin.z)/direction.z;
    }
    float tmax;

    if(maxtx<maxty)
        tmax=maxtx;
    else
        tmax=maxty;

    if(mintx>maxty ||  minty>maxtx)
        return false;

    if(tmin>maxtz || mintz>tmax)
        return false;

    if(mintz>tmin)
        tmin=mintz;
    if(maxtz<tmin)
        tmin=maxtz;

    return true;
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//  @RayBoxIntersection::IsPointInsideBoundingBox()
//-------------------------------------------------------------------------------
bool
RayBoxIntersection::IsPointInsideBoundingBox(const IvVector3 &point, const BoundingBox &boundingBox)
{
    float minX=boundingBox.min.x;
    float minY=boundingBox.min.y;
    float minZ=boundingBox.min.z;
    
    float maxX=boundingBox.max.x;
    float maxY=boundingBox.max.y;
    float maxZ=boundingBox.max.z;
    
    return (point.x>=minX && point.x<=maxX) && (point.y>=minY && point.y<=maxY) && (point.z>=minZ && point.z<=maxZ);
}
//-------------------------------------------------------------------------------
//  @RayBoxIntersection::Distance()
//-------------------------------------------------------------------------------
float
RayBoxIntersection::Distance(const IvVector3& point1,const IvVector3& point2)
{
    float distance= (point2.x-point1.x)*(point2.x-point1.x)+(point2.y-point1.y)*(point2.y-point1.y)+(point2.z-point1.z)*(point2.z-point1.z);
    return distance;
}
//-------------------------------------------------------------------------------
//  @RayBoxIntersection::I()
//-------------------------------------------------------------------------------
bool
RayBoxIntersection::IsCollision(const IvVector3& mouseCoordinates,const BoundingBox &boundingBox)
{
    
    IvVector3 cameraPosition=IvVector3(-1,-0.1,-1);
    
    IvRay3 ray2(cameraPosition,mouseCoordinates);
    if(IsRayIntersectingBox(ray2, boundingBox))
        return true;
    return false;
}
