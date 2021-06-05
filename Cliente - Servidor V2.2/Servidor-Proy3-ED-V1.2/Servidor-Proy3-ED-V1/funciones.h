#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <sstream>
using namespace std;

class nodoLista {
public:
    nodoLista(string v) {
        valor = v;
        siguiente = NULL;
    }

    nodoLista(string v, nodoLista* signodoLista) {
        valor = v;
        siguiente = signodoLista;
    }

private:
    string valor;
    nodoLista* siguiente;

    friend class lista;
};
typedef nodoLista* pnodoLista;

class lista {
public:
    lista() { primero = NULL; }
    void insertar(string v);
    bool vacio() { return primero == NULL; };
    int largo();
    string obtenerValorPos(int pos);

private:
    pnodoLista primero;
};

void lista::insertar(string v) {
    if (vacio())
        primero = new nodoLista(v);
    else {
        pnodoLista aux = primero;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = new nodoLista(v);
    }
}

int lista::largo() {
    int cont = 0;
    pnodoLista aux = primero;
    while (aux != NULL) {
        aux = aux->siguiente;
        cont++;
    }
    return cont;
}

string lista::obtenerValorPos(int pos) {
    pnodoLista temp = primero;
    int cont = 1;
    string resultado = "";
    while (temp != NULL) {
        if (pos == cont) {
            resultado = temp->valor;
            break;
        }
        temp = temp->siguiente;
        cont++;
    }
    return resultado;
}

lista dividirString(string divisible, string divisor) {
    lista elems;
    string elem = "", temp;
    for (int i = 0; i < divisible.length(); i++) {
        temp = divisible[i];
        if (temp == divisor) {
            elems.insertar(elem);
            elem = "";
        }
        else {
            elem += temp;
        }
    }
    elems.insertar(elem);
    return elems;
}

int StrToNum(string str) {
    stringstream trans(str);
    int num;
    trans >> num;
    return num;
}

#endif FUNCIONES_H