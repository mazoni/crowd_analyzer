#include<string>
#pragma once
using namespace std;

class Walkable
{
private:
	float density;
public:
	Walkable(int density);
	~Walkable(void);
	void toString(void);

};

