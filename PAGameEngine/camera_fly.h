#pragma once
#include "camera_fps.h"
class CameraFly :  public CameraFPS{
public:
	Vector3D getVectorVel() {
		double ry = deg2grad(getRot().getY());
		double rx = deg2grad(getRot().getX());
		Vector3D vel = { sin(ry)*cos(rx),-sin(rx),-cos(ry)*cos(rx) };
		return vel;
	}
};

