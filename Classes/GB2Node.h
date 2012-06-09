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
#ifndef __GB2NODE_H__
#define __GB2NODE_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "GB2ShapeCache.h"

using namespace cocos2d;

class GB2Contact;

class GB2Node : public CCNode
{
public:
	CC_SYNTHESIZE(CCNode*, ccNode, CCNode);  
	CC_SYNTHESIZE(bool, deleteLater, DeleteLater); 
	CC_SYNTHESIZE(b2World*, _world, World); 
	CC_SYNTHESIZE(b2Body*, _body, Body); 
	CC_SYNTHESIZE(int, _tag, ObjTag); 
 	CC_SYNTHESIZE(int, _animPhase, AnimPhase);

	GB2Node();
	~GB2Node();

	bool init();

	GB2Node *node();

	bool initWithShapeNameAndSprite(CCString *shape, b2BodyType bodyType, CCNode *node);
	

	virtual void Contact(GB2Contact *contact);

	/**
	 * Inits the object with a CCNode but no physics object
	 * @param node CCNode which represents the object
	 * @return the object
	 */
	static GB2Node* initWithNode(CCNode *node);

	/**
	 * Inits the object with a dynamic shape and node
	 * @param shape name of the physics shape to use
	 * @param node CCNode to use for this object
	 * @return the object
	 */
	static GB2Node* initWithDynamicBody(CCString *shape, CCNode *node);
	
	/**
	 * Inits the object with a static shape and node
	 * @param shape name of the physics shape to use
	 * @param node CCNode to use for this object
	 * @return the object
	 */
	static GB2Node* initWithStaticBody(CCString *shape, CCNode *node);
	
	/**
	 * Inits the object with a kinematic shape and node
	 * @param shape name of the physics shape to use
	 * @param node CCNode to use for this object
	 * @return the object
	 */
	static GB2Node* initWithKinematicBody(CCString *shape, CCNode *node);

	/**
	 * Inits the object with a shape, body type and node
	 * @param shape name of the physics shape to use
	 * @param node CCNode to use for this object
	 * @return the object
	 */
	static GB2Node* nodeFromShapeNameandSprite(CCString *shape, b2BodyType bodyType, CCNode *node);

	/**
	 * Adds a fixture to the body
	 * @param fixtureDef fixture definition
	 * @return the added fixture
	 */
	b2Fixture* addFixture(b2FixtureDef *fixtureDef);
	
	/**
	 * Starts the given action on the inner CCNode
	 * Should only be used with actions which do not
	 * move or scale / rotate the object
	 * @param action action to run
	 * @return action
	 */
	CCAction* runAction(CCAction *action);

	/**
	 * Stops all actions on the inner CCNode
	 */
	void stopAllActions();

	/**
	 * Stops the given action on the inner CCNode
	 * @param action action to stop
	 */
	void stopAction(CCAction *action);

	/**
	 * Sets the CCNode to visible/invisible
	 */
	void setVisible(bool isVisible);

	/**
	 * Sets the object's angle
	 * @param angle angle to set
	 */
	void setAngle(float angle);

	/**
	 * Sets the position from pixel coordinates
	 * @param p position to set
	 */
	void setCcPosition(CCPoint p);

	/**
	 * Scales the graphics (currently not the object!)
	 * @param scale scale to set
	 */
	void setScale(float scale);

	/**
	 * Returns the object's position in pixel coordinates
	 */
	CCPoint ccPosition();

	/**
	 * Delete the object, remove it from the parent scene
	 */
	void deleteNow();

	/**
	 * Returns true if the body is awake
	 */
	bool isAwake();

	/**
	 * Called by GB2Engine to update the shape's position
	 * and rotation from the physics coordinates 
	 */
	virtual void updateCCFromPhysics();

	/**
	 * Replaces the current fixtures with the new shape
	 * @param shapeName name of the shape to set
	 */
	void setBodyShape(CCString *shapeName);

	/**
	 * Returns the object's mass
	 * @return mass
	 */
	float mass();

	/**
	 * Returns the position of the object in physics coordinates
	 * @return position
	 */
	b2Vec2 physicsPosition();

	/**
	 * Sets the physics position of the object
	 * @param position position to set
	 */
	void setPhysicsPosition(b2Vec2 position);

	/**
	 * Returns the world center of the object
	 * @return world center
	 */
	b2Vec2 worldCenter();

	/**
	 * Replaces the object's fixtures with the new shape
	 * and sets the positon and body type to kinematic
	 * @param shapeName name of the shape to set
	 * @param pos position of the object
	 */
	void setKinematicBody(CCString *shapeName, b2Vec2 pos);

	/**
	 * Replaces the object's fixtures with the new shape
	 * and sets the positon and body type to dynamic
	 * @param shapeName name of the shape to set
	 * @param pos position of the object
	 */
	void setDynamicBody(CCString *shapeName, b2Vec2 pos);

	/**
	 * Replaces the object's fixtures with the new shape
	 * and sets the positon and body type to static
	 * @param shapeName name of the shape to set
	 * @param pos position of the object
	 */
	void setStaticBody(CCString *shapeName, b2Vec2 pos);

	/**
	 * Sets the body type of the object
	 * b2_kinematicBody, b2_staticBody, b2_dynamicBody
	 * @param bodyType
	 */
	void setBodyType(b2BodyType bodyType);

	/**
	 * Applies an impulse at the given point of the object
	 * Use [self worldCenter] to apply the impulse to the 
	 * center of the object without setting the object 
	 * into a rotation
	 * @param impulse impulse to apply
	 * @param point point to apply the impulse to
	 */
	void applyLinearImpulse(b2Vec2 impulse, b2Vec2 point);

	/**
	 * Sets the linear velocity of the object
	 * @param velocity velocity vector to set
	 */
	void setLinearVelocity(b2Vec2 velocity);

	/**
	 * Enables / disables rotation on the object
	 * If called with YES the object can't rotate
	 * @param fixedRotation
	 */
	void setFixedRotation(bool fixedRotation);

	/**
	 * Add damping
	 * @param linearDamping daming value to set
	 */
	void setLinearDamping(float linearDamping);

	/**
	 * Add angular damping
	 * @param angularDamping damping value
	 */
	void setAngularDamping(float angularDamping);

	/**
	 * Apply a force to the given point of the object
	 * @param force force to apply
	 * @param point point on the object to apply the force to
	 */
	void applyForce(b2Vec2 force, b2Vec2 point);

	/**
	 * Returns the angle of the object
	 * @return angle
	 */
	float angle();

	/**
	 * Sets the position and rotation of the object
	 * @param pos position to set
	 * @param angle angle to set
	 */
	void setTransform(b2Vec2 pos, float angle);

	/**
	 * Returns true if the object is active (participates
	 * in collition detection etc.
	 */
	bool active();

	/**
	 * Sets the object to active (or not)
	 * If the object is inactive it will not participate in 
	 * collition detection
	 */
	void setActive(bool isActive);

	/**
	 * Returns true if the body is sleeping
	 * That means was not hit by other objects for some time
	 * @return true if object is awake
	 */
	bool awake();

	/**
	 * Returns the linear velocity of the object
	 * @return linear velocity
	 */
	b2Vec2 linearVelocity();

	/**
	 * Sets the object to bullet mode and activates continuous collision
	 * detection for the object
	 */
	void setBullet(bool bulletFlag);

	/**
	 * Destroys the physics body of the object
	 */
	void destroyBody();

	/**
	 * Returns the object's width in meters taken from the
	 * sprite's size. If the sprite has transparent borders
	 * this might differ from the object's real size
	 */
	float widthInM();

	/**
	 * Clears mask bits on the object's fixtures
	 * Bits to clear must be set to 1
	 * @param bits bits to clear
	 */
	void clrCollisionMaskBits(uint16 bits);

	/**
	 * Clears mask bits on the object's fixtures
	 * Bits to clear must be set to 1
	 * @param bits bits to clear
	 * @param forId only change the bits for the given fixtureID
	 */
	void clrCollisionMaskBits(uint16 bits, CCString *fixtureId);

	/**
	 * Adds mask bits on the object's fixtures
	 * Bits to set must be set to 1
	 * @param bits bits to set
	 */
	void addCollisionMaskBits(uint16 bits);

	/**
	 * Adds mask bits on the object's fixtures
	 * Bits to set must be set to 1
	 * @param bits bits to set
	 * @param forId only change the bits for the given fixtureID
	 */
	void addCollisionMaskBits(uint16 bits, CCString *fixtureId);

	/**
	 * Sets the mask bits to the given value
	 * @param bits bits
	 */
	void setCollisionMaskBits(uint16 bits);

	/**
	 * Sets the mask bits to the given value
	 * @param bits bits
	 * @param forId only change the bits for the given fixtureID
	 */
	void setCollisionMaskBits(uint16 bits, CCString *fixtureId);

	/**
	 * Add bits to the collision category
	 * @param bits bits to set
	 */
	void addCollisionCategoryBits(uint16 bits);

	/**
	 * Add bits to the collision category
	 * @param bits bits to set
	 * @param forId only change the bits for the given fixtureID
	 */
	void addCollisionCategoryBits(uint16 bits, CCString *fixtureId);

	/**
	 * Clr bits on the collition category
	 * Bits to clear must be set to 1
	 * @param bits to clr
	 */
	void clrCollisionCategoryBits(uint16 bits);

	/**
	 * Clr bits on the collition category
	 * Bits to clear must be set to 1
	 * @param bits to clr
	 * @param forId only change the bits for the given fixtureID
	 */
	void clrCollisionCategoryBits(uint16 bits, CCString *fixtureId);

	/**
	 * Sets the category bits to the given value
	 * @param bits bits to set
	 */
	void setCollisionCategoryBits(uint16 bits);

	/**
	 * Sets the category bits to the given value
	 * @param bits bits to set
	 * @param forId only change the bits for the given fixtureID
	 */
	void setCollisionCategoryBits(uint16 bits, CCString *fixtureId);


	virtual b2Fixture *createFixture(const b2FixtureDef *fixtureDef);

	/**
	 * Returns the object's tag
	 * @return tag of the object
	 */
	int objectTag();

	/**
	 * Tag the object with an integer value
	 * @param tag tag value to set
	 */
	void setObjectTag(int tag);


	/**
	 * Sets the object's angular velocity
	 * @param v velocity to set
	 */
	void setAngularVelocity(float32 v);

	/**
	 * Adds an edge to the fixture
	 */
	void addEdgeFrom(b2Vec2 start, b2Vec2 end);
	void addBoxFrom(b2Vec2 start, b2Vec2 end);
	 
	CCString *description();

	void setParent(CCNode *parent);
	void setParent(CCNode *parent, float z);
	
	void setBodyAndType(CCString *shapeName, b2BodyType bodyType, b2Vec2 pos);

	void setName(CCString *name);
	CCString *getName();

protected:
	int _objectTag; //!< tag might be used to query an object
	CCString *_name;

};

#endif  // __GB2NODE_H__