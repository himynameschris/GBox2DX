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
#ifndef __GB2SPRITE_H__
#define __GB2SPRITE_H__

#include "cocos2d.h"
#include "GB2Node.h"

class GB2Sprite : public GB2Node
{
public:
	
	
	/**
	 * Create a GB2Sprite with the given shape and dispay frame name.
	 * The body is created as dynamic body
	 * @param shape shape name for the body
	 * @param spriteName name of the sprite
	 */
	static GB2Sprite *initWithDynamicBody(CCString *shape, CCString *spriteName);
	static GB2Sprite *initWithStaticBody(CCString *shape, CCString *spriteName);
	static GB2Sprite *initWithKinematicBody(CCString *shape, CCString *spriteName);

	/**
	 * Create a GB2Sprite with the given shape and dispay frame name.
	 * The body is created as dynamic body
	 * @param shape shape name for the body
	 * @param spriteName name of the sprite
	 */
	static GB2Sprite *spriteWithDynamicBody(CCString *shape, CCString *spriteName);
	static GB2Sprite *spriteWithStaticBody(CCString *shape, CCString *spriteName);
	static GB2Sprite *spriteWithKinematicBody(CCString *shape, CCString *spriteName);

	void setDisplayFrame(CCSpriteFrame *newFrame);
	void setDisplayFrameNamed(CCString *name);

protected:



};
#endif  // __GB2NODE_H__