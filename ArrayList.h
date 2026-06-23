/*
Clase ArrayList elaborada en clase
Utilizada para el atributo ventanillas en la clase Area
Tiene como funcion permitir el acceso a las diferentes ventanillas de las areas
*/

#pragma once
#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Config.h"



using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class ArrayList : public List<E> {
private:
	E* elements;
	int pos;
	int size;
	int max;

	void resize() {
		max = max * 2;
		E* newList = new E[max];
		for (int i = 0; i < size; i++) {
			newList[i] = elements[i];
		}
		delete[] elements;
		elements = newList;
	}

public:
	ArrayList(int max = DEFAULT_MAX) {
		if (max < 1) {
			throw runtime_error("Invalid max size.");
		}
		elements = new E[max];
		this->max = max;
		pos = 0;
		size = 0;
	}

	~ArrayList() {
		delete[] elements;
	}

	void insert(E element) {
		if (size == max) {
			resize();
		}
		for (int i = size - 1; i >= pos; i--) {
			elements[i + 1] = elements[i];
		}
		elements[pos] = element;
		size++;
	}

	void append(E element) {
		if (size == max) {
			resize();
		}
		elements[size] = element;
		size++;
	}

	void setElement(E element) {
		if (pos >= size) {
			throw runtime_error("Posicion invalida.");
		}
		elements[pos] = element;
	}

	E remove() {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (pos >= size) {
			throw runtime_error("Posicion invalida.");
		}

		E res = elements[pos];
		for (int i = pos + 1; i < size; i++) {
			elements[i - 1] = elements[i];
		}
		size--;
		return res;
	}

	E& getElement() {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (pos >= size) {
			throw runtime_error("Posicion invalida.");
		}
		return elements[pos];
	}

	void clear() {
		pos = 0;
		size = 0;
	}

	void goToStart() {
		pos = 0;
	}

	void goToEnd() {
		pos = size;
	}

	void goToPos(int pos) {
		if (pos > size || pos < 0) {
			throw runtime_error("Index out of bounds.");
		}
		this->pos = pos;
	}

	void next() {
		if (pos < size) {
			pos++;
		}
	}

	void previous() {
		if (pos > 0) {
			pos--;
		}
	}

	bool atStart() {
		return (pos == 0);
	}

	bool atEnd() {
		return (pos == size);
	}

	int getPos() {
		return pos;
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i != size - 1) {
				cout << ", ";
			}
		}
		cout << "]";
	}
};