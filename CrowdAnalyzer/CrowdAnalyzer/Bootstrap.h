#include<string>
#pragma once
class Bootstrap
{
	std::string templateXml;
public:
	Bootstrap(std::string templateXml);
	void run(void);
	void initWindow(void);
	~Bootstrap(void);
};

