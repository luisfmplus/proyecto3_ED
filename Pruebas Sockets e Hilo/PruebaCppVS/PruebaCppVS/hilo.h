#pragma once

#ifndef  HILO_H
#define HILO_H

#include <iostream>
#include <thread>
using namespace std;

string str = "A";

void procesoHilo(){
	str = "B";
}

string crearHilo() {
	thread th(procesoHilo);
	//th.join();
	return str;
}

#endif // ! HILO_H
