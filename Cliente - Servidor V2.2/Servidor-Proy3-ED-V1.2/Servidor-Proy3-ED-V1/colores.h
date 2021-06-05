#ifndef COLORES_H
#define COLORES_H

#include <windows.h>
#include <iostream>
using namespace std;

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void azul() {
    SetConsoleTextAttribute(hConsole, 9);
}

void rojo() {
    SetConsoleTextAttribute(hConsole, 4);
}

void amarillo() {
    SetConsoleTextAttribute(hConsole, 6);
}

void verde() {
    SetConsoleTextAttribute(hConsole, 2);
}

void gris() {
    SetConsoleTextAttribute(hConsole, 8);
}

void rosado() {
    SetConsoleTextAttribute(hConsole, 5);
}

void celeste() {
    SetConsoleTextAttribute(hConsole, 11);
}

void blanco() {
    SetConsoleTextAttribute(hConsole, 7);
}

void verde_blanco() {
    SetConsoleTextAttribute(hConsole, 242);
}

void rojo_amarillo() {
    SetConsoleTextAttribute(hConsole, 100);
}

void colores() {
    for (int i = 0; i < 255; i++) {
        SetConsoleTextAttribute(hConsole, i);
        cout << "Color " << i << endl;
    }
}

#endif