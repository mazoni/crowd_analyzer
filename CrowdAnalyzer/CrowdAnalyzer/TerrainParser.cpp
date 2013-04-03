#include "TerrainParser.h"
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include<iostream>


TerrainParser::TerrainParser(string terrainXml)
{
	// take a look at http://xerces.apache.org/xerces-c/program-dom-3.html#ConstructDOMLSParser
	this->terrainXml = terrainXml;
	cout << terrainXml << endl;
	Walkable* w = new Walkable(1);
	this->walkables.push_back(*w);
	w = new Walkable(2);
	this->walkables.push_back(*w);
	for(list<Walkable>::iterator it = this->walkables.begin(); it != this->walkables.end(); ++it) 
	{
		it->toString();
	}

}


TerrainParser::~TerrainParser(void)
{
}

