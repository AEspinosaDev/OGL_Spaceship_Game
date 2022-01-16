#include "triangle.h"
void Triangle :: render() {
	//glColor3d(getColor().getX(), getColor().getY(), getColor().getZ());
	glBegin(GL_TRIANGLES);
	 glColor3d(c0.getX(), c0.getY(), c0.getZ());
	 glNormal3d(n0.getX(), n0.getY(), n0.getZ());
	 glVertex3d(p0.getX(), p0.getY(), p0.getZ());
	 glColor3d (c1.getX(), c1.getY(), c1.getZ());
	 glNormal3d(n1.getX(), n1.getY(), n1.getZ());
	 glVertex3d(p1.getX(), p1.getY(), p1.getZ());
	 glColor3d (c2.getX(), c2.getY(), c2.getZ());
	 glNormal3d(n2.getX(), n2.getY(), n2.getZ());
	 glVertex3d(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
}
