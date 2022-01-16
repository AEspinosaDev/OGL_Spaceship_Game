#include "teapot.h"
Teapot* Teapot::clone() {
	return new Teapot(*this);
}
void Teapot::render() {
	glPushMatrix();
	 glTranslated(getPos().getX(), getPos().getY(), getPos().getZ());
	 glRotated(this->getRot().getX(), 1, 0, 0);
	 glRotated(this->getRot().getY(), 0, 1, 0);
	 glRotated(this->getRot().getZ(), 0, 0, 1);
	 glColor3d(getColor().getX(), getColor().getY(), getColor().getZ());
	 glutSolidTeapot(getSize());
	glPopMatrix();
}
