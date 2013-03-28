#include "Bootstrap.h"
#include<string>
#include<xercesc\dom\DOM.hpp>
#include<iostream>
#include "TerrainParser.h"

using namespace std;

Bootstrap::Bootstrap(string templateXml)
{
	this->templateXml = templateXml;
}

void Bootstrap::run(void)
{
	TerrainParser* terrainParser = new TerrainParser(this->templateXml);
	this->initWindow();
}

void Bootstrap::initWindow(void)
{

}

Bootstrap::~Bootstrap(void)
{
}
