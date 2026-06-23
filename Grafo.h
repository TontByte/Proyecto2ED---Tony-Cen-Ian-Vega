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
#include "Pair.h"

using std::cout;
using std::endl;
using std::runtime_error;
using std::sqrt;

class UnionFind {
private:
	int* parent;
	int* rango;
	int size;

public:
	UnionFind(int size) {
		this->size = size;
		parent = new int[size];
		rango = new int[size];

		for (int i = 0; i < size; i++) {
			parent[i] = i;
			rango[i] = 0;
		}
	}

	~UnionFind() {
		delete[] parent;
		delete[] rango;
	}

	int find(int nodo) {
		if (parent[nodo] != nodo) {
			parent[nodo] = find(parent[nodo]);
		}

		return parent[nodo];
	}

	bool unir(int a, int b) {
		int raizA = find(a);
		int raizB = find(b);

		if (raizA == raizB) {
			return false;
		}

		if (rango[raizA] < rango[raizB]) {
			parent[raizA] = raizB;
		}
		else if (rango[raizA] > rango[raizB]) {
			parent[raizB] = raizA;
		}
		else {
			parent[raizB] = raizA;
			rango[raizA]++;
		}

		return true;
	}
};

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

				if (nodoA->isClose(nodoB)) {
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

	Nodo* obtenerNodoEnPosicion(sf::Vector2f posicion) {
		for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
			Nodo* nodo = listaNodos.getElement();
			if (nodo->isClicked(posicion)) {
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
		pila.append(inicio);

		while (pila.getSize() > 0) {
			pila.goToPos(pila.getSize() - 1);
			Nodo* actual = pila.remove();

			if (!actual->getVisited()) {
				actual->setVisited(true);

				if (actual->getPadre() != nullptr) {
					Arco* arco = obtenerArco(actual->getPadre(), actual);
					if (arco != nullptr) {
						arco->partOfTree = true;
					}
				}

				ArrayList<Nodo*>& vecinos = actual->getVecinos();
				for (vecinos.goToStart(); !vecinos.atEnd(); vecinos.next()) {
					Nodo* vecino = vecinos.getElement();
					if (!vecino->getVisited()) {
						vecino->setPadre(actual);
						pila.append(vecino);
					}
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

	void ejecutarDijkstra(Nodo* inicio, Nodo* destino) {
		resetGrafo();
		inicio->setDistancia(0.0f);
		MinHeap<Pair<float, Nodo*>> pQueue;
		ArrayList<Nodo*> visitedNodes(CANT_NODOS);
		Pair<float, Nodo*> p(inicio->getDistancia(), inicio);
		pQueue.insert(p);

		while (!pQueue.isEmpty()) {
			Nodo* actual = pQueue.removeFirst().value;
			if (actual == destino) {
				break;
			}
			if (actual->getVisited()) {
				continue;
			}
			actual->setVisited(true);
			visitedNodes.append(actual);

			ArrayList<Nodo*>& vecinos = actual->getVecinos();
			vecinos.goToStart();
			while (!vecinos.atEnd()) {
				Nodo* vecino = vecinos.getElement();
				Arco* arcoConexion = obtenerArco(actual, vecino);
				
				if (!vecino->getVisited()) {
					float newDistance = actual->getDistancia() + arcoConexion->peso;
					if (newDistance < vecino->getDistancia()) {
						vecino->setDistancia(newDistance);
						vecino->setPadre(actual);
						Pair<float, Nodo*> p(vecino->getDistancia(), vecino);
						pQueue.insert(p);
					}
				}
				vecinos.next();
			}
		}

		for (visitedNodes.goToStart(); !visitedNodes.atEnd(); visitedNodes.next()) {
			visitedNodes.getElement()->setVisited(false);
		}

		Nodo* search = destino;
		while (search != nullptr && search->getPadre() != nullptr) {
			search->setVisited(true);
			Nodo* padre = search->getPadre();
			Arco* arco = obtenerArco(search, padre);
			if (arco != nullptr) {
				arco->partOfTree = true;
			}
			search = padre;
		}
		search->setVisited(true);
	}
	void ejecutarPrim(Nodo* inicio) {
		resetGrafo();

		if (inicio == nullptr) {
			return;
		}

		MinHeap<Arco> heap(CANT_NODOS * MAX_CONEXIONES);

		inicio->setVisited(true);

		ArrayList<Nodo*>& vecinosInicio = inicio->getVecinos();

		for (vecinosInicio.goToStart(); !vecinosInicio.atEnd(); vecinosInicio.next()) {
			Nodo* vecino = vecinosInicio.getElement();
			float peso = obtenerPeso(inicio, vecino);

			heap.insert(Arco(inicio, vecino, peso));
		}

		while (!heap.isEmpty()) {
			Arco arcoMenor = heap.removeFirst();

			Nodo* a = arcoMenor.nodoA;
			Nodo* b = arcoMenor.nodoB;

			Nodo* nuevo = nullptr;

			if (a->getVisited() && !b->getVisited()) {
				nuevo = b;
			}
			else if (b->getVisited() && !a->getVisited()) {
				nuevo = a;
			}
			else {
				continue;
			}

			nuevo->setVisited(true);

			Arco* arcoOriginal = obtenerArco(a, b);
			if (arcoOriginal != nullptr) {
				arcoOriginal->partOfTree = true;
			}

			ArrayList<Nodo*>& vecinos = nuevo->getVecinos();

			for (vecinos.goToStart(); !vecinos.atEnd(); vecinos.next()) {
				Nodo* vecino = vecinos.getElement();

				if (!vecino->getVisited()) {
					float peso = obtenerPeso(nuevo, vecino);
					heap.insert(Arco(nuevo, vecino, peso));
				}
			}
		}
	}
	void ejecutarKruskal() {
		resetGrafo();

		MinHeap<Arco> heap(listaArcos.getSize());

		for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
			Arco* arco = listaArcos.getElement();
			heap.insert(*arco);
		}

		UnionFind conjuntos(listaNodos.getSize());

		while (!heap.isEmpty()) {
			Arco arcoMenor = heap.removeFirst();

			int idA = arcoMenor.nodoA->getNumNodo();
			int idB = arcoMenor.nodoB->getNumNodo();

			if (conjuntos.unir(idA, idB)) {
				Arco* arcoOriginal = obtenerArco(arcoMenor.nodoA, arcoMenor.nodoB);

				if (arcoOriginal != nullptr) {
					arcoOriginal->partOfTree = true;
					arcoOriginal->nodoA->setVisited(true);
					arcoOriginal->nodoB->setVisited(true);
				}
			}
		}
	}
};

