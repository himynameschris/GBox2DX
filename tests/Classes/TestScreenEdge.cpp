#include "TestScreenEdge.h"
#include "TestScene.h"

USING_NS_GB;

BEGIN_COLLISION(TestScreenEdge, GB2Node)

TestScreenEdge::TestScreenEdge()
{

}

TestScreenEdge::~TestScreenEdge()
{

}

void TestScreenEdge::beginContactWithGB2Node(GB2Node* otherObject, GB2Collision *c)
{

	CCLog("TestScreenEdge::beginContactWithGB2Node");

	otherObject->setDeleteLater(true);

}

TestScreenEdge * TestScreenEdge::initWithLevelLayer(TestScene *layer)
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	
	TestScreenEdge *s = new TestScreenEdge();
	if(s && s->init())
	{

		s->setLevelLayer(layer);

		b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(0,0);
        bodyDef.angle = 0;

		s->setBody(s->getWorld()->CreateBody(&bodyDef));
		
		s->getBody()->SetUserData(s);

		s->setObjTag(1);

		return s;

	}
	CC_SAFE_DELETE(s);
	return NULL;
	
}