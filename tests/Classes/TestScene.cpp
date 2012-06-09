#include "TestScene.h"
#include "../../GBox2D/GBox2D.h"

using namespace cocos2d;

#define DO_DEBUG

TestScene::TestScene()
{
	
}

CCScene *TestScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        TestScene *layer = TestScene::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
	
}

//typedef CCDictionary<std::string, CCObject*> ObjectDict;

bool TestScene::init()
{
	bool bRet = false;
	do 
    {
		//super init
		CC_BREAK_IF(! CCLayer::init());

		GB2Engine::sharedInstance()->getworld()->SetGravity(b2Vec2(0.0, 0.0));
		
		loadPVR("GBox2DTestSprites");
		loadPhysics("GBox2DTestPhysics");
		
		createWall();

		counter = 0;
		this->scheduleUpdate();
		
#ifdef	DO_DEBUG
		this->addChild(GB2DebugDrawLayer::init(), 30);
#endif
		setIsTouchEnabled( true );

		bRet = true;

	} while (0);

	return bRet;
}

void TestScene::setupWorld()
{
	_world = GB2Engine::sharedInstance()->getworld();
}

void TestScene::createWall()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	_wall = TestScreenEdge::initWithLevelLayer(this);
	//_wall->addEdgeFrom(b2Vec2FromCCPoint(ccp(winSize.width *.9, 0)), b2Vec2FromCCPoint(ccp(winSize.width *.9, winSize.height * PTM_RATIO))); 
	_wall->addEdgeFrom(b2Vec2FromCCPoint(ccp(winSize.width *.9, 0)), b2Vec2FromCCPoint(ccp(winSize.width *.9, winSize.height * PTM_RATIO))); 
	_wall->retain();
}

void TestScene::loadPVR(string name)
{
	_batchNode = CCSpriteBatchNode::batchNodeWithFile((name + ".pvr.ccz").c_str(), 150);
	addChild(_batchNode);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile((name + ".plist").c_str());
}

void TestScene::loadPhysics(string name)
{
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile((name + ".plist").c_str());
}

CCSprite *TestScene::loadSprite(string name)
{
	return CCSprite::spriteWithSpriteFrameName((name+".png").c_str());
}

GB2Node *TestScene::createNode(string name, cocos2d::CCSprite *node)
{
	return GB2Node::nodeFromShapeNameandSprite(&CCString((name).c_str()), b2_dynamicBody, node);
}

void TestScene::update(ccTime dt)
{

}

void TestScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	CCSetIterator it;
	
	for(it=touches->begin(); it!=touches->end(); it++)
	{
		CCTouch *touch = (CCTouch*)(*it);
		
		fireBullet(touch->locationInView().y);
	}

}

void TestScene::fireBullet(float y)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();	
		
	GB2Node * n = createNode("bullet", loadSprite("bullet"));
	n->setFixedRotation(true);
	_batchNode->addChild(n->getCCNode(), 50);
	n->retain();

	n->setPhysicsPosition(b2Vec2FromCCPoint(ccp(-winSize.width * .1, winSize.height - y)));

	n->applyLinearImpulse(b2Vec2(400, 0), n->worldCenter());

}