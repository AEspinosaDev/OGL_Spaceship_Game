#pragma once
#include "solid.h"
class Camera:public Solid{
public:
	Camera(Vector3D p=Vector3D(0,0,0)) :Solid() {
		setPos(p);
	}
	void render();
};

