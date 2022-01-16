#pragma once
#include "solid.h"
class Triangle :    public Solid{
	Vector3D p0, p1, p2;
	Vector3D n0, n1, n2;
	Vector3D c0, c1, c2;
public:
	Triangle(Vector3D p0, Vector3D p1, Vector3D p2,
		     Vector3D c0=Vector3D(1,1,0),
		     Vector3D c1=Vector3D(1,1,0),
	  	     Vector3D c2=Vector3D(1,1,0)) :
		Solid(),p0(p0), p1(p1), p2(p2),
		        c0(c0), c1(c1), c2(c2) {
		Vector3D v10 = p1 - p0;
		Vector3D v21 = p2 - p1;
		Vector3D normal = v10.X(v21);
		n0 = n1 = n2= normal.normalized();
	}
	Vector3D getP0() { return p0; }
	void setP0(Vector3D p) { p0 = p; }
	Vector3D getP1() { return p1; }
	void setP1(Vector3D p) { p1 = p; }
	Vector3D getP2() { return p2; }
	void setP2(Vector3D p) { p2 = p; }
	Vector3D getN0() { return n0; }
	void setN0(Vector3D p) { n0 = p; }
	Vector3D getN1() { return n1; }
	void setN1(Vector3D p) { n1 = p; }
	Vector3D getN2() { return n2; }
	void setN2(Vector3D p) { n2 = p; }
	Vector3D getC0() { return c0; }
	void setC0(Vector3D p) { c0 = p; }
	Vector3D getC1() { return c1; }
	void setC1(Vector3D p) { c1 = p; }
	Vector3D getC2() { return c2; }
	void setC2(Vector3D p) { c2 = p; }
	void render();
};

