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
    
    int count = 2;
    IvVector3* mPositions = new IvVector3[count];
    mPositions[0] = {0, 0, 0};
    mPositions[1] = {15, 0, 5};
    
    IvVector3* mControls = new IvVector3[2*(count-1)];
    mControls[0] = {14, 0, 0};
    mControls[1] = {-3, 0, 5};
    
    float* mTimes = new float[count];
    mTimes[0] = 2;
    mTimes[1] = 4;
    
   
    Initialize(mPositions, mControls, mTimes, count);
    
}   // End of BezierCurve::BezierCurve()


//-------------------------------------------------------------------------------
// @ BezierCurve::~BezierCurve()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
BezierCurve::~BezierCurve()
{
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
    
    // draw geometry
    IvDrawTeapot();
    
    IvBezier::Render();
    
}
