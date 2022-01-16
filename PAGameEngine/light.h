#pragma once
#include "solid.h"
class Light :   public Solid{
public:
	Light(Vector3D p = Vector3D(50, 150, 50)) :Solid(1,p) {}
	void render() {
		float x = getPos().getX();
		float y = getPos().getY();
		float z = getPos().getZ();

		GLfloat lightpos[] = { x,y,z,0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	}
};

