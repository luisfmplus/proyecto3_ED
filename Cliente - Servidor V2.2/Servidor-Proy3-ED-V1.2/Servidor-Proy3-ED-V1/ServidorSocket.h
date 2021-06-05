#ifndef SERVIDORSOCKET_H
#define SERVIDORSOCKET_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstring>
#include <sstream>

#include "colores.h"

int const largoBuffer = 512;

class ServidorSocket {
    public:

        ServidorSocket() {}

        ServidorSocket(int puerto) {
            this->puerto = puerto;
        }

        void inicio() {
            iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockdata);
            if (iWsaStartup != 0) {
                rojo();  cout << "WSAStartUp Failed | \n" << endl;
            }
            else {
                verde();  cout << "WSAStartUp-Success | \n";
            }
        }

        void creacionEstructura() {
            TCPServerAdd.sin_family = AF_INET;
            //TCPServerAdd.sin_addr.s_addr = inet_addr("localhost");
            IN_ADDR ip_value;
            TCPServerAdd.sin_addr.s_addr = inet_pton(AF_INET, "localhost", &ip_value);
            TCPServerAdd.sin_port = htons(puerto);
        }

        void creacionSocket() {
            TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (TCPServerSocket == INVALID_SOCKET) {
                rojo(); cout << "TCP-Server-Socket-Creation-Failed: " << WSAGetLastError() << " | " << endl;
            }
            else {
                string msg = "Creacion de server socket TCP en puerto: " + to_string(puerto) + " | \n";
                verde();  cout << msg;
            }
        }

        void bindar() {
            iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
            if (iBind == SOCKET_ERROR) {
                rojo();  cout << "Binding failed & Error No -> " << WSAGetLastError() << " | " << endl;
            }
            else {
                verde();  cout << "Binding Success | \n";
            }
        }

        void escuchar() {
            iListen = listen(TCPServerSocket, 2);
            if (iListen == SOCKET_ERROR) {
                rojo(); cout << "Listen Fun Failed & Error No -> " << WSAGetLastError() << " | " << endl;
            }
            else {
                string msg = "Escuchando en puerto: " + to_string(puerto) + " | \n";
                verde(); cout << msg;
            }
        }

        void conectarCliente() {
            sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
            if (sAcceptSocket == INVALID_SOCKET) {
                rojo(); cout << "Accept Failed & Error No -> " << WSAGetLastError() << " | " << endl;
            }
            else {
                string msg = "Conexion aceptada en puerto: " + to_string(puerto) + " | \n";
                gris(); cout << msg;
            }
        }

        bool enviarMensaje() {
            iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
            if (iSend == SOCKET_ERROR) {
                rojo(); cout << "Sending Failed & Error No -> " << WSAGetLastError() << " | " << endl;
                return FALSE;
            }
            else {
                rosado();  cout << "Datos enviados -> " + string(SenderBuffer) + " | \n";
                return TRUE;
            }
        }

        bool enviarMensaje(string mensaje) {
            if (mensaje.length() > largoBuffer) {
                mensaje = mensaje.substr(0, largoBuffer - 1);
            }
            strcpy_s(SenderBuffer, mensaje.c_str());
            return enviarMensaje();
        }

        bool recibirMensaje() {
            iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
            if (iRecv == SOCKET_ERROR) {
                rojo();  cout << "! Posible desconexion de cliente en puerto "+to_string(puerto)+" ! - Receive Data Failed & Error No -> " << WSAGetLastError() << " | " << endl;
                return FALSE;
            }
            else {
                string msg = "Datos recibidos -> " + string(RecvBuffer) + " | \n";
                celeste();  cout << msg;
                return TRUE;
            }
        }

        string getMensaje() {
            return string(RecvBuffer);
        }

        void cerrarSocket() {
            iCloseSocket = closesocket(TCPServerSocket);
            if (iCloseSocket == SOCKET_ERROR) {
                rojo(); cout << "Closing Socket Failed & Error No -> " << WSAGetLastError() << " | " << endl;
            }
            else {
                verde(); cout << "Socket cerrado con exito | \n";
            }
        }

        void limpiar() {
            iWsaCleanup = WSACleanup();
            if (iWsaCleanup == SOCKET_ERROR) {
                rojo(); cout << "CleanUp Fun Failed & Error No -> " << WSAGetLastError() << " | " << endl;
            }
            else {
                verde(); cout << "CleanUp Fun Success | \n";
            }
        }

    private:
        int puerto;

        WSADATA WinSockdata;
        int iWsaStartup;
        int iWsaCleanup;

        SOCKET TCPServerSocket;
        int iCloseSocket;

        struct sockaddr_in TCPServerAdd;
        struct sockaddr_in TCPClientAdd;
        int iTCPClientAdd = sizeof(TCPClientAdd);

        int iBind;

        int iListen;

        SOCKET sAcceptSocket;

        int iSend;
        char SenderBuffer[largoBuffer] = "Hola desde el servidor, se supone que este sea un mensaje largo, para probar el buffer del cliente";
        int iSenderBuffer = largoBuffer;

        int iRecv;
        char RecvBuffer[largoBuffer];
        int iRecvBuffer = largoBuffer;
};

#endif