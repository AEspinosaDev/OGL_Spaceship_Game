#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

inline double getRand(double min, double max) {
	static const int PRECISION = 10000;
	double n = max - min;
	int ir = rand() % PRECISION;
	double r = min + (double)ir / PRECISION * n;
	return r;
}

inline double getRand(double max = 1) { return getRand(0, max); }

inline vector<string> split0(string line) {
	string word;
	vector<string> words;
	istringstream ss(line);
	while (cin >> word) {
		words.push_back(word);
	}
	return words;
}

inline vector<string> split(string line, char delim = ' ') {
	string word;
	vector<string> words;
	istringstream ss(line);
	while (getline(ss, word, delim)) {
		words.push_back(word);
	}
	return words;
}
inline bool existe(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}
void cambiar(long* xp, long* yp)
{
	long temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void cambiarString(string* xp, string* yp)
{
	string temp = *xp;
	*xp = *yp;
	*yp = temp;
}
