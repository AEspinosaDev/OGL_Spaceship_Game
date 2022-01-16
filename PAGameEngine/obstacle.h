#pragma once
#include "model_mesh_triangles.h"
#include "collider.h"
#include "util.h"
#include "loader_obj.h"

class Obstacle : public ModelMeshTriangles {
	Collider* hitBox;
	float size;
public:
	Obstacle(int i) {
		this->size = getRand(1, 4);
		LoaderOBJ lobj(size);
		ModelMeshTriangles* aux = new ModelMeshTriangles();

		
		switch (i) {
		case 0:
			lobj.loadModel("diamond.obj");
			break;
		case 1:
			lobj.loadModel("extrasterrestrial.obj");

			break;
		

		}
			*aux = lobj.getModelMeshTriangles();
			this->setSolids(aux->getTriangles());
			
			this->setColor(Vector3D(0, 0, 1));

			hitBox = new Collider(this->getPos(), size);

			delete aux;
	}
	~Obstacle() {
		delete hitBox;
	}


	inline void setPos(Vector3D p) {
		ModelMeshTriangles::setPos(p);
		this->hitBox->setP(p);
	}

	void update(double time) {
		this->setPos(Vector3D(this->getPos() + this->getVel() * time));
		this->setRot(Vector3D(this->getRot() + this->getRotVel() * time));
	}

	inline Collider* &getHitBox() {	return this->hitBox;}

};
