#include "Bootstrap.h"
#include "GUIManager.h"
#include<string>
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
	int response = terrainParser->parseTerrain();
	this->initWindow();
}

void Bootstrap::initWindow(void)
{
	GUIManager* guiManager = new GUIManager();
	guiManager->render();
}

Bootstrap::~Bootstrap(void)
{
}
