#include "scene.h"
Scene* Scene::clone() {
	return new Scene(*this);
}

void Scene::render()
{
	this->camera->render();
	Composite::render();
}

void Scene::update(const double& dt) {
	for (Solid* ps : getSolids()) {
		ps->update(dt);
		Vector3D pos = ps->getPos();
		if (pos.getY() < 0) {
			pos.setY(0.01);
			ps->setPos(pos);
			Vector3D vel = ps->getVel();
			vel.setY(-vel.getY());
			ps->setVel(vel);
		}
		if (pos.getY() > this->getSize().getY()) {
			pos.setY(this->getSize().getY() - 0.01);
			ps->setPos(pos);
			Vector3D vel = ps->getVel();
			vel.setY(-vel.getY());
			ps->setVel(vel);
		}
		if (pos.getX() > this->getSize().getX()) {
			pos.setX(this->getSize().getX() - 0.01);
			ps->setPos(pos);
			Vector3D vel = ps->getVel();
			vel.setX(-vel.getX());
			ps->setVel(vel);
		}
		if (pos.getX() < 0) {
			pos.setX(0.01);
			ps->setPos(pos);
			Vector3D vel = ps->getVel();
			vel.setX(-vel.getX());
			ps->setVel(vel);
		}
		if (pos.getZ() > this->getSize().getZ()) {
			pos.setZ(this->getSize().getZ() - 0.01);
			ps->setPos(pos);
			Vector3D vel = ps->getVel();
			vel.setZ(-vel.getZ());
			ps->setVel(vel);
		}
		if (pos.getZ() < 0) {
			pos.setZ(0.01);
			ps->setPos(pos);
			Vector3D vel = ps->getVel();
			vel.setZ(-vel.getZ());
			ps->setVel(vel);
		}
	}
}

void Scene::processKeyPressed(unsigned char key, int x, int y) {
	//cout << "Has pulsado la tecla: " << key << endl;
	switch (key) {
	case 'w':
	case 'W':
		this->camera->update(0.1);
		break;
	case 's':
	case 'S':
		this->camera->update(-0.1);
		break;
	}
}

void Scene::processMouseMovement(int x, int y) {
	//cout << "La posicion del raton es:" << x << "," << y << endl;
}
void Scene::processMouseClick(int button, int state, int x, int y) {
	//cout << "boton:" << button << " estado:" << state << " x:" << x << " y:" << y << endl;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mx = x;
		my = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		mx = 0;
		my = 0;
	}
}
