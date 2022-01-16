#pragma once
#include "vector3d.h"
#include "solid.h"
#include "sphere.h"

class Collider {
	Vector3D p;
	float r;
	
public:
	Collider(Vector3D p, float r):p(p), r(r){}
		
	~Collider(){}

	Vector3D& getP()  { return p; }
	void setP(Vector3D pos) { this->p = pos; }
	float getR() { return r; }
	void setR(float r) { this->r = r; }

	bool colision(Collider* e) {
		Vector3D pe = e->getP();
		float re = e->getR();
		Vector3D vd = pe - p;
		float l = vd.length();
		return l < r + re;
		

	}
};
