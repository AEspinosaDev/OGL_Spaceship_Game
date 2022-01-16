#include "sphere.h"
Sphere* Sphere::clone() {
	return new Sphere(*this);
}
void Sphere::render() {
	glPushMatrix();
	 glTranslated(getPos().getX(), getPos().getY(), getPos().getZ());
	 glRotated(this->getRot().getX(), 1, 0, 0);
	 glRotated(this->getRot().getY(), 0, 1, 0);
	 glRotated(this->getRot().getZ(), 0, 0, 1);
	 glColor3d(getColor().getX(), getColor().getY(), getColor().getZ());
	 glutSolidSphere(getSize(),10,10);
	glPopMatrix();
}
