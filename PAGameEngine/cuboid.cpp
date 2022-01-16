#include "cuboid.h"

void Cuboid::render()
{
	glPushMatrix();
	glTranslated(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
	glRotated(this->getRot().getX(), 1, 0, 0);
	glRotated(this->getRot().getY(), 0, 1, 0);
	glRotated(this->getRot().getZ(), 0, 0, 1);
	glColor3d(this->getColor().getX(), this->getColor().getY(), this->getColor().getZ());
	glScalef(getLength(), getHeight(), getWidth());
	glutSolidCube(1);
	glPopMatrix();
}
