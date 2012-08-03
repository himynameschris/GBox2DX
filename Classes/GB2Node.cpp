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
#include "GB2Node.h"
#include "GB2Engine.h"
#include "GB2ShapeCache.h"
#include "GB2Helper.h"

USING_NS_GB;

GB2Node::GB2Node(void)
{
	_body = NULL;
	_world = NULL;
	ccNode = NULL;
}

GB2Node::~GB2Node()
{
	
}

GB2Node * GB2Node::node()
{
	GB2Node * gbnode = new GB2Node();
	if(gbnode && gbnode->init())
	{
		gbnode->autorelease();
		return gbnode;
	}
	CC_SAFE_DELETE(gbnode);
	return NULL;
}

bool GB2Node::init()
{
	_world = GB2Engine::sharedInstance()->getworld();
	deleteLater = false;
	_tag = -1;
	_animPhase = 0;
	return true;
}

GB2Node * GB2Node::nodeFromShapeNameandSprite(CCString *shape, b2BodyType bodyType, CCNode *node)
{	
	GB2Node * gbnode = new GB2Node();
	if(gbnode && gbnode->initWithShapeNameAndSprite(shape, bodyType, node))
	{
		gbnode->autorelease();
		return gbnode;
	}
	CC_SAFE_DELETE(gbnode);
	return NULL;
}

bool GB2Node::initWithShapeNameAndSprite(CCString *shape, b2BodyType bodyType, CCNode *node)
{
	init();

	b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        bodyDef.position.Set(0,0);
        bodyDef.angle = 0;

	_body = _world->CreateBody(&bodyDef);
	
	_body->SetUserData(this);

	ccNode = node;
	
	if(shape)
    {
        setBodyShape(shape);            
    }

	return true;
}

void GB2Node::addEdgeFrom(b2Vec2 start, b2Vec2 end)
{
	b2PolygonShape *edgeShape = new b2PolygonShape();

	b2Vec2 vertices[2];

	vertices[0].Set(start.x, start.y);
	vertices[1].Set(end.x, end.y);

    //edgeShape.SetAsEdge(start, end);
	//edgeShape->Set(vertices, 2);
	edgeShape->SetAsBox(0, end.y-start.y, start, 0);

    _body->CreateFixture(edgeShape,0);

}

void GB2Node::addBoxFrom(b2Vec2 start, b2Vec2 end)
{
	b2PolygonShape *edgeShape = new b2PolygonShape();

	//b2Vec2 vertices[2];

	//vertices[0].Set(start.x, start.y);
	//vertices[1].Set(end.x, end.y);

    //edgeShape.SetAsEdge(start, end);
	//edgeShape->Set(vertices, 2);
	edgeShape->SetAsBox(end.x - start.y, end.y-start.y, start, 0);

    _body->CreateFixture(edgeShape,0);

}

GB2Node* GB2Node::initWithNode(CCNode *node)
{
	return nodeFromShapeNameandSprite(NULL, b2_dynamicBody, node);
}

GB2Node* GB2Node::initWithDynamicBody(CCString *shape, CCNode *node)
{
	return nodeFromShapeNameandSprite(shape, b2_dynamicBody, node);
}

GB2Node* GB2Node::initWithStaticBody(CCString *shape, CCNode *node)
{
	return nodeFromShapeNameandSprite(shape, b2_staticBody, node);
}

GB2Node* GB2Node::initWithKinematicBody(CCString *shape, CCNode *node)
{
	return nodeFromShapeNameandSprite(shape, b2_kinematicBody, node);
}

void GB2Node::destroyBody()
{
	if(_body)
	{
		_world->DestroyBody(_body);
		_body = NULL;

	}
}

void GB2Node::deleteNow()
{
	// remove object from cocos2d parent node
	ccNode->removeFromParentAndCleanup(true);

	this->ccNode = NULL;

	// delete the body
	destroyBody();
}

CCAction *GB2Node::runAction(CCAction *action)
{
    return ccNode->runAction(action);
}

void GB2Node::stopAllActions()
{
	ccNode->stopAllActions();
}

void GB2Node::stopAction(CCAction *action)
{
	ccNode->stopAction(action);
}

void GB2Node::setParent(CCNode *parent)
{
    parent->addChild(ccNode);
}

void GB2Node::setParent(CCNode *parent, float z)
{
    parent->addChild(ccNode,z);    
}

float GB2Node::widthInM()
{
	return ccNode->getContentSize().width / PTM_RATIO;
}

void GB2Node::setLinearDamping(float linearDamping)
{
    _body->SetLinearDamping(linearDamping);    
}

void GB2Node::setAngularDamping(float angularDamping)
{
    _body->SetAngularDamping(angularDamping);    
}

void GB2Node::setBodyShape(CCString *shapeName)
{
    b2Fixture *f;
    while((f = _body->GetFixtureList()))
    {
        _body->DestroyFixture(f);        
    }
    
    if(shapeName)
    {
		GB2ShapeCache *shapeCache = GB2ShapeCache::sharedGB2ShapeCache();
		shapeCache->addFixturesToBody(_body, shapeName->getCString());
		ccNode->setAnchorPoint(shapeCache->anchorPointForShape(shapeName->getCString()));        
    }
}

void GB2Node::setScale(float scale)
{
    // currently only graphics
	ccNode->setScale(scale);
}

b2Fixture *GB2Node::addFixture(b2FixtureDef *fixtureDef)
{
    return _body->CreateFixture(fixtureDef);
}

void GB2Node::setBodyAndType(CCString *shapeName, b2BodyType bodyType, b2Vec2 pos)
{
	assert(_body);
	this->setBodyShape(shapeName);
	this->setBodyType(bodyType);
	this->setPhysicsPosition(pos);
}

void GB2Node::clrCollisionMaskBits(uint16 bits, CCString *fixtureId)
{
    b2Fixture *f = _body->GetFixtureList();
    while(f)
    {
        if(!fixtureId  || (fixtureId->isEqual((CCString *)f->GetUserData())))
        {
            b2Filter filter = f->GetFilterData();
            filter.maskBits &= ~bits;        
            f->SetFilterData(filter);
        }
        f = f->GetNext();            
    }  
}

void GB2Node::addCollisionMaskBits(uint16 bits, CCString *fixtureId)
{
    b2Fixture *f = _body->GetFixtureList();
    while(f)
    {
        if(!fixtureId || (fixtureId->isEqual((CCString *)f->GetUserData())))
        {
            b2Filter filter = f->GetFilterData();
            filter.maskBits |= bits;        
            f->SetFilterData(filter);
        }
        f = f->GetNext();            
    } 
}

void GB2Node::setCollisionMaskBits(uint16 bits, CCString *fixtureId)
{
    b2Fixture *f = _body->GetFixtureList();
    while(f)
    {
        if(!fixtureId || (fixtureId->isEqual((CCString *)f->GetUserData())))
        {
            b2Filter filter = f->GetFilterData();
            filter.maskBits = bits;        
            f->SetFilterData(filter);
        }
        f = f->GetNext();            
    } 
}

void GB2Node::setCollisionMaskBits(uint16 bits)
{
    this->setCollisionMaskBits(bits, NULL);
}

void GB2Node::clrCollisionMaskBits(uint16 bits)
{
    this->clrCollisionMaskBits(bits, NULL);
}

void GB2Node::addCollisionMaskBits(uint16 bits)
{
    this->addCollisionMaskBits(bits, NULL);
}

void GB2Node::addCollisionCategoryBits(uint16 bits)
{
    this->addCollisionCategoryBits(bits, NULL);
}

void GB2Node::clrCollisionCategoryBits(uint16 bits)
{
    this->clrCollisionCategoryBits(bits, NULL);
}

void GB2Node::setCollisionCategoryBits(uint16 bits)
{
    this->setCollisionCategoryBits(bits, NULL);
}

void GB2Node::addCollisionCategoryBits(uint16 bits, CCString *fixtureId)
{
    b2Fixture *f = _body->GetFixtureList();
    while(f)
    {
        if(!fixtureId || (fixtureId->isEqual((CCString *)f->GetUserData())))
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits |= bits;        
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }        
}

void GB2Node::clrCollisionCategoryBits(uint16 bits, CCString *fixtureId)
{
    b2Fixture *f = _body->GetFixtureList();
    while(f)
    {
        if(!fixtureId || (fixtureId->isEqual((CCString *)f->GetUserData())))
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits &= ~bits;        
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }        
}

void GB2Node::setCollisionCategoryBits(uint16 bits, CCString *fixtureId)
{
    b2Fixture *f = _body->GetFixtureList();
    while(f)
    {
        if(!fixtureId || (fixtureId->isEqual((CCString *)f->GetUserData())))
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits = bits;        
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }        
}

void GB2Node::setKinematicBody(CCString *shapeName, b2Vec2 pos)
{
    this->setBodyAndType(shapeName, b2_kinematicBody, pos);
}

void GB2Node::setDynamicBody(CCString *shapeName, b2Vec2 pos)
{
    this->setBodyAndType(shapeName, b2_dynamicBody, pos);
}

void GB2Node::setStaticBody(CCString *shapeName, b2Vec2 pos)
{
    this->setBodyAndType(shapeName, b2_staticBody, pos);    
}

void GB2Node::updateCCFromPhysics(float dt)
{
	//CCLog("GB2Node::updateCCFromPhysics");
    b2Vec2 position = _body->GetPosition();
    if(ccNode != NULL)
	{
		ccNode->setPosition(ccp(PTM_RATIO*position.x, PTM_RATIO*position.y));
		ccNode->setRotation(-1 * CC_RADIANS_TO_DEGREES(_body->GetAngle()));
	}
}

void GB2Node::setFixedRotation(bool fixedRotation)
{
    assert(_body);
    _body->SetFixedRotation(fixedRotation);
}

void GB2Node::setLinearVelocity(b2Vec2 velocity)
{
    assert(_body);
    _body->SetLinearVelocity(velocity);
}

void GB2Node::applyLinearImpulse(b2Vec2 impulse, b2Vec2 point)
{
    assert(_body);
    _body->ApplyLinearImpulse(impulse, point);
}

b2Vec2 GB2Node::physicsPosition()
{
    assert(_body);
    return _body->GetPosition();
}

b2Vec2 GB2Node::worldCenter()
{
    assert(_body);
    return _body->GetWorldCenter();
}

float GB2Node::mass()
{
    assert(_body);
    return _body->GetMass();
}

void GB2Node::setBodyType(b2BodyType bodyType)
{
    assert(_body);
    _body->SetType(bodyType);
}

bool GB2Node::isAwake()
{
    return _body->IsAwake();
}

void GB2Node::applyForce(b2Vec2 force, b2Vec2 point)
{
    assert(_body);
    _body->ApplyForce(force, point);
}

float GB2Node::angle()
{
    assert(_body);
    return _body->GetAngle();
}

void GB2Node::setTransform(b2Vec2 pos, float angle)
{
    assert(_body);
    _body->SetTransform(pos, angle);
}

void GB2Node::setAngle(float angle)
{
    _body->SetTransform(_body->GetWorldCenter(), angle);
}

void GB2Node::setPhysicsPosition(b2Vec2 pos)
{
    assert(_body);
    ccNode->setPosition(CCPointFromb2Vec2(pos));
    _body->SetTransform(pos, _body->GetAngle());
}

void GB2Node::setCcPosition(CCPoint pos)
{
    assert(_body);
	ccNode->setPosition(pos);
    _body->SetTransform(b2Vec2FromCCPoint(pos), _body->GetAngle());
}

CCPoint GB2Node::ccPosition()
{
    return ccNode->getPosition();;
}

bool GB2Node::active()
{
    return _body->IsActive();
}

void GB2Node::setActive(bool isActive)
{
	_body->SetActive(isActive);    
}

bool GB2Node::awake()
{
    return _body->IsAwake();
}

b2Vec2 GB2Node::linearVelocity()
{
    return _body->GetLinearVelocity();
}

void shapeCacheFixtureUserdataForValue()
{
    return;
}

void GB2Node::setBullet(bool bulletFlag)
{
    _body->SetBullet(bulletFlag);
}

b2Fixture *GB2Node::createFixture(const b2FixtureDef *fixtureDef)
{
    return _body->CreateFixture(fixtureDef);
}

int GB2Node::objectTag()
{
    return _objectTag;
}

void GB2Node::setObjectTag(int aTag)
{
    _objectTag = aTag;
}

void GB2Node::setAngularVelocity(float32 v)
{
    _body->SetAngularVelocity(v);
}

void GB2Node::setVisible(bool isVisible)
{
	ccNode->setVisible(isVisible);
}

void GB2Node::setDisplayFrame(CCSpriteFrame *newFrame)
{
	((CCSprite *)ccNode)->setDisplayFrame(newFrame);
}

void GB2Node::setDisplayFrameNamed(CCString *name)
{
	((CCSprite *)ccNode)->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
}