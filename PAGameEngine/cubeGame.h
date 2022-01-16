#pragma once
#include "game.h"
#include "cubeScene.h"


class CubeGame : public Game {
	int lineCounter = 0;

public:
	CubeGame() : Game() {}



	void init() {

		srand(time(NULL));

		CubeScene* mainMenu = new(nothrow) CubeScene();
		Text* title = new Text("SPACE PILOT");
		title->setPos(Vector3D(-1.9, 4, 3));
		title->setColor(Vector3D(1, 1, 1));
		mainMenu->add(title);
		Text* play = new Text("Pulsa espacio para jugar");
		play->setPos(Vector3D(-2.7, 2, 3));
		play->setColor(Vector3D(1, 1, 1));
		mainMenu->add(play);
		Text* controles = new Text("CONTROLES");
		controles->setPos(Vector3D(-1.9, 0, 3));
		controles->setColor(Vector3D(1, 1, 1));
		mainMenu->add(controles);
		Text* controles1 = new Text("W,A,S,D : Control de la nave");
		controles1->setPos(Vector3D(-3.4, -1, 3));
		controles1->setColor(Vector3D(1, 1, 1));
		mainMenu->add(controles1);
		Text* controles2 = new Text("C : Cambiar camara");
		controles2->setPos(Vector3D(-2.2, -2, 3));
		controles2->setColor(Vector3D(1, 1, 1));
		mainMenu->add(controles2);
		Text* trabajo = new Text("Trabajo realizado por Antonio Espinosa Garcia y Rodrigo Garcia Suarez");
		trabajo->setPos(Vector3D(-5.5, -6.0, 3));
		trabajo->setColor(Vector3D(1, 1, 1));
		mainMenu->add(trabajo);

		mainMenu->setGame(this);
		this->addScene(mainMenu);
		this->setActiveScene(mainMenu);

		LoaderOBJ lobj(1);
		LoaderOBJ::setBasePath(".\\3dModels");
		CubeScene* chooseSc = new(nothrow) CubeScene();
		Light* light0 = new Light(Vector3D(0, -20, -20));
		chooseSc->add(light0);
		ModelMeshTriangles* ship1 = new ModelMeshTriangles();
		lobj.loadModel("ship1.obj");
		*ship1 = lobj.getModelMeshTriangles();
		ship1->setColor(Vector3D(0, 1, 0));
		ship1->setPos(Vector3D(-5, 0, 10));
		ship1->setRotVel(Vector3D(0, 3, 0));
		chooseSc->add(ship1);
		LoaderOBJ lobj2(1);
		ModelMeshTriangles* ship2 = new ModelMeshTriangles();
		lobj2.loadModel("ship2.obj");
		*ship2 = lobj2.getModelMeshTriangles();
		ship2->setColor(Vector3D(1, 0, 0));
		ship2->setPos(Vector3D(0, 0, 10));
		ship2->setRotVel(Vector3D(0, 3, 0));
		chooseSc->add(ship2);
		LoaderOBJ lobj3(1);
		ModelMeshTriangles* ship3 = new ModelMeshTriangles();
		lobj3.loadModel("ship3.obj");
		*ship3 = lobj3.getModelMeshTriangles();
		ship3->setColor(Vector3D(0, 0, 1));
		ship3->setPos(Vector3D(5, 0, 10));
		ship3->setRotVel(Vector3D(0, 3, 0));
		chooseSc->add(ship3);
		Text* ch = new Text("ELIGE TU NAVE");
		ch->setPos(Vector3D(-2, 6, 3));
		ch->setColor(Vector3D(1, 1, 1));
		chooseSc->add(ch);

		Text* one = new Text("Pulsa 1");
		one->setPos(Vector3D(-9, 4, 3));
		one->setColor(Vector3D(1, 1, 1));
		chooseSc->add(one);
		Text* oneInfo = new Text("Baja maniobrabilidad");
		oneInfo->setPos(Vector3D(-10, -4, 3));
		oneInfo->setColor(Vector3D(1, 1, 1));
		chooseSc->add(oneInfo);


		Text* two = new Text("Pulsa 2");
		two->setPos(Vector3D(-1, 4, 3));
		two->setColor(Vector3D(1, 1, 1));
		chooseSc->add(two);
		Text* twoInfo = new Text("Media maniobrabilidad");
		twoInfo->setPos(Vector3D(-2, -4, 3));
		twoInfo->setColor(Vector3D(1, 1, 1));
		chooseSc->add(twoInfo);


		Text* three = new Text("Pulsa 3");
		three->setPos(Vector3D(7, 4, 3));
		three->setColor(Vector3D(1, 1, 1));
		chooseSc->add(three);
		Text* threeInfo = new Text("Alta maniobrabilidad");
		threeInfo->setPos(Vector3D(6, -4, 3));
		threeInfo->setColor(Vector3D(1, 1, 1));
		chooseSc->add(threeInfo);

		this->addScene(chooseSc);
		chooseSc->setGame(this);


		CubeScene* mainSc = new(nothrow) CubeScene();
		Player* jugador = new Player(1);
		jugador->setNombre("JugadorActual");
		mainSc->setPlayer(jugador);
		Ranking* ranking1 = new Ranking();
		mainSc->setRanking(ranking1);
		Light* light1 = new Light(Vector3D(0, -100, 0));
		mainSc->add(light1);
		Text* infoV = new Text(" ");
		infoV->setPos(Vector3D(-2, -1, 18));
		infoV->setColor(Vector3D(1, 1, 1));
		mainSc->add(infoV);
		Text* infoP = new Text("Puntuacion: ");
		infoP->setPos(Vector3D(-2, -1.05, 18));
		infoP->setColor(Vector3D(1, 1, 1));
		mainSc->add(infoP);

		Text* ranking = new Text("RANKING");
		ranking->setPos(Vector3D(-2, 1, 18));
		ranking->setColor(Vector3D(1, 1, 1));
		mainSc->add(ranking);

		float bajar = -0.05;
		if (existe("ranking.txt") == 0) {
			ofstream crearRanking;
			crearRanking.exceptions(ofstream::failbit | ofstream::badbit);
			try {
				crearRanking.open("ranking.txt");
			}
			catch (exception& e) {
				cout << e.what() << "linea 71 cubegame.h" << endl;
			}
			if (crearRanking.is_open())
			{
				//crearRanking
				crearRanking.close();
			}
			else {
				cout << "Error abriendo el fichero";
			}
		}
		else {
			mainSc->getRanking()->abrirRanking(true, jugador, contadorlineas);
			mainSc->getRanking()->actualizar(0);
			string line0;
			int i = 1;
			while ((i - 1) < contadorlineas) {
				line0 = "" + mainSc->getRanking()->getNombres(i - 1) + ": " + to_string(mainSc->getRanking()->getPuntuaciones(i - 1));
				Text* puntuacion = new Text(line0);
				puntuacion->setPos(Vector3D(-2, 1 + bajar, 18));
				puntuacion->setColor(Vector3D(1, 1, 1));
				mainSc->add(puntuacion);
				bajar += -0.05;
				i++;
			}
		}


		Text* puntuacionPlayer = new Text("" + mainSc->getPlayer()->getNombre() + ":" + to_string(mainSc->getPlayer()->getPuntos()));
		puntuacionPlayer->setPos(Vector3D(-2, 1 + bajar, 18));
		puntuacionPlayer->setColor(Vector3D(1, 1, 1));
		mainSc->add(puntuacionPlayer);

		mainSc->setGame(this);
		this->addScene(mainSc);

		//mainSc->saveRanking(true, jugador);
		//this->setActiveScene(mainSc);


		CubeScene* deathSc = new(nothrow) CubeScene();
		Text* death = new Text("HAS MUERTO");
		death->setPos(Vector3D(-1.5, 1, 3));
		death->setColor(Vector3D(1, 1, 1));
		deathSc->add(death);
		Text* back = new Text("Pulse 1 para guardar su puntuacion en la consola y cerrar el juego");
		back->setPos(Vector3D(-4.5, -1, 3));
		back->setColor(Vector3D(1, 1, 1));
		deathSc->add(back);
		Text* expl = new Text("Su puntuacion se guardara para la proxima vez que se inicie el juego");
		expl->setPos(Vector3D(-5, -2, 3));
		expl->setColor(Vector3D(1, 1, 1));
		deathSc->add(expl);
		deathSc->setGame(this);
		this->addScene(deathSc);
		//this->setActiveScene(deathSc);
	}

	void update() {
		milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD)
		{


			this->getActiveScene()->update(TIME_INCREMENT);
			this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
		}

	}

	void processKeyPressed(unsigned char key, int x, int y) {
		this->getActiveScene()->processKeyPressed(key, x, y);
	}


};