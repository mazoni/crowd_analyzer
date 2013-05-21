#include<string>
#include<list>
#include<hash_map>

#include "Walkable.h"
#include "Walker.h"

#pragma once

using namespace std;

class Bootstrap
{
	std::string templateXml;
	std::string simulationXml;
	list<Walkable*> walkables;
	hash_map<int, Walker*> walkers;
public:
	Bootstrap(std::string templateXml, std::string simulationXml);
	void run(void);
	void initWindow(void);
	~Bootstrap(void);
};

