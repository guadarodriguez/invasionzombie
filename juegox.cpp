#include <iostream>
#include "SFML/Graphics.hpp"
#include "juegox.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Stack.h"
#include "ctime"

using namespace std;

juegox::juegox(sf::Vector2i resolucion, const sf::String &titulo) {

    srand(time(nullptr));
    game_over = false;
    fps = 60;

    ventana1 = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), titulo);
    ventana1->setFramerateLimit(fps);
    ventana1->setMouseCursorVisible(false);

    reloj1 = new sf::Clock;
    tiempo1 = new sf::Time;

    evento1 = new sf::Event;

    cargar_graficos();
}

void juegox::gameloop() {

    while (!game_over) {
        ventana1->clear();
        procesar_eventos();
        ventana1->draw(spr_fondo);
        *tiempo1 = reloj1->getElapsedTime();
        cout << tiempo1->asSeconds() << endl;
        tiempo2 = tiempo1->asSeconds();
        tiempo3 = tiempo1->asSeconds();
        for (int i = 0; i < 3; ++i) {
            posx[i] = rand() % 800 + 1;
            posy[i] = rand() % 600 + 1;
        }
        while (tiempo3 > 3) {
            for (int i = 0; i < 3; ++i) {
                spr_zombie[i].setPosition(posx[i], posy[i]);
                spr_zombie[i].setColor(sf::Color(255, 255, 255, 255));
                ventana1->draw(spr_zombie[i]);
            }

            /*spr_princess.setPosition(posx4, posy4);
            spr_princess.setColor(sf::Color(255, 255, 255, 255));
            ventana1->draw(spr_princess);*/

            tiempo3 = 0;
        }


        ventana1->draw(spr_mira);

        cout << tiempo1->asSeconds() << endl;
        cout << puntos << endl;
        cout << vidas << endl;

        if (tiempo2 > 15) {
            exit(1);
        }

        ventana1->display();
    }

    sumar_pila(pila);
}

void juegox::cargar_graficos() {
    txt_fondo.loadFromFile("bosque.png");
    spr_fondo.setTexture(txt_fondo);
    spr_fondo.setScale((float) ventana1->getSize().x / txt_fondo.getSize().x,
                       (float) ventana1->getSize().y / txt_fondo.getSize().y);

    txt_mira.loadFromFile("mira.png");
    spr_mira.setTexture(txt_mira);
    spr_mira.setScale(0.4f, 0.4f);
    spr_mira.setOrigin(txt_mira.getSize().x / 2, txt_mira.getSize().y / 2);


    for (int i = 0; i < 3; ++i) {
        stringstream png;
        png << "z" << i << ".png";
        txt_zombie[i].loadFromFile(png.str());
        spr_zombie[i].setTexture(txt_zombie[i]);
    }
    //txt_princess.loadFromFile("C:\\Users\\guada\\CLionProjects\\invasionzombie\\princess1.png");
    //spr_princess.setTexture(txt_princess);
    //spr_princess.setScale(0.5f, 0.5f);
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
                    for (int i = 0; i < 3; ++i) {
                        if (spr_zombie[i].getGlobalBounds().intersects(pos_mouse)) {
                            spr_zombie[i].setColor(sf::Color::Green);
                            puntos++;
                            pila.push(1);
                        }
                    }
                    //if (spr_princess.getGlobalBounds().intersects(pos_mouse)) {
                    //  spr_princess.setColor(sf::Color::Red);
                    // vidas --;
                    //pila.push(1);
                    break;
                }
        }
    }
}

void juegox::procesar_mouse() {
    posicion_mouse = sf::Mouse::getPosition(*ventana1);
    posicion_mouse = (sf::Vector2i) ventana1->mapPixelToCoords(posicion_mouse);
}

void juegox::sumar_pila(Stack<int> pila) {

    int sumatoria = 0;
    while (!pila.isEmpty()) {
        sumatoria = sumatoria + pila.peek();
        pila.pop();
    }
    ofstream ofs;
    ofs.open("Datos_Juego.txt");
    ofs << "Puntos totales en esta partida: " << endl;
    ofs << sumatoria << endl;
    ofs << "Vidas totales en esta partida: " << endl;
    ofs << vidas << endl;
    ofs.close();
}
