#include "solid.h"
Solid* Solid::clone() {
	return new Solid(*this);
}
void Solid::render() {
	glPushMatrix();
	 glTranslated(getPos().getX(), getPos().getY(), getPos().getZ());
	 glColor3d(getColor().getX(), getColor().getY(), getColor().getZ());
	 glutWireTeapot(getSize());
	glPopMatrix();
}
void Solid::update(double time) {
	this->setPos(Vector3D(this->getPos() + this->getVel() * time));
	this->setRot(Vector3D(this->getRot() + this->getRotVel() * time));
}
ostream& operator<<(ostream& os, const Solid& c) {
	os << c.pos << ";" << c.vel << ";" << c.rot << ";" << c.color <<  ";" << c.size;
	return os;
}
