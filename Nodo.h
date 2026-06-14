//la clase nodo, utilizada para crear objetos nodo para el grafo
//podriamos crear lo de la matriz para ver si se conectan con otros nodos
#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath> //para usar hypot (de distancia)

using std::cout;
using std::endl;
using std::runtime_error;
using std::hypot;

class Nodo{
public:
	int numNodo;
	int xCoord;
	int yCoord;

	Nodo(int numNodo, int xCoord, int yCoord) {
		this->numNodo = numNodo;
		this->xCoord = xCoord;
		this->yCoord = yCoord;
	}

	bool isClose(Nodo& otro, int maxDist) {
		double dist = hypot(otro.xCoord - xCoord, otro.yCoord - yCoord);
		if (dist <= maxDist) {
			return true;
		}
		else {
			return false;
		}
	}



};

