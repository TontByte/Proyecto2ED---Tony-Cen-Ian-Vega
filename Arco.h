#pragma once
#include "Nodo.h"
#include <SFML/Graphics.hpp>

class Arco{
public:
	Nodo* nodoA;
	Nodo* nodoB;
	float peso;
	bool partOfTree;

	Arco(Nodo* a, Nodo* b, float peso) {
		this->nodoA = a;
		this->nodoB = b;
		this->peso = peso;
		partOfTree = false;
	}

	Arco() {
		this->nodoA = nullptr;
		this->nodoB = nullptr;
		peso = 0;
		partOfTree = false;
	}

	void draw(sf::RenderWindow& window) {
		if (nodoA == nullptr || nodoB == nullptr) {
			return;
		}

		sf::Color color;
		if (partOfTree) {
			color = sf::Color::Green;
		}
		else {
			color = sf::Color(211, 211, 211);
		}

		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(nodoA->getXCoord(), nodoA->getYCoord()), color),
			sf::Vertex(sf::Vector2f(nodoB->getXCoord(), nodoB->getYCoord()), color)
		};

		window.draw(line, 2, sf::PrimitiveType::Lines);
	}
};

