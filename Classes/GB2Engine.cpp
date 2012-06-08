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

#include "Box2D.h"
#include "GB2Contact.h"
#include "GB2Engine.h"
#include "GB2WorldContactListener.h"
#include "GB2Sprite.h"

// default ptm ratio value

#ifndef PTM_RATIO
#define PTM_RATIO 32.0f
#endif

typedef void(GB2NodeCallBack)(GB2Node*);

static GB2Engine *instance = NULL;

GB2Engine *GB2Engine::sharedInstance()
{
	//static GB2Engine* instance = NULL;
	if(!instance)
	{
		instance = GB2Engine::init();
		
	}
	
	return instance;
}

GB2Engine *GB2Engine::init()
{
	GB2Engine *engine = new GB2Engine();
	if(engine)
	{
		b2Vec2 gravity(0.0f, -10.0f);
        bool doSleep = true;    
        
		b2World *w = new b2World(gravity);
		w->SetAllowSleeping(doSleep);
		        
        // get ptmRatio from GB2ShapeCache
        if(GB2_HIGHRES_PHYSICS_SHAPES)
        {
			//PTM_RATIO = GB2ShapeCache::sharedGB2ShapeCache()->getPtmRatio() / 2.0f;            
        }
        else
        {
            //PTM_RATIO = GB2ShapeCache::sharedGB2ShapeCache()->getPtmRatio();
        }
        
        // set the contact listener
		engine->setWorldContactListener(new GB2WorldContactListener());
		w->SetContactListener(engine->getWorldContactListener());    
        
		engine->setworld(w);

        // schedule update
		CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(engine, 0, false);
		
    }

    return engine;

}

void GB2Engine::deleteAllObjects()
{
    // iterate all bodies
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) 
    {      
		if(b->GetUserData() != NULL)
		{
			GB2Node *o = (GB2Node*)(b->GetUserData());
			if(o)
			{
				// destroy physics object
				o->getCCNode()->removeFromParentAndCleanup(true);
				o->setCCNode(NULL);
				
				world->DestroyBody(b);

				o->release();
			}
			else
			{
				// destroy body
				world->DestroyBody(b);
			}
		}
    }
}

void GB2Engine::deleteWorld()
{    
    // delete all objects
    this->deleteAllObjects();
    
    // delete the world
	delete world;
	world = NULL;
    
    // delete the contact listener
	delete this->worldContactListener;
    this->worldContactListener = NULL;
}

void GB2Engine::update(ccTime dt) 
{   
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    
	// step the world
	world->Step(timeStep, velocityIterations, positionIterations);
	
	std::vector<GB2Node *>toDestroy;

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) 
    {        
		
		if(b && b->GetUserData() != NULL)
		{
			GB2Node *obj = (GB2Node *)b->GetUserData();

			obj->updateCCFromPhysics();

			if(obj->getDeleteLater())
			{
				toDestroy.push_back(obj);
			}
		}
    } 
	
	std::vector<GB2Node *>::iterator pos2;
	   for(pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2) {
		   GB2Node *node = *pos2;     
       
			node->deleteNow();

	   }

}

void GB2Engine::iterateObjectsWithBlock(GB2NodeCallBack *callback)
{
	   
}

