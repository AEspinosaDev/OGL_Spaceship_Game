#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include "vector3d.h"
#include "cube.h"
#include "sphere.h"
#include "teapot.h"
#include "scene.h"
#include "camera.h"
#include "camera_fly.h"
#include "cylinder.h"
#include "triangle.h"
#include "model_mesh_triangles.h"
#include "loader_obj.h"
#include "light.h"
#include "cuboid.h"
#include "text.h"
#include <chrono>

using namespace std::chrono;
using namespace std;
class Game {

	Scene* activeScene;
	vector<Scene*> scenes;

public:
	int contadorlineas = 0;
	const double TIME_INCREMENT = 0.07; //ms tiempo en el juego
	const int UPDATE_PERIOD = 10; //ms tiempo en el mundo real

	milliseconds initialMilliseconds;
	long lastUpdatedTime;

	Game() : activeScene(nullptr), initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())), lastUpdatedTime(0) {}

	inline Scene* getActiveScene() { return this->activeScene; }
	inline void setActiveScene(Scene* sc) { this->activeScene = sc; }
	inline void addScene(Scene* sc) { this->scenes.push_back(sc); }
	inline Scene* getScene(int i) { return this->scenes[i]; }
	
	void init();
	void init(const string& file);

	void render();
	void update();
	void processKeyPressed(unsigned char key, int x, int y);
	void processMouseMovement(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
};

