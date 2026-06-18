#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
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

			int cantConexiones = 0;
			while (!candidatosVecinos.isEmpty() && cantConexiones < MAX_CONEXIONES) {
				Arco arcoGanador = candidatosVecinos.removeFirst();
				Nodo* nodoB = arcoGanador.nodoB;
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
				else {
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

	void draw(sf::RenderWindow& window) {
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			listaNodos.getElement()->draw(window);
		}

		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			listaArcos.getElement()->draw(window);
		}
	}
};

