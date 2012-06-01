//
//  GB2ShapeCache-x.cpp
//  
//  Loads physics sprites created with http://www.PhysicsEditor.de
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//      http://www.PhysicsEditor.de
//      http://texturepacker.com
//      http://www.code-and-web.de
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

#include "GB2ShapeCache.h"
#include "Box2D.h"
#include "..\cocoa\CCNS.h"

using namespace cocos2d;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
    : next(NULL) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }
    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
	BodyDef()
	: fixtures(NULL) {}
	
	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}
	
	FixtureDef *fixtures;
	CCPoint anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}
	
	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *so = (*pos).second;

	FixtureDef *fix = so->fixtures;
    while (fix) {
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

cocos2d::CCPoint GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

//typedef CCDictionary ObjectDict;

void GB2ShapeCache::addShapesWithFile(const std::string &plist) {

	//const char *fullName = CCFileUtils::fullPathFromRelativeFile(plist.c_str(), plist.c_str());
	//CCLog("GB2ShapeCache::addShapesWithFile plist:%s, fullName:%s", plist.c_str(), fullName);

	CCDictionary *dict = CCDictionary::dictionaryWithContentsOfFileThreadSafe(plist.c_str());
	CCAssert(dict != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    CCAssert(dict->count() != 0, "plist file empty or not existing");
	
	CCDictionary *metadataDict = (CCDictionary *)dict->objectForKey("metadata");
    int format = static_cast<CCString *>(metadataDict->objectForKey("format"))->intValue();
    ptmRatio = static_cast<CCString *>(metadataDict->objectForKey("ptm_ratio"))->floatValue();
	CCAssert(format == 1, "Format not supported");

	CCDictionary *bodyDict = (CCDictionary *)dict->objectForKey("bodies");

    b2Vec2 vertices[b2_maxPolygonVertices];

	//ObjectDict::CCObjectMapIter iter;
	
	//std::string bodyName = NULL;
	//CCDictionary *bodyData;
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(bodyDict, pElement)
	{
		BodyDef *bodyDef = new BodyDef();

		CCString *bodyName = ccs(pElement->getStrKey());

		CCDictionary *bodyData = (CCDictionary *)pElement->getObject();
		bodyDef->anchorPoint = CCPointFromString(static_cast<CCString *>(bodyData->objectForKey("anchorpoint"))->getCString());
		
		CCDictionary *fixtureList = (CCDictionary *)bodyData->objectForKey("fixtures");
		FixtureDef *nextFixtureDef = bodyDef->fixtures;
		
		CCDictElement *fixture = NULL;
		CCDICT_FOREACH(fixtureList, fixture)
		{
		
			b2FixtureDef basicData;
			CCDictionary *fixtureData = (CCDictionary *)fixture->getObject();

			basicData.filter.categoryBits = static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->intValue();
            basicData.filter.maskBits = static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->intValue();
            basicData.filter.groupIndex = static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->intValue();
            basicData.friction = static_cast<CCString *>(fixtureData->objectForKey("friction"))->floatValue();
            basicData.density = static_cast<CCString *>(fixtureData->objectForKey("density"))->floatValue();
            basicData.restitution = static_cast<CCString *>(fixtureData->objectForKey("restitution"))->floatValue();
            basicData.isSensor = (bool)static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->intValue();
			if(fixtureData->objectForKey("id")){
				basicData.fixID = static_cast<CCString *>(fixtureData->objectForKey("id"))->intValue();
			}

			CCString *cb = static_cast<CCString *>(fixtureData->objectForKey("userdataCbValue"));
			
            int callbackData = 0;
			
			if (cb)
				callbackData = cb->intValue();
            

			std::string fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->getCString();

			if (fixtureType == "POLYGON") {
				CCDictionary *polygons = (CCDictionary *)fixtureData->objectForKey("polygons");
				CCDictElement *polygon = NULL;
				CCDICT_FOREACH(polygons, polygon)
				{
					FixtureDef *fix = new FixtureDef();
					fix->fixture = basicData; // copy basic data
					fix->callbackData = callbackData;

					b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;

					CCDictionary *polygonData = (CCDictionary *)polygon->getObject();

					assert(polygonData->count() <= b2_maxPolygonVertices);

					CCDictElement *offset = NULL;
					CCDICT_FOREACH(polygonData, offset)
					{

						CCString *pStr = (CCString *)offset->getObject();
						CCPoint p = CCPointFromString(pStr->getCString());

						vertices[vindex].x = (p.x / ptmRatio) ; 
                        vertices[vindex].y = (p.y / ptmRatio) ; 
                        vindex++;

					}

					polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;

					nextFixtureDef = fix;
                    nextFixtureDef = (fix->next);
				}
				
			} else if (fixtureType == "CIRCLE") {
				FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
				CCDictionary *circleData = (CCDictionary *)fixtureData->objectForKey("circle");

                b2CircleShape *circleShape = new b2CircleShape();
				
                circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->floatValue() / ptmRatio;
				CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->getCString());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
				
                // create a list
                nextFixtureDef = fix;
                nextFixtureDef = (fix->next);

			} else {
				CCAssert(0, "Unknown fixtureType");
			}
			
			// add the body element to the hash
			shapeObjects[bodyName->getCString()] = bodyDef;


		}
	}

	/*
	//bodyDict->begin();
	std::string bodyName;
	CCDictionary *bodyData;
	while ((bodyData = (ObjectDict *)bodyDict->next(&bodyName))) {
		BodyDef *bodyDef = new BodyDef();
		bodyDef->anchorPoint = CCPointFromString(static_cast<CCString *>(bodyData->objectForKey("anchorpoint"))->toStdString().c_str());
		
		CCMutableArray<ObjectDict *> *fixtureList = (CCMutableArray<ObjectDict *> *)(bodyData->objectForKey("fixtures"));
        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);

		CCMutableArray<ObjectDict *>::CCMutableArrayIterator iter;
		for (iter = fixtureList->begin(); iter != fixtureList->end(); ++iter) {
            b2FixtureDef basicData;
            ObjectDict *fixtureData = *iter;
			
            basicData.filter.categoryBits = static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->toInt();
            basicData.filter.maskBits = static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->toInt();
            basicData.filter.groupIndex = static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->toInt();
            basicData.friction = static_cast<CCString *>(fixtureData->objectForKey("friction"))->toFloat();
            basicData.density = static_cast<CCString *>(fixtureData->objectForKey("density"))->toFloat();
            basicData.restitution = static_cast<CCString *>(fixtureData->objectForKey("restitution"))->toFloat();
            basicData.isSensor = (bool)static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->toInt();
			if(fixtureData->objectForKey("id")){
				basicData.fixID = static_cast<CCString *>(fixtureData->objectForKey("id"))->toInt();
				//CLog("basicData.fixID: i%", basicData.fixID);
			}

			CCString *cb = static_cast<CCString *>(fixtureData->objectForKey("userdataCbValue"));
			
            int callbackData = 0;
			
			if (cb)
				callbackData = cb->toInt();
            
			std::string fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->toStdString();
			
			if (fixtureType == "POLYGON") {
				CCMutableArray<ObjectDict *> *polygonsArray = (CCMutableArray<ObjectDict *> *)(fixtureData->objectForKey("polygons"));
				CCMutableArray<ObjectDict *>::CCMutableArrayIterator iter;

				for (iter = polygonsArray->begin(); iter != polygonsArray->end(); ++iter) {
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
					
                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
					CCMutableArray<CCString *> *polygonArray = (CCMutableArray<CCString *> *)(*iter);

                    assert(polygonArray->count() <= b2_maxPolygonVertices);

					CCMutableArray<CCString *>::CCMutableArrayIterator piter;
					
					for (piter = polygonArray->begin(); piter != polygonArray->end(); ++piter) {
                        CCPoint offset = CCPointFromString((*piter)->toStdString().c_str());
                        vertices[vindex].x = (offset.x / ptmRatio) ; 
                        vertices[vindex].y = (offset.y / ptmRatio) ; 
                        vindex++;
                    }
                    
                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
				}
				
			} else if (fixtureType == "CIRCLE") {
				FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
                ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");
                
                b2CircleShape *circleShape = new b2CircleShape();
				
                circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
				CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
				
                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);

			} else {
				CCAssert(0, "Unknown fixtureType");
			}
			
			// add the body element to the hash
			shapeObjects[bodyName] = bodyDef;
		}
	}
	*/
}