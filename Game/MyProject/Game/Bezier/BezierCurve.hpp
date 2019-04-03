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
#include <IvRendererHelp.h>
#include <IvBezier.h>
#include "Game.h"

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class BezierCurve : IvBezier
{
public:
    BezierCurve();
    ~BezierCurve();
    
    void Update( float dt );
    void Render();
    
private:
    IvMatrix44  mTransform;
};

