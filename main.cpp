#include <iostream>
#include "juegox.h"
#include <cstdlib>


using namespace std;

int main() {
    srand(time(NULL));
    juegox partida1({800, 600}, "ATAQUE ZOMBIE");

    partida1.gameloop();
    return 0;
}
