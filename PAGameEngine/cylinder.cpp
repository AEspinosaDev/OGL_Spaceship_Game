#include "cylinder.h"
Cylinder* Cylinder::clone() {
	return new Cylinder(*this);
}
void Cylinder::render() {
	glPushMatrix();
	 glTranslated(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
	 glRotated(this->getRot().getX(), 1, 0, 0);
	 glRotated(this->getRot().getY(), 0, 1, 0);
	 glRotated(this->getRot().getZ(), 0, 0, 1);
	 glColor3d(this->getColor().getX(), this->getColor().getY(), this->getColor().getZ());
	 glRotated(90, 1, 0, 0);
	 gluCylinder(quadratic, b, b, getSize(), 16, 16);
	glPopMatrix();
}
ostream& operator<<(ostream& os, const Cylinder& c) {
	//os << c; //NOOO llamada recursiva infinita
	os << static_cast<const Solid&>(c);//operator<<(os,c) de Solid;
	os << ";" << c.b;
	return os;
}
