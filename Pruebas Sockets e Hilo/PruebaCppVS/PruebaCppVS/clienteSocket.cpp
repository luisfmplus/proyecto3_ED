#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fstream>
#include <sstream>
using namespace std;

void escribirArchivo(string nombreArchivo, string texto) {
	ofstream archivo((nombreArchivo + ".txt").c_str());
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo " << nombreArchivo << " para limpiar" << endl;
	}
	else {
		archivo << texto;
	}
	archivo.close();
}

void agregarArchivo(string nombreArchivo, string texto) {
	ofstream archivo;
	archivo.open((nombreArchivo + ".txt").c_str(), ios_base::app);
	archivo << texto;
	archivo.close();
}

WSADATA WinSockData;
int iWsaStartUp;
int iWsaCleanUp;

SOCKET TCPClientSocket;
int iCloseSocket;

struct sockaddr_in TCPServerAdd;

int iConnect;

int iRecv;
char RecvBuffer[512];
int iRecvBuffer = 512;

int iSend;
char SenderBuffer[512] = "Hola desde el cliente";
string envio = "Mensaje de envio";
int iSenderBuffer = strlen(SenderBuffer) + 1;

void inicio() {
	iWsaStartUp = WSAStartup(MAKEWORD(2, 2), &WinSockData);
	if (iWsaStartUp != 0) {
		agregarArchivo("cliente", "WSAStartUp Failed " + to_string(WSAGetLastError()) + "\n");
	} else {
		agregarArchivo("cliente", "WSAStartUp Success\n");
	}
}

void crearSocket() {
	TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPClientSocket == INVALID_SOCKET) {
		agregarArchivo("cliente", "TCP Client Socket Creation Failed" + to_string(WSAGetLastError()) + "\n");
	} else {
		agregarArchivo("cliente", "TCP Client Socket Creation Success\n");
	}
}

void crearEstructura() {
	TCPServerAdd.sin_family = AF_INET;
	//TCPServerAdd.sin_addr.s_addr = inet_addr("localhost"); //Viejo de Servidor
	//IN_ADDR ip_value; // Nuevo de servidor
	//TCPServerAdd.sin_addr.s_addr = inet_pton(AF_INET, "localhost", &ip_value); //Nuevo de servidor
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1"); //Original de Cliente
	TCPServerAdd.sin_port = htons(8000);
}

void conectarServidor() {
	iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == SOCKET_ERROR) {
		agregarArchivo("cliente", "Connection Failed & Error No -> " + to_string(WSAGetLastError()) + "\n");
	} else {
		agregarArchivo("cliente", "Connection Success\n");
	}
}

void recibirMensaje() {
	iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR) {
		agregarArchivo("cliente", "Receive Data Failed & Error No -> " + to_string(WSAGetLastError()) + "\n");
	}
	agregarArchivo("cliente", "DATA RECEIVED -> ");
	agregarArchivo("cliente", RecvBuffer);
	agregarArchivo("cliente", "\n");
}

void enviarMensaje() {
	iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR) {
		agregarArchivo("cliente", "Sending Failed & Error No -> " + to_string(WSAGetLastError()) + "\n");
	} else {
		agregarArchivo("cliente", "Data Sending Success\n");
	}
}

void cerrarSocket() {
	iCloseSocket = closesocket(TCPClientSocket);
	if (iCloseSocket == SOCKET_ERROR) {
		agregarArchivo("cliente", "Closing Socket Failed & Error No -> " + to_string(WSAGetLastError()) + "\n");
	} else {
		agregarArchivo("cliente", "Closing Socket Success\n");
	}
}

void limpiar() {
	iWsaCleanUp = WSACleanup();
	if (iWsaCleanUp == SOCKET_ERROR) {
		agregarArchivo("cliente", "CleanUp Fun Failed & Error No -> " + to_string(WSAGetLastError()) + "\n");
	} else {
		agregarArchivo("cliente", "CleanUp Fun Success\n");
	}
}

void crearMensaje(string mensaje) {
	strcpy(SenderBuffer, mensaje.c_str());
	enviarMensaje();
	recibirMensaje();
}

void iniciarCliente() {
	escribirArchivo("cliente", "------------ TCP Client ------------\n\n");
	inicio();
	crearSocket();
	crearEstructura();
	conectarServidor();
	//recibirMensaje();
	//enviarMensaje();
	//cerrarSocket();
	//limpiar();
}