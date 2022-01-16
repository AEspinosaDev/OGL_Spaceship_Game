#pragma once
#include <vector>
#include "triangle.h"
class ModelMeshTriangles:public Solid {
	vector<Triangle> triangles;
public:
	//virtual ~ModelMeshTriangles(){}
	ModelMeshTriangles* clone() {
		return new ModelMeshTriangles(*this);
	}
	vector<Triangle> getTriangles() { return triangles; }
	void setSolids(vector<Triangle> vs) { triangles = vs; }
	Triangle getTriangle(int i) {
		if (i >= triangles.size() || i<0)
			throw runtime_error("Out of range index, with value "+to_string(i)+" at ModelMeshTriangles::getTriangle()");
		return triangles[i]; 
	}
	Triangle operator[](int i)  {
		if (i >= triangles.size() || i < 0)
			throw runtime_error("Out of range index, with value " + to_string(i) + " at ModelMeshTriangles::operator[]");
		return triangles[i]; 
	}
	void add(Triangle t) { triangles.push_back(t); }
	void render();
	virtual void update(double& dt);
	friend ostream& operator<<(ostream& os, const ModelMeshTriangles& m);

	void setColor(Vector3D color);

};

