#pragma once
#include<string>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE
using namespace std;

class TerrainParser
{
public:
	TerrainParser(string terrainXml);
	~TerrainParser(void);
};

