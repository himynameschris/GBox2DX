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

#include "GB2Contact.h"
#include "cocos2d.h"

GB2Contact *GB2Contact::initWithObject(GB2Node *object, b2Fixture *ownFixture, GB2Node *otherObject, b2Fixture *otherFixture, b2Contact *contact, int contactType)
{
	GB2Contact *gbcontact = new GB2Contact();

	if(contact)
	{
		gbcontact->setownObject(object);

		//_otherObject = otherObject;
		gbcontact->setotherObject(otherObject);
        
		//_ownFixture = ownFixture;
		gbcontact->setownFixture(ownFixture);

		//_otherFixture = otherFixture;
		gbcontact->setotherFixture(otherFixture);

		//_box2dContact = contact;
		gbcontact->setbox2dContact(contact);

		gbcontact->setContactType(contactType);

		gbcontact->autorelease();
		return gbcontact;
	}
	
	CC_SAFE_DELETE(gbcontact);
	return NULL;
}

GB2Contact *GB2Contact::contactWithObject(GB2Node *object, b2Fixture *ownFixture, GB2Node *otherObject, b2Fixture *otherFixture, b2Contact *contact, int contactType)
{
	return GB2Contact::initWithObject(object, ownFixture, otherObject, otherFixture, contact, contactType);
}

void GB2Contact::setEnabled(bool enabled)
{
	_box2dContact->SetEnabled(enabled);
}

GB2Contact::~GB2Contact()
{
	//CC_SAFE_DELETE(_otherObject);
	
}

void GB2Contact::setotherObject(GB2Node *node)
{
	_otherObject = node;
}

GB2Node *GB2Contact::getotherObject()
{
	return _otherObject;
}

void GB2Contact::setownObject(GB2Node *node)
{
	_ownObject = node;
}

GB2Node *GB2Contact::getownObject()
{
	return _ownObject;
}