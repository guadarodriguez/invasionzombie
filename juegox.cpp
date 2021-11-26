#include <iostream>
#include "SFML/Graphics.hpp"
#include "juegox.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

juegox::juegox(sf::Vector2i resolucion, const sf::String &titulo) {
    game_over = false;

    ventana1 = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), titulo);
    ventana1->setFramerateLimit(60);
    ventana1->setMouseCursorVisible(false);

    evento1 = new sf::Event;
    cont_seg = 0;
    cargar_graficos();
}

void juegox::gameloop() {

    while (!game_over) {
        // Verifico Eventos
        procesar_eventos();

        // Actualizar Entidades
        for (int i = 0; i < 3; ++i) {
            pos[i] = {static_cast<float>(rand() % 800 + 1), static_cast<float>(rand() % 600 + 1)};
        }
        while (cont_seg++ > 60) {
            for (int i = 0; i < 3; ++i) {
                spr_zombie[i].setPosition(pos[i]);
                spr_zombie[i].setColor(sf::Color(255, 255, 255, 255));
            }
            cont_seg = 0;
        }

        // Dibujar
        ventana1->clear();
        ventana1->draw(spr_fondo);
        ventana1->draw(spr_mira);
        for (sf::Sprite & zombie : spr_zombie) {
            ventana1->draw(zombie);
        }
        ventana1->display();
    }

    sumar_pila();
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
        png << "z" << (i + 1) << ".png";
        txt_zombie[i].loadFromFile(png.str());
        spr_zombie[i].setTexture(txt_zombie[i]);
    }
}

void juegox::procesar_eventos() {
    while (ventana1->pollEvent(*evento1)) {
        switch (evento1->type) {
            case sf::Event::MouseMoved:
                spr_mira.setPosition((sf::Vector2f) sf::Mouse::getPosition(*ventana1));
                break;
            case sf::Event::Closed:
                exit(1);
                break;
            case sf::Event::KeyPressed:
                if (evento1->key.code == sf::Keyboard::Escape) {
                    exit(1);
                    break;
                }
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    for (auto &zombie : spr_zombie) {
                        if (zombie.getGlobalBounds().contains(spr_mira.getPosition())) {
                            zombie.setColor(sf::Color::Green);
                            puntos++;
                            pila.push(1);
                        }
                    }
                    break;
                }
        }
    }
}

void juegox::sumar_pila() {

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
