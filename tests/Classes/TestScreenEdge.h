#ifndef TESTSCREENEDGE_H
#define TESTSCREENEDGE_H

#include "../../GBox2D/GBox2D.h"

class TestScene;

USING_NS_GB;

class TestScreenEdge : public GB2Node
{
public:
	TestScreenEdge();
	~TestScreenEdge();

	static TestScreenEdge * initWithLevelLayer(TestScene *layer);
	
	void setLevelLayer(TestScene *layer);
	TestScene * getLevelLayer();

	void beginContactWithGB2Node(GB2Node* otherObject, GB2Collision *c);
	
	COLLISION_OBJECT(TestScreenEdge)

protected:
	TestScene *m_levelLayer;

};

inline
	void TestScreenEdge::setLevelLayer(TestScene *layer)
{
	m_levelLayer = layer;
}

inline 
	TestScene * TestScreenEdge::getLevelLayer()
{
	return m_levelLayer;
}


#endif //TESTSCREENEDGE_H