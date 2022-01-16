#pragma once
#include "util.h"
#include "composite.h"
#include "cylinder.h"
#include "sphere.h"
#include "cube.h"
#include "obstacle.h"
class ProceduralGenerator
{
private:
public:
	ProceduralGenerator(){}

	Obstacle* generateAlien(float factor) {
		Vector3D newPos = Vector3D(floor(getRand(-12, 12)), floor(getRand(-8, 8)), -100);
		Vector3D newVel = Vector3D(0, 0, 8 + factor);

		Obstacle* obj = new Obstacle(1);
		obj->setVel(newVel);
		obj->setPos(newPos);
		obj->setRotVel(Vector3D(0, 120, 0));
		obj->setColor(Vector3D(0.5, 0.5, 0.5));
		
		
		return obj;

	}
	Obstacle* generateAsteroid(float factor) {
		
		Vector3D newPos = Vector3D(floor(getRand(-12, 12)), floor(getRand(-8, 8)), -100);
		Vector3D newVel = Vector3D(0, 0, 5+factor);
		
		Obstacle* obj = new Obstacle(0);
		obj->setVel(newVel);
		obj->setPos(newPos);
		obj->setRotVel(Vector3D(15, 10, 5));
		obj->setColor(Vector3D(0.78, 0.53, 0.36));
		

		return obj;

	}
};

