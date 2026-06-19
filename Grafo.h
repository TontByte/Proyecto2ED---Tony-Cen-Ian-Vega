#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <SFML/Graphics.hpp>
#include "ArrayList.h"
#include "Config.h"
#include "Nodo.h"
#include "Arco.h"
#include "MinHeap.h"

using std::cout;
using std::endl;
using std::runtime_error;
using std::sqrt;

class Grafo{
private:
	ArrayList<Nodo*> listaNodos;
	ArrayList<Arco*> listaArcos;

public:
	Grafo() : listaNodos(CANT_NODOS), listaArcos(CANT_NODOS * MAX_CONEXIONES) {}

	~Grafo() {
		clear();
	}

	ArrayList<Nodo*>& getListaNodos() {
		return listaNodos;
	}

	ArrayList<Arco*>& getListaArcos() {
		return listaArcos;
	}

	Arco* findArco(Nodo* a, Nodo* b) {
		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			Arco* arcoActual = listaArcos.getElement();
			Nodo* actualA = arcoActual->nodoA;
			Nodo* actualB = arcoActual->nodoB;

			if ((actualA == a && actualB == b) || (actualA == b && actualB == a)) {
				return arcoActual;
			}
		}
		return nullptr;
	}

	void clear() {
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			delete listaNodos.getElement();
		}
		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			delete listaArcos.getElement();
		}
		listaNodos.clear();
		listaArcos.clear();
	}

	void generarGrafo() {
		clear();

		//se crean los nodos
		for (int i = 0; i < CANT_NODOS; i++) {
			int x = rand() % (X_VENTANA - 40) + 20;
			int y = rand() % (Y_VENTANA - 40) + 20;
			Nodo* nuevoNodo = new Nodo(i, x, y);
			listaNodos.append(nuevoNodo);
		}

		//conectar con vecinos
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			Nodo* nodoA = listaNodos.getElement();
			int cantConexiones = nodoA->getVecinos().getSize();

			if (cantConexiones >= MAX_CONEXIONES) {
				continue;
			}

			MinHeap<Arco> candidatosVecinos(CANT_NODOS);

			for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
				Nodo* nodoB = listaNodos.getElement();
				if (nodoA == nodoB) {
					continue;
				}

				if (nodoA->isClose(*nodoB)) {
					float dx = static_cast<float>(nodoB->getXCoord() - nodoA->getXCoord());
					float dy = static_cast<float>(nodoB->getYCoord() - nodoA->getYCoord());
					float distancia = sqrt(dx * dx + dy * dy);

					Arco candidato(nodoA, nodoB, distancia);
					candidatosVecinos.insert(candidato);
				}
			}

			listaNodos.goToStart();
			while (listaNodos.getElement() != nodoA) {
				listaNodos.next();
			}

			while (!candidatosVecinos.isEmpty() && cantConexiones < MAX_CONEXIONES) {
				Arco arcoGanador = candidatosVecinos.removeFirst();
				Nodo* nodoB = arcoGanador.nodoB;

				if (nodoB->getVecinos().getSize() >= MAX_CONEXIONES) {
					continue;
				}

				bool duplicado = false;
				for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
					Arco* current = listaArcos.getElement();
					if (current->exists(nodoA, nodoB)) {
						duplicado = true;
						break;
					}
				}

				if (!duplicado) {
					nodoA->agregarVecino(nodoB);
					nodoB->agregarVecino(nodoA);

					Arco* arcoNuevo = new Arco(nodoA, nodoB, arcoGanador.peso);
					listaArcos.append(arcoNuevo);
					cantConexiones++;
				}
			}
		}
		listaNodos.goToStart();
	}

	void resetGrafo() {
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			Nodo* n = listaNodos.getElement();
			n->setVisited(false);
			n->setPadre(nullptr);
			n->setDistancia(std::numeric_limits<float>::max());
		}
		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			Arco* a = listaArcos.getElement();
			a->partOfTree = false;
		}
	}

	void draw(sf::RenderWindow& window, sf::Font& font) {
		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			listaArcos.getElement()->draw(window);
		}
		
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			listaNodos.getElement()->draw(window, font);
		}
	}
	Nodo* obtenerNodoPorNumero(int numero) {
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			Nodo* nodo = listaNodos.getElement();
			if (nodo->getNumNodo() == numero) {
				return nodo;
			}
		}
		return nullptr;
	}

	Arco* obtenerArco(Nodo* a, Nodo* b) {
		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			Arco* arco = listaArcos.getElement();
			if (arco->exists(a, b)) {
				return arco;
			}
		}
		return nullptr;
	}

	float obtenerPeso(Nodo* a, Nodo* b) {
		Arco* arco = obtenerArco(a, b);

		if (arco == nullptr) {
			return std::numeric_limits<float>::max();
		}

		return arco->peso;
	}
	void ejecutarDFS(Nodo* inicio) {
		resetGrafo();

		if (inicio == nullptr) {
			return;
		}

		ArrayList<Nodo*> pila(CANT_NODOS);

		inicio->setVisited(true);
		pila.append(inicio);

		while (pila.getSize() > 0) {
			pila.goToPos(pila.getSize() - 1);
			Nodo* actual = pila.remove();

			ArrayList<Nodo*>& vecinos = actual->getVecinos();

			for (vecinos.goToStart(); !vecinos.atEnd(); vecinos.next()) {
				Nodo* vecino = vecinos.getElement();

				if (!vecino->getVisited()) {
					vecino->setVisited(true);
					vecino->setPadre(actual);

					Arco* arco = obtenerArco(actual, vecino);
					if (arco != nullptr) {
						arco->partOfTree = true;
					}

					pila.append(vecino);
				}
			}
		}
	}
	void ejecutarBFS(Nodo* inicio) {
		resetGrafo();

		if (inicio == nullptr) {
			return;
		}

		ArrayList<Nodo*> cola(CANT_NODOS);

		inicio->setVisited(true);
		cola.append(inicio);

		while (cola.getSize() > 0) {
			cola.goToStart();
			Nodo* actual = cola.remove();

			ArrayList<Nodo*>& vecinos = actual->getVecinos();

			for (vecinos.goToStart(); !vecinos.atEnd(); vecinos.next()) {
				Nodo* vecino = vecinos.getElement();

				if (!vecino->getVisited()) {
					vecino->setVisited(true);
					vecino->setPadre(actual);

					Arco* arco = obtenerArco(actual, vecino);
					if (arco != nullptr) {
						arco->partOfTree = true;
					}

					cola.append(vecino);
				}
			}
		}
	}
};

