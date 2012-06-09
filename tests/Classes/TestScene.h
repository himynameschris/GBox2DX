#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "cocos2d.h"
#include "../../Box2D/Box2D.h"
#include "../../GBox2D/GBox2D.h"
#include "TestScreenEdge.h"

class TestScene : public cocos2d::CCLayer
{
protected:
	float counter;
	TestScreenEdge *_wall;

public:
	TestScene();

	CC_SYNTHESIZE(b2World*, _world, World);
	CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode*, _batchNode, BatchNode);
	//CC_SYNTHESIZE(GB2Node*, _node, Node);

	virtual bool init();
	static cocos2d::CCScene* scene();
	void update(ccTime dt);

	void createWall();

	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
	void fireBullet(float y);

	void setupWorld();

	LAYER_NODE_FUNC(TestScene);

	void loadPVR(string name);
	void loadPhysics(string name);

	cocos2d::CCSprite* loadSprite(string name);

	GB2Node* createNode(string name, cocos2d::CCSprite *node);

	void enableDebug();

	void runTest();
};

#endif