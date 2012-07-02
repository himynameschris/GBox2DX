/*
 MIT License
 
 Copyright (c) 2012 Chris Hannon / channon.us
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef GBOX2D_H
#define GBOX2D_H

#include "cocos2d.h"
#include "Box2D.h"

#include "Classes\GB2Config.h"

#include "Classes\GB2Collision.h"
#include "Classes\GB2DebugDrawLayer.h"
#include "Classes\GB2Engine.h"
#include "Classes\GB2Node.h"
#include "Classes\GB2ShapeCache.h"
#include "Classes\GB2WorldContactListener.h"
#include "Classes\GB2Helper.h"
#include "Classes\GB2CollisionRegistry.h"
#include "Classes\GB2Object.h"
#include "Classes\GB2ContactCallback.h"

NS_GB_BEGIN

const char* gbox2dVersion();

NS_GB_END

#endif // GBOX2D_H