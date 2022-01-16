#include "game.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

inline double getRand(double min, double max) {
	static const int PRECISION = 10000;
	double n = max - min;
	int ir = rand() % PRECISION;
	double r = min + (double)ir / PRECISION * n;
	return r;
}

inline double getRand(double max = 1) { return getRand(0, max); }

vector<string> split0(string line) {
	string word;
	vector<string> words;
	istringstream ss(line);
	while (cin >> word) {
		words.push_back(word);
	}
	return words;
}

vector<string> split(string line, char delim = ' ') {
	string word;
	vector<string> words;
	istringstream ss(line);
	while (getline(ss, word, delim)) {
		words.push_back(word);
	}
	return words;
}

class ExceptionGame :public exception {
public:
	virtual const char* what() const throw() {
		return "Customized ExceptionGame error";
	}
};

void Game::init() {
	srand(11);

	Scene* mainScene = new(nothrow) Scene();

	Light* light = new Light(Vector3D(1, 0, 0));
	mainScene->add(light);

	Text* pHola = new Text("Hola PA");
	pHola->setVel(Vector3D(0, 0.5, 0.5));
	mainScene->add(pHola);
	Cube* cube0 = new Cube();
	cube0->setPos(Vector3D(0, 0, 0));
	cube0->setVel(Vector3D(1, 0, 0));
	cube0->setRot(Vector3D(45, 33, 27));
	cube0->setRotVel(Vector3D(15, 23, 12));
	cube0->setColor(Vector3D(0.1, 0.2, 0.8));
	mainScene->add(cube0);

	LoaderOBJ::setBasePath(".\\3dModels");
	LoaderOBJ lobj(0.5);
	ModelMeshTriangles* diamond = new ModelMeshTriangles();
	lobj.loadModel("Diamond.obj");
	*diamond = lobj.getModelMeshTriangles();
	diamond->setColor(Vector3D(1,1,1));
	diamond->setPos(Vector3D(2, 4, 3));
	diamond->setVel(Vector3D(1, 0, 1));
	diamond->setRotVel(Vector3D(0, 23, 0));
	mainScene->add(diamond);

	LoaderOBJ lobj2(1.3);
	ModelMeshTriangles* gearCoin = new ModelMeshTriangles();
	lobj2.loadModel("GearCoin.obj");
	*gearCoin = lobj2.getModelMeshTriangles();
	gearCoin->setColor(Vector3D(0.3, 1, 0.0));
	gearCoin->setPos(Vector3D(1, 3, 2));
	gearCoin->setVel(Vector3D(0.2, 0, 0));
	gearCoin->setRot(Vector3D(30, 30, 0));
	gearCoin->setRotVel(Vector3D(15, 5, 0));
	mainScene->add(gearCoin);

	LoaderOBJ lobj3(2);
	ModelMeshTriangles* bolt = new ModelMeshTriangles();
	lobj3.loadModel("Bolt.obj");
	*bolt = lobj3.getModelMeshTriangles();
	bolt->setColor(Vector3D(1, 0.4, 0.0));
	bolt->setPos(Vector3D(2, 1, 1));
	bolt->setVel(Vector3D(0, 1, 0));
	bolt->setRotVel(Vector3D(0, 50, 0));
	mainScene->add(bolt);

	this->scenes.push_back(mainScene);
	this->activeScene = mainScene;

	Scene* secondaryScene = new(nothrow) Scene();

	Light* light2 = new Light(Vector3D(1, 0, 0));
	secondaryScene->add(light2);

	Sphere* ball0 = new Sphere();
	ball0->setPos(Vector3D(2, 3, 1));
	ball0->setVel(Vector3D(1, 1, 1));
	ball0->setColor(Vector3D(0.2, 0.7, 0.1));
	secondaryScene->add(ball0);

	Cuboid* floor = new Cuboid();
	floor->setPos(Vector3D(5, 0, 5));
	floor->setColor(Vector3D(0.1, 0.5, 0.3));
	floor->setHeight(0.1);
	floor->setLength(10);
	floor->setWidth(10);
	secondaryScene->add(floor);

	Cuboid* wall = new Cuboid();
	wall->setPos(Vector3D(0, 5, 5));
	wall->setColor(Vector3D(0.2, 0.2, 0.2));
	wall->setHeight(10);
	wall->setLength(0.1);
	wall->setWidth(10);
	secondaryScene->add(wall);

	Cuboid* wall2 = new Cuboid();
	wall2->setPos(Vector3D(5, 5, 0));
	wall2->setColor(Vector3D(0.4, 0.7, 0.9));
	wall2->setHeight(10);
	wall2->setLength(10);
	wall2->setWidth(0.1);
	secondaryScene->add(wall2);

	this->scenes.push_back(secondaryScene);
}

void Game::init(const string& file)
{
	LoaderOBJ::setBasePath(".\\3dModels");

	ifstream inputFileStream(file);
	json jsonInfo;
	if (inputFileStream.is_open() && inputFileStream.good())
	{
		inputFileStream >> jsonInfo;

		cout << jsonInfo << endl;

		for (int idx = 0; idx < jsonInfo.at("scenes").size(); idx++)
		{
			json currentScene = jsonInfo.at("scenes").at(idx);

			Scene* scene = new Scene();
			scene->setSize(Vector3D(currentScene.at("size").at("x"), currentScene.at("size").at("y"), currentScene.at("size").at("z")));
			
			for (int idx2 = 0; idx2 < currentScene.at("objects").size(); idx2++)
			{
				json currentObject = currentScene.at("objects").at(idx2);
				if (currentObject.at("type") == "light")
				{
					Light* light = new Light();
					light->setPos(Vector3D(currentObject.at("position").at("x"), currentObject.at("position").at("y"), currentObject.at("position").at("z")));
					scene->add(light);
				}
				else if (currentObject.at("type") == "cube")
				{
					Cube* cube = new Cube();
					cube->setPos(Vector3D(currentObject.at("position").at("x"), currentObject.at("position").at("y"), currentObject.at("position").at("z")));
					cube->setVel(Vector3D(currentObject.at("speed").at("x"), currentObject.at("speed").at("y"), currentObject.at("speed").at("z")));
					cube->setColor(Vector3D(currentObject.at("color").at("x"), currentObject.at("color").at("y"), currentObject.at("color").at("z")));
					cube->setRot(Vector3D(currentObject.at("rotation").at("x"), currentObject.at("rotation").at("y"), currentObject.at("rotation").at("z")));
					cube->setRotVel(Vector3D(currentObject.at("rotationSpeed").at("x"), currentObject.at("rotationSpeed").at("y"), currentObject.at("rotationSpeed").at("z")));
					cube->setSize(currentObject.at("size"));
					scene->add(cube);
				}
				else if (currentObject.at("type") == "sphere")
				{
					Sphere* sphere = new Sphere();
					sphere->setPos(Vector3D(currentObject.at("position").at("x"), currentObject.at("position").at("y"), currentObject.at("position").at("z")));
					sphere->setVel(Vector3D(currentObject.at("speed").at("x"), currentObject.at("speed").at("y"), currentObject.at("speed").at("z")));
					sphere->setColor(Vector3D(currentObject.at("color").at("x"), currentObject.at("color").at("y"), currentObject.at("color").at("z")));
					sphere->setSize(currentObject.at("size"));
					scene->add(sphere);
				}
				else if (currentObject.at("type") == "model")
				{
					LoaderOBJ lobj(currentObject.at("scale"));
					ModelMeshTriangles* model = new ModelMeshTriangles();
					lobj.loadModel(currentObject.at("file"));
					*model = lobj.getModelMeshTriangles();
					model->setPos(Vector3D(currentObject.at("position").at("x"), currentObject.at("position").at("y"), currentObject.at("position").at("z")));
					model->setVel(Vector3D(currentObject.at("speed").at("x"), currentObject.at("speed").at("y"), currentObject.at("speed").at("z")));
					model->setColor(Vector3D(currentObject.at("color").at("x"), currentObject.at("color").at("y"), currentObject.at("color").at("z")));
					model->setRot(Vector3D(currentObject.at("rotation").at("x"), currentObject.at("rotation").at("y"), currentObject.at("rotation").at("z")));
					model->setRotVel(Vector3D(currentObject.at("rotationSpeed").at("x"), currentObject.at("rotationSpeed").at("y"), currentObject.at("rotationSpeed").at("z")));
					scene->add(model);
				}
			}
			this->scenes.push_back(scene);
		}
		this->activeScene = this->scenes[0];
	}
	else
	{
		cout << "Error leyendo archivo: " << file << endl;
	}
}

void Game::render() {
	this->activeScene->render();
}

void Game::update() {

	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD)
	{
		this->activeScene->update(TIME_INCREMENT);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}

}

void Game::processKeyPressed(unsigned char key, int x, int y) {
	switch (key)
	{
	case '1':
		if (this->scenes[0] != nullptr)
		{
			this->activeScene = this->scenes[0];
		}
		break;
	case '2':
		if (this->scenes[1] != nullptr)
		{
			this->activeScene = this->scenes[1];
		}
		break;
	}
	this->activeScene->processKeyPressed(key, x, y);
}

void Game::processMouseMovement(int x, int y) {
	this->activeScene->processMouseMovement(x, y);
}

void Game::processMouseClick(int button, int state, int x, int y) {
	this->activeScene->processMouseClick(button, state, x, y);
}

