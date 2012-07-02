//
//  GContactCallback.h
//
//  This class contains the callbacks to call any function inside another class
//  You do not need to use the classes directly. Just use the Macros to register the
//  callbacks
//
//  To register a beginning contact callback use
//
//  BEGIN_COLLISION(A, B)
//  this registers a method A::beginContactWithB(other, collision);
//  which can be called when the contact between A and B begins
//
//  END_COLLISION(A, B)
//  this registers a method A::endContactWithB(other, collision);
//  which can be called when the contact between A and B ends
//
//  Copyright by Andreas Loew / http://www.codeandweb.com
//  Copyright (c) 2012 Chris Hannon / channon.us
//
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
#ifndef GB2CONTACTCALLBACK_H
#define GB2CONTACTCALLBACK_H

#include "GB2Config.h"
#include "GB2Node.h"
#include "GB2CollisionRegistry.h"

NS_GB_BEGIN

class GB2Collision;

/**
 * This class provides an interface to call collision functions
 */
class GB2ContactCallbackBase
{
public:
    virtual ~GB2ContactCallbackBase()
    {}

    virtual void collide( GB2Node *receiver, GB2Node *otherObject, GB2Collision *c ) = 0;
};

/**
 * This template class adapts to the destination object and provides
 * a method to call the registered function
 */
template <class T> class GB2ContactCallback : public GB2ContactCallbackBase
{
public:

    /**
     * Register a callback function to be called from collide()
     * @param ftp pointer to the method to call
     */
    GB2ContactCallback(void(T::*fpt)( GB2Node *otherObject, GB2Collision *c ))
    {
        mFpt=fpt;
    };

    /**
     * Calls the registered collision function on receiver,
     * using otherObject and c as parameter
     * @param receiver object to call the callback on
     * @param otherObject parameter to pass to the callback function
     * @param c collision parameter to pass to the callback object
     */
    virtual void collide(GB2Node *receiver, GB2Node *otherObject, GB2Collision *c)
    {
        T* r = dynamic_cast<T*>(receiver);
        (*r.*mFpt)(otherObject, c);
    };

private:
   void(T::*mFpt)(GB2Node *otherObject, GB2Collision *c);
};

/**
 * Macro to register the A:beginContactWithB()
 * @param A class to call the method on
 * @param B class which A collides with
 */
#define BEGIN_COLLISION(A,B) static bool gBeginContact_##A_##B_registered = GB2CollisionRegistry::sharedInstance()->registerCollision(#A"::beginContactWith"#B,new GB2ContactCallback<A>(&A::begin##ContactWith##B));

/**
 * Macro to register the A:endContactWithB()
 * @param A class to call the method on
 * @param B class which A collides with
 */
#define END_COLLISION(A,B) static bool gEndContact_##A_##B_registered = GB2CollisionRegistry::sharedInstance()->registerCollision(#A"::endContactWith"#B,new GB2ContactCallback<A>(&A::end##ContactWith##B));

/**
 * Macro to register the A:preContactWithB()
 * @param A class to call the method on
 * @param B class which A collides with
 */
#define PRE_COLLISION(A,B) static bool gPreContact_##A_##B_registered = GB2CollisionRegistry::sharedInstance()->registerCollision(#A"::preContactWith"#B,new GB2ContactCallback<A>(&A::pre##ContactWith##B));

/**
 * Macro to register the A:postContactWithB()
 * @param A class to call the method on
 * @param B class which A collides with
 */
#define POST_COLLISION(A,B) static bool gPostContact_##A_##B_registered = GB2CollisionRegistry::sharedInstance()->registerCollision(#A"::postContactWith"#B,new GB2ContactCallback<A>(&A::post##ContactWith##B));

NS_GB_END

#endif //GB2CONTACTCALLBACK_H