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
RayBoxIntersection::RayBoxIntersection(const IvRay3& ray):_ray(ray)
{
    
}
//-------------------------------------------------------------------------------
//  @RayBoxIntersection::GetRay()
//-------------------------------------------------------------------------------
IvRay3
RayBoxIntersection::GetRay()
{
    return _ray;
}
//-------------------------------------------------------------------------------
//  @RayBoxIntersection::IsRayIntersectingBox()
//-------------------------------------------------------------------------------
bool
RayBoxIntersection::IsRayIntersectingBox(const BoundingBox& boundingBox)
{
    IvVector3 min=boundingBox.getMin();
    IvVector3 max=boundingBox.getMax();
    
    IvVector3 origin=_ray.GetOrigin();
    IvVector3 direction=_ray.GetDirection();
    
    IvVector3 start;
    start.x = (min.x - origin.x) / direction.x;
    start.y = (min.y - origin.y) / direction.y;
    start.z = (min.z - origin.z) / direction.z;
    
    IvVector3 end;
    end.x = (max.x - origin.x) / direction.x;
    end.y = (max.y - origin.y) / direction.y;
    end.z = (max.z - origin.z) / direction.z;
    
    auto a = IvVector3(std::min(start.x,end.x), std::min(start.y,end.y),std::min(start.z,end.z));
    auto b = IvVector3(std::max(start.x,end.x), std::max(start.y,end.y),std::max(start.z,end.z));
    
    return std::max(a.x,std::max(a.y,a.z)) < std::min(b.x,std::min(b.y,b.z));
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------
