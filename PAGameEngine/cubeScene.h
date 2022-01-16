#pragma once
#include "scene.h"
#include "player.h"
#include "cubeGame.h"
#include "game.h"
#include "proceduralGenerator.h"
#include "obstacle.h"
#include "ranking.h"

class CubeScene : public Scene {
private:
	Player* player;
	Game* game;
	ProceduralGenerator* g;
	Ranking* ranking;
	int counter;
	float difficulty;
	int factor;
	bool firstPerson;
public:
	CubeScene(int c = 0, int d = 0, int f = 24, bool state = false) : Scene(), counter(c), difficulty(d), factor(f), firstPerson(state) {
		this->player = NULL;
	}
	~CubeScene() {
		delete player;
		delete game;
		delete g;
	}
	inline Player* getPlayer() { return this->player; }
	inline void setPlayer(Player* p) { this->player = p; }
	inline Game* getGame() { return this->game; }
	inline void setGame(Game* g) { this->game = g; }
	inline void setCounter(int c) { this->counter = c; }
	inline int& getCounter() { return this->counter; }
	inline ProceduralGenerator*& getGenerator() { return this->g; }
	inline void setGenerator(ProceduralGenerator* g) { this->g = g; }
	inline Ranking* getRanking() { return this->ranking; }
	inline void setRanking(Ranking* r) { this->ranking = r; }

	void switchCam() {
		if (firstPerson == false) {
			firstPerson = true;
			this->getCam()->setPos(Vector3D(this->player->getPos().getX(), this->player->getPos().getY() - 0.5, this->player->getPos().getZ() + 0.5));
			//this->getCam()->setRot(Vector3D(0, 0, this->player->getRot().getZ()));
		}
		else {
			firstPerson = false;
			this->getCam()->setPos(Vector3D(0, 0, 20));
			//this->getCam()->setRot(Vector3D(0, 0, 0));
		}
	}


	void update(const double& dt) {
		if (this->player != NULL) {
			this->player->update(dt);
		}
		if (this->getGame()->getActiveScene() == this->getGame()->getScene(0)) {
			if (this->getCounter() % 14 == 0) {
				if (this->getGame()->getActiveScene()->getSolid(1)->getColor().getZ() == 1) {

					this->getGame()->getActiveScene()->getSolid(1)->setColor(Vector3D(1, 0, 0));
				}
				else {

					this->getGame()->getActiveScene()->getSolid(1)->setColor(Vector3D(1, 1, 1));
				}
			}
			this->getCounter()++;

		}

		if (this->getGame()->getActiveScene() == this->getGame()->getScene(1)) {
			for (Solid* ps : getSolids()) {
				ps->update(dt);


			}

		}

		if (this->getGame()->getActiveScene() == this->getGame()->getScene(2)) {

			if (firstPerson == true) {
				this->getCam()->setPos(Vector3D(this->player->getPos().getX(), this->player->getPos().getY() - 0.5, this->player->getPos().getZ() + 0.5));
				//this->getCam()->setRot(this->player->getRot());
				//this->getCam()->setRot(Vector3D(0, 0, this->player->getRot().getZ()));
				static_cast<Text*>(this->getGame()->getActiveScene()->getSolid(1))->setPos(Vector3D(Vector3D(this->player->getPos().getX(), this->player->getPos().getY() - 1, this->player->getPos().getZ() - 1)));
				static_cast<Text*>(this->getGame()->getActiveScene()->getSolid(2))->setPos(Vector3D(Vector3D(this->player->getPos().getX() - 0.1, this->player->getPos().getY() - 1.1, this->player->getPos().getZ() - 1)));
			}
			else {
				static_cast<Text*>(this->getGame()->getActiveScene()->getSolid(1))->setPos(Vector3D(Vector3D(this->player->getPos().getX() + 1.5, this->player->getPos().getY() + 1.5, this->player->getPos().getZ())));
				static_cast<Text*>(this->getGame()->getActiveScene()->getSolid(2))->setPos(Vector3D(-2, -1.05, 18));

			}

			if (this->getCounter() % factor == 0) {

				this->add(this->g->generateAsteroid(difficulty));
				if (difficulty >= 5) {
					this->add(this->g->generateAlien(difficulty));
				}
			}
			this->getCounter()++;
			if (difficulty < 10) {
				this->difficulty += 0.002;
			}
			else {

				factor = 14;
			}

			static_cast<Text*>(this->getGame()->getActiveScene()->getSolid(1))->setText(to_string(static_cast<CubeScene*>(this->getGame()->getActiveScene())->getPlayer()->getVidas()));
			static_cast<Text*>(this->getGame()->getActiveScene()->getSolid(2))->setText("Puntuacion: " + to_string(static_cast<CubeScene*>(this->getGame()->getActiveScene())->getPlayer()->getPuntos()));

			if (this->getGame()->contadorlineas != 0) {
				int puntos = static_cast<CubeScene*>(this->getGame()->getActiveScene())->getPlayer()->getPuntos();
				ranking->actualizar(puntos);
				int i = 1;
				float bajar = -0.05;
				string line0 = "";
				while ((i - 1) <= this->getGame()->contadorlineas) {
					line0 = "" + ranking->getNombres(i - 1) + ": " + to_string(ranking->getPuntuaciones(i - 1));
					Text* puntuacion = new Text(line0);
					puntuacion->setPos(Vector3D(-2, 1 + bajar, 18));
					puntuacion->setColor(Vector3D(1, 1, 1));
					this->getGame()->getActiveScene()->getSolid(3 + i);
					this->getGame()->getActiveScene()->getSolid(3 + i) = puntuacion; //Actualizamos los textos en tiempo real para mostrar al jugador
					bajar += -0.05;
					i++;
				}
			}
			else {
				Text* puntuacionPlayer = new Text("" + static_cast<CubeScene*>(this->getGame()->getActiveScene())->getPlayer()->getNombre() + ":" + to_string(static_cast<CubeScene*>(this->getGame()->getActiveScene())->getPlayer()->getPuntos()));
				puntuacionPlayer->setPos(Vector3D(-2, 1 + (-0.05), 18));
				puntuacionPlayer->setColor(Vector3D(1, 1, 1));
				this->getGame()->getActiveScene()->getSolid(4) = puntuacionPlayer;
			}


			vector<Solid*>& v = this->getSolidos();
			auto it = v.begin();
			while (it != v.end()) {
				(*it)->update(dt);
				if ((*it)->getVel().getZ() != 0) {
					Obstacle* obj = static_cast<Obstacle*>((*it));
					this->player->computeColision(obj->getHitBox());
				}
				if ((*it)->getPos().getZ() > 20) {
					delete (*it);
					(*it) = nullptr;
					it = v.erase(it);
				}
				else {
					++it;
				}
			}

			if (this->getPlayer()->checkDestroy() == true) {
				ranking->guardarRanking();
				this->getGame()->setActiveScene(this->getGame()->getScene(3));

				static_cast<CubeScene*>(this->getGame()->getActiveScene())->setRanking(ranking);
				static_cast<CubeScene*>(this->getGame()->getActiveScene())->setPlayer(player);

				INPUT inp[2] = { 0 };
				inp[0].type = INPUT_KEYBOARD;
				inp[0].ki.wVk = VK_F11;
				inp[1].type = INPUT_KEYBOARD;
				inp[1].ki.wVk = VK_F11;
				inp[1].ki.dwFlags = KEYEVENTF_KEYUP;

				SendInput(2, inp, sizeof(INPUT));
				
				
			}

		}



	}

	void render() {
		this->getCam()->render();

		if (this->player != NULL) {
			this->player->render();
		}
		Composite::render();
	}
	void processKeyPressed(unsigned char key, int x, int y) {
		//cout << "Has pulsado la tecla: " << key << endl;
		if (this->player != NULL) {
			this->player->movement(key, x, y);
		}

		if (this->getGame()->getActiveScene() == this->getGame()->getScene(0))
		{
			if (key == ' ') {
				this->getGame()->setActiveScene(this->getGame()->getScene(1));
			}
		}
		if (this->getGame()->getActiveScene() == this->getGame()->getScene(1))
		{
			if (key == '1' || key == '2' || key == '3') {
				int op;
				if (key == '1') op = 1;
				if (key == '2') op = 2;
				if (key == '3') op = 3;
				static_cast<CubeScene*>(this->getGame()->getScene(2))->setPlayer(new Player(op));
				static_cast<CubeScene*>(this->getGame()->getScene(2))->getPlayer()->setNombre("JugadorActual");
				this->getGame()->setActiveScene(this->getGame()->getScene(2));
			}
		}
		if (this->getGame()->getActiveScene() == this->getGame()->getScene(2))
		{
			if (key == 'c' || key == 'C') {
				switchCam();
			}
		}

		if (this->getGame()->getActiveScene() == this->getGame()->getScene(3))
		{
			if (key == '1') {//Basicamente el guardar ranking pero solo se hace al final del juego y pide el nombre
				string name;
				cout << "Introduzca su nombre:" << endl;
				getline(cin, name);
				ranking->sustituirNombre(name);
				int puntos = static_cast<CubeScene*>(this->getGame()->getActiveScene())->getPlayer()->getPuntos();
				ranking->actualizar(puntos);

				ranking->guardarRanking();
				
				exit(0);
			}
		}
	}
	void processMouseMovement(int x, int y) {

	}

	void processMouseClick(int button, int state, int x, int y) {

	}
};
