// Proyecto2ED - Tony Cen & Ian Vega.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <ctime>
#include "Nodo.h"
#include "Arco.h"
#include "Config.h"

void generarNodos(ArrayList<Nodo*>& listaNodos) {
    
    for (int i = 0; i < CANT_NODOS; i++) {
        int x = rand() % X_VENTANA;
        int y = rand() % Y_VENTANA;
        Nodo* 
    }
}

void dibujarNodos(ArrayList<Nodo*>& listaNodos, sf::RenderWindow& window) {
    for (listaNodos.goToStart(); !listaNodos.atEnd(); listaNodos.next()) {
        listaNodos.getElement()->draw(window);
    }
}

void dibujarArcos(ArrayList<Arco>& listaArcos, sf::RenderWindow& window) {
    for (listaArcos.goToStart(); !listaArcos.atEnd(); listaArcos.next()) {
        listaArcos.getElement().draw(window);
    }
}

void resetVisited() {
}

int main(){
    srand(time(0));
    ArrayList<Nodo*> listaNodos(CANT_NODOS);
    ArrayList<Arco> listaArcos;

    sf::RenderWindow window(sf::VideoMode({ X_VENTANA, Y_VENTANA }), "Grafos");
    window.setFramerateLimit(60);

    dibujarArcos(listaArcos, window);
    dibujarNodos(listaNodos, window);
}

/* programa para probar sfml
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Test");

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({ 300.f, 200.f });

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }
}
*/

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
