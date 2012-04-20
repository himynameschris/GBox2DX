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

#include "GB2Sprite.h"
#include "GB2Engine.h"
#include "GB2ShapeCache.h"

GB2Sprite *GB2Sprite::initWithDynamicBody(CCString *shape, CCString *spriteName)
{
	
	return (GB2Sprite *)GB2Node::initWithDynamicBody(shape, CCSprite::spriteWithSpriteFrameName(spriteName->toStdString().c_str()));

}

GB2Sprite *GB2Sprite::initWithStaticBody(CCString *shape, CCString *spriteName)
{
	
	
	return (GB2Sprite *)GB2Node::initWithStaticBody(shape, CCSprite::spriteWithSpriteFrameName(spriteName->toStdString().c_str()));

}

GB2Sprite *GB2Sprite::initWithKinematicBody(CCString *shape, CCString *spriteName)
{
	
	return (GB2Sprite *)GB2Node::initWithKinematicBody(shape, CCSprite::spriteWithSpriteFrameName(spriteName->toStdString().c_str()));

}

GB2Sprite *GB2Sprite::spriteWithDynamicBody(CCString *shape, CCString *spriteName)
{
	
	return GB2Sprite::initWithDynamicBody(shape, spriteName);

}

GB2Sprite *GB2Sprite::spriteWithStaticBody(CCString *shape, CCString *spriteName)
{
	
	return GB2Sprite::initWithStaticBody(shape, spriteName);

}

GB2Sprite *GB2Sprite::spriteWithKinematicBody(CCString *shape, CCString *spriteName)
{
	
	return GB2Sprite::initWithKinematicBody(shape, spriteName);

}

void GB2Sprite::setDisplayFrame(CCSpriteFrame *newFrame)
{
	((CCSprite *)ccNode)->setDisplayFrame(newFrame);
}

void GB2Sprite::setDisplayFrameNamed(CCString *name)
{
	((CCSprite *)ccNode)->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->toStdString().c_str()));
}