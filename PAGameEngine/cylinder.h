#pragma once
#include "solid.h"
class Cylinder: public Solid{
	GLUquadricObj* quadratic;
	double b;
public:
	Cylinder(double b, double h) :Solid(), b(b) {
		this->setSize(h);
		quadratic = gluNewQuadric();
	}
	virtual ~Cylinder() {
		delete quadratic;
	}
	void render();
	Cylinder* clone();
	friend ostream& operator<<(ostream& os, const Cylinder& c);
};

