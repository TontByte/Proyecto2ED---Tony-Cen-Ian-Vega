// Proyecto2ED - Tony Cen & Ian Vega.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include "Nodo.h"
#include "Arco.h"
#include "Grafo.h"
#include "Config.h"

using std::runtime_error;
using std::string;

//dibuja la franja inferior con los controles y el mensaje de estado actual
void dibujarHUD(sf::RenderWindow& window, sf::Font& font, const string& mensaje) {
    sf::RectangleShape panel(sf::Vector2f(static_cast<float>(X_VENTANA), static_cast<float>(HUD_HEIGHT)));
    panel.setPosition(sf::Vector2f(0.f, static_cast<float>(Y_VENTANA)));
    panel.setFillColor(sf::Color(25, 25, 25));
    window.draw(panel);

    sf::Text lineaAlgoritmos(font);
    lineaAlgoritmos.setCharacterSize(13);
    lineaAlgoritmos.setFillColor(sf::Color::White);
    lineaAlgoritmos.setString("1:BFS   2:DFS   3:Dijkstra   4:Prim   5:Kruskal   R:Regenerar grafo   C:Limpiar");
    lineaAlgoritmos.setPosition(sf::Vector2f(10.f, static_cast<float>(Y_VENTANA) + 6.f));
    window.draw(lineaAlgoritmos);

    sf::Text lineaMouse(font);
    lineaMouse.setCharacterSize(13);
    lineaMouse.setFillColor(sf::Color(200, 200, 200));
    lineaMouse.setString("Clic izquierdo = nodo de inicio   |   Clic derecho = nodo destino (solo Dijkstra)");
    lineaMouse.setPosition(sf::Vector2f(10.f, static_cast<float>(Y_VENTANA) + 28.f));
    window.draw(lineaMouse);

    sf::Text estado(font);
    estado.setCharacterSize(13);
    estado.setFillColor(sf::Color(120, 200, 255));
    estado.setString(mensaje);
    estado.setPosition(sf::Vector2f(10.f, static_cast<float>(Y_VENTANA) + 52.f));
    window.draw(estado);
}

int main(){
    srand(time(0));
    

    sf::RenderWindow window(sf::VideoMode({ X_VENTANA, Y_VENTANA + HUD_HEIGHT }), "Grafos");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("fonts/ARIAL.ttf")) {
        throw runtime_error("No se logra cargar font");
    }

    Grafo g;
    g.generarGrafo();

    Nodo* nodoInicio = nullptr;
    Nodo* nodoDestino = nullptr;
    string mensaje = "Selecciona un nodo de inicio con clic izquierdo";

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x), static_cast<float>(mousePressed->position.y));

                if (mousePressed->button == sf::Mouse::Button::Left) {
                    Nodo* clickeado = g.obtenerNodoEnPosicion(mousePos);
                    if (clickeado != nullptr) {
                        if (nodoInicio != nullptr) {
                            nodoInicio->setEsInicio(false);
                        }
                        nodoInicio = clickeado;
                        nodoInicio->setEsInicio(true);
                        mensaje = "Nodo de inicio seleccionado: " + std::to_string(nodoInicio->getNumNodo());
                    }
                }
                else if (mousePressed->button == sf::Mouse::Button::Right) {
                    Nodo* clickeado = g.obtenerNodoEnPosicion(mousePos);
                    if (clickeado != nullptr) {
                        if (nodoDestino != nullptr) {
                            nodoDestino->setEsDestino(false);
                        }
                        nodoDestino = clickeado;
                        nodoDestino->setEsDestino(true);
                        mensaje = "Nodo destino seleccionado: " + std::to_string(nodoDestino->getNumNodo());
                    }
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->code) {
                case sf::Keyboard::Key::Num1: //BFS
                    if (nodoInicio != nullptr) {
                        g.ejecutarBFS(nodoInicio);
                        mensaje = "BFS ejecutado desde el nodo " + std::to_string(nodoInicio->getNumNodo());
                    }
                    else {
                        mensaje = "Selecciona un nodo de inicio (clic izquierdo) antes de correr BFS";
                    }
                    break;

                case sf::Keyboard::Key::Num2: //DFS
                    if (nodoInicio != nullptr) {
                        g.ejecutarDFS(nodoInicio);
                        mensaje = "DFS ejecutado desde el nodo " + std::to_string(nodoInicio->getNumNodo());
                    }
                    else {
                        mensaje = "Selecciona un nodo de inicio (clic izquierdo) antes de correr DFS";
                    }
                    break;

                case sf::Keyboard::Key::Num3: //Dijkstra
                    if (nodoInicio != nullptr && nodoDestino != nullptr) {
                        g.ejecutarDijkstra(nodoInicio, nodoDestino);
                        mensaje = "Dijkstra ejecutado de " + std::to_string(nodoInicio->getNumNodo()) +
                            " a " + std::to_string(nodoDestino->getNumNodo());
                    }
                    else {
                        mensaje = "Selecciona nodo de inicio (clic izq) y destino (clic der) para Dijkstra";
                    }
                    break;

                case sf::Keyboard::Key::Num4: //Prim
                    if (nodoInicio != nullptr) {
                        g.ejecutarPrim(nodoInicio);
                        mensaje = "Prim ejecutado desde el nodo " + std::to_string(nodoInicio->getNumNodo());
                    }
                    else {
                        mensaje = "Selecciona un nodo de inicio (clic izquierdo) antes de correr Prim";
                    }
                    break;

                case sf::Keyboard::Key::Num5: //Kruskal
                    g.ejecutarKruskal();
                    mensaje = "Kruskal ejecutado (arbol de expansion minima completo)";
                    break;

                case sf::Keyboard::Key::R: //Regenerar grafo
                    g.generarGrafo();
                    nodoInicio = nullptr;
                    nodoDestino = nullptr;
                    mensaje = "Nuevo grafo generado";
                    break;

                case sf::Keyboard::Key::C: //Limpiar seleccion y resultados
                    g.resetGrafo();
                    if (nodoInicio != nullptr) {
                        nodoInicio->setEsInicio(false);
                    }
                    if (nodoDestino != nullptr) {
                        nodoDestino->setEsDestino(false);
                    }
                    nodoInicio = nullptr;
                    nodoDestino = nullptr;
                    mensaje = "Seleccion y resultados limpiados";
                    break;

                default:
                    break;
                }
            }
        }

        window.clear();
        g.draw(window, font);
        dibujarHUD(window, font, mensaje);
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
