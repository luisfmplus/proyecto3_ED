#ifndef FUNCIONESGENERALES_H
#define FUNCIONESGENERALES_H

#include "listas.h" //Se llama al header que posee las definiciones de las clases de los tipos de listas
#include <sstream> //librería que utilizamos para convertir datos en otros tipos de datos
#include <fstream> //librería que utilizamos para abrir archivos y leerlos

//Abre el archivo y va guardando cada línea en una lista simple
listaSimple leerArchivo(string nombreArchivo){
	listaSimple lineas;
	ifstream archivo;
	archivo.open(("Archivos/"+nombreArchivo+".txt").c_str());
	string linea;
	if (!archivo.fail()){
		while (getline(archivo, linea)){
            lineas.insertarFinal(linea);
        }
	}else{
		rojo(); cout << "No se pudo abrir el archivo " << nombreArchivo << " para leer" << endl; 
        rojo_amarillo(); cout << "Recuerde que los archivos tienen que estar en una carpeta llamada: Archivos y deben tener los nombres que se habian indicado previamente para los archivos de lectura"; azul(); cout << endl;
	}
	archivo.close();
	return lineas;
}

//Transforma strings en numeros
int StrToNum(string str){
	stringstream trans(str);
  	int num; 
    trans >> num; 
	return num;
}

//segmenta un string en partes, divididos por una letra específicada, devuelve una lista simple con cada uno elemento de los elementos segmentados 
listaSimple dividirString(string divisible , string divisor){
    listaSimple elems;
    string elem="" , temp;
    for(int i=0;i<divisible.length();i++){
        temp = divisible[i];
        if(temp==divisor){
            elems.insertarFinal(elem);
            elem = "";
        }else{
            elem += temp;
        }
    }
    elems.insertarFinal(elem);
    return elems;
}

//Explora un string y si no tiene ningún número ni letra, solo "vacíos" devuelve un true
bool isVacio(string palabra){
    bool vacio = true;
    string letra ;
    for(int i=0;i<palabra.length();i++){
        letra = palabra[i];
        if(letra!=" "){
            vacio = false;
            break;
        }
    }
    return vacio;
}

//Devuelve un true si el string ingresado es un número, un false si no
bool isNum(string str){
	bool isnum = false;
	for (int i=0;i<str.length();i++){
		isnum = isdigit(str[i]);
	}
	return isnum;
}

//explora una serie de datos, divididos por |, si alguno es vacío imprime un mensaje especificando cuál de los datos es y devuelve un false indicando que hay alguno vacío, según los nombres ingresados en el segundo parámentro divididos por |, si ninguno es vacío devuelve un true
bool validarNoVacios(string datos , string nombres){
    bool noVacio = true;
    string dato , nombre;
    listaSimple listaDatos , listaNombres;
    listaDatos = dividirString(datos,"|");
    listaNombres = dividirString(nombres,"|");
    for(int i=1;i<=listaDatos.largoLista();i++){
        dato = listaDatos.obtenerValorPos(i);
        nombre = listaNombres.obtenerValorPos(i);
        if(isVacio(dato)){
            rojo(); cout << "!!!!! Por favor no deje el campo de "+nombre+" vacio !!!!!" << endl; azul();
            noVacio = false;
        }
    }
    return noVacio;
}

//explora una serie de datos divididos por |, si uno no es un número lo indica aludiendo al nombre ingresado en la misma posición y devuelve un false
bool validarNumeros(string numeros , string nombres){
    bool num = true;
    string numero , nombre;
    listaSimple listaNumeros , listaNombres;
    listaNumeros = dividirString(numeros,"|");
    listaNombres = dividirString(nombres,"|");
    for(int i=1;i<=listaNumeros.largoLista();i++){
        numero = listaNumeros.obtenerValorPos(i);
        nombre = listaNombres.obtenerValorPos(i);
        if(!isNum(numero)){
            rojo(); cout << "!!!!! Por favor ingrese un numero en el campo de "+nombre+" !!!!!" << endl; azul();
            num = false;
        }
    }
    return num;
}

#endif