#include "loader_obj.h"

string LoaderOBJ::basePath = "";

void LoaderOBJ::loadModel(const string& fileName) {
	Vector3D max(-1, -1, -1);
	Vector3D min(1, 1, 1);

	string line;
	string fullPath = basePath + "\\" + fileName;
	ifstream fObj(fullPath);
	if (fObj.is_open()) {
		while (getline(fObj, line)) {
			if (line[0] == 'v' && line[1] == 't') {
				Vector3D vt = parseLineToVector3D(line);
				textures.push_back(vt);
			}
			else if (line[0] == 'v' && line[1] == 'n')
			{
				Vector3D vn = parseLineToVector3D(line);
				normals.push_back(vn);
			}
			else if (line[0] == 'v')
			{
				Vector3D v = parseLineToVector3D(line);
				calcBoundaries(v);
				vertex.push_back(v);
			}
			else if (line[0] == 'f') {
				Triangle t = parseTriangle(line);
				m.add(center(t));
			}
		}
		fObj.close();
	}
	else {
		throw runtime_error("Error openning file: " + fullPath);
	}
}
Vector3D LoaderOBJ::parseLineToVector3D(const string& line) {
	string c;
	istringstream ss(line);
	double x, y, z;
	ss >> c;
	ss >> x;
	ss >> y;
	ss >> z;
	return Vector3D(x, y, z) * s;
}
Triangle LoaderOBJ::parseTriangle(const string& line) {
	char c;
	size_t idx0Vertex, idx1Vertex, idx2Vertex;
	size_t idx0Normal, idx1Normal, idx2Normal;
	
	istringstream ss(line);
	// ejemplo face: f 4//1 1//1 2//1
	ss >> c >> idx0Vertex >> c >> c >> idx0Normal;
	ss >> idx1Vertex >> c >> c >> idx1Normal;
	ss >> idx2Vertex >> c >> c >> idx2Normal;
	Vector3D p0 = vertex[idx0Vertex - 1];
	Vector3D p1 = vertex[idx1Vertex - 1];
	Vector3D p2 = vertex[idx2Vertex - 1];
	Vector3D n = normals[idx0Normal - 1];
	Triangle result(p0, p1, p2);
	result.setN0(n);
	result.setN1(n);
	result.setN2(n);
	return result;
}

void LoaderOBJ::calcBoundaries(Vector3D v) {
	maxX = fmax(maxX, v.getX());
	maxY = fmax(maxY, v.getY());
	maxZ = fmax(maxZ, v.getZ());
	minX = fmin(minX, v.getX());
	minY = fmin(minY, v.getY());
	minZ = fmin(minZ, v.getZ());
}

Triangle LoaderOBJ::center(Triangle t) {
	Vector3D centro(minX + getWidth() / 2.0, minY + getHeight() / 2.0, minZ + getLength() / 2);
	Vector3D p0 = t.getP0();
	Vector3D p1 = t.getP1();
	Vector3D p2 = t.getP2();
	return(Triangle(p0 - centro, p1 - centro, p2 - centro));
}
