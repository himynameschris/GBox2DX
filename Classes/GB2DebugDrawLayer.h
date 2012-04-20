/*
 MIT License
 
 Copyright (c) 2010 Andreas Loew / www.code-and-web.de
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
#ifndef __GB2DEBUGDRAWLAYER_H__
#define __GB2DEBUGDRAWLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class b2World;
class GLESDebugDraw;

/** 
 * Debug draw layer 
 * Wraps the GLESDebugDraw in an CCLayer
 * Detects retina display
 */

class GB2DebugDrawLayer : public CCLayer
{
protected:
	CC_SYNTHESIZE(b2World*, _world, World);  
	CC_SYNTHESIZE(GLESDebugDraw*, _debugDraw, DebugDraw); 

	~GB2DebugDrawLayer();
	static GB2DebugDrawLayer* init();
	void draw();

public:
	//b2World *world;                 //!< weak reference to the world
    //GLESDebugDraw *debugDraw;       //!< weak reference to a GLESDebugDraw
};


#endif