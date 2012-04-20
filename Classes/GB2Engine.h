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
#ifndef __GB2ENGINE_H__
#define __GB2ENGINE_H__

#include "cocos2d.h"
#include "../../Box2d/Box2D.h"
#include "GB2Config.h"
#include "GB2Node.h"
#include "GB2WorldContactListener.h"

//extern float PTM_RATIO;

typedef void(GB2NodeCallBack)(GB2Node*);

class GB2Engine : public CCObject
{
public:
	/**
	 * Access to the b2World object
	 */
	CC_SYNTHESIZE(b2World*, world, world);  
	CC_SYNTHESIZE(GB2WorldContactListener*, worldContactListener, WorldContactListener);

	/**
	 * Returns the shared instance
	 */
	static GB2Engine* sharedInstance();
	static GB2Engine* init();

	/**
	 * Delete all objects in the world
	 * including the world
	 */
	void deleteWorld();

	/**
	 * Delete all objects
	 */
	void deleteAllObjects();


	void update(ccTime dt);

	/**
	 * Iterate all objects and performs the block with the object
	 */
	void iterateObjectsWithBlock(GB2NodeCallBack *callback);

	SEL_CallFuncND *findSelector(CCString name);
	void addSelector(CCString *name, SEL_CallFuncND func);

protected:
	//GB2WorldContactListener *worldContactListener;
	//std::map <CCString*, SEL_CallFuncND*> *_selectors;
	//b2World *world;

};

#endif  // __GB2ENGINE_H__