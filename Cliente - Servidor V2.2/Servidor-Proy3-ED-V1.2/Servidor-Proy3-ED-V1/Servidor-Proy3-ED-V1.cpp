#include "ServidorSocket.h"
#include <thread>
#include "proyecto3_ED-main/principal.h"
#include "funciones.h"

int const largo = 5;

thread hilos[largo];

int puerto = 8000;

string opciones(int opcion, string solicitud) {
    string resultado;
    lista datos = dividirString(solicitud, "|");
    string seccion = datos.obtenerValorPos(1);
    int codigoPais = StrToNum(datos.obtenerValorPos(2));
    if (opcion == 1) {
        //MantenimientoPaises();
        string nombre = datos.obtenerValorPos(3);
        if (seccion == "IP") {
            resultado = insertarPais(codigoPais, nombre);
        }
        if (seccion == "EP") {
            resultado = eliminarPais(codigoPais);
        }
        if (seccion == "MP") {
            resultado = modificarPais(codigoPais, nombre);
        }
        if (seccion == "RP") {
            resultado = obtenerPaises();
        }
        if (seccion == "RA") {
            resultado = getAgencias(codigoPais);
        }
        if (seccion == "RH") {
            resultado = getHoteles(codigoPais);
        }
    }
    if (opcion == 2) {
        //AdminHotel();
        if (seccion == "AH") {
            int id = StrToNum(datos.obtenerValorPos(2));
            resultado = getNombreAdminHotel(id);
        }
        int codigoHotel = StrToNum(datos.obtenerValorPos(3));
        if (seccion == "IH") {
            string nombre = datos.obtenerValorPos(4);
            int cantEst = StrToNum(datos.obtenerValorPos(5));
            resultado = insertarHotel(codigoPais, codigoHotel, nombre, cantEst);
        }
        int numPiso = StrToNum(datos.obtenerValorPos(4));
        if (seccion == "IP") {
            string nombre = datos.obtenerValorPos(5);
            int cantHabs = StrToNum(datos.obtenerValorPos(6));
            resultado = insertarPiso(codigoPais, codigoHotel, numPiso, nombre, cantHabs);
        }
        int codHab = StrToNum(datos.obtenerValorPos(5));
        if (seccion == "IHa") {
            string tipoCuarto = datos.obtenerValorPos(6);
            int numeroCamas = StrToNum(datos.obtenerValorPos(7));
            int precioHab = StrToNum(datos.obtenerValorPos(8));
            string estadoHab = datos.obtenerValorPos(9);
            resultado = insertarHabitacion(codigoPais, codigoHotel, numPiso, codHab, tipoCuarto, numeroCamas, precioHab, estadoHab);
        }
        if (seccion == "RH") {
            resultado = getHoteles(codigoPais);
        }
        if (seccion == "RP") {
            resultado = getPisos(codigoPais, codigoHotel);
        }
        if (seccion == "RHa") {
            resultado = getHabitaciones(codigoPais, codigoHotel, numPiso);
        }
        if (seccion == "RCEH") {
            resultado = getEstrellasHotel(codigoPais, codigoHotel);
        }
        if (seccion == "RCHaP") {
            resultado = getCantHabsPiso(codigoPais, codigoHotel, numPiso);
        }
        if (seccion == "RUH") {
            resultado = getUltimoHotel();
        }
        if (seccion == "RUP") {
            resultado = getUltimoPiso();
        }
        if (seccion == "RUHa") {
            resultado = getUltimaHabitacion();
        }
        if (seccion == "RDH") {
            resultado = getDatosHotel(codigoPais, codigoHotel);
        }
        if (seccion == "MH") {
            string nombre = datos.obtenerValorPos(4);
            int cantEst = StrToNum(datos.obtenerValorPos(5));
            resultado = modificarHotel(codigoPais, codigoHotel, nombre, cantEst);
        }
        if (seccion == "RDP"){
            resultado = getDatosPiso(codigoPais,codigoHotel,numPiso);
        }
        if (seccion == "MP") {
            string nombre = datos.obtenerValorPos(5);
            int cantHabs = StrToNum(datos.obtenerValorPos(6));
            resultado = modificarPiso(codigoPais, codigoHotel, numPiso, nombre, cantHabs);
        }
        if (seccion == "RDHa") {
            resultado = getDatosHabitacion(codigoPais, codigoHotel, numPiso, codHab);
        }
        if (seccion == "MHa") {
            string tipoCuarto = datos.obtenerValorPos(6);
            int numeroCamas = StrToNum(datos.obtenerValorPos(7));
            int precioHab = StrToNum(datos.obtenerValorPos(8));
            string estadoHab = datos.obtenerValorPos(9);
            resultado = modificarHabitacion(codigoPais, codigoHotel, numPiso, codHab, tipoCuarto, numeroCamas, precioHab, estadoHab);
        }
        if (seccion == "EH") {
            resultado = eliminarHotel(codigoPais, codigoHotel);
        }
        if (seccion == "EP") {
            resultado = eliminarPiso(codigoPais, codigoHotel, numPiso);
        }
        if (seccion == "EHa") {
            resultado = eliminarHabitacion(codigoPais, codigoHotel, numPiso, codHab);
        }
        if (seccion == "RRH") {
            resultado = getReservacionesHotel();
        }
        if (seccion == "GFR") {
            string codigoReservacion = datos.obtenerValorPos(2);
            resultado = facturarReservacion(codigoReservacion);
        }
    }
    if (opcion == 3) {
        //AdminAgencia();
        int idAgencia = StrToNum(datos.obtenerValorPos(3));
        if (seccion == "AA") {
            int id = StrToNum(datos.obtenerValorPos(2));
            resultado = getNombreAdminAgencia(id);
        }
        if (seccion == "IA") {
            string nombre = datos.obtenerValorPos(4);
            int cantVehs = StrToNum(datos.obtenerValorPos(5));
            resultado = insertarAgencia(codigoPais, idAgencia, nombre, cantVehs);
        }
        int codTipoFlotilla = StrToNum(datos.obtenerValorPos(4));
        if (seccion == "ITF") {
            string nombre = datos.obtenerValorPos(5);
            int cantCarros = StrToNum(datos.obtenerValorPos(6));
            resultado = insertarTipoFlotilla(codigoPais, idAgencia, codTipoFlotilla, nombre, cantCarros);
        }
        int placa = StrToNum(datos.obtenerValorPos(5));
        if (seccion == "IC") {
            string modelo = datos.obtenerValorPos(6);
            int numAsientos = StrToNum(datos.obtenerValorPos(7));
            int anno = StrToNum(datos.obtenerValorPos(8));
            int precio = StrToNum(datos.obtenerValorPos(9));
            string estado = datos.obtenerValorPos(10);
            resultado = insertarCarro(codigoPais, idAgencia, codTipoFlotilla, placa, modelo, numAsientos, anno, precio, estado);
        }
        if (seccion == "EA"){
            resultado = eliminarAgencia(codigoPais, idAgencia);
        }
        if (seccion == "ETF") {
            resultado = eliminarTipoFlotilla(codigoPais, idAgencia, codTipoFlotilla);
        }
        if (seccion == "EC") {
            resultado = eliminarCarro(codigoPais, idAgencia, codTipoFlotilla, placa);
        }
        if (seccion == "RDA") {
            resultado = getDatosAgencia(codigoPais, idAgencia);
        }
        if (seccion == "MA") {
            string nombre = datos.obtenerValorPos(4);
            int cantVehs = StrToNum(datos.obtenerValorPos(5));
            resultado = modificarAgencia(codigoPais, idAgencia, nombre, cantVehs);
        }
        if (seccion == "RDTF") {
            resultado = getDatosTipoFlotilla(codigoPais, idAgencia, codTipoFlotilla);
        }
        if (seccion == "MTF") {
            string nombre = datos.obtenerValorPos(5);
            int cantCarros = StrToNum(datos.obtenerValorPos(6));
            resultado = modificarTipoFlotilla(codigoPais, idAgencia, codTipoFlotilla, nombre, cantCarros);
        }
        if (seccion == "RDC") {
            resultado = getDatosCarro(codigoPais, idAgencia, codTipoFlotilla, placa);
        }
        if (seccion == "MC") {
            string modelo = datos.obtenerValorPos(6);
            int numAsientos = StrToNum(datos.obtenerValorPos(7));
            int anno = StrToNum(datos.obtenerValorPos(8));
            int precio = StrToNum(datos.obtenerValorPos(9));
            string estado = datos.obtenerValorPos(10);
            resultado = modificarCarro(codigoPais, idAgencia, codTipoFlotilla, placa, modelo, numAsientos, anno, precio, estado);
        }
        if (seccion == "RA") {
            resultado = getAgencias(codigoPais);
        }
        if (seccion == "RTF") {
            resultado = getTiposFlotilla(codigoPais, idAgencia);
        }
        if (seccion == "RC") {
            resultado = getCarros(codigoPais, idAgencia, codTipoFlotilla);
        }
        if (seccion == "RCCA") {
            resultado = getCarrosAgencia(codigoPais, idAgencia);
        }
        if (seccion == "RCAC") {
            resultado = getAsientosCarro(codigoPais, idAgencia, codTipoFlotilla, placa);
        }
        if (seccion == "RUA") {
            resultado = getUltimaAgencia();
        }
        if (seccion == "RUTF") {
            resultado = getUltimoTipoFlotilla();
        }
        if (seccion == "RUC") {
            resultado = getUltimoCarro();
        }
        if (seccion == "RRA") {
            resultado = getReservacionesAgencia();
        }
    }
    if (opcion == 4) {
        //Usuario();
        if (seccion == "U") {
            int id = StrToNum(datos.obtenerValorPos(2));
            resultado = getNombreUsuario(id);
        }
        int codigoHotel = StrToNum(datos.obtenerValorPos(3));
        int numPiso = StrToNum(datos.obtenerValorPos(4));
        int codHab = StrToNum(datos.obtenerValorPos(5));
        string pasaporte = datos.obtenerValorPos(6);
        if (seccion == "RH") {
            resultado = reservarHabitacion(codigoPais, codigoHotel, numPiso, codHab, pasaporte);
        }
        if (seccion == "RC") {
            int idAgencia = StrToNum(datos.obtenerValorPos(3));
            int codTipoFlotilla = StrToNum(datos.obtenerValorPos(4));
            int placa = StrToNum(datos.obtenerValorPos(5));
            resultado = reservarCarro(codigoPais, idAgencia, codTipoFlotilla, placa, pasaporte);
        }
        if (seccion == "RTI") {
            int idAgencia = StrToNum(datos.obtenerValorPos(6));
            int codTipoFlotilla = StrToNum(datos.obtenerValorPos(7));
            int placa = StrToNum(datos.obtenerValorPos(8));
            resultado = reservarTodoIncluido(codigoPais, codigoHotel, numPiso, codHab, idAgencia, codTipoFlotilla, placa, pasaporte);
        }
        if (seccion == "CR") {
            string codigoReservacion = datos.obtenerValorPos(2);
            resultado = cancelarReservacion(codigoReservacion);
        }
        if (seccion == "CRH") {
            resultado = cancelarReservacionHabitacion(codigoPais, codigoHotel, numPiso, codHab);
        }
        if (seccion == "CRC") {
            int idAgencia = StrToNum(datos.obtenerValorPos(3));
            int codTipoFlotilla = StrToNum(datos.obtenerValorPos(4));
            int placa = StrToNum(datos.obtenerValorPos(5));
            resultado = cancelarReservacionCarro(codigoPais, idAgencia, codTipoFlotilla, placa);
        }
        if (seccion == "CRTI") {
            int idAgencia = StrToNum(datos.obtenerValorPos(6));
            int codTipoFlotilla = StrToNum(datos.obtenerValorPos(7));
            int placa = StrToNum(datos.obtenerValorPos(8));
            resultado = cancelarReservacionTodoIncluido(codigoPais, codigoHotel, numPiso, codHab, idAgencia, codTipoFlotilla, placa);
        }
        if (seccion == "EU") {
            int id = StrToNum(datos.obtenerValorPos(2));
            resultado = eliminarUsuario(id);
        }
        if (seccion == "GDH") {
            resultado = getHoteles(codigoPais);
        }
        if (seccion == "GDPi") {
            resultado = getPisos(codigoPais, codigoHotel);
        }
        if (seccion == "GDHa") {
            resultado = getHabitaciones(codigoPais, codigoHotel, numPiso);
        }
        int idAgencia = StrToNum(datos.obtenerValorPos(3));
        int codTipoFlotilla = StrToNum(datos.obtenerValorPos(4));
        if (seccion == "GDA") {
            resultado = getAgencias(codigoPais);
        }
        if (seccion == "GDTF") {
            resultado = getTiposFlotilla(codigoPais, idAgencia);
        }
        if (seccion == "GDC") {
            resultado = getCarros(codigoPais, idAgencia, codTipoFlotilla);
        }
        if (seccion == "GDP") {
            resultado = obtenerPaises();
        }
        if (seccion == "PR") {
            string codigoReservacion = datos.obtenerValorPos(2);
            resultado = pagarReservacion(codigoReservacion);
        }
        if (seccion == "RPP") {
            resultado = reportePosiblesPaises(codigoPais);
        }
    }
    return resultado;
}

void inicioSocket(ServidorSocket socket, int posicion) {
    socket.inicio();
    socket.creacionEstructura();
    socket.creacionSocket();
    socket.bindar();
    while (true) {
        socket.escuchar();
        socket.conectarCliente();
        socket.recibirMensaje();
        string mensaje = opciones(posicion, socket.getMensaje());
        socket.enviarMensaje(mensaje);
    }
    socket.cerrarSocket();
    socket.limpiar();
}

void inicioSocketV2(ServidorSocket socket, int posicion) {
    socket.inicio();
    socket.creacionEstructura();
    socket.creacionSocket();
    socket.bindar();
    bool correcto = TRUE;
    while (TRUE) {
        socket.escuchar();
        socket.conectarCliente();
        while (correcto) {
            correcto = correcto && socket.recibirMensaje();
            string mensaje = opciones(posicion, socket.getMensaje());
            correcto = correcto && socket.enviarMensaje(mensaje);
        }
        correcto = TRUE;
    }
    socket.cerrarSocket();
    socket.limpiar();
}

void inicioServidor(ServidorSocket socket) {
    string const solicitudes[largo-1] = { "MP" ,"AH","AA","U" };
    socket.inicio();
    socket.creacionEstructura();
    socket.creacionSocket();
    socket.bindar();
    while (TRUE) {
        socket.escuchar();
        socket.conectarCliente();
        socket.recibirMensaje();
        string mensaje = socket.getMensaje();
        int respuesta = 0;
        for (int i = 0; i < sizeof(solicitudes)/sizeof(solicitudes[0]); i++) {
            if (mensaje == solicitudes[i]) {
                respuesta = puerto + i + 1;
                break;
            }
        }
        socket.enviarMensaje(to_string(respuesta));
    }
    socket.cerrarSocket();
    socket.limpiar();
}

int main(){
    principal();
    ServidorSocket servidor(puerto);
    int numpuerto = puerto+1;
    hilos[0] = thread(inicioServidor, servidor);
    for (int i = 1; i < largo; i++) {
        ServidorSocket socket(numpuerto);
        hilos[i] = thread(inicioSocketV2, socket, i);
        numpuerto++;
    }
    hilos->join();
}