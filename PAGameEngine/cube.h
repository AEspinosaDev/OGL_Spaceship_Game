#pragma once
#include "solid.h"
class Cube: public Solid{
public:
	Cube(double d = 1.0, Vector3D p = Vector3D(0, 0, 0), Vector3D c = Vector3D(1, 1, 0)) :
		Solid(d,p,c) {}
	void render();
	Cube* clone();
};

