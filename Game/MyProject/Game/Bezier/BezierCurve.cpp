//===============================================================================
// @ BezierCurve.cpp
// ------------------------------------------------------------------------------
// BezierCurve object
//
// Copyright (C) 2008-2015 by James M. Van Verth and Lars M. Bishop.
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This example demonstrates the three basic transforms and how they interact
// with each other.   At each frame we append transforms to the current matrix,
// which is stored for the next frame.  The key commands are:
//
// I, K - translate in x
// J, L - translate in y
// U, O - rotate around z axis
// P, : - uniformly scale
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "BezierCurve.hpp"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ BezierCurve::BezierCurve()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
BezierCurve::BezierCurve()
{
    initializeCurve();
    Point p;
    p.position = {0, 0, 0};
    p.isControl = true;
    addPoint(1, p);
    
    
}   // End of BezierCurve::BezierCurve()


void BezierCurve::initializeCurve()
{
    Point p1, p2;
    p1.position = {-4, 0, 0};
    p2.position = {0, 0, 4};
    
    points.push_back(p1);
    points.push_back(p2);
}

BezierCurve::~BezierCurve()
{
    
}

void BezierCurve::addPoint(int position, Point p)
{
    if (position == 0 || position == points.size())
        if (p.isControl == true)
            return;
        
    points.insert(points.begin() + position, p);
}

void BezierCurve::deletePoint(int pointIndex)
{
    if (pointIndex > points.size() - 1)
        return;
    
    points.erase(points.begin() + pointIndex);
}

void
BezierCurve::Update( float dt )
{
    // get change in transform for this frame
    IvMatrix44 scale, rotate, xlate;
    scale.Identity();
    rotate.Identity();
    float s = 1.0f;
    float r = 0.0f;
    float x = 0.0f, y = 0.0f, z = 0.0f;
    
    // set up scaling
    if (IvGame::mGame->mEventHandler->IsKeyDown(';'))
    {
        s -= 0.25f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('p'))
    {
        s += 0.25f*dt;
    }
    scale.Scaling( IvVector3(s, s, s) );
    
    // set up rotate
    if (IvGame::mGame->mEventHandler->IsKeyDown('o'))
    {
        r -= kPI*0.25f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('u'))
    {
        r += kPI*0.25f*dt;
    }
    rotate.RotationZ( r );
    
    // set up translation
    if (IvGame::mGame->mEventHandler->IsKeyDown('k'))
    {
        x -= 3.0f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('i'))
    {
        x += 3.0f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('l'))
    {
        y -= 3.0f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('j'))
    {
        y += 3.0f*dt;
    }
    IvVector3 xlatevector(x,y,z);
    xlate.Translation( xlatevector );
    
    // clear transform
    if (IvGame::mGame->mEventHandler->IsKeyPressed(' '))
    {
        mTransform.Identity();
    }
    
    // append transforms for this frame to current transform
    // note order: mTransform is applied first, then scale, then rotate, then xlate
    mTransform = xlate*rotate*scale*mTransform;
    
}   // End of BezierCurve::Update()


//-------------------------------------------------------------------------------
// @ BezierCurve::Render()
//-------------------------------------------------------------------------------
// Render stuff
//-------------------------------------------------------------------------------
void
BezierCurve::Render()
{
    IvRenderer::mRenderer->SetWorldMatrix( mTransform );
    
    buildCurve();
    Draw();
}

IvVector3 BezierCurve::lerp(IvVector3& a, IvVector3& b, float t)
{
    float cx = (float)a.x + (float)(b.x - a.x) * t;
    float cz = (float)a.z + (float)(b.z - a.z) * t;
    
    return {cx, 0, cz};
}

IvVector3 BezierCurve::getPointFromLine(float t, vector<IvVector3>& line)
{
    std::vector<IvVector3> remainingPoints;
    for(int i = 0; i < line.size() - 1; i++)
    {
        remainingPoints.push_back(lerp(line[i], line[i+1], t));
    }
    
    if (remainingPoints.size() > 1)
        getPointFromLine(t, remainingPoints);
    
    return remainingPoints[0];
}

void BezierCurve::extractPoints(vector<IvVector3>& line)
{
    float tStep = 0.1f;
    for(float t = tStep; t <= 1 - tStep; t += tStep)
    {
        renderPoints.push_back(getPointFromLine(t, line));
    }
}

void BezierCurve::buildCurve()
{
    renderPoints.clear();
    int lastFixedPointIndex = 0;
    vector<IvVector3> curvePart;
    curvePart.push_back(points[lastFixedPointIndex].position);
    
    for(int i = 1; i < points.size(); i++)
    {
        
        if(points[i].isControl == false)
        {
            lastFixedPointIndex = i;
            curvePart.push_back(points[i].position);
            extractPoints(curvePart);
            curvePart.clear();
        }
        else
            curvePart.push_back(points[i].position);
    }
}


void BezierCurve::Draw()
{
    
  
    size_t currentOffset = IvStackAllocator::mScratchAllocator->GetCurrentOffset();
    IvCPVertex* dataPtr = (IvCPVertex*) IvStackAllocator::mScratchAllocator->Allocate(kIvVFSize[kCPFormat] * renderPoints.size());
    
    if (nullptr == dataPtr)
    {
        return;
    }
    
    for(int i = 0; i < renderPoints.size(); i++)
    {
        dataPtr[i].position = renderPoints[i];
        dataPtr[i].color.Set(255, 0, 0, 255);
    }
    
    
    IvVertexBuffer* axesVerts = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(kCPFormat, (unsigned int)renderPoints.size(), dataPtr,
                                                                                kImmutableUsage);
    
    IvStackAllocator::mScratchAllocator->Reset(currentOffset);
    
    
    IvSetWorldIdentity();
    
    // clear to default shader
    IvShaderProgram* oldShader = IvRenderer::mRenderer->GetShaderProgram();
    IvRenderer::mRenderer->SetShaderProgram(0);
    
    // draw it
    IvRenderer::mRenderer->Draw(kLineListPrim, axesVerts);
    
    // restore original shader
    IvRenderer::mRenderer->SetShaderProgram(oldShader);

}
