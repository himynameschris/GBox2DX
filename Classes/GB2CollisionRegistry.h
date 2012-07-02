/*
 MIT License
 
 Copyright (c) 2012 Andreas Loew / www.code-and-web.de
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
#ifndef GB2COLLISIONREGISTRY_H
#define GB2COLLISIONREGISTRY_H

#include <map>
#include <string>

#include "GB2Config.h"
#include "GB2ContactCallback.h"
#include "GB2Node.h"

NS_GB_BEGIN

/**
* A singleton class containing the registered collision callbacks, responsible for registry and calling of collisions
*/
class GB2CollisionRegistry
{
public:
	

	/**
	 * A method to register collisions by name (eg "nodeAbeginContactWithnodeB"
	 * @param name the name of the function to register
	 * @param callBack the class inheriting GB2ContactCallbackBase
	 * @return true if added successfully
	 */
    bool registerCollision(const char *name, GB2ContactCallbackBase *callBack);
    
	/**
	 * The method that will trigger the collision callback, usually called from the contact listener
	 * @param from the object colliding
	 * @param to the object being collided with
	 * @param c the collision object
	 * @param beginEnd the collision phase (pre, begin, end, post)
	 */
	void callCollision(GB2Node *from, GB2Node *to, GB2Collision *c, const char *beginEnd);

	static GB2CollisionRegistry* sharedInstance();

private:
	GB2CollisionRegistry();

    std::map<std::string, GB2ContactCallbackBase *> mCallBackMap; //!< the map containing callback names and handlers
};

NS_GB_END

static gbox2d::GB2CollisionRegistry *instance = NULL;

#endif