//la clase nodo, utilizada para crear objetos nodo para el grafo
//podriamos crear lo de la matriz para ver si se conectan con otros nodos
#pragma once
#include <iostream>
#include <stdexcept>
#include "ArrayList.h"
#include "Config.h"

using std::cout;
using std::endl;
using std::runtime_error;

class Nodo{
private:
	int numNodo;
	int xCoord;
	int yCoord;
	bool visited;
	ArrayList<Nodo*> vecinos;

public:
	Nodo(int numNodo, int xCoord, int yCoord) : vecinos(MAX_CONEXIONES) {
		this->numNodo = numNodo;
		this->xCoord = xCoord;
		this->yCoord = yCoord;
		visited = false;
	}

	bool isClose(Nodo& otro) {
		int dx = otro.getXCoord() - xCoord;
		int dy = otro.getYCoord() - yCoord;
		return (dx * dx + dy * dy) <= (MAX_DIST * MAX_DIST);
	}

	void agregarVecino(Nodo* vecino) {
		vecinos.append(vecino);
	}

	int getNumNodo() {
		return numNodo;
	}

	int getXCoord() {
		return xCoord;
	}
	
	int getYCoord() {
		return yCoord;
	}

	bool getVisited() {
		return visited;
	}

	void setVisited(bool value) {
		visited = value;
	}

};

