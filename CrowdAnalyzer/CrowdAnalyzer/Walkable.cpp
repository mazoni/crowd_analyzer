#include "Walkable.h"
#include<iostream>


Walkable::Walkable(int density)
{
	this->density = density;
}


Walkable::~Walkable(void)
{
}

void Walkable::toString(void)
{
	cout << "Density: " << this->density << endl;	
	Vertex* v;
	for(list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); ++it) 
	{
		v = *it;
		cout << "X: " << v->x << endl;
		cout << "Y: " << v->y << endl;
		cout << "Z: " << v->z << endl;
	}
}

void Walkable::setVertices(list<Vertex*> vertices)
{
	this->vertices = vertices;
}

list<Vertex*> Walkable::getVertices(void) 
{
	return this->vertices;
}