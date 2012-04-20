/*
 MIT License
 
 Copyright (c) 2010 Andreas Loew / www.code-and-web.de
 
 For more information about htis module visit
 http://www.PhysicsEditor.de

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

#include "Box2D.h"
#include "GB2Contact.h"
#include "GB2WorldContactListener.h"
#include "GB2Action.h"
#include <sstream>

using namespace std;

GB2WorldContactListener::GB2WorldContactListener()
: b2ContactListener()
{
}

GB2WorldContactListener::~GB2WorldContactListener() 
{
}

/**
 * Calls constructed selectors on the objects involved in the collision
 *
 * If a is an object of type A, and b is object of type B this method will
 * call 
 *
 * universal selector:
 *    [a <contactType>:gb2contactB];
 *    [b <contactType>:gb2contactA];
 *
 * typed selector:
 *    [a <contactType>WithB:gb2contactB];
 *    [b <contactType>WithA:gb2contactA];
 *
 * @param contact the b2Contact 
 * @param contactType string containing "beginContact", "endContact" or "presolveContact"
 */
void GB2WorldContactListener::notifyObjects(b2Contact *contact, int contactType)
{
	
	//current version: all contact logic is contained within one function in each class 
	
	//first step, determine contact type
	//CCLog("contact notification type: %i", contactType);
	
	//grab nodes from b2Contact
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	
	GB2Node *nodeA = (GB2Node *)(bodyA->GetUserData());
	GB2Node *nodeB = (GB2Node *)(bodyB->GetUserData());

	GB2Contact *contactWithA = GB2Contact::contactWithObject(nodeB, contact->GetFixtureB(), nodeA, contact->GetFixtureA(), contact, contactType);
	GB2Contact *contactWithB = GB2Contact::contactWithObject(nodeA, contact->GetFixtureA(), nodeB, contact->GetFixtureB(), contact, contactType);
	
	if(bodyA->GetUserData() != NULL)
	{
		nodeA->Contact(contactWithB);
	}

	if(bodyB->GetUserData() != NULL)
	{
		nodeB->Contact(contactWithA);
	}
	
	/*
	switch(nodeA->getobjTag())
	{
	case 1:
		((Object *)contact->GetFixtureA()->GetBody()->GetUserData())->Contact(contactWithB);
		break;
	case 2:
		((Floor *)contact->GetFixtureA()->GetBody()->GetUserData())->Contact(contactWithB);
		break;
	case 3:
		((Monkey *)contact->GetFixtureA()->GetBody()->GetUserData())->Contact(contactWithB);
		break;
	default:
		nodeA->Contact(contactWithB);
		break;
	}

	switch(nodeB->getobjTag())
	{
	case 1:
		((Object *)contact->GetFixtureB()->GetBody()->GetUserData())->Contact(contactWithA);
		break;
	case 2:
		((Floor *)contact->GetFixtureB()->GetBody()->GetUserData())->Contact(contactWithA);
		break;
	case 3:
		((Monkey *)contact->GetFixtureA()->GetBody()->GetUserData())->Contact(contactWithA);
		break;
	default:
		nodeB->Contact(contactWithA);
		break;
	}
	
	*/

	/*
	Channon: cocos2dx dynamic selectors, having an issue with class inheritance
	CCLog("NOTIFIED");

	SEL_CallFuncND cfs = callfuncND_selector(GB2Node::Contact);

	CCCallFuncND *cf = CCCallFuncND::actionWithTarget((GB2Node *)contact->GetFixtureA()->GetBody()->GetUserData(), cfs, contact->GetFixtureA()->GetBody()->GetUserData());
	
	cf->execute();

	cf->release();
	*/


	/*
	Version from Anreas Loew's Original Objective C
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    
    GB2Node *a = (GB2Node *)bodyA->GetUserData();
    GB2Node *b = (GB2Node *)bodyB->GetUserData();
    
	
	CCString *nameContactUniversal = contactType;
    CCString *nameContactA = [NSString stringWithFormat:@"%@With%@:", contactType, NSStringFromClass([a class])];
    CCString *nameContactB = [NSString stringWithFormat:@"%@With%@:", contactType, NSStringFromClass([b class])];
    
    SEL selectorContactWithB = NSSelectorFromString(nameContactB);
    SEL selectorContactUniversal = NSSelectorFromString(nameContactUniversal);
    if([a respondsToSelector:selectorContactWithB])
    {
        // perform designated contact listener
        GB2Contact *contactWithB = [GB2Contact contactWithObject:a 
                                                ownFixture:contact->GetFixtureA() 
                                               otherObject:b  
                                              otherFixture:contact->GetFixtureB()
                                                 b2Contact:contact
                                 ];    
        [a performSelector:selectorContactWithB withObject:contactWithB];
    }        
    else if([a respondsToSelector:selectorContactUniversal])
    {
        // perform universal contact listener
        GB2Contact *contactWithB = [GB2Contact contactWithObject:a 
                                                ownFixture:contact->GetFixtureA() 
                                               otherObject:b  
                                              otherFixture:contact->GetFixtureB()
                                                 b2Contact:contact
                                ];    
        [a performSelector:selectorContactUniversal withObject:contactWithB];        
    }
    
    SEL selectorContactWithA = NSSelectorFromString(nameContactA);
    if([b respondsToSelector:selectorContactWithA])
    {
        // perform designated contact listener
        GB2Contact *contactWithA = [GB2Contact contactWithObject:b 
                                                ownFixture:contact->GetFixtureB() 
                                               otherObject:a  
                                              otherFixture:contact->GetFixtureA()
                                                 b2Contact:contact
                                 ];
        [b performSelector:selectorContactWithA withObject:contactWithA];
    }    
    else if([b respondsToSelector:selectorContactUniversal])
    {
        // perform universal contact listener
        GB2Contact *contactWithA = [GB2Contact contactWithObject:b 
                                                ownFixture:contact->GetFixtureB()
                                               otherObject:a
                                              otherFixture:contact->GetFixtureA()
                                                 b2Contact:contact
                                 ];
        [b performSelector:selectorContactUniversal withObject:contactWithA];        
    }
	*/
}

/// Called when two fixtures begin to touch.
void GB2WorldContactListener::BeginContact(b2Contact* contact) 
{
    notifyObjects(contact, 1);        
}

/// Called when two fixtures cease to touch.
void GB2WorldContactListener::EndContact(b2Contact* contact) 
{ 
    notifyObjects(contact, 2);
}

/// This is called after a contact is updated. This allows you to inspect a
/// contact before it goes to the solver. If you are careful, you can modify the
/// contact manifold (e.g. disable contact).
/// A copy of the old manifold is provided so that you can detect changes.
/// Note: this is called only for awake bodies.
/// Note: this is called even when the number of contact points is zero.
/// Note: this is not called for sensors.
/// Note: if you set the number of contact points to zero, you will not
/// get an EndContact callback. However, you may get a BeginContact callback
/// the next step.
void GB2WorldContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    B2_NOT_USED(contact);
    B2_NOT_USED(oldManifold);

    notifyObjects(contact, 0);        
}

/// This lets you inspect a contact after the solver is finished. This is useful
/// for inspecting impulses.
/// Note: the contact manifold does not include time of impact impulses, which can be
/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
/// in a separate data structure.
/// Note: this is only called for contacts that are touching, solid, and awake.
void GB2WorldContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    B2_NOT_USED(contact);
    B2_NOT_USED(impulse);
}


