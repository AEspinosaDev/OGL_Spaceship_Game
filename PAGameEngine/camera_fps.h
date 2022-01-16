#pragma once
#include "camera.h"
const double PI = 3.14159265358979;
const double DEG2GRAD = PI / 180.0;
const double GRAD2DEG = 1 / DEG2GRAD;
inline double deg2grad(double d) { return d * DEG2GRAD; }
inline double grad2deg(double g) { return g * GRAD2DEG; }

class CameraFPS : public Camera{
public:
	virtual Vector3D getVectorVel() {
		double ry = deg2grad(getRot().getY());
		Vector3D vel = { sin(ry),0,-cos(ry) };
		return vel;
	}
	inline void buildVel() {
		setVel(getVectorVel());
	}
	void update(double dt) {
		buildVel();
		Solid::update(dt);
	}
	void render() {
		glRotated(this->getRot().getX(), 1, 0, 0);
		glRotated(this->getRot().getY(), 0, 1, 0);
		glRotated(this->getRot().getZ(), 0, 0, 1);
		glTranslated(-this->getPos().getX(), -this->getPos().getY(), -this->getPos().getZ());
	}
};

