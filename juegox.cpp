#include <iostream>
#include "SFML/Graphics.hpp"
#include "juegox.h"
#include <cstdlib>
#include <fstream>
#include "Stack.h"
#include "ctime"

using namespace std;
Stack<int>pila;

juegox::juegox(sf::Vector2f resolucion, sf::String titulo) {
    game_over = false;
    fps = 60;

    ventana1 = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), titulo);
    ventana1->setFramerateLimit(fps);
    ventana1->setMouseCursorVisible(false);

    reloj1 = new sf::Clock;
    tiempo1 = new sf::Time;

    evento1 = new sf::Event;

    cargar_graficos();
    fuente = new sf::Font;
    fuente->loadFromFile("C:\\Users\\guada\\CLionProjects\\invasionzombie\\fuente\\04B_30__.TTF");

    gameloop();

}

void juegox::gameloop() {
    srand(time(NULL));

    while (!game_over) {
        ventana1->clear();
        procesar_eventos();
        ventana1->draw(spr_fondo);
        *tiempo1 = reloj1->getElapsedTime();
        cout << tiempo1->asSeconds() << endl;
        tiempo2 = tiempo1->asSeconds();
        tiempo3 = tiempo1->asSeconds();
        while (tiempo3 > 3) {
            posx1 = rand() % 800 + 1;
            posy1 = rand() % 600 + 1;
            posx2 = rand() % 800 + 1;
            posy2 = rand() % 600 + 1;
            posx3 = rand() % 800 + 1;
            posy3 = rand() % 600 + 1;
            posx4 = rand() % 800 + 1;
            posy4 = rand() % 600 + 1;
            spr_zombie1.setPosition(posx1, posy1);
            ventana1->draw(spr_zombie1);
            spr_zombie1.setColor(sf::Color(255, 255, 255, 255));
            spr_zombie2.setPosition(posx2, posy2);
            ventana1->draw(spr_zombie2);
            spr_zombie1.setColor(sf::Color(255, 255, 255, 255));
            spr_zombie3.setPosition(posx3, posy3);
            ventana1->draw(spr_zombie3);
            spr_zombie1.setColor(sf::Color(255, 255, 255, 255));
            spr_zombie4.setPosition(posx4, posy4);
            ventana1->draw(spr_zombie4);
            spr_zombie1.setColor(sf::Color(255, 255, 255, 255));
            tiempo3 = 0;
        }

        ventana1->draw(spr_mira);
        *tiempo1 = reloj1->getElapsedTime();
        cout << tiempo1->asSeconds() << endl;
        cout << puntos << endl;
        tiempo2 = tiempo1->asSeconds();
        // sumar_pila(pila); no implementada

        if (tiempo2 > 15) {
            exit(1);
        }
        ventana1->display();
    }
}

void juegox::cargar_graficos() {
    srand(time(NULL));
    txt_fondo.loadFromFile("bosque.png");
    spr_fondo.setTexture(txt_fondo);
    spr_fondo.setScale((float) ventana1->getSize().x / txt_fondo.getSize().x,
                       (float) ventana1->getSize().y / txt_fondo.getSize().y);

    txt_mira.loadFromFile("mira.png");
    spr_mira.setTexture(txt_mira);
    spr_mira.setScale(0.4f, 0.4f);
    spr_mira.setOrigin(txt_mira.getSize().x / 2, txt_mira.getSize().y / 2);

    txt_zombie1.loadFromFile("z1.png");
    spr_zombie1.setTexture(txt_zombie1);


    txt_zombie2.loadFromFile("z2.png");
    spr_zombie2.setTexture(txt_zombie2);

    txt_zombie3.loadFromFile("z3.png");
    spr_zombie3.setTexture(txt_zombie1);

    txt_zombie4.loadFromFile("z4.png");
    spr_zombie4.setTexture(txt_zombie4);

}

void juegox::procesar_eventos() {
    while (ventana1->pollEvent(*evento1)) {
        switch (evento1->type) {
            case sf::Event::MouseMoved:
                spr_mira.setPosition((sf::Vector2f) sf::Mouse::getPosition(*ventana1));
                break;
            case sf::Event::Closed:
                if (tiempo1->asSeconds() == 15) {
                    exit(1);
                }
                exit(1);
                break;
            case sf::Event::KeyPressed:
                if (evento1->key.code == sf::Keyboard::Escape) {
                    exit(1);
                    break;
                }
            case sf::Event::MouseButtonPressed:

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::FloatRect pos_mouse(spr_mira.getPosition(), {100, 100});
                    if (spr_zombie1.getGlobalBounds().intersects(pos_mouse)) {
                        spr_zombie1.setColor(sf::Color::Red);
                        puntos++;
                        pila.push(1);


                    }
                    if (spr_zombie2.getGlobalBounds().intersects(pos_mouse)) {
                        spr_zombie2.setColor(sf::Color::Red);
                        puntos++;
                        pila.push(1);

                    }
                    if (spr_zombie3.getGlobalBounds().intersects(pos_mouse)) {
                        spr_zombie3.setColor(sf::Color::Red);
                        puntos++;
                        pila.push(1);

                    }
                    if (spr_zombie4.getGlobalBounds().intersects(pos_mouse)) {
                        spr_zombie4.setColor(sf::Color::Red);
                        puntos++;
                        pila.push(1);

                    }

                    break;

                }
        }
    }
}

void juegox::procesar_mouse() {
    posicion_mouse = sf::Mouse::getPosition(*ventana1);
    posicion_mouse = (sf::Vector2i) ventana1->mapPixelToCoords(posicion_mouse);
}

void sumar_pila(Stack<int> pila) {
    ofstream ofs;
    int sumatoria = 0;
    while (!pila.isEmpty()) {
        sumatoria = sumatoria + pila.peek();
        pila.pop();
    }
    cout << "\nSumatoria de pila: " << sumatoria << endl;
    ofs.open("Datos_Juego.txt");
    ofs << "Puntos totales en esta partida: " << endl;
    ofs << sumatoria << endl;
    ofs.close();
}
