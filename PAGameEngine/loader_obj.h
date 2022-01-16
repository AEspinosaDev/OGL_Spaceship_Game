#pragma once
#include <fstream>
#include <sstream>
#include "model_mesh_triangles.h"
class LoaderOBJ{
	double s;
	ModelMeshTriangles m;
	vector<Vector3D> vertex;
	vector<Vector3D> normals;
	vector<Vector3D> textures;
	static string basePath;

	float maxX, maxY, maxZ;
	float minX, minY, minZ;
	inline float getWidth() { return maxX - minX; }
	inline float getHeight() { return maxY - minY; }
	inline float getLength() { return maxZ - minZ; }

public:
	LoaderOBJ(double s=1) :s(s) {}
	ModelMeshTriangles getModelMeshTriangles() { return m; }
	void loadModel(const string &fileName);
	Vector3D parseLineToVector3D(const string &line);
	Triangle parseTriangle(const string& line);
	static string getBasePath() { return basePath; }
	static void setBasePath(string s) {  basePath = s; }
	
	void calcBoundaries(Vector3D v);
	Triangle center(Triangle t);

};


