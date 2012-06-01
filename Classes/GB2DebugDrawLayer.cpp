#include "GB2DebugDrawLayer.h"
#include "GB2Engine.h"
#include "GLES-Render.h"
#include "Box2D.h"
#include "GB2Helper.h"

using namespace cocos2d;

enum  	{ 
  e_shapeBit = 0x0001, e_jointBit = 0x0002, e_aabbBit = 0x0004, e_pairBit = 0x0008, 
  e_centerOfMassBit = 0x0010 
};

GB2DebugDrawLayer *GB2DebugDrawLayer::init()
{
    
	GB2DebugDrawLayer *ddlayer = new GB2DebugDrawLayer();
	
	if(ddlayer)
    {

        // take world from the singleton
        //world = [GB2Engine sharedInstance].world;
		b2World *bworld = GB2Engine::sharedInstance()->getworld();

        // Enable debug draw
		GLESDebugDraw *debugDraw = new GLESDebugDraw( PTM_RATIO * CCDirector::sharedDirector()->getContentScaleFactor());
        
        // Set the flags
        uint32 flags = 0;
		
        flags += e_shapeBit;
        // flags += b2DebugDraw::e_aabbBit;
        flags += e_centerOfMassBit;
        
        debugDraw->SetFlags(flags);

		bworld->SetDebugDraw(debugDraw);

		ddlayer->setWorld(bworld);
    }
    return ddlayer;
}

GB2DebugDrawLayer::~GB2DebugDrawLayer()
{
    // remove debug draw from the world
    _world->SetDebugDraw(0);
    
    // delete debug draw
    delete _debugDraw;
    
    // dealloc super objects
    
}

void GB2DebugDrawLayer::draw()
{
	// store render state
	glDisable(GL_TEXTURE_2D);
	glDisableVertexAttribArray(0);
	    
    // draw the world stuff
	_world->DrawDebugData();
    
    // restore render state
	glEnable(GL_TEXTURE_2D);
	glEnableVertexAttribArray(0);
}
