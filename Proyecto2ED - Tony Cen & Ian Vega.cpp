// Proyecto2ED - Tony Cen & Ian Vega.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdexcept>
#include <ctime>
#include "Nodo.h"
#include "Arco.h"
#include "Grafo.h"
#include "Config.h"

using std::runtime_error;

void resetVisited() {
}

int main(){
    srand(time(0));
    ArrayList<Nodo*> listaNodos(CANT_NODOS);
    ArrayList<Arco> listaArcos;

    sf::RenderWindow window(sf::VideoMode({ X_VENTANA, Y_VENTANA }), "Grafos");
    window.setFramerateLimit(60);

    sf::Font font;

    Grafo g;
    g.generarGrafo();

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        g.draw(window, font);
        window.display();
    }

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
