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
	static void ejecutarDFS(Nodo* inicio, Grafo& grafo) {
		if (inicio == nullptr) {
			return;
		}

		inicio->setVisited(true);
		ArrayList<Nodo*>& vecinos = inicio->getVecinos();
		for (int i = 0; i < vecinos.getSize(); i++) {
			vecinos.goToPos(i);
			Nodo* vecino = vecinos.getElement();
			if (vecino != nullptr && !vecino->getVisited()) {
				Arco* arcoConector = grafo.findArco(inicio, vecino);
				if (arcoConector != nullptr) {
					arcoConector->partOfTree = true;
				}
				ejecutarDFS(vecino, grafo);
			}
		}
	}

	static void ejecutarBFS(Nodo* inicio, Grafo& grafo) {

	}

	static void ejecutarPrim(Grafo& grafo, Nodo* inicio) {

	}

	static void ejecutarKruskal(Grafo& grafo) {
		//escribir algoritmo kruskal aqui
	}

	static void ejecutarDijkstra(Nodo* inicio, Nodo* destino, Grafo& grafo) {
		//escribir algoritmo de dijkstra aqui
	}
};

