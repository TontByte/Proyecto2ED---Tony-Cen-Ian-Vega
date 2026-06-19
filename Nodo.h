//la clase nodo, utilizada para crear objetos nodo para el grafo
//podriamos crear lo de la matriz para ver si se conectan con otros nodos
#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <SFML/Graphics.hpp>
#include <limits>
#include "ArrayList.h"
#include "Config.h"

using std::cout;
using std::endl;
using std::runtime_error;
using std::string;

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

	float getRadio() {
		float areaVentana = X_VENTANA * Y_VENTANA;
		float radio = std::sqrt(areaVentana / static_cast<float>(CANT_NODOS)) / 6.0f;
		radio = std::clamp(radio, 8.0f, 20.0f);
		return radio;
	}

public:
	Nodo(int numNodo, int xCoord, int yCoord) : vecinos(MAX_CONEXIONES) {
		this->numNodo = numNodo;
		this->xCoord = xCoord;
		this->yCoord = yCoord;
		this->distancia = std::numeric_limits<float>::max();
		visited = false;
		this->padre = nullptr;

		float radio = getRadio();
		shape.setRadius(radio);
		shape.setOrigin(sf::Vector2f(radio, radio));
		shape.setPosition(sf::Vector2f(static_cast<float>(xCoord), static_cast<float>(yCoord)));
		shape.setFillColor(sf::Color::White);
		shape.setOutlineThickness(1.5f);
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

	bool allNeighborVisited() {
		for (vecinos.goToStart(); !vecinos.atEnd(); vecinos.next()) {
			if (vecinos.getElement()->getVisited() == false) {
				return false;
			}
		}
		return true;
	}

	void draw(sf::RenderWindow& window, sf::Font& font) {
		if (visited) {
			shape.setFillColor(sf::Color::Green);
		}
		else {
			shape.setFillColor(sf::Color::White);
		}
		window.draw(shape);
		
		sf::Text texto(font);
		string numID = std::to_string(numNodo);
		texto.setString(numID);
		texto.setCharacterSize(8);
		texto.setFillColor(sf::Color::Black);
		sf::FloatRect bounds = texto.getLocalBounds();
		texto.setOrigin(sf::Vector2f(bounds.size.x / 2.0f, bounds.size.y / 2.0f));
		float centroX = shape.getPosition().x;
		float centroY = shape.getPosition().y;
		texto.setPosition(sf::Vector2f(static_cast<float>(centroX), static_cast<float>(centroY)));

		window.draw(texto);
	}

};

