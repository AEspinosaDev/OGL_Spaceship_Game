#pragma once
#include <iostream>
#include <cmath>

using namespace std;

template <class S> class Vector3Dx;

typedef Vector3Dx<double> Vector3D;

typedef Vector3Dx<float>  Vector3Df;
typedef Vector3Dx<double> Vector3Dd;
typedef Vector3Dx<int>    Vector3Di;

template<class S>
class Vector3Dx {
	S x,y,z;
public:
	Vector3Dx():x(0), y(0), z(0) {}
	Vector3Dx(S x, S y, S z = 0):x(x), y(y), z(z) {}
	inline S getX() const { return x; }
	inline S getY() const { return y; }
	inline S getZ() const { return z; }
	inline void setX(S d) { x = d; }
	inline void setY(S d) { y = d; }
	inline void setZ(S d) { z = d; }
	Vector3Dx<S> operator+(Vector3Dx<S> v);
	Vector3Dx<S> operator-(Vector3Dx<S> v);
	Vector3Dx<S> operator-();
	Vector3Dx<S> operator*(S s);
	Vector3Dx<S> operator/(S s);
	S operator*(Vector3Dx<S> v);
	//Vector product
	Vector3Dx<S> X(Vector3Dx<S> v);
	S norm2();
	S norm();
	S length();
	S distance(Vector3Dx<S> v);
	Vector3Dx<S> normalized();
	Vector3Dx<S> project(Vector3Dx<S> v);
	Vector3Dx<S> coproject(Vector3Dx<S> a);
	void imprime();
	//friend ostream& operator<<(ostream& os, const Vector3D<S>& v);
};
template <class S=double>
ostream& operator<<(ostream& os, const Vector3Dx<S>& v) {
	os << v.getX() << "," << v.getY() << "," << v.getZ();
	return os;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::operator+(Vector3Dx<S> v) {
	Vector3Dx<S> r(this->getX() + v.getX(),
		this->getY() + v.getY(),
		this->getZ() + v.getZ());
	return r;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::operator-(Vector3Dx<S> v) {
	return Vector3Dx<S>(x - v.x, y - v.y, z - v.z);
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::operator-() { return Vector3Dx<S>(-x, -y, -z); }
template <class S>
Vector3Dx<S> Vector3Dx<S>::operator*(S s) {
	Vector3Dx<S> r;
	r.setX(this->getX() * s);
	r.setY(this->getY() * s);
	r.setZ(this->getZ() * s);
	return r;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::operator/(S s) {
	Vector3Dx<S> r;
	r.x = this->getX() / s;
	r.y = this->getY() / s;
	r.z = this->getZ() / s;
	return r;
}
template <class S>
S Vector3Dx<S>::operator*(Vector3Dx<S> v) {
	S s;
	s = this->getX() * v.getX() + this->getY() * v.getY() + this->getZ() * v.getZ();
	return s;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::X(Vector3Dx<S> v1) {
	Vector3Dx<S>& v2 = *this;
	Vector3Dx<S> r(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
	return r;
}
template <class S>
S Vector3Dx<S>::norm2() {
	S s;
	Vector3Dx<S>& este = *this;
	//s= x*x + y*y + z*z;
	s = este * este;//(*this)*(*this) <=> this->operator*(*this)
	return s;
}
template <class S>
S Vector3Dx<S>::norm() {
	Vector3Dx<S>& este = *this;
	S s;
	s = sqrt(este.norm2());
	return s;
}
template <class S>
S Vector3Dx<S>::length() {
	return norm();
}
template <class S>
S Vector3Dx<S>::distance(Vector3Dx<S> v) {
	Vector3Dx<S> dif;
	dif.setX(v.getX() - (*this).getX());
	dif.setY(v.getY() - this->getY());
	dif.setZ(v.getZ() - this->getZ());
	S d;
	d = dif.norm();
	return d;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::normalized() {
	Vector3Dx<S> r;
	S l;
	Vector3Dx<S>& este = *this;
	l = norm();
	r = este / l;
	return r;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::project(Vector3Dx<S> v) {
	Vector3Dx<S> n;
	Vector3Dx<S> r;
	n = this->normalized();
	S prjL;
	prjL = n * v;
	r = n * prjL;
	return r;
}
template <class S>
Vector3Dx<S> Vector3Dx<S>::coproject(Vector3Dx<S> a) {
	Vector3Dx<S> a1;
	Vector3Dx<S> a2;
	a1 = this->project(a);
	a2 = a - a1;
	return a2;
}
template <class S>
void Vector3Dx<S>::imprime() {
	cout << this->getX() << "," << this->getY() << "," << this->getZ() << endl;
}
