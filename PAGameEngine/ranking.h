#pragma once
#include "util.h"
#include "player.h"

class Ranking {
private:
	vector<string> nombres;
	vector<long int> puntuaciones;
	vector<long int>::size_type sizePuntuaciones;
public:
	Ranking(){
	}
	string getNombres(int i) { return this->nombres[i]; }
	long int getPuntuaciones(int i) { return this->puntuaciones[i]; }

	void abrirRanking(bool player, Player* player1, int &contadorlineas) {
		ifstream leerRanking;
		leerRanking.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			leerRanking.open("ranking.txt");
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		string line;
		if (leerRanking.is_open()) {
			try {
				while (getline(leerRanking, line)) {
					istringstream iss(line);
					string cosa;
					int i = 0;
					while (getline(iss, cosa, ':')) { //Separamos las palabras y los numeros y los metemos en dos vectores diferentes
						if (i == 0) {
							nombres.push_back(cosa);
							i++;
						}
						else {
							stringstream val0(cosa);
							long int val = 0;
							val0 >> val;
							puntuaciones.push_back(val);
						}
					}
					contadorlineas++;
				}
			}
			catch (exception& e) {
				if (&ifstream::eof) {
					goto endOfLoop;
				}
			}
		endOfLoop:
			leerRanking.close();
		}
		else {
			cout << "Error abriendo el fichero" << endl;
		}
		if (player) {//solo es verdadero la primera vez, para meter al jugador actual
			nombres.push_back(player1->getNombre());
			puntuaciones.push_back(player1->getPuntos());
		}
	}

	void actualizar(int pts) {
		//Actualizamos el jugador y si hay instancias repetidas las borramos
		sizePuntuaciones = puntuaciones.size();
		int numNombres = 0;
		for (unsigned i = sizePuntuaciones - 1; i > 0; i--) {
			if (nombres[i] == "JugadorActual") {
				if (numNombres == 0) {
					puntuaciones[i] = pts;
					numNombres++;
				}
				else {
					nombres.erase(nombres.begin() + i);
					puntuaciones.erase(puntuaciones.begin() + i);
					sizePuntuaciones--;
				}
			}
		}
		//Comprobación extra para la posicion 0 del array, ya que el bucle anterior no pasa por ella
		if (nombres[0] == "JugadorActual") {
			if (numNombres == 0) {
				puntuaciones[0] = pts;
				numNombres++;
			}
			else {
				nombres.erase(nombres.begin());
				puntuaciones.erase(puntuaciones.begin());
				sizePuntuaciones--;
			}
		}

		//Algoritmo de burbuja para ordenar las puntuaciones
		for (unsigned i = 0; i < sizePuntuaciones - 1; i++) {
			for (unsigned j = 0; j < sizePuntuaciones - i - 1; j++) {
				if (puntuaciones[j] < puntuaciones[j + 1]) {
					cambiar(&puntuaciones[j], &puntuaciones[j + 1]);
					cambiarString(&nombres[j], &nombres[j + 1]);
				}
			}
		}
	}
	void guardarRanking() {
		//Guardar las puntuaciones en el fichero
		ofstream guardarRanking;
		guardarRanking.exceptions(ofstream::failbit | ofstream::badbit);
		try {
			guardarRanking.open("ranking.txt");
		}
		catch (exception& e) {
			cout << e.what() << "linea 225 cubescene.h" << endl;
		}
		if (guardarRanking.is_open()) {
			for (unsigned i = 0; i < sizePuntuaciones; i++) {
				guardarRanking << nombres[i] << ": " << puntuaciones[i] << endl;
			}
			guardarRanking.close();
		}
		else {
			cout << "Error abriendo el fichero";
		}
	}

	void sustituirNombre(string name) {
		for (unsigned i = 0; i < sizePuntuaciones; i++) {
			if (nombres[i] == "JugadorActual") {
				nombres[i] = name;
			}
		}
	}
};

