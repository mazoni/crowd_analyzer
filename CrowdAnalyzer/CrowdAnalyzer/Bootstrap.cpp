#include "Bootstrap.h"
#include "GUIManager.h"
#include<string>
#include<iostream>
#include "TerrainParser.h"
#include "SimulationParser.h"

using namespace std;

Bootstrap::Bootstrap(string templateXml, string simulationXml)
{
	this->templateXml = templateXml;
	this->simulationXml = simulationXml;
}

void Bootstrap::run(void)
{
	//prepare walkables
	TerrainParser* terrainParser = new TerrainParser(this->templateXml);
	int response = terrainParser->ParseTerrain();
	this->walkables = terrainParser->GetWalkables();

	//prepare walkers
	SimulationParser* simulationParser = new SimulationParser(this->simulationXml);
	simulationParser->ParseWalkers();

	this->initWindow();
}

void Bootstrap::initWindow(void)
{
	GUIManager* guiManager = new GUIManager(this->walkables);
	guiManager->render();
}

Bootstrap::~Bootstrap(void)
{
}
