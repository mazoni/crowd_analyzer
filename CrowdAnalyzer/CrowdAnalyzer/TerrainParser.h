#pragma once

#include<string>
#include<list>
#include "Walkable.h"

using namespace std;

class TerrainParser
{
	list<Walkable> walkables;
	string terrainXml;

public:
	TerrainParser(string terrainXml);
	~TerrainParser(void);
	int parseTerrain(void);
};

