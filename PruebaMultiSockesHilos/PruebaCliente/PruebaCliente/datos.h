#ifndef DATOS_H
#define DATOS_H

#include <iostream>
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

string getDato(string json, string nombre) {
    string res = "";
    if (json.length() > 0) json = json.substr(1, json.length() - 2);
    lista datos = dividirString(json, ",");
    for (int i = 1; i <= datos.largo(); i++) {
        lista dato = dividirString(datos.obtenerValorPos(i), ":");
        if (dato.obtenerValorPos(1) == nombre) {
            res = dato.obtenerValorPos(2);
            break;
        }
    }
    return res;
}

string setDato(string json, string nombre, string valor) {
    string nuevoJSON = "", tempNombre, tempValor;
    bool encontrado = false;
    if (json.length() > 0) json = json.substr(1, json.length() - 2);
    lista info = dividirString(json, ",");
    nuevoJSON += "{";
    for (int i = 1; i <= info.largo(); i++) {
        lista dato = dividirString(info.obtenerValorPos(i), ":");
        tempNombre = dato.obtenerValorPos(1);
        tempValor = dato.obtenerValorPos(2);
        if (tempNombre == nombre) {
            tempValor = valor;
            encontrado = true;
        }
        if (tempNombre != "") nuevoJSON += tempNombre + ":" + tempValor + ",";
    }
    if (!encontrado && nombre != "") nuevoJSON += nombre + ":" + valor;
    else nuevoJSON = nuevoJSON.substr(0, nuevoJSON.length() - 1);
    nuevoJSON += "}";
    return nuevoJSON;
}

#endif