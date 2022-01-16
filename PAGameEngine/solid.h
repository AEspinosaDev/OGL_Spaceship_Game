#pragma once
#include <GL/glut.h>
#include <string>
#include <exception>
#include "vector3d.h"
class Solid
{
	Vector3D pos;
	Vector3D vel;
	Vector3D rot;
	Vector3D rotVel;
	Vector3D color;
	double size;
public:
	Solid( double d = 1.0, Vector3D p = Vector3D(0, 0, 0), Vector3D v = Vector3D(0, 0, 0),
		Vector3D c = Vector3D(1, 1, 0))	: size(d), pos(p), vel(Vector3D()), rot(Vector3D()), rotVel(Vector3D()), color(c) {}
	virtual ~Solid(){}
	inline double getSize() { return size; }
	inline Vector3D getPos() { return pos; }
	inline Vector3D getVel() { return vel; }
	inline Vector3D &getRot() { return rot; }
	inline Vector3D getRotVel() { return rotVel; }
	inline Vector3D getColor() { return color; }
	inline void setSize(double d) { size = d; }
	inline void setPos(Vector3D p) { pos = p; }
	inline void setVel(Vector3D v) { vel = v; }
	inline void setRot(Vector3D r) { rot = r; }
	inline void setRotVel(Vector3D rv) { rotVel = rv; }
	inline void setColor(Vector3D c) { color = c; }
	virtual void render();
	virtual void update(double dt);
	virtual Solid* clone();
	friend ostream& operator<<(ostream& os, const Solid& v);
};

