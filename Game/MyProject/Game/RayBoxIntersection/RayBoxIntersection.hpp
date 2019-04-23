//-------------------------------------------------------------------------------
//-- RayBoxIntersection.h -------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "IvRay3.h"
#include "IvVector3.h"
#include "IvRendererHelp.h"
#include<iostream>
#include<IvGame.h>
#include<IvEventHandler.h>
//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------
struct BoundingBox
{
    IvVector3 min;
    IvVector3 max;
    IvVector3 center;
};
//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------


class RayBoxIntersection
{
public:
    //constructor/destructor
    RayBoxIntersection(){}
    ~RayBoxIntersection(){}
    
    bool IsRayIntersectingBox(const IvRay3& ray,const BoundingBox& boundingBox);
    bool IsCollision(const IvVector3&,const BoundingBox&);
private:
    IvRay3 ray;
    
    float Distance(const IvVector3& point1,const IvVector3& point2);
    bool  IsPointInsideBoundingBox(const IvVector3& point,const BoundingBox& boundingBox);
    
};
