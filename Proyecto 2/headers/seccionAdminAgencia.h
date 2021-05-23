#ifndef SECCIONADMINAGENCIA_H
#define SECCIONADMINAGENCIA_H

#include "paises.h"

adminsAgenciaA arbolAdminsAgencia;

//Se saca la informacion de los archivos en forma de lista, se desglosan los datos y se insertan en la lista de administradores de agencia
void obtenerAdministradoresAgencia(){
    listaSimple datosAdminsAgencia = leerArchivo("AdministradorA") , datosAdminAgencia;
    adminsAgenciaA adminsAgencia;
    int codigo;
    string nombre;
    for(int i=1;i<=datosAdminsAgencia.largoLista();i++){
        datosAdminAgencia = dividirString(datosAdminsAgencia.obtenerValorPos(i),";");
        codigo = StrToNum(datosAdminAgencia.obtenerValorPos(1));
        nombre = datosAdminAgencia.obtenerValorPos(2);
        adminsAgencia.insertarAdminAgencia(codigo,nombre);
    }
    arbolAdminsAgencia = adminsAgencia;
}

//Se saca la información de los archivos de agencias, tipos de flotilla y carros y se guardan en los árboles
void obtenerAgencias(){
    listaSimple datosAgencias = leerArchivo("Agencias") , datosAgencia;
    int codPais, identificacionAg , cantidadVehiculos;
    string nombre;
    for(int i=1;i<=datosAgencias.largoLista();i++){
        datosAgencia = dividirString(datosAgencias.obtenerValorPos(i),";");
        codPais = StrToNum(datosAgencia.obtenerValorPos(1));
        identificacionAg = StrToNum(datosAgencia.obtenerValorPos(2));
        nombre = datosAgencia.obtenerValorPos(3);
        cantidadVehiculos = StrToNum(datosAgencia.obtenerValorPos(4));
        arbolPaises.insertarAgencia(codPais,identificacionAg,nombre,cantidadVehiculos);
    }
    listaSimple datosTiposFlotila = leerArchivo("TipoFlotilla") , datosTipoFlotila;
    int codTipo,cantCarrosTipo;
    for(int i=1;i<=datosTiposFlotila.largoLista();i++){
        datosTipoFlotila = dividirString(datosTiposFlotila.obtenerValorPos(i),";");
        codPais = StrToNum(datosTipoFlotila.obtenerValorPos(1));
        identificacionAg = StrToNum(datosTipoFlotila.obtenerValorPos(2));
        codTipo = StrToNum(datosTipoFlotila.obtenerValorPos(3));
        nombre = datosTipoFlotila.obtenerValorPos(4);
        cantCarrosTipo = StrToNum(datosTipoFlotila.obtenerValorPos(5));
        arbolPaises.insertarTipoFlotilla(codPais,identificacionAg,codTipo,nombre,cantCarrosTipo);
    }
    listaSimple datosCarros = leerArchivo("Carros") , datosCarro;
    int placa,numeroAsientos,anno,precioCarro;
    string modelo,estadoCarro;
    for(int i=1;i<=datosCarros.largoLista();i++){
        datosCarro = dividirString(datosCarros.obtenerValorPos(i),";");
        codPais = StrToNum(datosCarro.obtenerValorPos(1));
        identificacionAg = StrToNum(datosCarro.obtenerValorPos(2));
        codTipo = StrToNum(datosCarro.obtenerValorPos(3));
        placa = StrToNum(datosCarro.obtenerValorPos(4));
        modelo = datosCarro.obtenerValorPos(5);
        numeroAsientos = StrToNum(datosCarro.obtenerValorPos(6));
        anno = StrToNum(datosCarro.obtenerValorPos(7));
        precioCarro = StrToNum(datosCarro.obtenerValorPos(8));
        estadoCarro = datosCarro.obtenerValorPos(9);
        arbolPaises.insertarCarro(codPais,identificacionAg,codTipo,placa,modelo,numeroAsientos,anno,precioCarro,estadoCarro);
    }
}

//Se valida que el id ingresado no esté vacío, sea un número y exista una agencia con ese id
bool validarIdAgencia(string codPais,string idAg){
    bool valido = validarCodigoPais(codPais) && validarNoVacios(idAg,"identificacion de agencia") && validarNumeros(idAg,"identificacion de agencia");
    if(valido){
        pagenciaNA tempAgencia = arbolPaises.obtenerAgenciaId(StrToNum(codPais),StrToNum(idAg));
        if(tempAgencia==NULL){
            valido = false;
            rojo(); cout << "!!!!! La identificacion de agencia no es valida, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//Valida la existencia de la agencia, que el codigo no esté vacío y sea un número y que exista la flotilla
bool validarCodFlotilla(string codPais,string idAg,string codTipo){
    bool valido = validarIdAgencia(codPais,idAg) && validarNoVacios(codTipo,"codigo de tipo de flotilla") && validarNumeros(codTipo,"codigo de tipo de flotilla");
    if(valido){
        if(arbolPaises.obtenerTipoFlotillaCod(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo))==NULL){
            valido = false;
            rojo(); cout << "!!!!! El codigo de tipo de flotilla no es valido, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//valida la existencia del tipo de flotilla dentro de la agencia, que la placa no esté vacía, que sea un número y que exista un carro con la respectiva placa
bool validarPlacaCarro(string codPais,string idAg,string codTipo,string placa){
    bool valido = validarCodFlotilla(codPais,idAg,codTipo) && validarNoVacios(placa,"placa de carro") && validarNumeros(placa,"placa de carro");
    if(valido){
        pcarroNA tempCarro = arbolPaises.obtenerCarroPlaca(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo),StrToNum(placa));
        if(tempCarro==NULL){
            valido = false;
            rojo(); cout << "!!!!! La placa de carro no es valida, ya que no existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//valida que los campos no estén vacíos, que los que tienen que ser número efectivamente lo sean y que no exista una agencia con el mismo id
bool validarAgencia(string codPais,string idAg,string nombre,string cantVehs){
    bool valido = validarCodigoPais(codPais) && validarNoVacios(idAg+"|"+nombre+"|"+cantVehs,"identificacion de agencia|nombre de agencia|cantidad de vehiculos de agencia") && validarNumeros(idAg+"|"+cantVehs,"identificacion de agencia|cantidad de vehiculos");
    if(valido && arbolPaises.obtenerAgenciaId(StrToNum(codPais),StrToNum(idAg))!=NULL){
        valido = false;
        rojo(); cout << "!!!!! La identificacion de agencia de carros ingresada no es valida, por que ya existe !!!!!" << endl; azul();
    }
    return valido;
}

//Se valida que el estado del carro sea L, R u O
bool validarEstadoCarro(string estadoCarro){
    bool valido = true;
    if(estadoCarro!="L" && estadoCarro!="R" && estadoCarro!="O"){
        rojo(); cout << "!!!!! El estado de carro ingresado no es valido; tiene que ser L, R u O !!!!!" << endl; azul();
        valido = false;
    }
    return valido;
}

//valida los datos ingresados para añadir un nuevo tipo de flotilla, que exista la agencia, que no exista el tipo de flotilla, que los campos no estén vacios y que los números los sean
bool validarTipoFlotilla(string codPais,string idAg,string codTipo,string nombre,string cantCarrosTipo){
    bool valido = validarIdAgencia(codPais,idAg) && validarNoVacios(codTipo+"|"+nombre+"|"+cantCarrosTipo,"codigo de tipo de flotilla|nombre de  tipo de flotilla|cantidad de carros del tipo de flotillas") && validarNumeros(codTipo+"|"+cantCarrosTipo,"codigo de tipo de flotilla|cantidad de carros del tipo de flotillas");
    if(valido && arbolPaises.obtenerTipoFlotillaCod(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo))!=NULL){
        valido = false;
        rojo(); cout << "!!!!! El codigo de tipo de flotilla no es valido, porque ya existe !!!!!" << endl; azul();
    }
    return valido;
}

//valida los datos del carro que se quiere ingresar, no vacíos, números, que no exista un carro con la misma placa, que exista el tipo de flotilla de agencia
bool validarCarro(string codPais,string idAg,string codTipo,string placa,string modelo,string numeroAsientos,string anno,string precioCarro,string estadoCarro){
    bool valido = validarCodFlotilla(codPais,idAg,codTipo) && validarNoVacios(placa+"|"+modelo+"|"+numeroAsientos+"|"+anno+"|"+precioCarro+"|"+estadoCarro,"placa|modelo|numero de asientos|año|precio de carro|estado de carro") && validarNumeros(placa+"|"+numeroAsientos+"|"+anno+"|"+precioCarro,"placa|numero de asientos|año|precio de carro") && validarEstadoCarro(estadoCarro);
    if(valido){
        if(arbolPaises.obtenerCarroPlaca(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo),StrToNum(placa))!=NULL){
            valido = false;
            rojo(); cout << "!!!!! La placa de carro no es valida, porque ya existe !!!!!" << endl; azul();
        }
    }
    return valido;
}

//se solicitan los datos de una agencia, se validan y se insertan en la lista de agencias
void insertarAgencia(bool first){
    string conf , codPais, idAg , nombre , cantVehs;
    if(first) getline(cin,idAg);
    celeste(); cout << "Ha escogido insertar agencia de carros" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese la identificacion de la agencia: "; amarillo(); getline(cin,idAg); azul();
    cout<<"Ingrese el nombre de la agencia: "; amarillo(); getline(cin,nombre);  azul();
    cout << "Ingrese la cantidad de vehiculos de la agencia: "; amarillo(); getline(cin,cantVehs); azul();
    celeste(); cout << "Seguro de querer ingresar la agencia? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarAgencia(codPais,idAg,nombre,cantVehs)){
            arbolPaises.insertarAgencia(StrToNum(codPais),StrToNum(idAg),nombre,StrToNum(cantVehs));
            verde(); cout << endl << "Agencias de carros registrada" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            insertarAgencia(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar la agencia de carros" << endl << endl; azul();
    }
}

//se solicitan los datos de un tipo de flotilla, se validan y se insertan en la lista de agencias, en la agencia correspondiente
void insertarTipoFlotilla(bool first){
    string conf , codPais , idAg , codTipo, nombre , cantCarrosTipo;
    if(first) getline(cin,idAg);
    celeste(); cout << "Ha escogido insertar tipo de flotilla" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese la identificacion de la agencia: "; amarillo(); getline(cin,idAg); azul();
    cout<<"Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo);  azul();
    cout << "Ingrese el nombre del tipo de flotilla: "; amarillo(); getline(cin,nombre); azul();
    cout << "Ingrese cantidad de carros del tipo de flotilla: "; amarillo(); getline(cin,cantCarrosTipo); azul();
    celeste(); cout << "Seguro de querer ingresar el tipo de flotilla? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarTipoFlotilla(codPais,idAg,codTipo,nombre,cantCarrosTipo)){
            arbolPaises.insertarTipoFlotilla(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo),nombre,StrToNum(cantCarrosTipo));
            verde(); cout << endl << "Tipo de flotilla registrado" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            insertarTipoFlotilla(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar el tipo de flotilla" << endl << endl; azul();
    }
}

//Se solicitan los datos de carro, se validan los datos y que no existan uno igual y se inserta en la lista de agencias en su respectiva agencia y flotilla
void insertarCarro(bool first){
    string conf , codPais,idAg , codTipo , placa , modelo , numAsientos , anno , precioCarro , estadoCarro;
    if(first) getline(cin,idAg);
    celeste(); cout << "Ha escogido insertar carro" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese la identificacion de la agencia: "; amarillo(); getline(cin,idAg); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    cout << "Ingrese el numero de placa del carro: "; amarillo(); getline(cin,placa); azul();
    cout << "Ingrese el modelo del carro: "; amarillo(); getline(cin,modelo); azul();
    cout << "Ingrese el numero de asientos del carro: "; amarillo(); getline(cin,numAsientos); azul();
    cout << "Ingrese el año del carro: "; amarillo(); getline(cin,anno); azul();
    cout << "Ingrese el precio del carro: "; amarillo(); getline(cin,precioCarro); azul();
    cout << "Ingrese el estado del carro (L, O u R): "; amarillo(); getline(cin,estadoCarro); azul();
    celeste(); cout << "Seguro de querer ingresar el carro? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarCarro(codPais,idAg,codTipo,placa,modelo,numAsientos,anno,precioCarro,estadoCarro)){
            arbolPaises.insertarCarro(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo),StrToNum(placa),modelo,StrToNum(numAsientos),StrToNum(anno),StrToNum(precioCarro),estadoCarro);
            verde(); cout << endl << "Carro registrado" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            insertarCarro(false);
        }
    }else{
        gris(); cout << endl << "Decidio no ingresar el carro" << endl << endl; azul();
    }
}

//se muestran al administrador de agencia las opciones de inserción que tiene disponibles
void opcionesInsercionAdminA(){
    string opcion;
    while(true){
        cout << "Opciones de insercion:" <<endl <<endl << "1 - Insertar Agencia" << endl << "2 - Insertar Tipo de Flotilla" << endl << "3 - Insertar Carro" << endl << "4 - Salir" << endl << endl;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>4){
            rojo(); cout << "Lo escrito no concuerda con ninguna de las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                insertarAgencia(true);
            }
            if(num==2){
                insertarTipoFlotilla(true);
            }
            if(num==3){
                insertarCarro(true);
            }
            if(num==4){
                break;
            }
        }
    }
}

//muestra las opciones de modificación de agencia disponibles al usuario, y solicita el tipo y el nuevo dato a ingresar
void modificarAgencia(bool first){
    string conf, codPais, id;
    if(first) getline(cin,id);
    celeste(); cout << endl << "Ha escogido modificar agencia de carros" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    if(validarIdAgencia(codPais,id)){
        string opcion , dato; int numOpcion;
        while(true){
            cout << endl << "Que dato desea modificar?" << endl << endl << "1 - Nombre" << endl << "2 - Cantidad de vehiculos" << endl << "3 - Salir" << endl << endl << "Ingrese el numero de la opcion que desee modificar: "; amarillo(); getline(cin,opcion); azul();
            numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>3){
                rojo(); cout << "Lo ingresado no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion==1){
                    celeste(); cout << "Decidio modificar el nombre de la agencia" << endl; azul();
                    cout << "Ingrese el nuevo nombre: "; amarillo(); getline(cin,dato); azul();
                    celeste(); cout << "Seguro de querer modificar el nombre de la agencia? (S/N): "; amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nuevo nombre")){
                            arbolPaises.modificarDatoAgencia(StrToNum(codPais),StrToNum(id),dato,numOpcion);
                            verde(); cout << endl << "Nombre de agencia modificado" << endl << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar el nombre de la agencia" << endl; azul();
                    }
                } 
                if(numOpcion==2){
                    celeste(); cout << "Decidio modificar la cantidad de vehiculos de la agencia" << endl; azul();
                    cout << "Ingrese la nueva cantidad de vehiculos: "; amarillo(); getline(cin,dato); azul();
                    celeste(); cout << "Seguro de querer modificar la cantidad de vehiculos de la agencia? (S/N): ";amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nueva cantidad de vehiculos") && validarNumeros(dato,"nueva cantidad de vehiculos")){
                            arbolPaises.modificarDatoAgencia(StrToNum(codPais),StrToNum(id),dato,numOpcion);
                            verde(); cout << endl << "Cantidad de vehiculos de agencia modificada" << endl << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar la cantidad de vehiculos de la agencia" << endl; azul();
                    }
                }
                if(numOpcion==3){
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese el dato de manera correcta" << endl; azul();
        modificarAgencia(false);
    }
}

//muestra al usuario las opciones de modificación de tipo de flotilla de la que especificó a través de la identificación de la agencia y del código de tipo de flotilla, posteriormente los datos que puede modificar y solicita los nuevos datos
void modificarTipoFlotilla(bool first){
    string conf, codPais, id, codTipo;
    if(first) getline(cin,id);
    celeste(); cout << endl << "Ha escogido modificar tipo de flotilla" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    if(validarCodFlotilla(codPais,id,codTipo)){
        string opcion , dato; int numOpcion;
        while(true){
            cout << endl << "Que dato desea modificar?" << endl << endl << "1 - Nombre" << endl << "2 - Cantidad de carros" << endl << "3 - Salir" << endl << endl << "Ingrese el numero de la opcion que desee modificar: "; getline(cin,opcion);
            numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>3){
                rojo(); cout << "Lo ingresado no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion==1){
                    celeste(); cout << "Decidio modificar el nombre del tipo de flotilla" << endl; azul();
                    cout << "Ingrese el nuevo nombre: "; amarillo(); getline(cin,dato); azul();
                    celeste(); cout << "Seguro de querer modificar el nombre del tipo de flotilla? (S/N): "; amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nuevo nombre")){
                            arbolPaises.modificarDatoTipoFlotilla(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),dato,numOpcion);
                            verde(); cout << endl << "Nombre de tipo de flotilla modificado" << endl << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar el nombre del tipo de flotilla" << endl; azul();
                    }
                } 
                if(numOpcion==2){
                    celeste(); cout << "Decidio modificar la cantidad de carros del tipo de flotilla" << endl; azul();
                    cout << "Ingrese la nueva cantidad de carros: "; getline(cin,dato);
                    celeste(); cout << "Seguro de querer modificar la cantidad de carros del tipo de flotilla? (S/N): "; amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nueva cantidad de carros") && validarNumeros(dato,"nueva cantidad de carros")){
                            arbolPaises.modificarDatoTipoFlotilla(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),dato,numOpcion);
                            verde(); cout << endl << "Cantidad de carros de tipo de flotilla modificada" << endl << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar la cantidad de carros del tipo de flotilla" << endl; azul();
                    }
                }
                if(numOpcion==3){
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarTipoFlotilla(false);
    }
}

//brinda las opciones de modificación de datos de carro y y el nuevo dato, después de especificar el carro ingresando la identificación de la agencia, el código del tipo de flotilla y la placa del propio carro
void modificarCarro(bool first){
    string conf, codPais, id, codTipo, placa;
    if(first) getline(cin,id);
    celeste(); cout << endl << "Ha escogido modificar carro" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    cout << "Ingrese la placa del carro: "; amarillo(); getline(cin,placa); azul();
    if(validarPlacaCarro(codPais,id,codTipo,placa)){
        string opcion , dato; int numOpcion;
        while(true){
            cout << endl << "Que dato desea modificar?" << endl << endl << "1 -  Numero de asientos" << endl << "2 - Precio" << endl << "3 - Estado" << endl << "4 - Salir" << endl << endl << "Ingrese el numero de la opcion que desee modificar: "; amarillo(); getline(cin,opcion); azul();
            numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>4){
                rojo(); cout << "Lo ingresado no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion==1){
                    celeste(); cout << "Decidio modificar el numero de asientos del carro" << endl; azul();
                    cout << "Ingrese el nuevo numero de asientos: "; amarillo(); getline(cin,dato); azul();
                    celeste(); cout << "Seguro de querer modificar el numero de asientos del carro? (S/N): "; amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nuevo numero de asientos") && validarNumeros(dato,"nuevo numero de asientos")){
                            arbolPaises.modificarDatoCarro(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),StrToNum(placa),dato,numOpcion);
                            verde(); cout << endl << "Numero de asientos de carro modificado" << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar el nombre del tipo de flotilla" << endl; azul();
                    }
                } 
                if(numOpcion==2){
                    celeste(); cout << "Decidio modificar el precio del carro" << endl; azul();
                    cout << "Ingrese el nuevo precio: "; amarillo(); getline(cin,dato); azul();
                    celeste(); cout << "Seguro de querer modificar el precio del carro? (S/N): "; amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nuevo precio") && validarNumeros(dato,"nuevo precio")){
                            arbolPaises.modificarDatoCarro(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),StrToNum(placa),dato,numOpcion);
                            verde(); cout << endl << "Precio de carro modificado" << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar el precio del carro" << endl; azul();
                    }
                }
                if(numOpcion==3){
                    celeste(); cout << "Decidio modificar el estado del carro" << endl; azul();
                    cout << "Ingrese el nuevo estado (L, R u O): "; amarillo(); getline(cin,dato); azul();
                    celeste(); cout << "Seguro de querer modificar el estado del carro? (S/N): "; amarillo(); getline(cin,conf); azul();
                    if(conf=="S"){
                        if(validarNoVacios(dato,"nuevo estado") && validarEstadoCarro(dato)){
                            arbolPaises.modificarDatoCarro(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),StrToNum(placa),dato,numOpcion);
                            verde(); cout << endl << "Estado de carro modificado" << endl; azul();
                        }else{
                            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
                        }
                    }else{
                        gris(); cout << "Decidio no modificar el estado del carro" << endl; azul();
                    }
                }
                if(numOpcion==4){
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        modificarCarro(false);
    }
}

//se muestran al usuario las opciones de modificacion que tiene disponibles
void opcionesModificacionAdminA(){
    string opcion;
    while(true){
        cout << endl << "Opciones de eliminacion:" <<endl <<endl << "1 - Modificar Agencia" << endl << "2 - Modificar Tipo de Flotilla" << endl << "3 - Modificar Carro" << endl << "4 - Salir" << endl << endl;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>4){
            rojo(); cout << "Lo escrito no concuerda con ninguna de las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                modificarAgencia(true);
            }
            if(num==2){
                modificarTipoFlotilla(true);
            }
            if(num==3){
                modificarCarro(true);
            }
            if(num==4){
                break;
            }
        }
    }
}

//Se solicita el codigo de pais, se valida y se muestran los agencias
void muestraDetalladaAgencias(bool first){
    string codPais;
    if(first) getline(cin,codPais);
    azul(); cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    if(validarCodigoPais(codPais)){
        arbolPaises.muestraDetalladaAgencias(StrToNum(codPais));
    }else{
        rosado(); cout << "Por favor ingrese el dato de manera correcta" << endl; azul();
        muestraDetalladaAgencias(false);
    }
}

//solicita la identificacion de la agencia que se quiera consultar
void muestraDetalladaFlotillasAgencia(bool first){
    string codPais,id;
    if(first) getline(cin,id);
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    if(validarIdAgencia(codPais,id)){
        arbolPaises.muestraDetalladaTiposFlotilla(StrToNum(codPais),StrToNum(id));
    }else{
        rosado(); cout << "Por favor ingrese el dato de manera correcta" << endl; azul();
        muestraDetalladaFlotillasAgencia(false);
    }
}

//solicita la identificacion de la agencia y el codigo de tipo de flotilla del cuál se quieren mostrar los carros
void muestraDetalladaCarros(bool first){
    string codPais, id, codTipo;
    if(first) getline(cin,id);
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    if(validarCodFlotilla(codPais,id,codTipo)){
        arbolPaises.muestraDetalladaCarros(StrToNum(codPais),StrToNum(id),StrToNum(codTipo));
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        muestraDetalladaCarros(false);
    }
}

//se solicita los datos de identificacion del carro para mostrar su cantidad de estrellas
void mostrarCantAsientosCarro(bool first){
    string codPais, id, codTipo, placa;
    if(first) getline(cin,id);
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    cout << "Ingrese la placa del carro: "; amarillo(); getline(cin,placa); azul();
    if(validarPlacaCarro(codPais,id,codTipo,placa)){
        arbolPaises.mostrarDatoCarro(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),StrToNum(placa),3);
        cout << endl;
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        mostrarCantAsientosCarro(false);
    }
}

//se muestran al usuario las opciones de reporte de carro que tiene disponibles
void mostrarDatosCarro(bool first){
    string codPais, id, codTipo, placa;
    if(first) getline(cin,id);
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el identificacion de la agencia: "; amarillo(); getline(cin,id); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    cout << "Ingrese la placa del carro: "; amarillo(); getline(cin,placa); azul();
    if(validarPlacaCarro(codPais,id,codTipo,placa)){
        string opcion;
        while(true){
            cout << endl << "1 - Mostrar modelo" << endl;
            cout << "2 - Mostrar año" << endl;
            cout << "3 - Mostrar numero de asientos" << endl;
            cout << "4 - Mostrar precio" << endl;
            cout << "5 - Mostrar estado" << endl;
            cout << "6 - Salir" << endl << endl;
            cout << "Ingrese el numero de opcion que desee escoger: "; amarillo(); getline(cin,opcion); azul();
            int numOpcion = StrToNum(opcion);
            if(numOpcion<1 || numOpcion>6){
                rojo(); cout << "La opcion ingresada no esta dentro de las opciones brindadas" << endl; azul();
            }else{
                if(numOpcion!=6){
                    arbolPaises.mostrarDatoCarro(StrToNum(codPais),StrToNum(id),StrToNum(codTipo),StrToNum(placa),numOpcion);
                }else{
                    break;
                }
            }
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        mostrarDatosCarro(false);
    }  
}

//se muestran las opciones de reporte que tiene disponible el administrador de agencia
void opcionesReporteAdminA(){
    string opcion;
    while(true){
        cout << "Opciones de reportes:" <<endl <<endl << "1 - Consultar agencias" << endl << "2 - Consultar tipos de flotilla" << endl << "3 - Consultar carros" << endl << "4 - Cantidad de asientos de un carro" << endl << "5 - Consultar datos de un carro (modelo, año, numero de asientos, precio o estado del carro)" << endl << "6 - Ultima agencia insertada" << endl << "7 - Ultimo tipo de flotilla insertado" << endl << "8 - Ultimo carro insertado" << endl << "9 - Consultar reservaciones" << endl << "10 - Salir" << endl << endl;
        cout << "Ingrese el numero de la opcion que desee escoger: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>10){
            rojo(); cout << "Lo escrito no concuerda con ninguna de las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                muestraDetalladaAgencias(true);
            }
            if(num==2){
                muestraDetalladaFlotillasAgencia(true);
            }
            if(num==3){
                muestraDetalladaCarros(true);
            }
            if(num==4){
                mostrarCantAsientosCarro(true);
            }
            if(num==5){
                mostrarDatosCarro(true);
            }
            if(num==6){
                arbolPaises.mostrarUltimaAgencia();
            }
            if(num==7){
                arbolPaises.mostrarUltimoTipoFlotilla();
            }
            if(num==8){
                arbolPaises.mostrarUltimoCarro();
            }
            if(num==9){
                arbolPaises.mostrarCarrosReservados();
            }
            if(num==10){
                break;
            }
        }
    }
}

//Se muestran las opciones generales que el administrador de agencia tiene disponibles, y se le solicita que escoja una de ellas
void opcionesAdminAgencia(){
    while(true){
        cout << "Opciones: " << endl << endl << "1 - Inserciones" <<endl << "2 - Modificaciones" <<endl << "3 - Reportes" <<endl << "4 - Salir" << endl << endl;
        string opcion;
        cout << "Digite el numero de una de las opciones: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>4){
            rojo(); cout << "Lo escrito no esta entre las opciones brindadas" << endl; azul();
        }else{
            if(num==1){
                opcionesInsercionAdminA();
            }
            if(num==2){
                opcionesModificacionAdminA();
            }
            if(num==3){
                opcionesReporteAdminA();
            }
            if(num==4){
                break;
            }
        }
    }
}

#endif