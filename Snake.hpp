//Snake.hpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------

#include <iostream>

struct Block
{
    bool Snake;
    bool Essen;
    bool Leer;
    Feld():Snake(false),Essen(false),Leer(true)
    {}
};

Block SpielFeld[50][50];
