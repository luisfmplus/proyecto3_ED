#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "LectorCola.cpp"
#include "Codigo\8LDCPaises.cpp"
#include "Codigo\9ABBPaises.cpp"
#include "Codigo\10LDCReservaciones.cpp"
#include "Codigo\ArbolesBinarios.h"

#include "Codigo\Conexiones.h"

LectorCola* Lector;
LDCPaises* LisPaises;
ArbolABB_Paises* ArbPaises;
ArbolB_Persona* Usuarios;
ArbolB_Persona* AdminAgencia;
ArbolB_Persona* AdminHotel;
LDCReservaciones* Reservac;
pnodocarro PosCarro;

void limpiarbuffer(char* buff, int tamano){ //limpia los arreglos de chars

    for (int i = 0; i < tamano; i++){
        buff[i] = '\000';
    }
}

void leer_todo_los_archivos(pnodohotel& ultimoHotel, pnodopisohotel& ultimoPiso, pnodohabitacion& ultimaHabitacion, pnodoAgencia& ultimaAgencia, pnodotipoflotilla& ultimaFlotilla, pnodocarro& ultimoCarro){
    //punteros
    pnodoabbpais abbp;
    pnodoldcpais ldcp;
    pnodohotel i;
    pnodopisohotel j;
    pnodoAgencia k;
    pnodotipoflotilla c;

    // punteros
    LisPaises = new LDCPaises();
    ArbPaises = new ArbolABB_Paises();
    Usuarios = new ArbolB_Persona(4);
    AdminAgencia = new ArbolB_Persona(4);
    AdminHotel = new ArbolB_Persona(4);

    // variables temporales tipo int
    int pais;
    int temp1;
    int temp2;
    int temp3;
    int temp4;
    int temp5;
    int temp6;
    int temp7;
    int temp8;


    //varialbes temporales tipo char[]
    char aux1[30] = "\000";
    char aux2[30] = "\000";



    Lector = new LectorCola(0); //leemos paises

    while (!Lector->ListaVacia()){
        
        Lector->getValor(1,pais);
        Lector->getValor(2,aux1);//debe leerse el nombre

        if ((pais == -1)||(aux1[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }

        ArbPaises->insertarNodo(pais,aux1);
        LisPaises->InsertarInicio(pais,aux1);

        Lector->BorrarInicio();

    }


    delete Lector;



//__________________________

    Lector = new LectorCola(1); //leemos hoteles

    while (!Lector->ListaVacia()){
        
        Lector->getValor(1,pais);
        Lector->getValor(2,temp1);//debe leerse el codigo
        Lector->getValor(3,aux1);//debe leerse el nombre
        Lector->getValor(4,temp3);//debe leerse la cantidad de estrellas

        if ((pais == -1)||(temp1 == -1)||(aux1[0] == '\000')||(temp3 == -1)){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }
        
        abbp = ArbPaises->getNodo(pais);

        if (abbp == NULL){
            //pais no existe
            Lector->BorrarInicio();
            continue;

        }
        
        if (abbp->Hoteles->insertarNodo(temp1,aux1,temp3) == 1){
            ultimoHotel = abbp->Hoteles->getultimoNodoInsertado();//se actualiza la ubicacion del ultimo nodo insertado
        }
        Lector->BorrarInicio();

    }
    delete Lector;

    Lector = new LectorCola(2); //leemos Pisohoteles

    //se debe manejar la insercion de los pisos en los hoteles aqui
    while (!Lector->ListaVacia()){

        Lector->getValor(1,pais);
        Lector->getValor(2,temp1);//debe leerse el codigo hotel
        Lector->getValor(3,temp2);//debe leerse el codigo piso
        Lector->getValor(4,aux1); //debe leerse el nombre
        Lector->getValor(5,temp4);//debe leerse la cantidad de habitaciones

        if ((pais == -1)||(temp1 == -1)||(temp2 == -1)||(aux1[0] == '\000')||(temp4 == -1)){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }

        abbp = ArbPaises->getNodo(pais);

        if (abbp == NULL){
            //pais no existe
            Lector->BorrarInicio();
            continue;

        }

        //todos los hoteles ya fueron insertados
        i = abbp->Hoteles->getNodo(temp1);

        if (i == NULL){
            //hotel no existe
            Lector->BorrarInicio();
            continue;
        }
        

        if (i->piso->insertarNodo(temp2, aux1, temp4) == 1){
            
            ultimoPiso = i->piso->getultimoNodoInsertado(); //se actualiza la ubicacion del ultimo nodo insertado
        }
        Lector->BorrarInicio();
    
    }
    delete Lector;

    Lector = new LectorCola(3); //leemos Habitaciones

    //se debe manejar la insercion de las habitaciones en los pisos aqui
    while (!Lector->ListaVacia()){

        Lector->getValor(1,pais);
        Lector->getValor(2,temp1);//debe leerse el codigo hotel
        Lector->getValor(3,temp2);//debe leerse el codigo piso
        Lector->getValor(4,temp3);//debe leerse el codigo habitacion
        Lector->getValor(5,aux1); //debe leerse el tipo cuarto
        Lector->getValor(6,temp5);//debe leerse el numero de camas
        Lector->getValor(7,temp6);//debe leerse el precio de la habitacion
        Lector->getValor(8,aux2);//debe leerse el estado de la habitacion


        if ((pais == -1)||(temp1 == -1)||(temp2 == -1)||(temp3 == -1)||(temp5 == -1)||(temp6 == -1)||(aux1[0] == '\000')||(aux2[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }

        abbp = ArbPaises->getNodo(pais);

        if (abbp == NULL){
            //pais no existe
            Lector->BorrarInicio();
            continue;

        }

        //todos los hoteles ya fueron insertados
        i = abbp->Hoteles->getNodo(temp1);

        if (i == NULL){
            //hotel no existe
            Lector->BorrarInicio();
            continue;
        }

        //todos los pisos ya fueron insertados
        j = i->piso->getNodo(temp2);

        if (j == NULL){
            //piso no existe
            Lector->BorrarInicio();
            continue;
        }



        if (j->habitacion->insertarNodo(temp3, aux1, temp5, temp6, aux2[0]) == 1){
            
            if ((aux2[0] == 'r') ||(aux2[0] == 'R') ){
                //Reservac->InsertarInicio(pais,temp1, temp2, temp3,j->habitacion->getultimoNodoInsertado());
            }
            

            ultimaHabitacion = j->habitacion->getultimoNodoInsertado(); //se actualiza la ubicacion del ultimo nodo insertado
        }
        Lector->BorrarInicio();
    
    }
    delete Lector;

    Lector = new LectorCola(4); //leemos Agencias

    while (!Lector->ListaVacia()){
        
        Lector->getValor(1,pais);
        Lector->getValor(2,temp1);//debe leerse el codigo
        Lector->getValor(3,aux1);//debe leerse el nombre
        Lector->getValor(4,temp3);//debe leerse la cantidad de vehiculos

        if ((pais == -1)||(temp1 == -1)||(temp3 == -1)||(aux1[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }

        abbp = ArbPaises->getNodo(pais);

        if (abbp == NULL){
            //pais no existe
            Lector->BorrarInicio();
            continue;

        }


        if (abbp->Agencias->insertarNodo(temp1,aux1,temp3) == 1){
            ultimaAgencia = abbp->Agencias->getultimoNodoInsertado(); //se actualiza la ubicacion del ultimo nodo insertado
        }
        Lector->BorrarInicio();

    }
    delete Lector;

    Lector = new LectorCola(5); //leemos Flotillas

    //se debe manejar la insercion de las Flotillas en los hoteles aqui
    while (!Lector->ListaVacia()){

        Lector->getValor(1,pais);
        Lector->getValor(2,temp1);//debe leerse el codigo agencia
        Lector->getValor(3,temp2);//debe leerse el codigo flotilla
        Lector->getValor(4,aux1); //debe leerse el tipo carro
        Lector->getValor(5,temp4);//debe leerse el cantida de carros tipo

        if ((pais == -1)||(temp1 == -1)||(temp2 == -1)||(temp4 == -1)||(aux1[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }

        abbp = ArbPaises->getNodo(pais);

        if (abbp == NULL){
            //pais no existe
            Lector->BorrarInicio();
            continue;

        }

        k = abbp->Agencias->getNodo(temp1);

        if (k == NULL){
            //Agencia no existe
            Lector->BorrarInicio();
            continue;

        }

        if (k->flotilla->insertarNodo(temp2, aux1, temp4) == 1){
            
            ultimaFlotilla = k->flotilla->getultimoNodoInsertado(); //se actualiza la ubicacion del ultimo nodo insertado
        }
        Lector->BorrarInicio();
    
    }
    delete Lector;

    Lector = new LectorCola(6); //leemos Carros

    //se debe manejar la insercion de los carros aquí
    while (!Lector->ListaVacia()){

        Lector->getValor(1,pais);
        Lector->getValor(2,temp1);//debe leerse el codigo agencia
        Lector->getValor(3,temp2);//debe leerse el codigo flotilla
        Lector->getValor(4,temp3);//debe leerse el codigo carro(placa)
        Lector->getValor(5,aux1); //debe leerse el modelo
        Lector->getValor(6,temp5);//debe leerse el numero de asientos
        Lector->getValor(7,temp6);//debe leerse el año
        Lector->getValor(8,temp7);//debe leerse el precio del carro
        Lector->getValor(9,aux2);//debe leerse el estado del carro


        if ((pais == -1)||(temp1 == -1)||(temp2 == -1)||(temp3 == -1)||(temp5 == -1)||(temp6 == -1)||(temp7 == -1)||(aux1[0] == '\000')||(aux2[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;
        }


        abbp = ArbPaises->getNodo(pais);

        if (abbp == NULL){
            //pais no existe
            Lector->BorrarInicio();
            continue;

        }

        k = abbp->Agencias->getNodo(temp1);

        if (k == NULL){
            //Agencia no existe
            Lector->BorrarInicio();
            continue;

        }

        c = k->flotilla->getNodo(temp2);

        if (c->carro->insertarNodo(temp3, aux1, temp5, temp6, temp7, aux2[0]) == 1){
            
            if ((aux2[0] == 'r') ||(aux2[0] == 'R') ){
                // Reservac->InsertarInicio(pais,temp1, temp2, temp3, (c->carro->getultimoNodoInsertado()));
            }

            ultimoCarro = c->carro->getultimoNodoInsertado(); //se actualiza la ubicacion del ultimo nodo insertado
        }
        Lector->BorrarInicio();
    
    }
    delete Lector;

    Lector = new LectorCola(7); //leemos usuarios

    while (!Lector->ListaVacia()){
        
        Lector->getValor(1,temp1);//debe leerse el codigo
        Lector->getValor(2,aux1);//debe leerse el nombre
        if ((temp1 == -1)||(aux1[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;

        }
        Usuarios->insertarNodo(temp1,aux1);//la clase no lo insetar si temp esta repetido
        Lector->BorrarInicio();

    }
    delete Lector;

    Lector = new LectorCola(8); //leemos AdminH

    while (!Lector->ListaVacia()){
        
        Lector->getValor(1,temp1);//debe leerse el codigo
        Lector->getValor(2,aux1);//debe leerse el nombre
        if ((temp1 == -1)||(aux1[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;

        }
        AdminHotel->insertarNodo(temp1,aux1);//la clase no lo insetar si temp esta repetido
        Lector->BorrarInicio();

    }
    delete Lector;

    Lector = new LectorCola(9); //leemos AdminA

    while (!Lector->ListaVacia()){
        
        Lector->getValor(1,temp1);//debe leerse el codigo
        Lector->getValor(2,aux1);//debe leerse el nombre
        if ((temp1 == -1)||(aux1[0] == '\000')){ //validacion de que la informacion viene completa
            Lector->BorrarInicio();
            continue;

        }
        AdminAgencia->insertarNodo(temp1,aux1);//la clase no lo insetar si temp esta repetido
        Lector->BorrarInicio();

    }
    delete Lector;

}

void imprimirMenus(int numero, bool opcion){
    /*
    1.Menu principal
    2.Menu Administrador
    3.Menu Insercion
    4.Menu Eliminacion
    5.Menu Modificacion
    6.Menu reporte hoteles
    7.Menu reporte agencias
    8.Propiedades carros
    9.Menu Usuario
    */
    int i;
    char hotel[] ="Hotel";
    char piso[] = "Piso";
    char habitacion[] = "Habitacion";
    char agencia[] ="Agencia";
    char flotilla[] = "Flotilla";
    char carro[] = "Carro";
    char nodoprincipal[10] = "\000";
    char nodosecundario[10] = "\000";
    char nodoterceario[12] = "\000";



    if (opcion){
        for ( i = 0; ((i < sizeof(nodoprincipal))&& (i < sizeof(hotel))); i++){
            nodoprincipal[i] = hotel[i];

        }

        for ( i = 0; ((i < sizeof(nodosecundario))&& (i < sizeof(piso))); i++){
            nodosecundario[i] = piso[i];

        }

        for ( i = 0; ((i < sizeof(nodoterceario))&& (i < sizeof(habitacion))); i++){
            nodoterceario[i] = habitacion[i];

        }

    } else{
        for ( i = 0; ((i < sizeof(nodoprincipal))&& (i < sizeof(agencia))); i++){
            nodoprincipal[i] = agencia[i];

        }

        for ( i = 0; ((i < sizeof(nodosecundario))&& (i < sizeof(flotilla))); i++){
            nodosecundario[i] = flotilla[i];

        }

        for ( i = 0; ((i < sizeof(nodoterceario))&& (i < sizeof(carro))); i++){
            nodoterceario[i] = carro[i];

        }

    }
    
    switch (numero){

    case -1:
        cout << "\nERROR: Lista Vacia"<<endl;
        break;

    case -2:
        cout << "\nERROR: Fuera de Rango"<<endl;
        break;

    case -3:
        cout << "\nERROR: Repetido"<<endl;
        break;

    case -4:
        cout << "\nERROR: Error encontrado"<<endl;
        break;

    case 1:
        cout <<"\nMenu Principal\n\n";
        cout << "0. Salir\n";
        cout << "1. Administrador Agencia\n";
        cout << "2. Administrador Hoteles\n";
        cout << "3. Usuarios\n";
        cout << "4. Mantenimiento paises"<< endl;
        break;

    case 2:
        cout <<"\nMenu Administrador ";
        if (opcion){
            cout <<"Hoteles\n\n";
        
        } else {
            cout <<"Agencias\n\n";
        }
        
        cout << "0. retornar\n";
        cout << "1. Insertar\n";
        cout << "2. Eliminar\n";
        cout << "3. Modificar\n";
        cout << "4. Generar Reporte"<<endl;
        break;

    case 3:
        cout <<"\nMenu Inserciones\n\n";
        cout << "0. retornar\n";
        cout << "1. Insertar " << nodoprincipal<< "\n";
        cout << "2. Insertar " << nodosecundario << "\n";
        cout << "3. Insertar "<< nodoterceario << endl;
        break;

    case 4:
        cout << "\nMenu Eliminacion\n\n";
        cout << "0. retornar\n";
        cout << "1. Eliminar " << nodoprincipal << "\n";
        cout << "2. Eliminar " << nodosecundario << "\n";
        cout << "3. Eliminar "<< nodoterceario << endl;
        break;

    case 5:
        cout << "\nMenu Modificaciones\n\n";
        cout << "0. retornar\n";
        cout << "1. Modificar " << nodoprincipal << "\n";
        cout << "2. Modificar " << nodosecundario << "\n";
        cout << "3. Modificar "<< nodoterceario << endl;
        break;

    case 6:
        cout << "\nMenu Reporte\n\n";
        cout << "0. retornar\n";
        cout << "1. Consultar Hoteles" << "\n";
        cout << "2. Consultar Pisos" << "\n";
        cout << "3. Consultar Habitaciones" << "\n";
        cout << "4. Consultar estrellas" << "\n";
        cout << "5. Consultar cantidad Habitaciones" << "\n";
        cout << "6. Consultar ultimo Hotel" << "\n";
        cout << "7. Consultar ultimo Piso" << "\n";
        cout << "8. Consultar ultimo Habitacion" << "\n";
        cout << "9. Consultar reservaciones" << endl;
        break;

    case 7:
        cout << "\nMenu Reporte\n\n";
        cout << "0. retornar\n";
        cout << "1. Consultar Agencias" << "\n";
        cout << "2. Consultar Flotilla" << "\n";
        cout << "3. Consultar cantidad CarrosTipos" << "\n";
        cout << "4. Consultar cantidad de asientos" << "\n";
        cout << "5. Consultar propiedades Carro" << "\n";
        cout << "6. Consultar ultima Agencia" << "\n";
        cout << "7. Consultar ultima Flotilla" << "\n";
        cout << "8. Consultar ultimo Carro" << "\n";
        cout << "9. Consultar Carros" << "\n";
        cout << "10. Consultar reservaciones" << endl;
        break;
    
    case 8:
        cout << "\nPropiedades Carro\n\n";
        cout << "0. retornar\n";
        cout << "1. Consultar Modelo" << "\n";
        cout << "2. Consultar Anno" << "\n";
        cout << "3. Consultar Numero de asientos" << "\n";
        cout << "4. Consultar Precio" << "\n";
        cout << "5. Consultar Estado del Carro" << endl;
        break;

    case 9:
        cout << "\nMenu Usuario\n\n";
        cout << "0. retornar\n";
        cout << "1. Consultar hoteles" << "\n";
        cout << "2. Consultar pisos de un hotel" << "\n"; 
        cout << "3. Consultar habitaciones de un piso de un hotel" << "\n";
        cout << "4. Consultar agencias" << "\n";
        cout << "5. Consultar flotillas de una agencia" << "\n"; 
        cout << "6. Consultar carros de una flotilla de una agencia" << "\n";
        cout << "7. Consultar paises" << "\n";
        cout << "8. Hacer una reservacion" << "\n";
        break;


    case 10:
        cout << "\nMenu Mantenimiento\n\n";
        cout << "0. retornar\n";
        cout << "1. Insertar Pais" << "\n";
        cout << "2. Eliminar Pais" << "\n"; 
        cout << "3. Modificar Pais" << "\n";
        cout << "4. Consultar Paises" << "\n";
        break;

    case 11:
        cout << "\nMenu Reservaciones\n\n";
        cout << "0. retornar\n";
        cout << "1. Reservar hotel" << "\n";
        cout << "2. Reservar Agencia" << "\n"; 
        cout << "3. Reservacion todo incluido" << "\n";
        cout << "9. Pagar una reservacion"<<endl;
        cout << "10. Cancelar Reservacion "<<endl;
        break;

    default:
        break;
    }
}

int transformarint(char* fp){ //requiere que fp contenga solo numeros

  int j = 0;
  int i;

  for ( i = 0; fp[i]!='\000'; i++){
    
    j = (10*j)+(fp[i]-48);
  }
  return j;
}

int verificarEntrada(char* entrada){ 
    // verifica que la entrada sea un numero y que este no tenga otro caracter siguiente
    //por lo tanto limita a un maximo de 100 opciones. de 0 a 9

    bool esNumero = false;
    int i;

    for (i = 0; entrada[i] != '\000'; i++){
        //contamos cuando elementos tiene la entrada
    }
    

    // son los primero dos caracteres numeros
    for (int j = 0; j <= 1; j++){

        if ((entrada[j]>=48) && (entrada[j] <= 57)){

            esNumero = true;
            continue;

        }

        esNumero = false;
        break;
    }
    
    entrada[2] = '\000';


    if (i == 1){

        return (entrada[0] - 48);

    }
    

    // entra si de entrada venian solo numeros
    if (esNumero && (i <= 2) ){
        
        return transformarint(entrada);
    }
    
    return -4;

}

bool verificarEntrada(char* entrada, int& numero){
    //verifica que la entrada sea solamente numeros
    //retorna el numero leeido
    int i;
    int var;

  for ( i = 0; entrada[i] != '\000'; i++){ // es toda la expresion un numero entero?

    if(entrada[i]>=48 && entrada[i] <= 57){
      continue;

    }
    return false; //no

  }
  numero = transformarint(entrada);
  return true; //si

}

void cancelarReservacion(LDCReservaciones* reserva, string pasaporte){
    reserva->reservasPendientes(pasaporte);
    string opcionReserva;
    cout<<endl;
    cout<<"Digite el codigo de la reserva a cancelar: ";
    cin>>opcionReserva;
    //verificar si existe ese codigo de reserva
    if(reserva->existeCodigoR(opcionReserva)==false){
        cout<<"No existe esa reservacion"<<endl;
        return;
    }
    reserva->cancelarReservacion(opcionReserva);
}

void insertar_Nodo(bool AH, int numero, pnodohotel& ultimoHotel, pnodopisohotel& ultimoPiso, pnodohabitacion& ultimaHabitacion, pnodoAgencia& ultimaAgencia, pnodotipoflotilla& ultimaFlotilla, pnodocarro& ultimoCarro, string pasaporte){
//es posible aumentar la eficiencia de esta funcion y eliminar

    pnodoabbpais abbp;
    pnodohotel hotel;
    pnodopisohotel piso;
    pnodohabitacion habitacion;
    pnodoAgencia agencia;
    pnodotipoflotilla flotilla;
    pnodocarro carro;


    int entradaInt1 = -4;
    int entradaInt2 = -4;
    int entradaInt3 = -4;
    int entradaInt4 = -4;
    int entradaInt5 = -4;
    char entradaChar1[30] = "\000";
    char entradaChar2[30] = "\000";
    char entradaChar3[30] = "\000";
    char entradaChar4[30] = "\000";
    char entradaChar5[30] = "\000";


    if (AH){

        switch (numero){

        case 0: // Paises de LDC y ABB

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp != NULL){
                cout << "\n\nPais ya existe" << endl;
                break;
            }

            cout << "\nDigite el nombre del Pais: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            LisPaises->InsertarInicio(entradaInt1,entradaChar2);
            ArbPaises->insertarNodo(entradaInt1,entradaChar2);
            cout<<"\ninformacion insertada exitosamente\n\n";
            break;



        case 1: // Hoteles

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }
            

            cout <<"\nDigite un codigo(numerico) para el hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel != NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite el nombre del hotel: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            cout << "\nDigite la cantidad de estrellas: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido?
                cout<<"\ninformacion insertada exitosamente\n\n";
                abbp->Hoteles->insertarNodo(entradaInt1,entradaChar2,entradaInt3);
                ultimoHotel = abbp->Hoteles->getultimoNodoInsertado();
                break; // fin del proceso

            }
            cout << "\n\nentrada no valida" << endl;
            break;//fin del proceso

        case 2: //Pisos

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado es valido(not)?
                cout<< "entrada no valida " << endl;
                break;//fin del proceso

            }
            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para el piso: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
            if (!verificarEntrada(entradaChar3,entradaInt3)){//es el codigo digitado valido(not)?
                cout<< "entrada no valida " << endl;
                break;//fin del proceso
            }
                            
            piso = hotel->piso->getNodo(entradaInt3);

            if (piso != NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }
            cout << "\nDigite el nombre del piso: ";
            cin >> entradaChar4;
            entradaChar4[(sizeof(entradaChar4)-1)] = '\000';

            cout << "\nDigite la cantidad de habitaciones: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
            if (!(verificarEntrada(entradaChar2,entradaInt2))){ //es el codigo digitado valido(not)?
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }

            cout<< "\nInsercion exitosa de la informacion\n";
            hotel->piso->insertarNodo(entradaInt3,entradaChar4,entradaInt2);
            ultimoPiso = hotel->piso->getultimoNodoInsertado();
            break;//fin del proceso
            

        case 3: //Habitaciones (modificar)
            
            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado es valido(not)?
                cout<< "entrada no valida " << endl;
                break;//fin del proceso

            }
            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para el piso: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
            if (!verificarEntrada(entradaChar3,entradaInt3)){//es el codigo digitado valido(not)?
                cout<< "entrada no valida " << endl;
                break;//fin del proceso
            }
                            
            piso = hotel->piso->getNodo(entradaInt3);

            if (piso == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            /*al ya tener las ubicaciones de los nodos en "nodoubicacion 1 y 2" 
            debemos limpiar las entradas correspondientes
            */
            limpiarbuffer(entradaChar1, sizeof(entradaChar1));
            limpiarbuffer(entradaChar2, sizeof(entradaChar2));

            cout << "\nDigite el codigo(numerico) para la habitacion: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';
            if (!(verificarEntrada(entradaChar1,entradaInt3))){ //es el codigo digitado valido(not)?
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }
            habitacion = piso->habitacion->getNodo(entradaInt3);

            if (habitacion != NULL){//se encontro el codigo?
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }

            cout << "\nindique que tipo de cuarto es la habitacion: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            cout << "\nindique cuantas camas tiene la habitacion: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (!(verificarEntrada(entradaChar3,entradaInt4))){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }

            cout << "\nindique el precio de la habitacion: ";
            cin >> entradaChar4;
            entradaChar4[(sizeof(entradaChar4)-1)] = '\000';

            if (!(verificarEntrada(entradaChar4,entradaInt5))){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
                    
            cout << "\nindique el estado actual de la habitacion: ";
            cin >> entradaChar5;
            entradaChar5[(sizeof(entradaChar5)-1)] = '\000';

            //validacion de la entrada?
            if ((entradaChar5[1] != '\000')||((entradaChar5[0] != 'o') && (entradaChar5[0] != 'r') && (entradaChar5[0] != 'l') && (entradaChar5[0] != 'O') && (entradaChar5[0] != 'R') && (entradaChar5[0] != 'L'))){
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
                    

            cout<< "\nInsercion exitosa de la informacion\n";
            piso->habitacion->insertarNodo(entradaInt3,entradaChar2,entradaInt4,entradaInt5,entradaChar5[0]);
            ultimaHabitacion = piso->habitacion->getultimoNodoInsertado();
            break;//fin del proceso


        case 4: // Reservacion de hotel

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt2)){ //es el codigo digitado es valido(not)?
                cout<< "\nentrada no valida\n" ;
                break;//fin del proceso

            }
            hotel = abbp->Hoteles->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para el piso: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
            if (!verificarEntrada(entradaChar3,entradaInt3)){//es el codigo digitado valido(not)?
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }
                            
            piso = hotel->piso->getNodo(entradaInt3);

            if (piso == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            /*al ya tener las ubicaciones de los nodos en "nodoubicacion 1 y 2" 
            debemos limpiar las entradas correspondientes
            */
            limpiarbuffer(entradaChar1, sizeof(entradaChar1));
            limpiarbuffer(entradaChar2, sizeof(entradaChar2));

            cout << "\nDigite el codigo(numerico) para la habitacion: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';
            if (!(verificarEntrada(entradaChar1,entradaInt4))){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
            habitacion = piso->habitacion->getNodo(entradaInt4);

            if (habitacion == NULL){//se encontro el codigo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            piso->habitacion->getEstadoHab(entradaChar2[0],habitacion);

            if (entradaChar2[0] == 'L'){
                piso->habitacion->setEstadoHab('R',habitacion);
                Reservac->InsertarInicio(entradaInt1,entradaInt2,entradaInt3,entradaInt4, habitacion,pasaporte);
                cout<< "\nReservacion exitosa\n";
                break;
            }
            
            cout<< "\nReservacion fallida\n";

            break;

        case 5: // Reservacion de agecia

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }

            cout <<"\nDigite un codigo(numerico) para la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt2)){ //es el codigo digitado valido?
                cout << "\nentrada no valida\n";
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
            if (!verificarEntrada(entradaChar2,entradaInt3)){
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }
            
            flotilla = agencia->flotilla->getNodo(entradaInt3);

            if (flotilla == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }
            /*al ya tener las ubicaciones de los nodos en "nodoubicacion 1 y 2" 
            debemos limpiar las entradas correspondientes
            */
            limpiarbuffer(entradaChar1, sizeof(entradaChar1));
            limpiarbuffer(entradaChar2, sizeof(entradaChar2));

            cout << "\nDigite el codigo(numerico) para el carro: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';
            if (!(verificarEntrada(entradaChar1,entradaInt4))){ // es el codigo valido(not)
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
            carro = flotilla->carro->getNodo(entradaInt4);

            if (carro == NULL){
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            flotilla->carro->getEstadodelCarro(entradaChar2[0], carro);

            if (entradaChar2[0] == 'L'){
                flotilla->carro->setEstadodelCarro('R',carro);
                Reservac->InsertarInicio(entradaInt1,entradaInt2,entradaInt3,entradaInt4, carro,pasaporte);
                cout<< "\nReservacion exitosa\n";
                break;
            }
            
            cout<< "\nReservacion fallida\n";

            break;

        case 6: // Reservacion todo incluido

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt2)){ //es el codigo digitado es valido(not)?
                cout<< "\nentrada no valida\n" ;
                break;//fin del proceso

            }
            hotel = abbp->Hoteles->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para el piso: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
            if (!verificarEntrada(entradaChar3,entradaInt3)){//es el codigo digitado valido(not)?
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }
                            
            piso = hotel->piso->getNodo(entradaInt3);

            if (piso == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            /*al ya tener las ubicaciones de los nodos en "nodoubicacion 1 y 2" 
            debemos limpiar las entradas correspondientes
            */
            limpiarbuffer(entradaChar1, sizeof(entradaChar1));
            limpiarbuffer(entradaChar2, sizeof(entradaChar2));

            cout << "\nDigite el codigo(numerico) para la habitacion: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';
            if (!(verificarEntrada(entradaChar1,entradaInt4))){ //es el codigo digitado valido(not)?
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
            habitacion = piso->habitacion->getNodo(entradaInt4);

            if (habitacion == NULL){//se encontro el codigo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite un codigo(numerico) para la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt2)){ //es el codigo digitado valido?
                cout << "\nentrada no valida\n";
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
            if (!verificarEntrada(entradaChar2,entradaInt3)){
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }
            
            flotilla = agencia->flotilla->getNodo(entradaInt3);

            if (flotilla == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }
            /*al ya tener las ubicaciones de los nodos en "nodoubicacion 1 y 2" 
            debemos limpiar las entradas correspondientes
            */
            limpiarbuffer(entradaChar1, sizeof(entradaChar1));
            limpiarbuffer(entradaChar2, sizeof(entradaChar2));

            cout << "\nDigite el codigo(numerico) para el carro: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';
            if (!(verificarEntrada(entradaChar1,entradaInt4))){ // es el codigo valido(not)
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
            carro = flotilla->carro->getNodo(entradaInt4);

            if (carro == NULL){
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            flotilla->carro->getEstadodelCarro(entradaChar1[0],carro);
            piso->habitacion->getEstadoHab(entradaChar2[0],habitacion);

            if ((entradaChar1[0] == 'L') && (entradaChar2[0] == 'L')){
                
                flotilla->carro->setEstadodelCarro('R',carro);
                piso->habitacion->setEstadoHab('R',habitacion);
                Reservac->InsertarInicio(entradaInt1,entradaInt2,entradaInt3,entradaInt4, carro, pasaporte);

                abbp->Hoteles->getCodHotel(entradaInt2, hotel);
                hotel->piso->getNumPiso(entradaInt3, piso);
                piso->habitacion->getCodHabitacion(entradaInt4, habitacion);

                Reservac->InsertarInicio(entradaInt1,entradaInt2,entradaInt3,entradaInt4, carro, habitacion,pasaporte);
                
                cout<< "\nReservacion exitosa\n";
                break;

            }
                
            if ((entradaChar1[0] != 'L')){
                cout<< "\nCarro no disponible\n";
            
            }

            if ((entradaChar2[0] != 'L')){
                cout<< "\nHabitacion no disponible\n";
            
            }
            
            cout<< "\nReservacion fallida\n";
            break;



        default:
            break;
        }

    } else {

        switch (numero){

        case 1: // Agencias

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite un codigo(numerico) para la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia != NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite el nombre de la agencia: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            cout << "\nDigite la cantidad de vehiculos: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (verificarEntrada(entradaChar3,entradaInt3)){
                cout<<"\ninformacion insertada exitosamente\n\n";
                abbp->Agencias->insertarNodo(entradaInt1,entradaChar2,entradaInt3);
                ultimaAgencia = abbp->Agencias->getultimoNodoInsertado();
                break; // fin del proceso

            }
            cout << "\n\nentrada no valida" << endl;
            break;//fin del proceso


        case 2: //Flotilla

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite un codigo(numerico) para la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
            if (!verificarEntrada(entradaChar2,entradaInt2)){
                cout<< "entrada no valida " << endl;
                break;//fin del proceso
            }
            
            flotilla = agencia->flotilla->getNodo(entradaInt2);

            if (flotilla != NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite el nombre de tipo de flotilla: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            cout << "\nDigite la cantidad de carros: ";
            cin >> entradaChar4;
            entradaChar4[(sizeof(entradaChar4)-1)] = '\000';
            if (!(verificarEntrada(entradaChar4,entradaInt4))){ //es el codigo digitado valido(not)?
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }

            cout<< "\nInsercion exitosa de la informacion\n";
            agencia->flotilla->insertarNodo(entradaInt2,entradaChar3,entradaInt4);
            ultimaFlotilla = agencia->flotilla->getultimoNodoInsertado();
            break;//fin del proceso
            

        case 3: //Carros
            
            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite un codigo(numerico) para la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nDigite un codigo(numerico) para la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
            if (!verificarEntrada(entradaChar2,entradaInt2)){
                cout<< "\nentrada no valida\n";
                break;//fin del proceso
            }
            
            flotilla = agencia->flotilla->getNodo(entradaInt2);

            if (flotilla == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }
            /*al ya tener las ubicaciones de los nodos en "nodoubicacion 1 y 2" 
            debemos limpiar las entradas correspondientes
            */
            limpiarbuffer(entradaChar1, sizeof(entradaChar1));
            limpiarbuffer(entradaChar2, sizeof(entradaChar2));

            cout << "\nDigite el codigo(numerico) para el carro: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';
            if (!(verificarEntrada(entradaChar1,entradaInt3))){ // es el codigo valido(not)
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
            carro = flotilla->carro->getNodo(entradaInt3);

            if (carro != NULL){
                cout << "\nEl codigo digitado ya existe\n";
                break;//fin del proceso

            }

            cout << "\nindique el modelo del carro: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            cout << "\nindique el numero de asientos: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (!(verificarEntrada(entradaChar3,entradaInt4))){ // es el codigo valido(not)
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }

            cout << "\nindique el anno del carro: ";
            cin >> entradaChar4;
            entradaChar4[(sizeof(entradaChar4)-1)] = '\000';

            if (!(verificarEntrada(entradaChar4,entradaInt5))){ // es el codigo valido(not)
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
            limpiarbuffer(entradaChar4, sizeof(entradaChar4));

            cout << "\nindique el precio del carro: ";
            cin >> entradaChar4;
            entradaChar4[(sizeof(entradaChar4)-1)] = '\000';

            if (!(verificarEntrada(entradaChar4,entradaInt1))){ // es el codigo valido(not)
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
                    
            cout << "\nindique el estado del carro: ";
            cin >> entradaChar5;
            entradaChar5[(sizeof(entradaChar5)-1)] = '\000';

            if ((entradaChar5[1] != '\000')||((entradaChar5[0] != 'o') && (entradaChar5[0] != 'r') && (entradaChar5[0] != 'l') && (entradaChar5[0] != 'O') && (entradaChar5[0] != 'R') && (entradaChar5[0] != 'L'))){
                cout << "\nentrada no valida\n";
                break;//fin del proceso

            }
                    

            cout<< "\nInsercion exitosa de la informacion\n";
            flotilla->carro->insertarNodo(entradaInt3,entradaChar2,entradaInt4,entradaInt5,entradaInt1, entradaChar5[0]);
            ultimoCarro = flotilla->carro->getultimoNodoInsertado();
            break;//fin del proceso

        default:
            break;
        }
    }
    return;
}

void eliminar_Nodo(bool AH, int numero, pnodohotel& ultimoHotel, pnodopisohotel& ultimoPiso, pnodohabitacion& ultimaHabitacion, pnodoAgencia& ultimaAgencia, pnodotipoflotilla& ultimaFlotilla, pnodocarro& ultimoCarro){ //elimina un nodo

    // AH = true y numero = 0
    // borramos nodo de la lista LDC de paises

    pnodoabbpais abbp;
    pnodoldcpais ldcp;
    pnodohotel hotel;
    pnodopisohotel piso;
    pnodohabitacion habitacion;
    pnodoAgencia agencia;
    pnodotipoflotilla flotilla;
    pnodocarro carro;


    int entradaInt1 = -4;
    int entradaInt2 = -4;
    int entradaInt3 = -4;
    char entradaChar1[30] = "\000";
    char entradaChar2[30] = "\000";
    char entradaChar3[30] = "\000";


    if (AH){

        switch (numero){

        case 0: // Paises de LDC


            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            ldcp = LisPaises->getNodo(entradaInt1);

            if (ldcp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            LisPaises->BorrarPosicion(ldcp);
            cout << "\nEliminacion exitosa en LDC paises"<<endl;
            break;//fin del proceso




        case 1: // Hoteles


            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            if (hotel == ultimoHotel ){
                ultimoHotel = NULL;
            }

            // ubicacion_de_borrado
            abbp->Hoteles->borrarNodo(hotel);
            cout << "\nEliminacion exitosa"<<endl;
            break;//fin del proceso
            

        case 2: // pisos


            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del piso: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            piso = hotel->piso->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (piso == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            if (piso == ultimoPiso){
                ultimoPiso = NULL;
            }
            

            cout << "\nEliminacion exitosa"<<endl;
            //ubicacion_de_borrado
            hotel->piso->borrarNodo(piso);
            
            break;//fin del proceso
            

        case 3: // habitaciones

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del piso: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            piso = hotel->piso->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (piso == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la habitacion: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (!verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            habitacion = piso->habitacion->getNodo(entradaInt3); // verficamos que el codigo exista en la base de datos

            if (habitacion == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            if (habitacion == ultimaHabitacion){
                ultimaHabitacion = NULL;
            }
            

            cout << "\nEliminacion exitosa"<<endl;
            //ubicacion_de_borrado
            piso->habitacion->borrarNodo(habitacion);
            break;//fin del proceso


        default:
            break;
        }

    } else {

        switch (numero){

        case 1: // Agencias

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            if (agencia == ultimaAgencia){
                ultimaAgencia = NULL;
            }
            

            cout << "\nEliminacion exitosa"<<endl;
            //ubicacion_de_borrado
            abbp->Agencias->borrarNodo(agencia);
            break;//fin del proceso
            

        case 2: // flotillas

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            flotilla = agencia->flotilla->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (flotilla == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            if (flotilla == ultimaFlotilla){
                ultimaFlotilla = NULL;
            }
            

            cout << "\nEliminacion exitosa"<<endl;
            //ubicacion_de_borrado
            agencia->flotilla->borrarNodo(flotilla);
            break;//fin del proceso
            

        case 3: // carros

            cout <<"\nDigite un codigo(numerico) para el Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1);

            if (abbp == NULL){
                cout << "\n\nPais no existe" << endl;
                break;
            }


            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            flotilla = agencia->flotilla->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (flotilla == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del carro: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (!verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            carro = flotilla->carro->getNodo(entradaInt3); // verficamos que el codigo exista en la base de datos

            if (carro == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout << "\nEliminacion exitosa"<<endl;
            //ubicacion_de_borrado
            flotilla->carro->borrarNodo(carro);
            
            break;//fin del proceso
            

        default:
            break;
        }
    }
    return;
}

void imprimir_Nodo(bool AH, int numero, pnodohotel& ultimoHotel, pnodopisohotel& ultimoPiso, pnodohabitacion& ultimaHabitacion, pnodoAgencia& ultimaAgencia, pnodotipoflotilla& ultimaFlotilla, pnodocarro& ultimoCarro){//imprime el nodo

    

    pnodoabbpais abbp;
    pnodoldcpais ldcp;
    pnodohotel hotel;
    pnodopisohotel piso;
    pnodohabitacion habitacion;
    pnodoAgencia agencia;
    pnodotipoflotilla flotilla;
    pnodocarro carro;

    ArbolAA_Carros tempCarro;
    ArbolAVL_Flotilla tempFlotilla;
    ArbolABB_Agencias tempAgencias;
    ArbolRN_Habitaciones tempHabitaciones;
    ArbolAVL_Pisos tempPisos;
    ArbolABB_Hoteles tempHoteles;


    int entradaInt1 = -4;
    int entradaInt2 = -4;
    int entradaInt3 = -4;
    char entradaChar1[30] = "\000";
    char entradaChar2[30] = "\000";
    char entradaChar3[30] = "\000";
    int cestrellas;
    int asientos;
    int chabitaciones;
    int cantidadc;


    if (AH){
        
        switch (numero){

        case 1:
            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            abbp->Hoteles->Mostrar();
            break;

        case 2:

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            hotel->piso->Mostrar();
            break;

        case 3: // habitaciones

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del piso: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            piso = hotel->piso->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (piso == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            piso->habitacion->Mostrar();
            break;
        
        case 4: // cantidad estrellas

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            abbp->Hoteles->getCantidadEstrellas(cestrellas, hotel);
            abbp->Hoteles->MostrarNodo(hotel);
            cout << "\nNumero de estrellas (hotel): "<< cestrellas << endl;
            break;

        case 5: // cantidad habitaciones de un piso

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del hotel: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            hotel = abbp->Hoteles->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (hotel == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del piso: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            piso = hotel->piso->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (piso == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            hotel->piso->getCantidadHabitaciones(chabitaciones,piso);
            hotel->piso->MostrarNodo(piso);
            cout << "\nNumero de habitaciones (piso) : "<< chabitaciones << endl;
            break;
    
        case 6: // consultar ultimo nodo hotel
            tempHoteles.MostrarNodo(ultimoHotel);            
            break;

        case 7: // consultar ultimo nodo piso
            
            tempPisos.MostrarNodo(ultimoPiso);
            break;

            break;

        case 8: // consultar ultimo nodo habitacion

            tempHabitaciones.MostrarNodo(ultimaHabitacion);
            break;


        case 9: // consultar reservaciones

            Reservac->MostrarHotel();
            break;
            
        default:
            break;
        }
    
    } else {

        switch (numero){

        case 1://consultar agencias

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            abbp->Agencias->Mostrar();
            break;

        case 2://consultar flotillas

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            agencia->flotilla->Mostrar();
            break;

        case 3: // consultar cantidad carros

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            abbp->Agencias->getCantidadVehiculos(cantidadc,agencia);
            abbp->Agencias->MostrarNodo(agencia);
            cout << "\nCantidad de carros (Agencia): " << cantidadc << endl;

            break;

        case 4: // consultar asientos carros

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            flotilla = agencia->flotilla->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (flotilla == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del carro: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (!verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            carro = flotilla->carro->getNodo(entradaInt3); // verficamos que el codigo exista en la base de datos

            if (carro == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            flotilla->carro->getNumeroAsientos(asientos,carro);
            flotilla->carro->MostrarNodo(carro);
            cout << "\nNumero de asientos del carro: " << asientos <<endl;
            break;

        case 5: // consultar un carro

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                PosCarro = NULL;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                PosCarro = NULL;
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                PosCarro = NULL;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                PosCarro = NULL;
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                PosCarro = NULL;
                break;
            }

            flotilla = agencia->flotilla->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (flotilla == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                PosCarro = NULL;
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) del carro: ";
            cin >> entradaChar3;
            entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

            if (!verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                PosCarro = NULL;
                break;
            }

            carro = flotilla->carro->getNodo(entradaInt3); // verficamos que el codigo exista en la base de datos

            if (carro == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                PosCarro = NULL;
                break;//fin del proceso

            }
            
            PosCarro = carro;

            break;

        case 6://consultar ultimo nodo agencia
            tempAgencias.MostrarNodo(ultimaAgencia);
            break;

        case 7://consultar ultimo nodo flotilla
            tempFlotilla.MostrarNodo(ultimaFlotilla);
            break;

        case 8://consultar ultimo nodo carros
            tempCarro.MostrarNodo(ultimoCarro);
            break;

        case 9: // consultar carros

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (abbp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la agencia: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            agencia = abbp->Agencias->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos

            if (agencia == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            cout <<"\nDigite el codigo(numerico) de la flotilla: ";
            cin >> entradaChar2;
            entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

            if (!verificarEntrada(entradaChar2,entradaInt2)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            flotilla = agencia->flotilla->getNodo(entradaInt2); // verficamos que el codigo exista en la base de datos

            if (flotilla == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }


            flotilla->carro->Mostrar();
            break;
        
        case 10://consultar reservaciones
            
            Reservac->MostrarAgencia();
            break;


        default:
            break;
        }
    }
}

pnodohotel ultimoHotel = NULL;
pnodopisohotel ultimoPiso = NULL;
pnodohabitacion ultimaHabitacion = NULL;
pnodoAgencia ultimaAgencia = NULL;
pnodotipoflotilla ultimaFlotilla = NULL;
pnodocarro ultimoCarro = NULL;

void principal(){
    int control = 1;
    int nodoubicacion;
    int entradaInt;
    string pasaporte = "";
    char entradaS[30] = "\000";
    bool AH = true;
    
    int sosten1;
    int sosten2;
    int sosten3;
    char buffer[50] = "\000";
    PosCarro = NULL;

    pnodopersona AdminAs;
    pnodopersona AdminHs;
    pnodopersona Usio;

    ArbolAA_Carros tempCarro;
    Reservac = new LDCReservaciones();


    leer_todo_los_archivos(ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro); //se leen los archivos

    char nombre [30] = "nuevo pais";

    Conexiones.leerPaises();
    Conexiones.leerArchivoConexiones();
}

string insertarPais(int codigo, string nombre){
    if(LisPaises->getNodo(codigo)==NULL){
        char nombreChar[50];
        strcpy_s(nombreChar, (nombre).c_str());
        ArbPaises->insertarNodo(codigo,nombreChar);
        LisPaises->InsertarFinal(codigo,nombreChar);
        return"1|País insertado exitosamente";
    }
    return "0|Ya existe un país con este código";
}

string modificarPais(int codigo, string nombre){
    if(LisPaises->getNodo(codigo)!=NULL){
        char nombreChar[50];
        strcpy_s(nombreChar, (nombre).c_str());
        pnodoabbpais nodo;
        ArbPaises->getNodo(nodo,codigo);
        ArbPaises->setNombre(nombreChar,nodo);
        pnodoldcpais nodoLista = LisPaises->getNodo(codigo);
        LisPaises->setNombre(nombreChar,nodoLista);
        return "1|Nombre de País modificado exitosamente";
    }
    return "0|No existe un país con el código ingresado";
}

string eliminarPais(int codigo){
    if(LisPaises->getNodo(codigo)!=NULL){
        pnodoabbpais nodo;
        ArbPaises->getNodo(nodo,codigo);
        ArbPaises->borrarNodo(nodo);
        pnodoldcpais nodoLista = LisPaises->getNodo(codigo);
        LisPaises->BorrarPosicion(nodoLista);
        return "1|País eliminado exitosamente";
    }
    return "0|No existe un país con el código ingresado";
}

string obtenerPaises(){
    return ArbPaises->Mostrar();
}

string getNombreAdminHotel(int codigo){
    string nombre = AdminHotel->getNombre(codigo);
    if(nombre=="NULL"){
        return "0|No existe un administrador de hotel con el codigo ingresado";
    }
    return "1|Bienvenido "+string(nombre);
}

string insertarHotel(int codigoPais,int codigoHotel, string nombre, int cantEst){
    if(LisPaises->getNodo(codigoPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)==NULL){
        char nombreChar[50];
        strcpy_s(nombreChar, (nombre).c_str());
        ArbPaises->getNodo(codigoPais)->Hoteles->insertarNodo(codigoHotel,nombreChar,cantEst);
        ultimoHotel = ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel);
        return "1|Hotel insertado exitosamente";
    }else{
        return "0|Ya existe un hotel con el codigo ingresado";
    }
}

string insertarPiso(int codigoPais,int codigoHotel, int numPiso, string nombre, int cantHabs){
    if(LisPaises->getNodo(codigoPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->getNodo(numPiso)==NULL){
        char nombreChar[50];
        strcpy_s(nombreChar, (nombre).c_str());
        ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->insertarNodo(numPiso,nombreChar,cantHabs);
        ultimoPiso = ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->getNodo(numPiso);
        return "1|Piso insertado existosamente";
    }
    return "0|Ya existe un piso con el numero insertado";
}

string insertarHabitacion(int codigoPais,int codigoHotel,int numPiso, int codHab, string tipoCuarto, int numeroCamas, int precioHab, string estadoHab){
    if(LisPaises->getNodo(codigoPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    if(ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)==NULL){
        char tipoCuartoChar[50];
        strcpy_s(tipoCuartoChar, (tipoCuarto).c_str());
        ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->getNodo(numPiso)->habitacion->insertarNodo(codHab,tipoCuartoChar,numeroCamas,precioHab,estadoHab[0]);
        ultimaHabitacion = ArbPaises->getNodo(codigoPais)->Hoteles->getNodo(codigoHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab);
        return "1|Habitación insertada exitosamente";
    }
    return "0|Ya existe una habitacion con el codigo insertado";
}

string eliminarHotel(int codPais, int codHotel){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    ArbPaises->getNodo(codPais)->Hoteles->borrarNodo(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel));
    return "1|Hotel eliminado exitosamente";
}

string eliminarPiso(int codPais, int codHotel, int numPiso){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->borrarNodo(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso));
    return "1|Piso eliminado exitosamente";
}

string eliminarHabitacion(int codPais, int codHotel, int numPiso, int codHab){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)==NULL){
        return "0|No existe una habitación con el codigo insertado";
    }
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->borrarNodo(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab));
    return "1|Habitación eliminada exitosamente";
}

string getDatosHotel(int codPais, int codHotel){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->getInfoHotel();
}

string modificarHotel(int codPais, int codHotel, string nombre, int cantEstrellas){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    pnodohotel hotel = ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel);
    char nombreChar[50];
    strcpy_s(nombreChar, (nombre).c_str());
    ArbPaises->getNodo(codPais)->Hoteles->setNombre(nombreChar,hotel);
    ArbPaises->getNodo(codPais)->Hoteles->setCantidadestrellas(cantEstrellas,hotel);
    return "1|Hotel modificado exitosamente";
}

string getDatosPiso(int codPais, int codHotel, int numPiso){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->getInfoPiso();
}

string modificarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    pnodopisohotel piso = ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso);
    char nombreChar[50];
    strcpy_s(nombreChar, (nombre).c_str());
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->setNombre(nombreChar,piso);
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->setCantidadHabitaciones(cantHabs,piso);
    return "1|Piso modificado exitosamente";
}

string getDatosHabitacion(int codPais, int codHotel, int numPiso, int codHab){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)->getInfoHabitacion();
}

string modificarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precio, string estado){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)==NULL){
        return "0|No existe una habitación con el codigo insertado";
    }
    pnodohabitacion hab = ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab);
    char tipoCuartoChar[50];
    strcpy_s(tipoCuartoChar, (tipoCuarto).c_str());
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->setTipoCuarto(tipoCuartoChar,hab);
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->setNumeroCamas(numCamas,hab);
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->setPrecioHabitacion(precio,hab);
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->setEstadoHab(estado[0],hab);
    return "1|Habitación modificada exitosamente";
}

string getHoteles(int codPais){
    if(LisPaises->getNodo(codPais)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Hoteles->Mostrar();
}

string getPisos(int codPais, int codHotel){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->Mostrar();
}

string getHabitaciones(int codPais, int codHotel, int numPiso){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL || ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->Mostrar();
}

string getEstrellasHotel(int codPais, int codHotel){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    int estrellas;
    ArbPaises->getNodo(codPais)->Hoteles->getCantidadEstrellas(estrellas,ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel));
    return "1|El hotel específicado cuenta con "+to_string(estrellas)+" estrellas";
}

string getCantHabsPiso(int codPais, int codHotel, int numPiso){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    int habs;
    ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getCantidadHabitaciones(habs,ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso));
    return "1|La cantidad de habitaciones del piso especificado es de "+to_string(habs);
}

string getUltimoHotel(){
    if(ultimoHotel==NULL){
        return "";
    }
    return ultimoHotel->getInfoHotel();
}

string getUltimoPiso(){
    if(ultimoPiso==NULL){
        return "";
    }
    return ultimoPiso->getInfoPiso();
}

string getUltimaHabitacion(){
    if(ultimaHabitacion==NULL){
        return "";
    }
    return ultimaHabitacion->getInfoHabitacion();
}

string insertarAgencia(int codPais, int idAgencia, string nombre, int cantVehs){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        char nombreChar[50];
        strcpy_s(nombreChar, (nombre).c_str());
        ArbPaises->getNodo(codPais)->Agencias->insertarNodo(idAgencia,nombreChar,cantVehs);
        ultimaAgencia = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia);
        return "1|Agencia insertada exitosamente";
    }else{
        return "0|La identificacion de agencia ya existe";
    }
}

string insertarTipoFlotilla(int codPais,int idAgencia, int codFlotilla, string nombre, int cantCarros){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        char nombreChar[50];
        strcpy_s(nombreChar, (nombre).c_str());
        ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->insertarNodo(codFlotilla,nombreChar,cantCarros);
        ultimaFlotilla = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla);
        return "1|Tipo de Flotilla insertada exitosamente";
    }else{
        return "0|El codigo de tipo de flotilla ya existe";
    }
}

string insertarCarro(int codPais, int idAgencia, int codFlotilla, int placa, string modelo, int numAsientos, int anno, int precio, string estado){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa)==NULL){
        char modeloChar[50];
        strcpy_s(modeloChar, (modelo).c_str());
        ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->insertarNodo(placa,modeloChar,numAsientos,anno,precio,estado[0]);
        ultimoCarro = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa);
        return "1|Carro insertado exitosamente";
    }
    return "0|Ya existe un carro con la placa insertada";
}

string eliminarAgencia(int codPais,int idAgencia){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    ArbPaises->getNodo(codPais)->Agencias->borrarNodo(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia));
    return "1|Agencia eliminada exitosamente";
}

string eliminarTipoFlotilla(int codPais, int idAgencia, int codFlotilla){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->borrarNodo(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla));
    return "1|Tipo de flotilla eliminada exitosamente";
}

string eliminarCarro(int codPais, int idAgencia, int codFlotilla, int placa){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa)==NULL){
        return "0|No existe un carro con el codigo insertado";
    }
    ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->borrarNodo(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa));
    return "1|Carro eliminado exitosamente";
}

string getDatosAgencia(int codPais, int idAgencia){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->mostrar();
}

string modificarAgencia(int codPais, int idAgencia, string nombre, int cantVehs){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    pnodoabbpais pais = ArbPaises->getNodo(codPais);
    pnodoAgencia agencia  = pais->Agencias->getNodo(idAgencia);
    char nombreChar[50];
    strcpy_s(nombreChar, (nombre).c_str());
    pais->Agencias->setNombre(nombreChar,agencia);
    pais->Agencias->setCantidadVehiculos(cantVehs,agencia);
    return "1|Agencia modificada exitosamente";
}

string getDatosTipoFlotilla(int codPais,int idAgencia, int codTipoFlotilla){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL || ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)->mostrar();
}

string modificarTipoFlotilla(int codPais,int idAgencia, int codTipoFlotilla, string nombre, int cantCarros){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    pnodoAgencia agencia = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia);
    pnodotipoflotilla flotilla  = agencia->flotilla->getNodo(codTipoFlotilla);
    char nombreChar[50];
    strcpy_s(nombreChar, (nombre).c_str());
    agencia->flotilla->setNombre(nombreChar,flotilla);
    agencia->flotilla->setCantidaddCarrosTipo(cantCarros,flotilla);
    return "1|Tipo de Flotilla modificada exitosamente";
}

string getDatosCarro(int codPais, int idAgencia, int codTipoFlotilla, int placa){
    if(LisPaises->getNodo(codPais)==NULL || ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL || ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)==NULL || ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)->carro->getNodo(placa)==NULL){
        return "";
    }
    return ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)->carro->getNodo(placa)->mostrar();
}

string modificarCarro(int codPais, int idAgencia, int codFlotilla, int placa, string modelo, int numAsientos, int anno, int precio, string estado){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa)==NULL){
        return "0|No existe un carro con el codigo insertado";
    }
    pnodotipoflotilla flotilla = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla);
    pnodocarro carro = flotilla->carro->getNodo(placa);
    char modeloChar[50];
    strcpy_s(modeloChar, (modelo).c_str());
    flotilla->carro->setModelo(modeloChar,carro);
    flotilla->carro->setNumeroAsientos(numAsientos,carro);
    flotilla->carro->setAno(anno,carro);
    flotilla->carro->setPrecioCarro(precio,carro);
    flotilla->carro->setEstadodelCarro(estado[0],carro);
    return "1|Carro modificado exitosamente";
}

string getNombreAdminAgencia(int codigo){
    string nombre = string(AdminAgencia->getNombre(codigo));
    if(nombre=="NULL"){
        return "0|No existe un administrador de agencia con el codigo ingresado";
    }
    return "1|Bienvenido "+nombre;
}

string getAgencias(int codPais){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    return ArbPaises->getNodo(codPais)->Agencias->Mostrar();
}

string getTiposFlotilla(int codPais, int idAgencia){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    return ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->Mostrar();
}

string getCarros(int codPais, int idAgencia, int codFlotilla){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    return ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->Mostrar();
}

string getCarrosAgencia(int codPais, int idAgencia){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    int vehs;
    ArbPaises->getNodo(codPais)->Agencias->getCantidadVehiculos(vehs,ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia));
    return "1|La agencia posee "+to_string(vehs)+" carros";
}

string getAsientosCarro(int codPais,int idAgencia, int codTipoFlotilla, int placa){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)->carro->getNodo(placa)==NULL){
        return "0|No existe un carro con el codigo insertado";
    }
    int asientos;
    ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)->carro->getNumeroAsientos(asientos,ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codTipoFlotilla)->carro->getNodo(placa));
    return "1|El carro tiene "+to_string(asientos)+" asientos";
}

string getUltimaAgencia(){
    if(ultimaAgencia==NULL){
        return "";
    }
    return ultimaAgencia->mostrar();
}

string getUltimoTipoFlotilla(){
    if(ultimaFlotilla==NULL){
        return "";
    }
    return ultimaFlotilla->mostrar();
}

string getUltimoCarro(){
    if(ultimoCarro==NULL){
        return "";
    }
    return ultimoCarro->mostrar();
}

string getNombreUsuario(int pasaporte){
    string nombre = string(Usuarios->getNombre(pasaporte));
    if(nombre=="NULL"){
        return "0|No existe un usuario con el pasaporte ingresado";
    }
    return "1|Bienvenido "+nombre;
}

string getReservacionesHotel(){
    return Reservac->MostrarHotel();
}

string getReservacionesAgencia(){
    return Reservac->MostrarAgencia();
}

string reservarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string pasaporte){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)==NULL){
        return "0|No existe una habitación con el codigo insertado";
    }
    ArbolRN_Habitaciones* habitaciones = ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion;
    pnodohabitacion habitacion = habitaciones->getNodo(codHab);
    char estado;
    if(habitaciones->getEstadoHab(estado,habitacion)=='R'){
        return "0|La habitacion ya esta reservada";
    }
    if(habitaciones->getEstadoHab(estado,habitacion)=='O'){
        return "0|La habitacion ya esta ocupada";
    }
    habitaciones->setEstadoHab('R',habitacion);
    Reservac->InsertarInicio(codPais,codHotel,numPiso,codHab,habitacion, pasaporte);
    return "1|Habitación reservada exitosamente";
}

string reservarCarro(int codPais, int idAgencia, int codFlotilla, int placa, string pasaporte){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa)==NULL){
        return "0|No existe un carro con el codigo insertado";
    }
    ArbolAA_Carros* carros = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro;
    pnodocarro carro = carros->getNodo(placa);
    char estado;
    carros->getEstadodelCarro(estado,carro);
    if(estado=='R'){
        return "0|La habitacion ya esta reservada";
    }
    carros->getEstadodelCarro(estado,carro);
    if(estado=='O'){
        return "0|La habitacion ya esta ocupada";
    }
    carros->setEstadodelCarro('R',carro);
    Reservac->InsertarInicio(codPais,idAgencia,codFlotilla,placa,carro,pasaporte);
    return "1|Carro reservado exitosamente";
}

string reservarTodoIncluido(int codPais, int codHotel, int numPiso, int codHab, int idAgencia, int codFlotilla, int placa, string pasaporte){
    string habit, carro;
    habit = reservarHabitacion(codPais,codHotel,numPiso,codHab, pasaporte);
    carro = reservarCarro(codPais,idAgencia,codFlotilla,placa, pasaporte);
    if(habit[0]=='0'){
        return habit;
    }
    if(carro[0]=='0'){
        return carro;
    }
    return "1|Reservación todo incluido realizada con éxito";
}

string cancelarReservacionHabitacion(int codPais, int codHotel, int numPiso, int codHab){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)==NULL){
        return "0|No existe un hotel con el codigo ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)==NULL){
        return "0|No existe un piso con el numero insertado";
    }
    if(ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion->getNodo(codHab)==NULL){
        return "0|No existe una habitación con el codigo insertado";
    }
    ArbolRN_Habitaciones* habitaciones = ArbPaises->getNodo(codPais)->Hoteles->getNodo(codHotel)->piso->getNodo(numPiso)->habitacion;
    pnodohabitacion habitacion = habitaciones->getNodo(codHab);
    char estado;
    habitaciones->getEstadoHab(estado,habitacion);
    if(estado=='L'){
        return "0|La habitación no está reservada";
    }
    Reservac->BorrarPosicion(habitacion);
    habitaciones->setEstadoHab('L',habitacion);
    return "1|Reservación de habitación cancelada exitosamente";
}

string cancelarReservacionCarro(int codPais, int idAgencia, int codFlotilla, int placa){
    if(LisPaises->getNodo(codPais)==NULL){
        return "0|No existe un país con el código ingresado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)==NULL){
        return "0|No existe una agencia con la identificacion ingresada";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)==NULL){
        return "0|No existe la codigo de flotilla insertado";
    }
    if(ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro->getNodo(placa)==NULL){
        return "0|No existe un carro con el codigo insertado";
    }
    ArbolAA_Carros* carros = ArbPaises->getNodo(codPais)->Agencias->getNodo(idAgencia)->flotilla->getNodo(codFlotilla)->carro;
    pnodocarro carro = carros->getNodo(placa);
    char estado;
    carros->getEstadodelCarro(estado,carro);
    if(estado=='L'){
        return "0|El carro no está reservado";
    }
    Reservac->BorrarPosicion(carro);
    carros->setEstadodelCarro('L',carro);
    return "1|Reservación de carro cancelada exitosamente";
}

string cancelarReservacionTodoIncluido(int codPais, int codHotel, int numPiso, int codHab, int idAgencia, int codFlotilla, int placa){
    string habit, carro;
    habit = cancelarReservacionHabitacion(codPais,codHotel,numPiso,codHab);
    carro = cancelarReservacionCarro(codPais,idAgencia,codFlotilla,placa);
    if(habit[0]=='0'){
        return habit;
    }
    if(carro[0]=='0'){
        return carro;
    }
    return "1|Reservación todo incluido cancelada con éxito";
}

string cancelarReservacion(string codigo){
    if(!Reservac->existeCodigoR(codigo)){
        return "0|No existe el codigo de reservacion ingresado";
    }
    Reservac->cancelarReservacion(codigo);
    return "1|Reservacion cancelada exitosamente";
}

string facturarReservacion(string codigo){
    return Reservac->generarFactura(codigo);
}

string eliminarUsuario(int pasaporte){
    Usuarios->borrarNodo(Usuarios->getNodo(pasaporte));
    return "1|Usuario eliminado exitosamente";
}

string pagarReservacion(string codigoReservacion){
    return Reservac->pagarReservacion(codigoReservacion);
}

string reportePosiblesPaises(int codPais){
    return "Anchura|" + Conexiones.Anchura(codPais) + "Profundidad|" + Conexiones.Profundidad(codPais);
}

#endif PRINCIPAL_H