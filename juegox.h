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
    juegox(sf::Vector2i resolucion, const sf::String& titulo);

    void gameloop();

    void cargar_graficos();

    void procesar_eventos();

    void procesar_mouse();

    void sumar_pila(Stack<int> pila);


private:
    sf::RenderWindow *ventana1;

    sf::Texture txt_fondo;
    sf::Sprite spr_fondo;

    sf::Texture txt_mira;
    sf::Sprite spr_mira;

    sf::Texture txt_zombie[3];
    sf::Sprite spr_zombie[3];


    sf::Texture txt_princess;
    sf::Sprite spr_princess;

    sf::Vector2i posicion_mouse;

    int puntos = 0;
    int vidas = 10;
    sf::Clock *reloj1;
    sf::Time *tiempo1;
    float tiempo2;
    float tiempo3;


    sf::Event *evento1;

    float posx[4];
    float posy[4];
    // LinkedList<float> pos;

    int sumatoria;

    bool game_over;

    Stack<int>pila;
    int fps;
    //sf::Font *fuente;
    //sf::Text txt_name;

};