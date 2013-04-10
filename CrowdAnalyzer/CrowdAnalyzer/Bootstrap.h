#include<string>
#include<list>
#include "Walkable.h"

#pragma once

using namespace std;

class Bootstrap
{
	std::string templateXml;
	list<Walkable*> walkables;
public:
	Bootstrap(std::string templateXml);
	void run(void);
	void initWindow(void);
	~Bootstrap(void);
};

