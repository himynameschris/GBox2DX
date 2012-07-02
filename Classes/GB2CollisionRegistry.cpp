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
#include "GB2CollisionRegistry.h"

#include <iostream>
#include "stdio.h"

using namespace std;

USING_NS_GB;

GB2CollisionRegistry* theCollisionRegistry()
{
    static GB2CollisionRegistry* instance = new GB2CollisionRegistry();
    return instance;
}

GB2CollisionRegistry::GB2CollisionRegistry()
{
}

bool GB2CollisionRegistry::registerCollision(const char *name, GB2ContactCallbackBase *callBack)
{
    cocos2d::CCLog("registering %s as %i", name, (long)callBack);
    mCallBackMap[std::string(name)] = callBack;
    return true;
}

void GB2CollisionRegistry::callCollision(GB2Node *from, GB2Node *to, GB2Collision *c, const char *beginEnd)
{
    const char *nameA = from->nameForObject();
    const char *nameB = to->nameForObject();
    char functionName[255];
	sprintf(functionName, "%s::%sContactWith%s", nameA, beginEnd, nameB);

    map<string,GB2ContactCallbackBase*>::const_iterator it = mCallBackMap.find(functionName);
    if(it != mCallBackMap.end())
    {
		cocos2d::CCLog("calling: %s", functionName);
        (*it).second->collide(from, to, c);
    }
}