#ifndef PAISES_H
#define PAISES_H

#include "clasesArboles.h"
#include "clasesListas.h"

paisesL listaPaises;
paisesA arbolPaises;

void obtenerPaises(){
    listaSimple datosPaises = leerArchivo("Paises"), datosPais;
    paisesL paisesLista;
    paisesA paisesArbol;
    int codPais;
    string nombre;
    for(int i=1;i<=datosPaises.largoLista();i++){
        datosPais = dividirString(datosPaises.obtenerValorPos(i),";");
        codPais = StrToNum(datosPais.obtenerValorPos(1));
        nombre = datosPais.obtenerValorPos(2);
        paisesLista.insertarPais(codPais,nombre);
        paisesArbol.insertarPais(codPais);
    }
    listaPaises = paisesLista;
    arbolPaises = paisesArbol;
}

bool validarPais(string codigo, string nombre){
    bool valido = validarNoVacios(codigo+"|"+nombre,"codigo|nombre") && validarNumeros(codigo,"codigo");
    if(valido && listaPaises.obtenerPaisCodigo(StrToNum(codigo))!=NULL){
        valido = false;
        rojo(); cout << "!!!!! El codigo de pais no es valido, ya existe !!!!!" << endl; azul();
    }
    return valido;
}

bool validarCodigoPais(string codigo){
    bool valido = validarNoVacios(codigo,"codigo de pais") && validarNumeros(codigo,"codigo de pais");
    if(valido){
        ppaisNL tempPais = listaPaises.obtenerPaisCodigo(StrToNum(codigo));
        if(tempPais==NULL){
            valido = false;
            rojo(); cout << "!!!!! El codigo de pais ingresado no es valido, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

void insertarPais(bool first){
    string conf , codigo , nombre , estrellas;
    if(first) getline(cin,codigo);
    celeste(); cout << "Ha escogido insertar pais" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codigo); azul();
    cout<<"Ingrese el nombre del pais: "; amarillo(); getline(cin,nombre); azul();
    celeste(); cout << "Seguro de querer ingresar el hotel? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarPais(codigo,nombre)){
            listaPaises.insertarPais(StrToNum(codigo),nombre);
            verde(); cout << endl << "Pais registrado" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            insertarPais(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar el pais" << endl << endl; azul();
    }
}

void eliminarPais(bool first){
    string conf , codigo;
    if(first) getline(cin,codigo);
    celeste(); cout << "Ha escogido eliminar pais" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codigo); azul();
    celeste(); cout << "Seguro de querer eliminar el pais? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarCodigoPais(codigo)){
            listaPaises.eliminarPais(StrToNum(codigo));
            verde(); cout << endl << "Pais eliminado" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            eliminarPais(false);
        }
    }else{
        gris(); cout << endl << "Decidio no eliminar el pais" << endl << endl; azul();
    }
}

void modificarPais(bool first){
    string conf, codigo;
    if(first) getline(cin,codigo);
    celeste(); cout << endl << "Ha escogido modificar pais" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codigo); azul();
        if(validarCodigoPais(codigo)){
            cout << "Ingrese el nuevo nombre que va a sustituir a " << listaPaises.nombrePaisCodigo(StrToNum(codigo)) << ": "; string nuevoNombre; amarillo(); cin >> nuevoNombre; azul();
            celeste(); cout << "Seguro de querer modificar el nombre del pais? (S/N): "; amarillo(); getline(cin,conf); getline(cin,conf); azul();
            if(conf=="S"){
                if(validarNoVacios(nuevoNombre,"nuevo nombre de pais")){
                    listaPaises.modificarNombrePais(StrToNum(codigo),nuevoNombre);
                    verde(); cout << endl << "Nombre de pais modificado" << endl << endl; azul();
                }else{
                    rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                    modificarPais(false);
                }
            }else{
                gris(); cout << endl << "Decidio no modificar el nombre el pais" << endl << endl; azul();
            }
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            modificarPais(false);
        }
}

void opcionesPaises(){
    while(true){
        cout << "Opciones:" << endl << endl << "1 - Insertar Pais" << endl << "2 - Eliminar Pais" << endl << "3 - Modificar Nombre de Pais" << endl << "4 - Imprimir Lista de Paises" << endl << "5 - Salir" <<endl << endl;
        string opcion;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        if(opcion=="S") break;
        int numOpcion = StrToNum(opcion);
        if(numOpcion>0 && numOpcion<6){
            if(numOpcion==1){
                insertarPais(true);
            }
            if(numOpcion==2){
                eliminarPais(true);
            }
            if(numOpcion==3){
                modificarPais(true);
            }
            if(numOpcion==4){
                listaPaises.muestraDetalladaPaises();
            }
            if(numOpcion==5){
                break;
            }
        }else{
            rojo(); cout << "La opcion ingresada no esta dentro de las opciones brindadas" << endl; azul();
        }
    }
}

#endif