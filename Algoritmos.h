#pragma once
#include <iostream>
#include <stdexcept>
#include "Nodo.h"
#include "Grafo.h"

using std::cout;
using std::endl;
using std::runtime_error;

class Algoritmos{
public:
	//se usa static void para no tener que instancear algoritmos
	static void ejecutarDFS(Nodo* inicio) {

	}

	static void ejecutarBFS(Nodo* inicio) {

	}

	static void ejecutarPrim(Grafo& grafo, Nodo* inicio) {

	}

	static void ejecutarKruskal(Grafo& grafo) {
		//escribir algoritmo kruskal aqui
	}

	static void ejecutarDijkstra(Nodo* inicio, Nodo* destino) {
		//escribir algoritmo de dijkstra aqui
	}
};

