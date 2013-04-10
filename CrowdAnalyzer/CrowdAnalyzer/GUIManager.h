#include <list>
#include "Walkable.h"

using namespace std;

#pragma once
class GUIManager
{
	list<Walkable*> walkables;
public:
	GUIManager(list<Walkable*> walkables);
	void render(void);
	void renderSample(void);
	~GUIManager(void);
};

