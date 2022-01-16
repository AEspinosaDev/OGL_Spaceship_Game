#pragma once
#include "model_mesh_triangles.h"
#include "loader_obj.h"
#include "collider.h"

class Player : public ModelMeshTriangles {
private:
	string nombre;
	int type;
	int pts;
	int life;
	Collider* hitBox;
	double vel;
	double rotVel;
	double power;

public:
	Player(int t, int pts = 0, int v = 100) : ModelMeshTriangles(), type(t), pts(pts), life(v) {
		LoaderOBJ::setBasePath(".\\3dModels");
		LoaderOBJ lobj(1);
		ModelMeshTriangles* ship = new ModelMeshTriangles();
		switch (t) {
		case 1:
			lobj.loadModel("ship1.obj");
			*ship = lobj.getModelMeshTriangles();
			this->setSolids(ship->getTriangles());
			this->setPos(Vector3D(0, 0, 0));
			this->setColor(Vector3D(0, 1, 0));
			this->setRot(Vector3D(0, 180, 0));
			hitBox = new Collider(this->getPos(), 1.25);
			power = 5;
			vel = 5;
			rotVel = 40;

			break;
		case 2:
			lobj.loadModel("ship2.obj");
			*ship = lobj.getModelMeshTriangles();
			this->setSolids(ship->getTriangles());
			this->setPos(Vector3D(0, 0, 0));
			this->setColor(Vector3D(1, 0, 0));
			this->setRot(Vector3D(0, 180, 0));
			hitBox = new Collider(this->getPos(), 1.5);
			power = 10;
			vel = 10;
			rotVel = 80;
			break;
		case 3:
			lobj.loadModel("ship3.obj");
			*ship = lobj.getModelMeshTriangles();
			this->setSolids(ship->getTriangles());
			this->setPos(Vector3D(0, 0, 0));
			this->setColor(Vector3D(0, 0, 1));
			this->setRot(Vector3D(0, 180, 0));
			hitBox = new Collider(this->getPos(), 1.75);
			power = 30;
			vel = 20;
			rotVel = 160;
			break;
		}
	}

	inline void setPuntos(int pts) { this->pts = pts; }
	inline int getPuntos() { return this->pts; }
	inline int& getRPuntos() { return this->pts; }
	inline void setVidas(int v) { this->life = v; }
	inline int getVidas() { return this->life; }
	inline int& getRVidas() { return this->life; }
	inline void setNombre(string nom) { this->nombre = nom; }
	inline string getNombre() { return this->nombre; }
	inline Collider*& getHitBox() { return this->hitBox; }
	inline void setHitbox(Collider* c) { this->hitBox = c; }

	void computeColision(Collider* c) {
		if (this->getHitBox()->colision(c) == true) {
			this->life--;
		}
	}
	bool checkDestroy() {
		return life == 0;
	}
	void render() {
		ModelMeshTriangles::render();

	}
	void update(double time) {

		if (this->getVel().getX() > 0) {

			this->setVel(this->getVel() + Vector3D(-power * time, 0, 0));
			if (this->getVel().getX() < 0) {
				this->setVel(Vector3D(0, 0, 0));
			}
		}

		if (this->getVel().getX() < 0) {

			this->setVel(this->getVel() + Vector3D(power * time, 0, 0));
			if (this->getVel().getX() > 0) {
				this->setVel(Vector3D(0, 0, 0));
			}

		}
		if (this->getVel().getY() > 0) {

			this->setVel(this->getVel() + Vector3D(0, -power * time, 0));
			if (this->getVel().getY() < 0) {
				this->setVel(Vector3D(0, 0, 0));
			}
		}

		if (this->getVel().getY() < 0) {

			this->setVel(this->getVel() + Vector3D(0, power * time, 0));
			if (this->getVel().getY() > 0) {
				this->setVel(Vector3D(0, 0, 0));
			}

		}
		this->pts++;

		if (this->getRotVel().getZ() > 0) {
			this->setRotVel(this->getRotVel() - Vector3D(0, 0, 35 * time));
			if (this->getRotVel().getZ() < 0) {
				this->setRotVel(Vector3D(0, 0, 0));
				//this->getRot().setZ(90);
			}
		}
		if (this->getRotVel().getZ() < 0) {
			this->setRotVel(this->getRotVel() + Vector3D(0, 0, 35 * time));
			if (this->getRotVel().getZ() > 0) {
				this->setRotVel(Vector3D(0, 0, 0));
				//this->getRot().setZ(-90);
			}
		}
		//cout << this->getRot().getZ() << endl;

		this->setPos(Vector3D(this->getPos() + this->getVel() * time));
		this->setRot(Vector3D(this->getRot() + this->getRotVel() * time));
		this->hitBox->setP(this->getPos());
		//cout << this->getHitBox()->getP().getX() << endl;
	}
	void movement(unsigned char key, int x, int y) {
		if (key == 'd' || key == 'D') {
			if (this->getPos().getX() < 10)
				this->setVel(Vector3D(vel, 0, 0));

		}
		if (key == 'a' || key == 'A') {
			if (this->getPos().getX() > -10)
				this->setVel(Vector3D(-vel, 0, 0));
		}
		if (key == 'w' || key == 'W') {
			if (this->getPos().getY() < 5)
				this->setVel(Vector3D(0, vel, 0));
		}

		if (key == 's' || key == 'S') {
			if (this->getPos().getY() > -5)
				this->setVel(Vector3D(0, -vel, 0));
		}
		/*
		if (key == 'e') {

			this->setRotVel(Vector3D(0, 0, rotVel));

		}
		if (key == 'q') {

		   this->setRotVel(Vector3D(0, 0, -rotVel));

		}
	*/
	}

};

