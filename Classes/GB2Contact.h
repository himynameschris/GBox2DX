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
#ifndef __GB2CONTACT_H__
#define __GB2CONTACT_H__

#include "cocos2d.h"
#include "../../Box2d/Box2D.h"
#include "GB2Node.h"

class GB2Contact : public CCObject
{
	//CC_SYNTHESIZE(GB2Node*, _otherObject, otherObject);  
	CC_SYNTHESIZE(b2Fixture*, _ownFixture, ownFixture); 
	CC_SYNTHESIZE(b2Fixture*, _otherFixture, otherFixture); 
	CC_SYNTHESIZE(b2Contact*, _box2dContact, box2dContact); 
	CC_SYNTHESIZE(int, _type, ContactType); 

	~GB2Contact();

	static GB2Contact* initWithObject(GB2Node *object, b2Fixture *ownFixture, GB2Node *otherObject, b2Fixture *otherFixture, b2Contact *contact, int contactType);
	static GB2Contact* contactWithObject(GB2Node *object, b2Fixture *ownFixture, GB2Node *otherObject, b2Fixture *otherFixture, b2Contact *contact, int contactType);

	void setEnabled(bool enabled);

	void setotherObject(GB2Node *node);
	GB2Node *getotherObject();

	void setownObject(GB2Node *node);
	GB2Node *getownObject();

protected:
	//b2Fixture *_ownFixture;   /**< the fixture that collided */
    GB2Node *_otherObject;    /**< the other object */
	GB2Node *_ownObject;    /**< the other object */
    //b2Fixture *_otherFixture; /**< the other object's fixture that collided */
    //b2Contact *_box2dContact; /**< the box2d contact structure */
};

#endif  // __GB2CONTACT_H__