//
// Created by guada on 22/11/2021.
//

#ifndef INFORMATICA2_JUEGOX_H
#define INFORMATICA2_JUEGOX_H
#endif //INFORMATICA2_JUEGOX_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include "Stack.h"


using namespace std;

class juegox {
public:
    juegox(sf::Vector2i resolucion, const sf::String &titulo);

    void gameloop();

    void cargar_graficos();

    void procesar_eventos();

    void sumar_pila();


private:
    sf::RenderWindow *ventana1;

    sf::Texture txt_fondo;
    sf::Sprite spr_fondo;

    sf::Texture txt_mira;
    sf::Sprite spr_mira;

    sf::Texture txt_zombie[3];
    sf::Sprite spr_zombie[3];

    int cont_seg;

    int puntos = 0;
    int vidas = 10;

    sf::Event *evento1;

    sf::Vector2f pos[4];
    // LinkedList<float> pos;

    bool game_over;

    Stack<int> pila;
};