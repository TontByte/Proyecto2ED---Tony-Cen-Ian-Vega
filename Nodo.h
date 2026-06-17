//la clase nodo, utilizada para crear objetos nodo para el grafo
//podriamos crear lo de la matriz para ver si se conectan con otros nodos
#pragma once
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <limits>
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
	float distancia; //para dijkstra
	Nodo* padre; //para simplificar procesos en los algoritmos
	ArrayList<Nodo*> vecinos;
	sf::CircleShape shape;

public:
	Nodo(int numNodo, int xCoord, int yCoord) : vecinos(MAX_CONEXIONES) {
		this->numNodo = numNodo;
		this->xCoord = xCoord;
		this->yCoord = yCoord;
		this->distancia = std::numeric_limits<float>::max();
		visited = false;
		this->padre = nullptr;

		shape.setRadius(15.0f);
		shape.setOrigin(sf::Vector2f(15.0f, 15.0f)); 
		shape.setPosition(sf::Vector2f(static_cast<float>(xCoord), static_cast<float>(yCoord)));
		shape.setFillColor(sf::Color::White);
		shape.setOutlineThickness(2.0f);
		shape.setOutlineColor(sf::Color::Black);
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

	float getDistancia() {
		return distancia;
	}

	void setDistancia(float distancia) {
		this->distancia = distancia;
	}

	Nodo* getPadre() {
		return padre;
	}

	void setPadre(Nodo* padre) {
		this->padre = padre;
	}

	ArrayList<Nodo*>& getVecinos() {
		return vecinos;
	}

	bool isClicked(sf::Vector2f mousePos) {
		return shape.getGlobalBounds().contains(mousePos);
	}

	void draw(sf::RenderWindow& window) {
		if (visited) {
			shape.setFillColor(sf::Color::Green);
		}
		else {
			shape.setFillColor(sf::Color::White);
		}
		window.draw(shape);
	}

};

