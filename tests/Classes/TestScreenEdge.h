#ifndef TESTSCREENEDGE_H
#define TESTSCREENEDGE_H

#include "../../GBox2D/GBox2D.h"

class TestScene;

class TestScreenEdge : public GB2Node
{
public:
	TestScreenEdge();
	~TestScreenEdge();

	static TestScreenEdge * initWithLevelLayer(TestScene *layer);

	virtual void Contact(GB2Contact *contact);

	void setLevelLayer(TestScene *layer);
	TestScene * getLevelLayer();
	
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