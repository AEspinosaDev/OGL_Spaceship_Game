#include "camera.h"
void Camera::render() {
	glTranslated(-this->getPos().getX(), -this->getPos().getY(), -this->getPos().getZ());
	glRotated(this->getRot().getX(), 1, 0, 0);
	glRotated(this->getRot().getY(), 0, 1, 0);
	glRotated(this->getRot().getZ(), 0, 0, 1);
}
