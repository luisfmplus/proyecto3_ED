#include <thread>
#include "ServidorSocket.h"

int const largo = 5;

thread hilos[largo+1];
bool disponibles[largo];

int puerto = 8000;

void inicioSocket(ServidorSocket socket, int posicion){
    socket.inicio();
    socket.creacionEstructura();
    socket.creacionSocket();
    socket.bindar();
    bool correcto = TRUE;
    while (TRUE) {
        disponibles[posicion] = TRUE;
        socket.escuchar();
        socket.conectarCliente();
        while (correcto) {
            disponibles[posicion] = FALSE;
            correcto = correcto && socket.recibirMensaje();
            correcto = correcto && socket.enviarMensaje();
        }
        correcto = TRUE;
    }
    socket.cerrarSocket();
    socket.limpiar();
}

void inicioFiltro(ServidorSocket filtro){
    filtro.inicio();
    filtro.creacionEstructura();
    filtro.creacionSocket();
    filtro.bindar();
    while (TRUE) {
        filtro.escuchar();
        filtro.conectarCliente();
        int disponible = 0;
        for (int i = 0; i < largo; i++) {
            if (disponibles[i]) {
                disponible = puerto+i;
                break;
            }
        }
        filtro.enviarMensaje(to_string(disponible));
    }
}

int main(){
    int numpuerto = puerto;
    ServidorSocket filtro(numpuerto - 1);
    hilos[0] = thread(inicioFiltro, filtro);
    for (int i = 1; i < largo+1; i++) {
        ServidorSocket socket(numpuerto);
        numpuerto++;
        hilos[i] = thread(inicioSocket, socket,i-1);
    }
    hilos->join();
}