#include <list>
#include <osg/Geode>
#include "Walkable.h"

using namespace std;

#pragma once
class GUIManager
{
	list<Walkable*> walkables;
private:
	osg::Geode* renderWalkables(void);
	osg::Geode* renderWalkers(void);
public:
	GUIManager(list<Walkable*> walkables);
	void render(void);
	void renderSample(void);
	~GUIManager(void);
};

