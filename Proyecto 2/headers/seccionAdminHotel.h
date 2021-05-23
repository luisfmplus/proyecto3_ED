#ifndef SECCIONADMINHOTEL_H
#define SECCIONADMINHOTEL_H

#include "paises.h"

adminsHotelA arbolAdminsHotel;

//Se saca la información de los hoteles, pisos y habitaciones desde los archivos y se guardan en los árboles .
void obtenerHoteles(){
    listaSimple datosHoteles = leerArchivo("Hoteles") , datosHotel;
    int codPais, codHotel , cantEstrellas;
    string nombre;
    for(int i=1;i<=datosHoteles.largoLista();i++){
        datosHotel = dividirString(datosHoteles.obtenerValorPos(i),";");
        codPais = StrToNum(datosHotel.obtenerValorPos(1));
        codHotel = StrToNum(datosHotel.obtenerValorPos(2));
        nombre = datosHotel.obtenerValorPos(3);
        cantEstrellas = StrToNum(datosHotel.obtenerValorPos(4));
        arbolPaises.insertarHotel(codPais,codHotel,nombre,cantEstrellas);
    }
    listaSimple datosPisos = leerArchivo("PisosHotel") , datosPiso;
    int numPiso, cantHabitaciones;
    for(int i=1;i<=datosPisos.largoLista();i++){
        datosPiso = dividirString(datosPisos.obtenerValorPos(i),";");
        codPais = StrToNum(datosPiso.obtenerValorPos(1));
        codHotel = StrToNum(datosPiso.obtenerValorPos(2));
        numPiso = StrToNum(datosPiso.obtenerValorPos(3));
        nombre = datosPiso.obtenerValorPos(4);
        cantHabitaciones = StrToNum(datosPiso.obtenerValorPos(5));
        arbolPaises.insertarPiso(codPais,codHotel,numPiso,nombre,cantHabitaciones);
    }
    listaSimple datosHabitaciones = leerArchivo("Habitaciones") , datosHabitacion;
    int codHabitacion, numeroCamas, precioHabitacion;
    string tipoCuarto,estadoHab;
    for(int i=1;i<=datosHabitaciones.largoLista();i++){
        datosHabitacion = dividirString(datosHabitaciones.obtenerValorPos(i),";");
        codPais = StrToNum(datosHabitacion.obtenerValorPos(1));
        codHotel = StrToNum(datosHabitacion.obtenerValorPos(2));
        numPiso = StrToNum(datosHabitacion.obtenerValorPos(3));
        codHabitacion = StrToNum(datosHabitacion.obtenerValorPos(4));
        tipoCuarto = datosHabitacion.obtenerValorPos(5);
        numeroCamas = StrToNum(datosHabitacion.obtenerValorPos(6));
        precioHabitacion = StrToNum(datosHabitacion.obtenerValorPos(7));
        estadoHab = datosHabitacion.obtenerValorPos(8);
        arbolPaises.insertarHabitacion(codPais,codHotel,numPiso,codHabitacion,tipoCuarto,numeroCamas,precioHabitacion,estadoHab);
    }
}

//Se saca la información de los administradores de hotel dentro de los archivos, se segmenta en datos y se van guardando dentro de la lista de administradores de hotel
void obtenerAdministradoresHotel(){
    listaSimple datosAdminsHotel = leerArchivo("AdministradorH") , datosAdminHotel;
    adminsHotelA adminsHotel;
    int codigo;
    string nombre;
    for(int i=1;i<=datosAdminsHotel.largoLista();i++){
        datosAdminHotel = dividirString(datosAdminsHotel.obtenerValorPos(i),";");
        codigo = StrToNum(datosAdminHotel.obtenerValorPos(1));
        nombre = datosAdminHotel.obtenerValorPos(2);
        adminsHotel.insertarAdminHotel(codigo,nombre);
    }
    arbolAdminsHotel = adminsHotel;
}

//Se valida si el estado de la habitación que se ingresó es L, R u O
bool validarEstadoHabitacion(string estadoHab){
    bool valido = true;
    if(estadoHab!="L" && estadoHab!="R" && estadoHab!="O"){
        rojo(); cout << "!!!!! El estado de habitacion ingresado no es valido; tiene que ser L, R u O !!!!!" << endl; azul();
        valido = false;
    }
    return valido;
}

//Se valida si el codigo de hotel ingresado no es vacío, es un número y si existe un hotel con ese código, si no cumple con alguna condición devuelve un valor booleano falso
bool validarCodigoHotel(string codPais, string codigo){
    bool valido = validarCodigoPais(codPais) && validarNoVacios(codigo,"codigo de hotel") && validarNumeros(codigo,"codigo de hotel");
    if(valido){
        photelNA tempHotel = arbolPaises.obtenerHotelCodigo(StrToNum(codPais),StrToNum(codigo));
        if(tempHotel==NULL){
            valido = false;
            rojo(); cout << "!!!!! El codigo de hotel ingresado no es valido, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//Se valida si existe un hotel con el codigo ingresado, que el numero de piso no es un string vacio, que sea un numero y si existe un piso con un codigo y numero ingresado, si no cumple alguna de las condiciones devuelve un valor booleano falso
bool validarNumPiso(string codPais,string codigo,string numPiso){
    bool valido = validarCodigoHotel(codPais,codigo) && validarNoVacios(numPiso,"numero de piso") && validarNumeros(numPiso,"numero de piso");
    if(valido){
        ppisoNA tempPiso = arbolPaises.obtenerPisoNum(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso));
        if(tempPiso==NULL){
            valido = false;
            rojo(); cout << "!!!!! El numero de piso no es valido, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//Valida que exista un piso con el codigo de hotel y numero de piso ingresado, que el codigo de habitacion no esté vacío, que sea un número y que exista una habitacion con ese código, si no se cumple una de las condiciones devuelve un falso
bool validarCodHab(string codPais, string codigo, string numPiso, string codHab){
    bool valido = validarNumPiso(codPais,codigo,numPiso) && validarNoVacios(codHab,"codigo de habitacion") && validarNumeros(codHab,"codigo de habitacion");
    if(valido){
        phabitacionNA tempHab = arbolPaises.obtenerHabitacionCod(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab));
        if(tempHab==NULL){
            valido = false;
            rojo(); cout << "!!!!! El numero de habitacion no es valido, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//valida si los datos del hotel son validos, que no se repita el codigo de hotel, que no estén vacíos, que los valores numéricos efectivamente sean número
bool validarHotel(string codPais, string codigo, string nombre, string estrellas){
    bool valido = validarNoVacios(codigo+"|"+nombre+"|"+estrellas,"codigo|nombre|estrellas") && validarNumeros(codigo+"|"+estrellas,"codigo|estrellas (1-5)") && validarCodigoPais(codPais);
    if(StrToNum(estrellas)<1 || StrToNum(estrellas)>5){
        valido = false;
        rojo(); cout << "!!!!! Por favor ingrese el numero de estrellas entre 1 y 5 !!!!!" << endl; azul();
    }
    if(valido && arbolPaises.obtenerHotelCodigo(StrToNum(codPais),StrToNum(codigo))!=NULL){
        valido = false;
        rojo(); cout << "!!!!! El codigo de hotel no es valido, ya existe !!!!!" << endl; azul();
    }
    return valido;
}

//Valida que los datos del piso ingresado sean válidos
bool validarPiso(string codPais, string codigo , string numPiso , string nombre , string cantHabs){
    bool valido = validarCodigoHotel(codPais, codigo) && validarNoVacios(numPiso+"|"+nombre+"|"+cantHabs,"numero de piso|nombre|cantidad de habitaciones") && validarNumeros(numPiso+"|"+cantHabs,"piso|cantidad de habitaciones");
    if(valido){
        if(arbolPaises.obtenerPisoNum(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso))!=NULL){
            valido = false;
            rojo(); cout << "!!!!! El numero de piso no es valido, porque ya existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//Valida que todos los datos de la habitacion que se quiere ingresar sean válidos
bool validarHabitacion(string codPais, string codigo, string numPiso,string codHab,string tipoCuarto,string numCamas, string precioHab , string estadoHab){
    bool valido = validarNumPiso(codPais,codigo,numPiso) && validarNoVacios(numPiso+"|"+codHab+"|"+tipoCuarto+"|"+numCamas+"|"+precioHab+"|"+estadoHab,"numero de piso|codigo de habitacion|tipo de cuarto|numero de camas|precio de habitacion|estado de habitacion|") && validarNumeros(numPiso+"|"+codHab+"|"+numCamas+"|"+precioHab,"numero de piso|codigo de habitacion|numero de camas|precio de habitacion") && validarEstadoHabitacion(estadoHab);
    if(valido && arbolPaises.obtenerHabitacionCod(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab))!=NULL){
        rojo(); cout << "!!!!! El codigo de habitacion no es valido, porque ya existe !!!!!" << endl; azul();
        valido = false;
    }
    return valido;
}

//Solicita los datos del nuevo hotel que se quiera ingresar, se pide la confirmación del usuario (Si para, lo demás para No), se validan los datos ingresados, y se inserta el nuevo hotel en la lista de hoteles
void insertarHotel(bool first){
    string conf , codPais, codigo , nombre , estrellas;
    if(first) getline(cin,codigo);
    celeste(); cout << "Ha escogido insertar hotel" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    cout<<"Ingrese el nombre del hotel: "; amarillo(); getline(cin,nombre); azul();
    cout << "Ingrese la cantidad de estrellas del hotel (1 - 5): "; amarillo(); getline(cin,estrellas); azul();
    celeste(); cout << "Seguro de querer ingresar el hotel? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarHotel(codPais,codigo,nombre,estrellas)){
            arbolPaises.insertarHotel(StrToNum(codPais),StrToNum(codigo),nombre,StrToNum(estrellas));
            verde(); cout << endl << "Hotel registrado" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            insertarHotel(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar el hotel" << endl << endl; azul();
    }
}

//Se solicitan los datos del piso que se quiera ingresar, se validan y se inserta el nuevo piso en el hotel correspondiente al codigo de hotel seleccionado
void insertarPiso(bool first){
    string conf , codPais, codigo , numPiso , nombre , cantHabs;
    if(first) getline(cin,codigo);
    celeste(); cout << "Ha escogido insertar piso" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    cout << "Ingrese el nombre: "; amarillo(); getline(cin,nombre); azul();
    cout << "Ingrese la cantidad de habitaciones: "; amarillo(); getline(cin,cantHabs); azul(); 
    celeste(); cout << "Seguro de querer ingresar la habitacion? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarPiso(codPais, codigo,numPiso,nombre,cantHabs)){
            arbolPaises.insertarPiso(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),nombre,StrToNum(cantHabs));
            verde(); cout << endl << "Piso de hotel registrado" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl;
            insertarPiso(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar el piso" << endl << endl; azul();
    }
}

//Se solicitan los datos para la habitacion que se desee ingresar y se validan los datos
void insertarHabitacion(bool first){
    string conf , codPais, codigo , numPiso, codHab , tipoCuarto , numCamas , precioHab , estadoHab;
    if(first) getline(cin,conf);
    celeste(); cout << "Ha escogido insertar habitacion" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo de hotel: "; amarillo(); getline(cin,codigo); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    cout << "Ingrese el codigo de habitacion: "; amarillo(); getline(cin,codHab); azul();
    cout << "Ingrese el tipo de cuarto: "; amarillo(); getline(cin,tipoCuarto); azul();
    cout << "Ingrese el numero de camas: "; amarillo(); getline(cin,numCamas); azul();
    cout << "Ingrese el precio de la habitacion: "; amarillo(); getline(cin,precioHab); azul();
    cout << "Ingrese el estado de la habitacion (L,R,O): "; amarillo(); getline(cin,estadoHab); azul();
    celeste(); cout << "Seguro de querer ingresar la habitacion? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarHabitacion(codPais,codigo,numPiso,codHab,tipoCuarto,numCamas,precioHab,estadoHab)){
            arbolPaises.insertarHabitacion(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab),tipoCuarto,StrToNum(numCamas),StrToNum(precioHab),estadoHab);
            verde();cout << endl << "Habitacion de hotel registrada" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            insertarHabitacion(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar la habitacion" << endl << endl; azul();
    }
}

//muestra al administrador de hotel las opciones disponibles de inserción y se le solicita que escoja una
void opcionesInsercionAdminH(){
    string opcion;
    while(true){
        cout << "Opciones de insercion:" <<endl <<endl << "1 - Insertar Hotel" << endl << "2 - Insertar Piso" << endl << "3 - Insertar Habitacion" << endl << "4 - Salir" << endl << endl;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>4){
            rojo(); cout << "Lo escrito no concuerda con ninguna de las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                insertarHotel(true);
            }
            if(num==2){
                insertarPiso(true);
            }
            if(num==3){
                insertarHabitacion(true);
            }
            if(num==4){
                break;
            }
        }
    }
}

//se solicita el nuevo nombre para modificarlo, mostrando el anterior al usuario
void modificarNombreHotel(int codPais, int codigo, bool first){
    string nuevoNombre;
    if(first) getline(cin,nuevoNombre);
    cout << endl << "Por favor ingrese un nuevo nombre para el hotel: "; amarillo(); getline(cin,nuevoNombre); azul();
    if(validarNoVacios(nuevoNombre,"nuevo nombre de hotel")){
        arbolPaises.modificarDatoHotel(codPais,codigo,nuevoNombre,1);
        verde(); cout << endl << "Nombre de hotel modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarNombreHotel(codPais,codigo,false);
    }
}

//Se ingresa el nuevo numro de estrellas para modificarlas, habiendo mostrado las anteriores al usuario
void modificarCantEstrellasHotel(int codPais,int codigo,bool first){
    string nuevoCantEst;
    if(first) getline(cin,nuevoCantEst);
    cout << endl << "Por favor ingrese la nueva cantidad de estrellas para el hotel: "; amarillo(); getline(cin,nuevoCantEst); azul();
    if(validarNoVacios(nuevoCantEst,"nueva cantidad de estrellas") && validarNoVacios(nuevoCantEst,"nueva cantidad de estrellas")){
        arbolPaises.modificarDatoHotel(codPais,codigo,nuevoCantEst,2);
        verde(); cout << endl << "Cantidad de estrellas de hotel modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarCantEstrellasHotel(codPais,codigo,false);
    }
}

//Se solicita el código de hotel y si es válido se muestran las opciones de modificación de hotel
void modificarHotel(bool first){
    string codPais, codigo;
    if(first) getline(cin,codigo);
    celeste(); cout << endl << "Ha escogido modificar hotel" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    if(validarCodigoHotel(codPais,codigo)){
        string opcion;
        listaSimple datosHotel = arbolPaises.obtenerDatosHotel(StrToNum(codPais),StrToNum(codigo));
        while(true){
            cout << endl << "1 - Desea modificar el nombre: " << datosHotel.obtenerValorPos(3) << " ?" << endl << "2 - Desea modificar la cantidad de estrellas: " << datosHotel.obtenerValorPos(4) << " ?" << endl << "3 - Salir" << endl << endl;
            cout << "Escriba el numero de la opcion que desea modificar: "; amarillo(); cin >> opcion; azul();
            int numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>3){
                rojo(); cout << "La opcion escogida no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion==1){
                    modificarNombreHotel(StrToNum(codPais),StrToNum(codigo),true);
                    break;
                }
                if(numOpcion==2){
                    modificarCantEstrellasHotel(StrToNum(codPais),StrToNum(codigo),true);
                    break;
                }
                if(numOpcion==3){
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarHotel(false);
    }
}

//Se solicita el nombre de piso para modificarlo
void modificarNombrePiso(int codPais, int codigo, int numPiso, bool first){
    string nuevoNombre;
    if(first) getline(cin,nuevoNombre);
    cout << endl << "Por favor ingrese un nuevo nombre para el piso: "; amarillo(); getline(cin,nuevoNombre); azul();
    if(validarNoVacios(nuevoNombre,"nuevo nombre de piso")){
        arbolPaises.modificarDatoPiso(codPais,codigo,numPiso,nuevoNombre,1);
        verde(); cout << endl << "Nombre de piso modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarNombrePiso(codPais,codigo,numPiso,false);
    }
}

//Solicita la cantidad de habitaciones del piso para modificarlo
void modificarCantHabsPiso(int codPais, int codigo, int numPiso, bool first){
    string nuevoCantHabs;
    if(first) getline(cin,nuevoCantHabs);
    cout << endl << "Por favor ingrese una nueva cantidad de habitaciones para el piso: "; amarillo(); getline(cin,nuevoCantHabs); azul();
    if(validarNoVacios(nuevoCantHabs,"nueva cantidad de habitaciones") && validarNumeros(nuevoCantHabs,"nueva cantidad de habitaciones")){
        arbolPaises.modificarDatoPiso(codPais,codigo,numPiso,nuevoCantHabs,2);
        verde(); cout << endl << "Cantidad de habitaciones de piso modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarCantHabsPiso(codPais, codigo,numPiso,false);
    }
}

//Solicita el código de hotel y el número de piso para conocer cuál piso tiene que modificar, lo valida y muestra las opciones de modificación
void modificarPiso(bool first){
    string codPais, codigo , numPiso;
    if(first) getline(cin,codigo);
    celeste(); cout << endl << "Ha escogido modificar piso" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    if(validarNumPiso(codPais,codigo,numPiso)){
        string opcion;
        listaSimple datosPiso = arbolPaises.obtenerDatosPiso(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso));
        while(true){
            cout << endl << "1 - Desea modificar el nombre: " << datosPiso.obtenerValorPos(4) << " ?" << endl << "2 - Desea modificar la cantidad de habitaciones: " << datosPiso.obtenerValorPos(5) << " ?" << endl << "3 - Salir" << endl << endl;
            cout << "Escriba el numero de la opcion que desea modificar: "; amarillo(); cin >> opcion; azul();
            int numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>3){
                rojo(); cout << "La opcion escogida no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion==1){
                    modificarNombrePiso(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),true);
                    break;
                }
                if(numOpcion==2){
                    modificarCantHabsPiso(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),true);
                    break;
                }
                if(numOpcion==3){
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarPiso(false);
    }
}

//Se solicita el nuevo tipo de cuarto, se valida y se modifica
void modificarTipoCuartoHabitacion(int codPais, int codigo,int numPiso,int codHab,bool first){
    string nuevoTipoCuarto;
    if(first) getline(cin,nuevoTipoCuarto);
    cout << endl << "Por favor ingrese el nuevo tipo de cuarto para la habitacion: "; amarillo(); getline(cin,nuevoTipoCuarto); azul();
    if(validarNoVacios(nuevoTipoCuarto,"nuevo tipo de cuarto")){
        arbolPaises.modificarDatoHabitacion(codPais,codigo,numPiso,codHab,nuevoTipoCuarto,1);
        verde(); cout << endl << "Tipo de cuarto de habitacion modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarTipoCuartoHabitacion(codPais,codigo,numPiso,codHab,false);
    }
}

//Se solicita el nuevo numero de camas, para validarlo y modificarlo a la habitación
void modificarNumeroCamasHabitacion(int codPais,int codigo,int numPiso,int codHab,bool first){
    string nuevoNumeroCamas;
    if(first) getline(cin,nuevoNumeroCamas);
    cout << endl << "Por favor ingrese el nuevo numero de camas para la habitacion: "; amarillo(); getline(cin,nuevoNumeroCamas); azul();
    if(validarNoVacios(nuevoNumeroCamas,"nuevo numero de camas") && validarNumeros(nuevoNumeroCamas,"nuevo numero de camas")){
        arbolPaises.modificarDatoHabitacion(codPais,codigo,numPiso,codHab,nuevoNumeroCamas,2);
        verde(); cout << endl << "Numero de camas de habitacion modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarNumeroCamasHabitacion(codPais,codigo,numPiso,codHab,false);
    }
}

//Se solicita el nuevo precio para la habitación y validarlo y modificarlo
void modificarPrecioHabitacion(int codPais,int codigo,int numPiso,int codHab,bool first){
    string nuevoPrecio;
    if(first) getline(cin,nuevoPrecio);
    cout << endl << "Por favor ingrese el nuevo precio de habitacion: "; amarillo(); getline(cin,nuevoPrecio); azul();
    if(validarNoVacios(nuevoPrecio,"nuevo precio") && validarNumeros(nuevoPrecio,"nuevo precio")){
        arbolPaises.modificarDatoHabitacion(codPais,codigo,numPiso,codHab,nuevoPrecio,3);
        verde(); cout << endl << "Precio de habitacion modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarPrecioHabitacion(codPais,codigo,numPiso,codHab,false);
    } 
}

//Se solicita el nuevo estado de habitación para validarlo y modificarlo
void modificarEstadoHabitacion(int codPais,int codigo,int numPiso,int codHab,bool first){
    string nuevoEstado;
    if(first) getline(cin,nuevoEstado);
    cout << endl << "Por favor ingrese el nuevo estado de la habitacion (L, R u O): "; amarillo(); getline(cin,nuevoEstado); azul();
    if(validarNoVacios(nuevoEstado,"nuevo estado") && validarEstadoHabitacion(nuevoEstado)){
        arbolPaises.modificarDatoHabitacion(codPais,codigo,numPiso,codHab,nuevoEstado,4);
        verde(); cout << endl << "Estado de habitacion modificado" << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarEstadoHabitacion(codPais,codigo,numPiso,codHab,false);
    } 
}

//Se solicita al usuario el código del hotel, el número del piso y el código de la habitación para verificar la existencia de la habitación y proceder a mostrar las opciones de modificación al usuario
void modificarHabitacion(bool first){
    string codPais , codigo , numPiso , codHab;
    if(first) getline(cin,codigo);
    celeste(); cout << endl << "Ha escogido modificar habitacion" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    cout << "Ingrese el codigo de habitacion: "; amarillo(); getline(cin,codHab); azul();
    if(validarCodHab(codPais,codigo,numPiso,codHab)){
        string opcion;
        listaSimple datosHabitacion = arbolPaises.obtenerDatosHabitacion(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab));
        while(true){
            cout << endl << "1 - Desea modificar el tipo de cuarto: " << datosHabitacion.obtenerValorPos(5) << " ?" << endl << "2 - Desea modificar el numero de camas: " << datosHabitacion.obtenerValorPos(6) << " ?" << endl << "3 - Desea modificar el precio: " << datosHabitacion.obtenerValorPos(7) << "?" << endl << "4 - Desea modificar el estado de habitacion: " << datosHabitacion.obtenerValorPos(8) << " ?" << endl << "5 - Salir" << endl << endl;
            cout << "Escriba el numero de la opcion que desea modificar: "; amarillo(); cin >> opcion; azul();
            int numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>5){
                rojo(); cout << "La opcion escogida no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion==1){
                    modificarTipoCuartoHabitacion(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab),true);
                    break;
                }
                if(numOpcion==2){
                    modificarNumeroCamasHabitacion(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab),true);
                    break;
                }
                if(numOpcion==3){
                    modificarPrecioHabitacion(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab),true);
                    break;
                }
                if(numOpcion==4){
                    modificarEstadoHabitacion(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso),StrToNum(codHab),true);
                    break;
                }
                if(numOpcion==5){
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; gris();
        modificarHabitacion(false);
    }
}

//muestra las opciones de modificación que se le brindarán al administrador de hotel y se le solicita que escoja una
void opcionesModificacionAdminH(){
    string opcion;
    while(true){
        cout << endl << "Opciones de modificacion" << endl << endl << "1 - Modificar Hotel" << endl << "2 - Modificar Piso" << endl << "3 - Modificar Habitacion" << endl << "4 - Salir" << endl << endl;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>4){
            rojo(); cout << "Lo escrito no concuerda con ninguna de las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                modificarHotel(true);
            }
            if(num==2){
                modificarPiso(true);
            }
            if(num==3){
                modificarHabitacion(true);
            }
            if(num==4){
                break;
            }
        }
    }
}

//Se solicita el codigo de pais, se valida y se muestran los hoteles
void muestraDetalladaHoteles(bool first){
    string codPais;
    if(first) getline(cin,codPais);
    azul(); cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    if(validarCodigoPais(codPais)){
        arbolPaises.muestraDetalladaHoteles(StrToNum(codPais));
    }else{
        rosado(); cout << "Por favor ingrese el dato de manera correcta" << endl; azul();
        muestraDetalladaHoteles(false);
    }
}

//Se solicita el codigo de hotel, se valida y se muestran los pisos de hotel
void muestraDetalladaPisosHotel(bool first){
    string codPais, codigo;
    if(first) getline(cin,codigo);
    azul(); cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    azul(); cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    if(validarCodigoHotel(codPais,codigo)){
        arbolPaises.muestraDetalladaPisos(StrToNum(codPais),StrToNum(codigo));
    }else{
        rosado(); cout << "Por favor ingrese el dato de manera correcta" << endl; azul();
        muestraDetalladaPisosHotel(false);
    }
}

//solicita el código de de hotel y el número de piso, los valida y muestra las habitaciones dentro de ese piso de hotel
void muestraDetalladaHabitacionesPisosHotel(bool first){
    string codPais, codigo , numPiso;
    if(first) getline(cin,codigo);
    azul(); cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    if(validarNumPiso(codPais,codigo,numPiso)){
        arbolPaises.muestraDetalladaHabitaciones(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso));
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        muestraDetalladaHabitacionesPisosHotel(false);
    }
}

//Se solicita el código del hotel que se desea consultar, se valida y se muestra su cantidad de estrellas
void mostrarEstrellasHotel(bool first){
    string codPais, codigo;
    if(first) getline(cin,codigo);
    azul(); cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    if(validarCodigoHotel(codPais,codigo)){
        listaSimple tempHotel = arbolPaises.obtenerDatosHotel(StrToNum(codPais),StrToNum(codigo));
        blanco(); cout << endl << "Cantidad de estrellas de hotel " << tempHotel.obtenerValorPos(2) << " de pais " << tempHotel.obtenerValorPos(1) << " : " << tempHotel.obtenerValorPos(4) << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese el dato de manera correcta" << endl; azul();
        mostrarEstrellasHotel(false);
    }
}

//se solicita un código de piso y un número de hotel para validarlo y mostrar su cantidad de habitaciones
void mostrarCantidadHabitaciones(bool first){
    string codPais, codigo , numPiso;
    if(first) getline(cin,codigo);
    azul(); cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo del hotel: "; amarillo(); getline(cin,codigo); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    if(validarNumPiso(codPais,codigo,numPiso)){
        listaSimple tempPiso = arbolPaises.obtenerDatosPiso(StrToNum(codPais),StrToNum(codigo),StrToNum(numPiso));
        blanco(); cout << endl << "La cantidad de habitaciones del hotel " << tempPiso.obtenerValorPos(2) << " en el piso " << tempPiso.obtenerValorPos(3) << " del pais " << tempPiso.obtenerValorPos(1) <<  " : " << tempPiso.obtenerValorPos(5) << endl; azul();
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl;
        mostrarCantidadHabitaciones(false);
    }
}

//muestra las opciones de reporte disponibles para el administrador de hotel, y solicita que escoja una opción
void opcionesReporteAdminH(){
    string opcion;
    while(true){
        cout << endl << "Opciones de reporte:" << endl << endl << "1 - Consultar hoteles" << endl << "2 - Consultar pisos" << endl << "3 - Consultar habitaciones" << endl << "4 - Cantidad de estrellas de un hotel" << endl << "5 - Cantidad de habitaciones de un piso de hotel" << endl << "6 - Ultimo hotel insertado" << endl << "7 - Ultimo piso insertado" << endl << "8 - Ultima habitacion insertada" << endl << "9 - Consultar reservaciones" << endl << "10 - Salir" << endl << endl;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>10){
            rojo(); cout << "Lo escrito no concuerda con ninguna de las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                muestraDetalladaHoteles(true);
            }
            if(num==2){
                muestraDetalladaPisosHotel(true);
            }
            if(num==3){
                muestraDetalladaHabitacionesPisosHotel(true);
            }
            if(num==4){
                mostrarEstrellasHotel(true);
            }
            if(num==5){
                mostrarCantidadHabitaciones(true);
            }
            if(num==6){
                arbolPaises.mostrarUltimoHotel();
            }
            if(num==7){
                arbolPaises.mostrarUltimoPiso();
            }
            if(num==8){
                arbolPaises.mostrarUltimaHab();
            }
            if(num==9){
                arbolPaises.mostrarHabitacionesReservadas();
            }
            if(num==10){
                break;
            }
        }
    }
}

//muestra el menú con las opciones principales que puede realizar el administrador de hoteles, se le solicita el número de opción y se le redirige a lo que seleccionó
void opcionesAdminH(){
    while(true){
        cout << "Opciones: " << endl << endl << "1 - Inserciones" << endl << "2 - Modificaciones" << endl << "3 - Reportes" << endl << "4 - Salir" << endl << endl;
        string opcion;
        cout << "Digite el numero de una de las opciones: ";
        amarillo(); cin >> opcion; azul(); cout << endl;
        int num = StrToNum(opcion);
        if(num<1 || num>4){
            rojo(); cout << "Lo escrito no esta entre las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                opcionesInsercionAdminH();
            }
            if(num==2){
                opcionesModificacionAdminH();
            }
            if(num==3){
                opcionesReporteAdminH();
            }
            if(num==4){
                break;
            }
        }
    }
}

#endif