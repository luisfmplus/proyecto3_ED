
/*falta :   actualizar la funcion modificarNodo()
            cambiar los menus para permitir reservaciones
            generar todos las opciones de generar reservacion
            crear menu de mantenimiento paises
            generar la logica del menu mantenimiento


*/
// palabra para encontrar todas las pocisiones con necesidad de implementacion de funciones: aaabbbcccddd
// palabra para encontrar todas las pocisiones con propiedades alteradas : alteracion_del_menu
//palabra para encontrar todas las pocisiones con funciones no implementadas de borrados: ubicacion_de_borrado


#include <iostream>
#include <string> 
#include "LectorCola.cpp"
#include "8LDCPaises.cpp"
#include "9ABBPaises.cpp"
#include "10LDCReservaciones.cpp"
#include "ArbolesBinarios.h"


using namespace std;


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
                //Reservac->InsertarInicio(pais,temp1, temp2, temp3, (c->carro->getultimoNodoInsertado()));
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
        cout << "9. Pagar una reservacion"<<endl;
        cout << "10. Cancelar Reservacion "<<endl;
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

void cambiosReservacion(LDCReservaciones* reserva, string pasaporte){
    reserva->reservasPendientes(pasaporte);
    string opcionReserva;
    cout<<endl;
	cout<<"Digite el codigo de la reserva a pagar: "<<endl;
    cin>>opcionReserva;
    //verificar si existe ese codigo de reserva
    if(reserva->existeCodigoR(opcionReserva)==false){
        cout<<"No existe esa reservacion"<<endl;
        return;
    }
    reserva->generarFactura(opcionReserva);
    cout<<"Archivo de Reserva Realizado"<<endl;
    return;
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

void modificar_Nodo(bool AH, int numero){

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


    int contador = 0;
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

        case 0: // Paises

            cout <<"\nDigite el codigo(numerico) del Pais: ";
            cin >> entradaChar1;
            entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

            if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                cout << "\n\nentrada no valida" << endl;
                break;
            }

            abbp = ArbPaises->getNodo(entradaInt1); // verficamos que el codigo exista en la base de datos
            ldcp = LisPaises->getNodo(entradaInt1);

            if (ldcp == NULL){ //se encontro la ubicacion del nodo(not)?
                cout << "\nEl codigo digitado no existe\n";
                break;//fin del proceso

            }

            while (1){ //se empieza el sub-menu de modificacion
                
                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar2, sizeof(entradaChar2));
                    continue;
                }
                
                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Nombre\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar2;
                entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
                entradaInt2 = verificarEntrada(entradaChar2);
            
                switch (entradaInt2){

                case 1:

                    cout<<"\nNuevo nombre: >>";
                    cin >> entradaChar4;
                    entradaChar4[(sizeof(entradaChar4)-1)] = '\000';
                    
                    if ((LisPaises->setNombre(entradaChar4,ldcp) == 1) && (ArbPaises->setNombre(entradaChar4,abbp) == 1)){
                        
                        cout << "\nModificacion exitosa\n";
                        limpiarbuffer(entradaChar2, sizeof(entradaChar2));
                        break; //finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;
                
                default:
                    break;
                }

                if (entradaInt2 == 0){
                    contador = 0;
                    break;
                }
                contador++;                
            }

            break;


        case 1: // Hoteles

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

            while (1){ //se empieza el sub-menu de modificacion
                
                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar2, sizeof(entradaChar2));
                    continue;
                }
                
                
                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Numero de estrellas\n";
                cout << "2. Nombre\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar2;
                entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
                entradaInt2 = verificarEntrada(entradaChar2);

                switch (entradaInt2){

                case 1:
                    cout<<"\nNuevo cantidad de estrellas: >>";
                    cin >> entradaChar3;
                    entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

                    if (!verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;

                    }
                    
                    if (tempHoteles.setCantidadestrellas(entradaInt3,hotel) == 1){
                        cout << "\nModificacion exitosa\n";
                        break; //finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual

                case 2:
                    cout<<"\nNuevo nombre: >>";
                    cin >> entradaChar4;
                    entradaChar4[(sizeof(entradaChar4)-1)] = '\000';
                    
                    if (tempHoteles.setNombre(entradaChar4,hotel) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual
                
                default:
                    break;
                }

                if (entradaInt2 == 0){
                    contador = 0;
                    break;//finaliza el menu modificacion
                }
                contador++;
            }
            
            break;//fin del proceso

        case 2: // Piso

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

            cout <<"\nDigite el codigo(numerico) del Hotel: ";
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

            cout <<"\nDigite el codigo(numerico) del Piso: ";
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

            while (1){ //se empieza el sub-menu de modificacion
                
                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar3, sizeof(entradaChar3));
                    continue;
                }
                
                
                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Cantidad de habitaciones\n";
                cout << "2. Nombre\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar3;
                entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
                entradaInt3 = verificarEntrada(entradaChar3);

                switch (entradaInt3){

                case 1:
                    cout<<"\nNuevo cantidad de habitaciones: >>";
                    cin >> entradaChar4;
                    entradaChar4[(sizeof(entradaChar4)-1)] = '\000';

                    if (!verificarEntrada(entradaChar4,entradaInt4)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;

                    }
                    if (tempPisos.setCantidadHabitaciones(entradaInt4,piso) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }
                    
                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual

                case 2:
                    cout<<"\nNuevo nombre: >>";
                    cin >> entradaChar5;
                    entradaChar5[(sizeof(entradaChar5)-1)] = '\000';
                    
                    if (tempPisos.setNombre(entradaChar5,piso) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual
                    
                
                default:
                    break;
                }

                if (entradaInt3 == 0){
                    contador = 0;
                    break;//finaliza el menu modificacion
                }
                contador++;
            }
            
            break;//fin del proceso

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

            cout <<"\nDigite el codigo(numerico) del Hotel: ";
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

            cout <<"\nDigite el codigo(numerico) del Piso: ";
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

            cout <<"\nDigite el codigo(numerico) de la Habitacion: ";
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
            limpiarbuffer(entradaChar1,sizeof(entradaChar1));
            limpiarbuffer(entradaChar2,sizeof(entradaChar2));
            limpiarbuffer(entradaChar3,sizeof(entradaChar3));

            while (1){ //se empieza el sub-menu de modificacion

                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar4, sizeof(entradaChar4));
                    continue;
                }

                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Tipo de cuarto\n";
                cout << "2. Numero de camas\n";
                cout << "3. Precio\n";
                cout << "4. Estado del cuarto\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar4;
                entradaChar4[(sizeof(entradaChar4)-1)] = '\000';
                entradaInt4 = verificarEntrada(entradaChar4);

                switch (entradaInt4){

                case 1:
                    cout<<"\nNuevo tipo de cuarto: >>";
                    cin >> entradaChar5;
                    entradaChar5[(sizeof(entradaChar5)-1)] = '\000';

                    if (tempHabitaciones.setTipoCuarto(entradaChar5, habitacion) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }
                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual

                case 2:
                    cout<<"\nNuevo numero de camas: >>";
                    cin >> entradaChar1;
                    entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

                    if (!verificarEntrada(entradaChar1,entradaInt5)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;
                    }
                    
                    if (tempHabitaciones.setNumeroCamas(entradaInt5, habitacion) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;
                    }
                    
                    cout << "\nModificacion fallida\n";
                    break;

                case 3:
                    cout<<"\nNuevo precio: >>";
                    cin >> entradaChar2;
                    entradaChar2[(sizeof(entradaChar2)-1)] = '\000';

                    if (!verificarEntrada(entradaChar2,entradaInt1)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;
                    }

                    if (tempHabitaciones.setPrecioHabitacion(entradaInt1, habitacion) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;
                    } 

                    cout << "\nModificacion fallida\n";
                    break;
                
                case 4:
                    cout<<"\nNuevo estado del cuarto: >>";
                    cin >> entradaChar3;
                    entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
                    
                    if (tempHabitaciones.setEstadoHab(entradaChar3[0], habitacion) == 1){
                        
                        if (piso->habitacion->getEstadoHab(entradaChar3[0], habitacion) == 'R' ){

                            //buscamos los codigos
                            abbp->Hoteles->getCodHotel(entradaInt1,hotel);
                            hotel->piso->getNumPiso(entradaInt2,piso);
                            piso->habitacion->getCodHabitacion(entradaInt3,habitacion);
                            ArbPaises->getCodPais(entradaInt4,abbp);
                            //Reservac->InsertarInicio(entradaInt4,entradaInt1, entradaInt2, entradaInt3,habitacion, pasaporte);
                            cout << "\nModificacion exitosa\n";
                            break;
                        }
                        
                        Reservac->BorrarPosicion(habitacion);
                        cout << "\nModificacion exitosa\n";
                        break;
                    }

                    cout << "\nModificacion fallida\n";
                    break;

                default:
                    break;
                }

                if (entradaInt4 == 0){
                    contador = 0;
                    break;
                }
                contador++;
            }
            
            break;//fin del proceso

        default:
            break;
        } //fin del switch

    } else {

        switch (numero){

        case 1: // agencias

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

            cout <<"\nDigite el codigo(numerico) de la Agencia: ";
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

            while (1){ //se empieza el sub-menu de modificacion
                
                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar2, sizeof(entradaChar2));
                    continue;
                }
                
                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Numero de carros\n";
                cout << "2. Nombre\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar2;
                entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
                entradaInt2 = verificarEntrada(entradaChar2);

                switch (entradaInt2){

                case 1:
                    cout<<"\nNuevo numero de carros: >>";
                    cin >> entradaChar3;
                    entradaChar3[(sizeof(entradaChar3)-1)] = '\000';

                    if (!verificarEntrada(entradaChar3,entradaInt3)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;

                    }
                    
                    if (tempAgencias.setCantidadVehiculos(entradaInt3,agencia) == 1){
                        cout << "\nModificacion exitosa\n";
                        break; //finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual

                case 2:
                    cout<<"\nNuevo nombre: >>";
                    cin >> entradaChar4;
                    entradaChar4[(sizeof(entradaChar4)-1)] = '\000';
                    
                    if (tempAgencias.setNombre(entradaChar4,agencia) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual
                
                default:
                    break;
                }

                if (entradaInt2 == 0){
                    contador = 0;
                    break;//finaliza el menu modificacion
                }
                contador++;
            }
            
            break;//fin del proceso

        case 2: // flotilla

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

            cout <<"\nDigite el codigo(numerico) de la Agencia: ";
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

            cout <<"\nDigite el codigo(numerico) de la Flotilla: ";
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

            while (1){ //se empieza el sub-menu de modificacion
                
                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar3, sizeof(entradaChar3));
                    continue;
                }

                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Cantidad de carro de tipo\n";
                cout << "2. Nombre\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar3;
                entradaChar3[(sizeof(entradaChar3)-1)] = '\000';
                entradaInt3 = verificarEntrada(entradaChar3);

                switch (entradaInt3){

                case 1:
                    cout<<"\nNueva cantidad de carros de tipo: >>";
                    cin >> entradaChar4;
                    entradaChar4[(sizeof(entradaChar4)-1)] = '\000';

                    if (!verificarEntrada(entradaChar4,entradaInt4)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;

                    }
                    if (tempFlotilla.setCantidaddCarrosTipo(entradaInt4,flotilla) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }
                    
                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual

                case 2:
                    cout<<"\nNuevo nombre: >>";
                    cin >> entradaChar5;
                    entradaChar5[(sizeof(entradaChar5)-1)] = '\000';
                    
                    if (tempFlotilla.setNombre(entradaChar5,flotilla) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }

                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual
                    
                
                default:
                    break;
                }

                if (entradaInt3 == 0){
                    contador = 0;
                    break;//finaliza el menu modificacion
                }
                contador++;
            }
            
            break;//fin del proceso

        case 3: // carros

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

            cout <<"\nDigite el codigo(numerico) de la Agencia: ";
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

            cout <<"\nDigite el codigo(numerico) de la Flotilla: ";
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

            cout <<"\nDigite el codigo(numerico) de la Carro: ";
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
            limpiarbuffer(entradaChar1,sizeof(entradaChar1));
            limpiarbuffer(entradaChar2,sizeof(entradaChar2));
            limpiarbuffer(entradaChar3,sizeof(entradaChar3));

            while (1){ //se empieza el sub-menu de modificacion

                if (contador == 1){
                    contador--;
                    limpiarbuffer(entradaChar4, sizeof(entradaChar4));
                    continue;
                }

                cout << "\n\nMenu modificar\n";
                cout << "0. Retornar\n";
                cout << "1. Numero de asientos\n";
                cout << "2. Precio y Estado del carro\n";
                cout << "\ndigite el numero de la opcion: ";
                cin >> entradaChar4;
                entradaChar4[(sizeof(entradaChar4)-1)] = '\000';
                entradaInt4 = verificarEntrada(entradaChar4);

                switch (entradaInt4){

                case 1:
                cout<<"\nNuevo numero de asientos: >>";
                    cin >> entradaChar5;
                    entradaChar5[(sizeof(entradaChar5)-1)] = '\000';

                    if (!verificarEntrada(entradaChar5,entradaInt5)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;
                    }

                    if (tempCarro.setNumeroAsientos(entradaInt5, carro) == 1){
                        cout << "\nModificacion exitosa\n";
                        break;//finaliza la modificacion individual
                    }
                    cout << "\nModificacion fallida\n";
                    break;//finaliza la modificacion individual

                case 2:
                    cout<<"\nNuevo precio: >>";
                    cin >> entradaChar1;
                    entradaChar1[(sizeof(entradaChar1)-1)] = '\000';

                    if (!verificarEntrada(entradaChar1,entradaInt1)){ //es el codigo digitado valido(not)?
                        cout << "\n\nentrada no valida" << endl;
                        break;
                    }

                    cout<<"\nNuevo estado del carro: >>";
                    cin >> entradaChar2;
                    entradaChar2[(sizeof(entradaChar2)-1)] = '\000';
                    
                    if ((tempCarro.setPrecioCarro(entradaInt2, carro) == 1) && (tempCarro.setEstadodelCarro(entradaChar2[0], carro) == 1)){
                                                
                                                
                        if (piso->habitacion->getEstadoHab(entradaChar3[0], habitacion) == 'R' ){

                            //buscamos los codigos
                            abbp->Agencias->getIdentidadAg(entradaInt1,agencia);
                            agencia->flotilla->getCodTipo(entradaInt2,flotilla);
                            flotilla->carro->getPlaca(entradaInt3,carro);
                            ArbPaises->getCodPais(entradaInt4,abbp);
                            //Reservac->InsertarInicio(entradaInt4,entradaInt1, entradaInt2, entradaInt3,habitacion);
                            cout << "\nModificacion exitosa\n";
                            break;
                        }
                        //borra la reservacion si se modifica la reservacion
                        Reservac->BorrarPosicion(carro);
                        cout << "\nModificacion exitosa\n";
                        break;
                    }
                    
                    cout << "\nModificacion fallida\n";
                    break;

                default:
                    break;
                }

                if (entradaInt4 == 0){
                    contador = 0;
                    break;
                }
                contador++;
            }
            
            break;//fin del proceso

        default:
            break;
        }
    }
    return;
}

int main(){

    //actualizaciones de la ubicacion de los nodos cuando swe insertan.

    int control = 1;
    int nodoubicacion;
    int entradaInt;
    string pasaporte="";
    char entradaS[30] = "\000";
    bool AH = true;
    
    int sosten1;
    int sosten2;
    int sosten3;
    char buffer[50] = "\000";
    PosCarro = NULL;
    pnodohotel ultimoHotel = NULL;
    pnodopisohotel ultimoPiso = NULL;
    pnodohabitacion ultimaHabitacion = NULL;
    pnodoAgencia ultimaAgencia = NULL;
    pnodotipoflotilla ultimaFlotilla = NULL;
    pnodocarro ultimoCarro = NULL;

    pnodopersona AdminAs;
    pnodopersona AdminHs;
    pnodopersona Usio;

    ArbolAA_Carros tempCarro;
    Reservac = new LDCReservaciones();


    leer_todo_los_archivos(ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro); //se leen los archivos


    while (control != 0){ //control de todo el sistema
        
        switch (control){

        case 1: // menu principal
            imprimirMenus(1,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);
            
            switch (entradaInt)
            {
            case 0:

                control = 0; //salir
                break;

            case 1:
                control = 2; // menu validacion AdminA
                break;

            case 2:
                control = 3;// menu validacion AdminH
                break;

            case 3:
                control = 10;// menu validacion Usuario
                break;

            case 4:
                control = 12;// menu mantenimiento (falta implementar)
                break;

            default:
            control = 1; //menu principal
                break;
            } // segundo switch
            
            break;

        case 2: // menu validacion AdminA
            cout <<"\nDigite su codigo de acceso: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            
            if (verificarEntrada(entradaS,entradaInt)){ //el codigo digitado es valido
                //verficamos que el codigo exista en la base de datos
                pnodopersona AdminAs = AdminAgencia->getNodo(entradaInt);

                if (AdminAs != NULL){ //se encontro la ubicacion del nodo
                    control = 4; //movemos control a menu comandos
                    AH = false;
                    break;

                }
                
                cout<<"\n\nCodigo no encontrado"<<endl;
                cout<<"Desea 1. reintentar o 2. salir: >>";
                cin >> entradaS;
                entradaS[(sizeof(entradaS)-1)] = '\000';
                while(1){
                    if (verificarEntrada(entradaS) == 1){
                        //se repite menu validacion AdminA
                        break;

                    } else if (verificarEntrada(entradaS) == 2){
                        //salimos a menu principal
                        control = 1;
                        break;

                    }
                    cin >> entradaS;
                    entradaS[(sizeof(entradaS)-1)] = '\000';
                }
        
            } else { //informa que el codigo no es valido

                cout << "\n\nCodigo no valido" << endl;
            }
            
            break;

        case 3: // menu validacion AdminH
            cout <<"\nDigite su codigo de acceso: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            
            if (verificarEntrada(entradaS,entradaInt)){ //el codigo digitado es valido
                //verficamos que el codigo exista en la base de datos
                AdminHs = AdminHotel->getNodo(entradaInt); //abcdefg

                if (AdminHs != NULL){ //se encontro la ubicacion del nodo
                    control = 4; //movemos control a menu comandos
                    AH = true;
                    break;

                }
                
                cout<<"\n\nCodigo no encontrado"<<endl;
                cout<<"Desea 1. reintentar o 2. salir: >>";
                cin >> entradaS;
                entradaS[(sizeof(entradaS)-1)] = '\000';
                while(1){
                    if (verificarEntrada(entradaS) == 1){
                        //se repite menu validacion AdminA
                        break;

                    } else if (verificarEntrada(entradaS) == 2){
                        //salimos a menu principal
                        control = 1;
                        break;

                    }
                    cin >> entradaS;
                    entradaS[(sizeof(entradaS)-1)] = '\000';
                }
        
            } else { //informa que el codigo no es valido

                cout << "\n\nCodigo no valido" << endl;
            }
            
            break;

        case 4: // menu comandos
            imprimirMenus(2,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

            switch (entradaInt){
                
            case 0:
                control = 1; // menu principal
                break;

            case 1:
                control = 5; // menu inserciones
                break;

            case 2:
                //alteracion_del_menu
                // previa a alteracion: "control = 6;" (llegamos al break)
                control = control;// menu eliminaciones
                cout<<"\nMenu no disponible\n";
                break;

            case 3:
                control = 7;// menu modificaciones
                break;

            case 4:
                control = 8;// generar reporte
                break;
            
            default:
                break;

            } //segundo switch
            break;

        case 5: // menu inserciones
            imprimirMenus(3,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

            switch (entradaInt){

            case 0:
                control = 4; //menu comando
                break;

            case 1:
                insertar_Nodo(AH, 1, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro,pasaporte); //hoteles/agencias
                break;

            case 2:
                insertar_Nodo(AH, 2, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro,pasaporte); //piso/flotilla
                break;

            case 3:
                insertar_Nodo(AH, 3, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro,pasaporte); //habitaciones/carros
                break;
                
            default:
                break;
            } //segundo switch

            break;//


        case 6: // menu Eliminaciones
            imprimirMenus(4,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

                
            switch (entradaInt){
                
            case 0:
                control = 4; //menu comandos
                break;

            case 1:
                eliminar_Nodo(AH, 1, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro); //hoteles/agencias
                break;

            case 2:
                eliminar_Nodo(AH, 2, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro); //piso/flotilla
                break;

            case 3:
                eliminar_Nodo(AH, 3, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro); //habitaciones/carros
                break;
                
            default:
                break;
            } //segundo switch

            break;

        case 7: // menu modificaciones
            imprimirMenus(5,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

                
            switch (entradaInt){

            case 0:
                control = 4;
                break;

            case 1:
                modificar_Nodo(AH, 1); //hoteles/agencias
                break;

            case 2:
                modificar_Nodo(AH, 2); //piso/flotilla
                break;

            case 3:
                modificar_Nodo(AH, 3); //habitaciones/carros
                break;
                
            default:
                break;
            
            } //segundo switch
            break;
        
        case 8: // Generar reporte
            if (AH){
                imprimirMenus(6,AH);
            
            } else {

                imprimirMenus(7,AH);
            }
            
            
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

            if (AH){
                
                switch (entradaInt){

                case 0:
                    control = 4;// menu comandos
                    break;

                case 1:
                    imprimir_Nodo(AH,1, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar hoteles
                    break;

                case 2:
                    imprimir_Nodo(AH,2, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar piso
                    break;

                case 3:
                    imprimir_Nodo(AH,3, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar habitaciones
                    break;

                case 4:
                    imprimir_Nodo(AH,4, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar estrellas
                    break;

                case 5:
                    imprimir_Nodo(AH,5, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar cantidad habitaciones
                    break;

                case 6:
                    imprimir_Nodo(AH,6, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultimo hotel
                    break;

                case 7:
                    imprimir_Nodo(AH,7, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultimo piso
                    break;

                case 8:
                    imprimir_Nodo(AH,8, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultima habitacion
                    break;

                case 9:
                    imprimir_Nodo(AH,9, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultima habitacion
                    break;

            
                default:
                    break;
                } //segundo switch

            } else {

                switch (entradaInt){

                case 0:
                    control = 4;
                    break;

                case 1:
                    imprimir_Nodo(AH,1, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar agencia
                    break;

                case 2:
                    imprimir_Nodo(AH,2, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar flotilla
                    break;

                case 3:
                    imprimir_Nodo(AH,3, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar un carro
                    
                    break;

                case 4:
                    imprimir_Nodo(AH,4, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar cantidad de asientos
                    break;

                case 5:
                    imprimir_Nodo(AH,5, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar propiedades carro
                    if (PosCarro != NULL){
                        control = 9;
                    }
                    break;

                case 6:
                    imprimir_Nodo(AH,6, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultima agencia
                    break;

                case 7:
                    imprimir_Nodo(AH,7, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultima flotilla
                    break;

                case 8:
                    imprimir_Nodo(AH,8, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar ultimo carro
                    break;

                case 9:
                    imprimir_Nodo(AH,9, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);//consultar carros
                    break;

                case 10:
                    imprimir_Nodo(AH,10, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);//consultar carros
                    break;
            
                default:
                    break;
                } //segundo switch
            
            } //else
            break;


        case 9: // Propiedades Carro 
            imprimirMenus(8,AH);
            //ArbolAA_Carros tempCarro;
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

            switch (entradaInt){

            case 0:
                control = 8;// generar reporte
                break;

            case 1:
                limpiarbuffer(buffer,sizeof(buffer));
                tempCarro.getModelo(buffer,PosCarro);
                cout << "\nModelo: " << buffer <<endl;
                break;

            case 2:
                tempCarro.getAno(sosten1,PosCarro);
                cout << "\nAnno: " << sosten1 <<endl;
                break;

            case 3:
                tempCarro.getNumeroAsientos(sosten1,PosCarro);
                cout << "\nNumero de asientos: " << sosten1 <<endl;
                break;

            case 4:
                tempCarro.getPrecioCarro(sosten1,PosCarro);
                cout << "\nPrecio: " << sosten1 <<endl;
                break;

            case 5:
                limpiarbuffer(buffer,sizeof(buffer));
                tempCarro.getEstadodelCarro(buffer[0],PosCarro);
                cout << "\nEstado del carro: " << buffer[0] <<endl;
                break;
            
            default:
                break;

            } //segundo switch

            break;

        case 10: // menu validacion Usuario
            cout <<"\nDigite su pasaporte de acceso: ";
            cin >> entradaS;
            pasaporte=entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            
            if (verificarEntrada(entradaS,entradaInt)){ //el codigo digitado es valido
                //verficamos que el codigo exista en la base de datos
                Usio = Usuarios->getNodo(entradaInt);

                if (Usio != NULL){ //se encontro la ubicacion del nodo
                    control = 11; //movemos control a menu comandos Usuario
                    break;

                }
                
                cout<<"\n\npasaporte no registrado"<<endl;
                cout<<"Desea 1. reintentar o 2. salir: >>";
                cin >> entradaS;
                entradaS[(sizeof(entradaS)-1)] = '\000';
                while(1){
                    if (verificarEntrada(entradaS) == 1){
                        //se repite menu validacion Usuario
                        break;

                    } else if (verificarEntrada(entradaS) == 2){
                        //salimos a menu principal
                        control = 1;
                        break;

                    }
                    cin >> entradaS;
                    entradaS[(sizeof(entradaS)-1)] = '\000';
                
                } //while
        
            } else { //informa que el codigo no es valido
                cout << "\n\nPasaporte no valido" << endl;
            }  // else
            
            break;

        case 11: // menu comandos Usuario
            imprimirMenus(9,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

                
            switch (entradaInt){

            case 0:
                control = 1;
                break;

            case 1:
                imprimir_Nodo(true,1, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar hoteles
                break;

            case 2:
                imprimir_Nodo(true,2, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar pisos de un hotel
                break;

            case 3:
                imprimir_Nodo(true,3, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar habitaciones de un piso de un hotel
                break;
                
            case 4:
                imprimir_Nodo(false,1, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar agencia
                break;

            case 5:
                imprimir_Nodo(false,2, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar flotilla de una agencia
                break;

            case 6:
                imprimir_Nodo(false,9, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);// consultar carro de una flotilla de una agencia
                break;

            case 7:
                LisPaises->Mostrar();// consultar paises 
                break;

            case 8:
                control = 13;// hacer una reservacion
                break;
            
            case 9:
                cambiosReservacion(Reservac, pasaporte);
                break;
            case 10:
                cancelarReservacion(Reservac, pasaporte);
                break;
            default:
                break;

            } //segundo switch
            break;

        case 12: // menu mantenimiento
            imprimirMenus(10,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

            switch (entradaInt)
            {
            case 0:
                control = 1;
                break;

            case 1:
                insertar_Nodo(true,0, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro, pasaporte);
                break;

            case 2:
                eliminar_Nodo(true,0, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro);
                break;

            case 3:
                modificar_Nodo(true,0);
                break;

            case 4:
                LisPaises->Mostrar();
                break;
            
            default:
                break;
            }

            break;

        case 13: // menu reservaciones
            imprimirMenus(11,AH);
            cout << "\ndigite el numero de la opcion: ";
            cin >> entradaS;
            entradaS[(sizeof(entradaS)-1)] = '\000';
            entradaInt = verificarEntrada(entradaS);

            switch (entradaInt)
            {
            case 0: //retornamos a menu principal
                control = 1;
                break;
            
            case 1: //reservar hotel
                
                insertar_Nodo(true,4, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro,pasaporte);

                break;

            case 2: //reservar agencias

                insertar_Nodo(true,5, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro,pasaporte);
                break;

            case 3: //todo incluido

                insertar_Nodo(true,6, ultimoHotel, ultimoPiso, ultimaHabitacion, ultimaAgencia, ultimaFlotilla, ultimoCarro,pasaporte);
                break;
            default:
                break;
            }

            break;



        default: // menu comandos Usuario
            break;
        } // primer switch 
    
    } //while




    return 0;
} // main



