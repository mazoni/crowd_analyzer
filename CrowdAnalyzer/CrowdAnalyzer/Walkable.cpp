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
	
}