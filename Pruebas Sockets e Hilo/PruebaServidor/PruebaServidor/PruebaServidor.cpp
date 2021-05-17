#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <iostream>
using namespace std;

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
char SenderBuffer[512] = "Hola desde el servidor";
int iSenderBuffer = strlen(SenderBuffer) + 1;

int iRecv;
char RecvBuffer[512];
int iRecvBuffer = 512;

void inicio() {
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockdata);
    if (iWsaStartup != 0) {
        cout << "WSAStartUp Failed" << endl;
    } else {
        cout << "WSAStartUp Success" << endl;
    }
}

void creacionEstructura() {
    TCPServerAdd.sin_family = AF_INET;
    //TCPServerAdd.sin_addr.s_addr = inet_addr("localhost");
    IN_ADDR ip_value;
    TCPServerAdd.sin_addr.s_addr = inet_pton(AF_INET, "localhost", &ip_value);
    TCPServerAdd.sin_port = htons(8000);
}

void creacionSocket() {
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TCPServerSocket == INVALID_SOCKET) {
        cout << "TCP Server Socket Creation Failed" << WSAGetLastError() << endl;
    } else {
        cout << "TCP Server Socket Creation Success" << endl;
    }
}

void bind() {
    iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iBind == SOCKET_ERROR) {
        cout << "Binding failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "Binding Success" << endl;
    }
}

void escuchar() {
    iListen = listen(TCPServerSocket, 2);
    if (iListen == SOCKET_ERROR) {
        cout << "Listen Fun Failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "Listen Fun Success" << endl;
    }
}

void conectarCliente() {
    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    if (sAcceptSocket == INVALID_SOCKET) {
        cout << "Accept Failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "Connection Accepted" << endl;
    }
}

void enviarMensaje() {
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
    if (iSend == SOCKET_ERROR) {
        cout << "Sending Failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "Data Sending Success" << endl;
    }
}

void recibirMensaje() {
    iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
    if (iRecv == SOCKET_ERROR) {
        cout << "Receive Data Failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "DATA RECEIVED -> " << RecvBuffer << endl;
    }
}

void cerrarSocket() {
    iCloseSocket = closesocket(TCPServerSocket);
    if (iCloseSocket == SOCKET_ERROR) {
        cout << "Closing Socket Failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "Closing Socket Success" << endl;
    }
}

void limpiar() {
    iWsaCleanup = WSACleanup();
    if (iWsaCleanup == SOCKET_ERROR) {
        cout << "CleanUp Fun Failed & Error No -> " << WSAGetLastError() << endl;
    } else {
        cout << "CleanUp Fun Success" << endl;
    }
}

void funcion() {
    cout << "Funcion" << endl;
}

int main(){
    thread t1(funcion);
    inicio();
    creacionEstructura();
    creacionSocket();
    bind();
    escuchar();
    conectarCliente();
    while (TRUE) {
        recibirMensaje();
        enviarMensaje();
    }
    cerrarSocket();
    limpiar();
}