#include "composite.h"
void Composite::render() {
	glPushMatrix();
	glTranslated(this->getPos().getX(), this->getPos().getY(), this->getPos().getZ());
	glRotated(this->getRot().getX(), 1, 0, 0);
	glRotated(this->getRot().getY(), 0, 1, 0);
	glRotated(this->getRot().getZ(), 0, 0, 1);
	for (Solid* ps : solids)
	ps->render();
	glPopMatrix();
}
void Composite::update(double &dt) {
	Solid::update(dt);
	//for (Solid* ps : solids) {
	//	ps->update(dt);
	//}
	for (vector<Solid*>::iterator i = solids.begin(); i < solids.end(); i++) {
		Solid* &s = *i;
		//(*(*i)).update(dt);
		//(*i)->update(dt);
		s->update(dt);
	}
}
ostream& operator<<(ostream& os, const Composite& c) {
	os << static_cast<const Solid&>(c);
	os << "{";
	for (Solid* ps : c.solids) {
		os << *ps << endl;
	}
	os << "}";
	return os;
}
