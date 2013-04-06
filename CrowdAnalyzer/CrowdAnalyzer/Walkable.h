#include<string>
#include<list>
#include "Vertex.h"

#pragma once
using namespace std;

class Walkable
{
private:
	list<Vertex*> vertices;
	float density;
public:
	Walkable(int density);
	~Walkable(void);
	void toString(void);
	list<Vertex*> getVertices(void);
	void setVertices(list<Vertex*> vertices);
};

