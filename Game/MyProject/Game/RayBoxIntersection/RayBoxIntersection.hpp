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
#include "BoundingBox.hpp"
#include<iostream>
#include<IvGame.h>
#include<IvEventHandler.h>

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------


class RayBoxIntersection
{
public:
    //constructor/destructor
    RayBoxIntersection(const IvRay3& ray);
    ~RayBoxIntersection(){}
    IvRay3 GetRay();
    
    bool IsRayIntersectingBox(const BoundingBox& boundingBox);
    
private:
    IvRay3 _ray;    
};
