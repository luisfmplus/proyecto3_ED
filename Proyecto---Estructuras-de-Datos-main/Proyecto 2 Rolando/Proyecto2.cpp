#include "headers/seccionAdminHotel.h"//Se llama el header que posee las opciones y acciones del administrador de hotel
#include "headers/seccionAdminAgencia.h" //Se llama el header que posee las opciones y acciones del administrador de agencia

usuariosA arbolUsuarios; //lista doble circular en dónde se guardan los usuarios junto con sus datos

//Se sacan los datos de los usuarios del archivo, se saca el pasaporte y el nombre y se van guardando dentro de la lista de usuarios
void obtenerUsuarios(){
    listaSimple datosUsuarios = leerArchivo("Usuarios") , datosUsuario;
    usuariosA usuarios;
    int pasaporte;
    string nombre;
    for(int i=1;i<=datosUsuarios.largoLista();i++){
        datosUsuario = dividirString(datosUsuarios.obtenerValorPos(i),";");
        pasaporte = StrToNum(datosUsuario.obtenerValorPos(1));
        nombre = datosUsuario.obtenerValorPos(2);
        usuarios.insertarUsuario(pasaporte,nombre);
    }
    arbolUsuarios = usuarios;
}

bool validarReservacionHabitacion(string codPais, string codHotel, string numPiso, string codHab){
    bool valido = validarCodHab(codPais,codHotel,numPiso,codHab);
    if(valido){
        listaSimple datos = arbolPaises.obtenerDatosHabitacion(StrToNum(codPais),StrToNum(codHotel),StrToNum(numPiso),StrToNum(codHab));
        string estado = datos.obtenerValorPos(8);
        if(estado=="R"){
            valido = false;
            rojo(); cout << "No se puede reservar la habitacion, porque ya esta reservada" << endl; azul();
        }
        if(estado=="O"){
            valido = false;
            rojo(); cout << "No se puede reservar la habitacion, porque ya esta ocupada" << endl; azul();
        }
    }
    return valido;
}

void reservarHabitacion(bool first){
    string conf , codPais, codHotel , numPiso, codHab;
    if(first) getline(cin,conf);
    celeste(); cout << "Ha escogido reservar habitacion" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese el codigo de hotel: "; amarillo(); getline(cin,codHotel); azul();
    cout << "Ingrese el numero de piso: "; amarillo(); getline(cin,numPiso); azul();
    cout << "Ingrese el codigo de habitacion: "; amarillo(); getline(cin,codHab); azul();
    celeste(); cout << "Seguro de querer reservar la habitacion? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarReservacionHabitacion(codPais,codHotel,numPiso,codHab)){
            arbolPaises.modificarDatoHabitacion(StrToNum(codPais),StrToNum(codHotel),StrToNum(numPiso),StrToNum(codHab),"R",4);
            verde(); cout << endl << "Reservacion de habitacion realizada con exito" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            reservarHabitacion(false);
        }
    }else{
        gris(); cout << endl << "Decidio no reservar la habitacion" << endl << endl; azul();
    }
}

bool validarReservacionCarro(string codPais, string idAgencia, string codTipo, string placa){
    bool valido = validarPlacaCarro(codPais,idAgencia,codTipo,placa);
    if(valido){
        string estado = arbolPaises.obtenerCarroPlaca(StrToNum(codPais),StrToNum(idAgencia),StrToNum(codTipo),StrToNum(placa))->obtenerEstadoCarro();
        if(estado=="R"){
            valido = false;
            rojo(); cout << "No se puede reservar el carro, porque ya esta reservado" << endl; azul();
        }
        if(estado=="O"){
            valido = false;
            rojo(); cout << "No se puede reservar el carro, porque ya esta ocupado" << endl; azul();
        }
    }
    return valido;
}

void reservarCarro(bool first){
    string conf , codPais,idAg , codTipo , placa;
    if(first) getline(cin,idAg);
    celeste(); cout << "Ha escogido reservar carro" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    cout << "Ingrese la identificacion de la agencia: "; amarillo(); getline(cin,idAg); azul();
    cout << "Ingrese el codigo de tipo de flotilla: "; amarillo(); getline(cin,codTipo); azul();
    cout << "Ingrese el numero de placa del carro: "; amarillo(); getline(cin,placa); azul();
    celeste(); cout << "Seguro de querer reservar el carro? (S/N): "; amarillo(); getline(cin,conf); azul();
    if(conf=="S"){
        if(validarReservacionCarro(codPais,idAg,codTipo,placa)){
            arbolPaises.modificarDatoCarro(StrToNum(codPais),StrToNum(idAg),StrToNum(codTipo),StrToNum(placa),"R",3);
            verde(); cout << endl << "Reservacion de carro realizada con exito" << endl << endl; azul();
        }else{
            rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
            reservarCarro(false);
        }
    }else{
        gris(); cout << endl << "Decidio no reservar la habitacion" << endl << endl; azul();
    }
}

void reservarTodoIncluido(bool first){
    string conf , codPais;
    if(first) getline(cin,codPais);
    celeste(); cout << "Ha escogido reservar todo incluido" << endl; azul();
    cout << "Ingrese el codigo del pais: "; amarillo(); getline(cin,codPais); azul();
    if(validarCodigoPais(codPais)){
        string codHotel, idAgencia;
        cout << "Ingrese el codigo de hotel: "; amarillo(); getline(cin,codHotel); azul();
        cout << "Ingrese la identificacion de la agencia: "; amarillo(); getline(cin,idAgencia); azul();
        if(validarCodigoHotel(codPais,codHotel) && validarIdAgencia(codPais,idAgencia)){
            arbolPaises.obtenerHotelCodigo(StrToNum(codPais),StrToNum(codHotel))->reservarHotel();
            arbolPaises.obtenerAgenciaId(StrToNum(codPais),StrToNum(idAgencia))->reservarAgencia();
            verde(); cout << endl << "Reservacion todo incluido realizada con exito" << endl << endl; azul();
        }
    }else{
        rosado(); cout << "Por favor ingrese los datos de manera correcta" << endl; azul();
        reservarTodoIncluido(false);
    }
}

void realizarReservacion(){
    cout << endl << "Opciones de reservacion: " << endl << endl << "1 - Reservar Habitacion" << endl << "2 - Reservar Carro" << endl << "3 - Reservacion Todo Incluido" << endl << "4 - Salir" << endl << endl << "Ingrese el numero de la opcion que desee escoger: ";
    string opcion;
    amarillo(); cin >> opcion; azul();
    int numOpcion = StrToNum(opcion);
    if(numOpcion>0 && numOpcion<5){
        if(numOpcion==1){
            reservarHabitacion(true);
        }
        if(numOpcion==2){
            reservarCarro(true);
        }
        if(numOpcion==3){
            reservarTodoIncluido(true);
        }
    }else{
        rojo(); cout << "Lo escrito no estra entre las opciones brindadas" << endl; azul();
    }
}

//Si el usuario decidió ingresar como Usuario, e ingresó un pasaporte existente se le brindan las opciones que ahora tiene, tiene que ingresar el número de opción al que desea entrar, si ingresa un número que no está dentro de las opciones se le solicita que lo vuelva a ingresar
void opcionesUsuario(){
    while(true){
        cout << "Opciones: " << endl << endl << "1 - Consultar Hoteles" <<endl << "2 - Consultar Pisos de un hotel" <<endl << "3 - Consultar Habitaciones de un hotel de un piso" <<endl << "4 - Consultar Agencias" <<endl << "5 - Consultar Flotilla de una agencia" << endl << "6 - Consultar Carros de un tipo de flotilla de una agencia" << endl << "7 - Consultar Paises" << endl << "8 - Realizar reservacion" << endl << "9 - Salir" << endl << endl;
        string opcion;
        cout << "Digite el numero de una de las opciones: ";
        amarillo(); cin >> opcion; azul();
        int num = StrToNum(opcion);
        if(num<1 || num>9){
            rojo(); cout << "Lo escrito no esta entre las opciones brindadas" << endl; azul();
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
                muestraDetalladaAgencias(true);
            }
            if(num==5){
                muestraDetalladaFlotillasAgencia(true);
            }
            if(num==6){
                muestraDetalladaCarros(true);
            }
            if(num==7){
                listaPaises.muestraDetalladaPaises();
            }
            if(num==8){
                realizarReservacion();
            }
            if(num==9){
                break;
            }
        }
    }
}

//Se le brindan al usuario los tipos de usuario con los que puede ingresar al sistema, si ingresa un numero que no está dentro de las opciones brindadas se le solicita que vuelva a ingresar el número de opción
int seleccionarTipoUsuario(){
    cout << "Buenas, seleccione como desea ingresar al sistema:" << endl << endl << "1 - Mantenimiento de Paises" << endl << "2 - Administrador de Hotel" << endl << "3 - Administrador de Agencia" << endl << "4 - Usuario" << endl << "5 - Salir" << endl << endl;
    string tipoUsuario;
    cout << "Ingrese el numero de opcion: ";
    while(true){
        amarillo(); cin >> tipoUsuario; azul();
        if(StrToNum(tipoUsuario)<1 || StrToNum(tipoUsuario)>5){
            rojo(); cout << "Lo escrito no corresponde con las opciones brindadas, por favor digite uno de los numeros dados: "; azul();
        }else{
            break;
        }
    }
    return StrToNum(tipoUsuario);
}

//Una vez el usuario escogió el tipo de usuario con el que quiere ingresar se le solicita que ingrese el código o el pasaporte, según la opción que haya escogido previamente, se busca dentro de la lista de administradores de hotel, de agencia o usuarios para verificar si existe, si es así se imprime el nombre junto con las opciones disponibles para el tipo de usuario en cuestión, si no existe se devuelve un string vacío y se solicita que vuelva a ingresar el codigo o el pasaporte.
int validarUsuario(int tipoUsuario){
    string idUsuario , nombre;
    if(tipoUsuario!=5){
        while(true){
            cout << "Ha decidido ingresar ";
            if(tipoUsuario==1){
                cout << "a Mantenimiento de Paises" << endl << endl << "Desea ingresar como:" << endl << endl << "1 - Administrador de Hotel" << endl << "2 - Administrador de Agencia" << endl << "3 - Salir"<< endl << endl << "Ingrese la opcion con la que desea ingresar: ";
                amarillo(); cin >> idUsuario; azul(); cout << endl;
                int opcionUsuario = StrToNum(idUsuario);
                if(opcionUsuario>0 && opcionUsuario<4){
                    if(opcionUsuario==1){
                        while(true){
                            cout << "Ingrese su codigo de Administrador de Hotel (S para Salir): ";
                            amarillo(); cin >> idUsuario; azul();
                            if(idUsuario=="S"){
                                break;
                            }else{
                                nombre = arbolAdminsHotel.nombreAdminHotel(StrToNum(idUsuario));
                                if(nombre==""){
                                    rojo(); cout << "El codigo ingresado no esta registrado" << endl; azul();
                                }else{
                                    verde(); cout << endl << "Bienvenido " << nombre << endl << endl; azul();
                                    opcionesPaises();
                                    cout << endl; break;
                                }
                            }
                        }
                    }
                    if(opcionUsuario==2){
                        while(true){
                            cout << "Ingrese su codigo de Administrador de Agencia (S para Salir): ";
                            amarillo(); cin >> idUsuario; azul();
                            if(idUsuario=="S"){
                                break;
                            }else{
                                nombre = arbolAdminsAgencia.nombreAdminAgencia(StrToNum(idUsuario));
                                if(nombre==""){
                                    rojo(); cout << "El codigo ingresado no esta registrado" << endl; azul();
                                }else{
                                    verde(); cout << endl << "Bienvenido " << nombre << endl << endl; azul();
                                    opcionesPaises();
                                    cout << endl; break;
                                }
                            }
                        }
                    }
                    if(opcionUsuario==3) break;
                }else{
                    rojo(); cout << "La opcion ingresada no corresponde con ninguna de las opciones brindadas" << endl; azul();
                }
            }
            if(tipoUsuario==2){
                cout << "como Administrador de Hotel, por favor ingrese su codigo (S para salir): ";
                amarillo(); cin >> idUsuario; azul();
                if(idUsuario=="S"){cout << endl; break;}
                nombre = arbolAdminsHotel.nombreAdminHotel(StrToNum(idUsuario));
                if(nombre==""){
                    rojo(); cout << "El codigo ingresado no esta registrado" << endl; azul();
                }else{
                    verde(); cout << endl << "Bienvenido " << nombre << endl << endl; azul();
                    opcionesAdminH();
                    cout << endl; break;
                }
            }
            if(tipoUsuario==3){
                cout << "como Administrador de Agencia, por favor ingrese su codigo (S para salir): ";
                amarillo(); cin >> idUsuario; azul();
                if(idUsuario=="S"){cout << endl; break;}
                nombre = arbolAdminsAgencia.nombreAdminAgencia(StrToNum(idUsuario));
                if(nombre==""){
                    rojo(); cout << "El codigo ingresado no esta registrado" << endl; azul();
                }else{
                    verde(); cout << endl << "Bienvenido " << nombre << endl << endl; azul();
                    opcionesAdminAgencia();
                    cout << endl; break;
                }
            }
            if(tipoUsuario==4){
                cout << "Usuario, por favor ingrese su numero de pasaporte (S para salir): ";
                amarillo(); cin >> idUsuario; azul();
                if(idUsuario=="S"){cout << endl; break;}
                nombre = arbolUsuarios.nombreUsuario(StrToNum(idUsuario));
                if(nombre==""){
                    rojo(); cout << "El pasaporte ingresado no esta registrado" << endl; azul();
                }else{
                    verde(); cout << endl << "Bienvenido " << nombre << endl << endl; azul();
                    opcionesUsuario();
                    cout << endl; break;
                }
            }
        }
    }
    return StrToNum(idUsuario);
}

//Da inicio a la ejecución del programa, saca los hoteles, los pisos, las habitaciones, agencias, tipos de flotillas, carros, administradores de agencias, administradores de hoteles y usuarios de los archivos y los inseta dentro de sus respectivas listas, pone el color de las letras de la consola en azul. Inicia el ciclo que llama a las funciones que muestran los menú y solicita los datos repectivos al usuario
void inicioPrograma(){
    obtenerPaises();
    obtenerHoteles();
    obtenerAdministradoresHotel();
    obtenerAgencias();
    obtenerAdministradoresAgencia();
    obtenerUsuarios();
    int tipoUsuario , idUsuario;
    azul();
    while(tipoUsuario!=5){
        tipoUsuario = seleccionarTipoUsuario();
        idUsuario = validarUsuario(tipoUsuario);
    }
}

int main(){
    inicioPrograma();
    cout << endl << "---------- Programa Finalizado ----------" << endl << endl;
    return 0;
}