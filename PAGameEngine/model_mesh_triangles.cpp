#include "model_mesh_triangles.h"
void ModelMeshTriangles::render() {
	glPushMatrix();
	glTranslated(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
	glRotated(this->getRot().getX(), 1, 0, 0);
	glRotated(this->getRot().getY(), 0, 1, 0);
	glRotated(this->getRot().getZ(), 0, 0, 1);
	for (Triangle &t : triangles)
		t.render();
	glPopMatrix();
}
void ModelMeshTriangles::update(double& dt) {
	ModelMeshTriangles::update(dt);
	for (Triangle &t:triangles) {
		t.update(dt);
	}
}
ostream& operator<<(ostream& os, const ModelMeshTriangles& m) {
	os << static_cast<const Solid&>(m);
	os << "[";
	for (const Triangle &t : m.triangles) {
		os << t << endl;
	}
	os << "]";
	return os;
}

void ModelMeshTriangles::setColor(Vector3D color)
{
	for (Triangle& t : triangles) {
		t.setC0(color);
		t.setC1(color);
		t.setC2(color);
	}
}