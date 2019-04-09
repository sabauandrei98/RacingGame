//===============================================================================
// @ Player.h
// ------------------------------------------------------------------------------
// Player object
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
//===============================================================================

#pragma once

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvMatrix44.h>
#include <IvRenderer.h>
#include <IvEventHandler.h>
#include <IvMath.h>
#include <IvVector3.h>
#include <IvVector4.h>
#include <IvRendererHelp.h>
#include <IvBezier.h>
#include <vector>
#include <IvResourceManager.h>
#include <IvVector4.h>
#include <IvMatrix33.h>
#include <IvLineSegment3.h>
#include <IvMath.h>
#include <IvQuat.h>
#include <IvStackAllocator.h>
#include <IvVertexFormats.h>
#include <IvVertexBuffer.h>
#include <IvIndexBuffer.h>
#include <IvFileReader.h>
#include <IvShaderProgram.h>
#include <IvUniform.h>
#include <IvImage.h>
#include <IvTexture.h>
#include <IvRenderer.h>
#include <IvRendererOGL.h>
#include "Game.h"

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

struct Point{
    IvVector3 position;
    IvVector4 color = {1.0, 0.0, 0.0, 1.0};
    bool isControl = false;
};

class BezierCurve
{
    
public:
    BezierCurve();
    ~BezierCurve();
    
    void addPoint(int position, Point p);
    void deletePoint(int pointIndex);
    void initializeCurve();
    
    
    void Update( float dt );
    void Render();
    void Draw();
    
private:
    std::vector<Point> points;
    std::vector<IvVector3> renderPoints;
    void buildCurve();
    void extractPoints(vector<IvVector3>& line);
    IvVector3 getPointFromLine(float t, vector<IvVector3>& line);
    IvVector3 lerp(IvVector3& a, IvVector3& b, float t);
    
    
    IvMatrix44  mTransform;
    
};

