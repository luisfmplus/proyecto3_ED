#ifndef CLASESARBOLES_H
#define CLASESARBOLES_H

#include "arboles.h"
#include "funcionesGenerales.h"

//Si se presentara un error en este archivo, por favor descomentar la librer�a y la funci�n de abajo que convierte n�mero a string
//  |
//  V

/*#include <sstream>

string to_string(int num){
	stringstream ss;
	ss << num;
	string str = ss.str();
	return str;
}*/

#pragma region Clases

class claseResultado;

class habitacionNA : nodoARN{
    public:
        habitacionNA(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab);
        void insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab);
        void mostrarDatosHabitacion();
        void muestraDetalladaHabitacion();
        void reservarHabitacion();
        void mostrarReservaciones();

    private:
        int codPais;
        int codHotel;
        int numPiso;
        int codHab;
        string tipoCuarto;
        int numCamas;
        int precioHab;
        string estadoHab;
        habitacionNA *hijoIzq;
        habitacionNA *hijoDer;

    friend class habitacionesA;
};
typedef habitacionNA *phabitacionNA;

class habitacionesA : arbolRojiNegro{
    public:
        habitacionesA();
        phabitacionNA obtenerHabitacionCod(int codHab);
        void insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab);
        listaSimple obtenerDatos(int codHab);
        void modificarDato(int codHab,string dato,int opcion);
        void muestraDetalladaHabitaciones();
        void reservarHabitaciones();
        void mostrarReservaciones();
        void borrar(pnodoAAVL nodoB, bool booleano);
        void borrarBalanceado(pnodoAAVL r, bool booleano, int eliminar);
        void equilibrar1(pnodoAAVL n, bool booleano);
        void equilibrar2(pnodoAAVL n, bool booleano);
        void insertarBalanceado(pnodoAAVL r, bool booleano, int x);
        void rotacionDobleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionDobleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void reglaTio();

    private:
        phabitacionNA raiz;
};

class pisoNA : nodoAAVL{
    public:
        pisoNA(int codPais, int codHotel, int numPiso, string nombre, int cantHabs);
        void insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs);
        void muestraDatosPiso();
        void muestraDetalladaPiso();
        void reservarPiso();
        void mostrarReservaciones();

    private:
        int codPais;
        int codHotel;
        int numPiso;
        string nombre;
        int cantHabs;
        habitacionesA habitaciones;
        pisoNA *hijoIzq;
        pisoNA *hijoDer;

    friend class pisosA;
};
typedef pisoNA *ppisoNA;

class pisosA : arbolAVL{
    public:
        pisosA();
        ppisoNA obtenerPisoNum(int numPiso);
        phabitacionNA obtenerHabitacionCod(int numPiso, int codHab);
        void insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs);
        void insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab);
        listaSimple obtenerDatos(int numPiso);
        void modificarDato(int numPiso, string dato, int opcion);
        listaSimple obtenerDatosHabitacion(int numPiso, int codHab);
        void modificarDatoHabitacion(int numPiso, int codHab, string dato, int opcion);
        void muestraDetalladaPisos();
        void muestraDetalladaHabitaciones(int numPiso);
        void reservarPisos();
        void mostrarReservaciones();
        void borrar(pnodoAAVL nodoB, bool booleano);
        void borrarBalanceado(pnodoAAVL r, bool booleano, int eliminar);
        void equilibrar1(pnodoAAVL n, bool booleano);
        void equilibrar2(pnodoAAVL n, bool booleano);
        void insertarBalanceado(pnodoAAVL r, bool booleano, int x);
        void rotacionDobleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionDobleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleDerecha(pnodoAAVL n1, pnodoAAVL n2);

    private:
        ppisoNA raiz;
};

class hotelNA : nodoABB {
    public:
        hotelNA(int codPais, int codHotel, string nombre, int cantEstrellas);
        void insertarHotel(int codPais, int codHotel, string nombre, int cantEstrellas);
        void muestraDatosHotel();
        void muestraDetalladaHotel();
        void reservarHotel();
        void mostrarReservaciones();

    private:
        int codPais;
        int codHotel;
        string nombre;
        int cantEstrellas;
        pisosA pisos;
        hotelNA *hijoIzq;
        hotelNA *hijoDer;

    friend class hotelesA;
};
typedef hotelNA *photelNA;

class hotelesA : arbolBinarioBusqueda {
    public:
        hotelesA();
        photelNA obtenerHotelCodigo(int codigo);
        ppisoNA obtenerPisoNum(int codHotel, int numPiso);
        phabitacionNA obtenerHabitacionCod(int codHotel, int numPiso, int codHab);
        void insertarHotel(int codPais, int codHotel, string nombre, int cantEstrellas);
        void insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs);
        void insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab);
        listaSimple obtenerDatos(int codPais);
        void modificarDato(int codHotel, string dato, int opcion);
        listaSimple obtenerDatosPiso(int codHotel,int numPiso);
        void modificarDatoPiso(int codHotel, int numPiso, string dato, int opcion);
        listaSimple obtenerDatosHabitacion(int codHotel, int numPiso, int codHab);
        void modificarDatoHabitacion(int codHotel, int numPiso, int codHab, string dato, int opcion);
        void muestraDetalladaHoteles();
        void muestraDetalladaPisos(int codHotel);
        void muestraDetalladaHabitaciones(int codHotel, int numPiso);
        void mostrarReservaciones();

    private:
        photelNA raiz;
};

class carroNA : nodoAAA{
    public:
        carroNA(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado);
        void insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado);
        void modificarDatoCarro(string dato, int opcion);
        void mostrarDatosCarro();
        void muestraDetalladaCarro();
        void mostrarDatoCarro(int opcion);
        string obtenerEstadoCarro();
        void reservarCarro();
        void mostrarRerservaciones();

    private:
        int codPais;
        int idAgencia;
        int codTipo;
        int placa;
        string modelo;
        int numAsientos;
        int anno;
        int precio;
        string estado;
        carroNA *hijoIzq;
        carroNA *hijoDer;
        carroNA *anterior;
        carroNA *siguiente;

    friend class carrosA;
};
typedef carroNA *pcarroNA;

class carrosA : arbolAA{
    public:
        carrosA();
        pcarroNA obtenerCarroPlaca(int placa);
        void insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado);
        void muestraDetalladaCarros();
        void reservarCarros();
        void mostrarReservaciones();
        void reparto();
        void giro();

    private:
        pcarroNA raiz;
};

class tipoFlotillaNA : nodoAAVL{
    public:
        tipoFlotillaNA(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo);
        void insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo);
        void insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado);
        void modificarDatoTipoFlotilla(string dato, int opcion);
        void muestraDatosTipoFlotilla();
        void muestraDetalladaTipoFlotilla();
        void reservarTipoFlotilla();
        void mostrarReservaciones();

    private:
        int codPais;
        int idAgencia;
        int codTipo;
        string nombre;
        int cantCarrosTipo;
        carrosA carros;
        tipoFlotillaNA *hijoIzq;
        tipoFlotillaNA *hijoDer;

    friend class tiposFlotillaA;
};
typedef tipoFlotillaNA *ptipoFlotillaNA;

class tiposFlotillaA : arbolAVL{
    public:
        tiposFlotillaA();
        ptipoFlotillaNA obtenerTipoFlotillaCod(int codTipo);
        pcarroNA obtenerCarroPlaca(int codTipo,int placa);
        void insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo);
        void muestraDetalladaTiposFlotilla();
        void muestraDetalladaCarros(int codTipo);
        void reservarTiposFlotilla();
        void mostrarReservaciones();
        void borrar(pnodoAAVL nodoB, bool booleano);
        void borrarBalanceado(pnodoAAVL r, bool booleano, int eliminar);
        void equilibrar1(pnodoAAVL n, bool booleano);
        void equilibrar2(pnodoAAVL n, bool booleano);
        void insertarBalanceado(pnodoAAVL r, bool booleano, int x);
        void rotacionDobleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionDobleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleDerecha(pnodoAAVL n1, pnodoAAVL n2);

    private:
        ptipoFlotillaNA raiz;
};

class agenciaNA : nodoABB {
    public:
        agenciaNA(int codPais,int idAgencia,string nombre,int cantVehs);
        void insertarAgencia(int codPais,int idAgencia,string nombre,int cantVehs);
        void insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo);
        void modificarDatoAgencia(string dato, int opcion);
        void muestraDatosAgencia();
        void muestraDetalladaAgencia();
        void reservarAgencia();
        void mostrarReservaciones();
    
    private:
        int codPais;
        int idAgencia;
        string nombre;
        int cantVehs;
        tiposFlotillaA tiposFlotilla;
        agenciaNA *hijoIzq;
        agenciaNA *hijoDer;

    friend class agenciasA;
};
typedef agenciaNA *pagenciaNA;

class agenciasA : arbolBinarioBusqueda{
    public:
        agenciasA();
        pagenciaNA obtenerAgenciaId(int idAgencia);
        ptipoFlotillaNA obtenerTipoFlotillaCod(int idAgencia,int codTipo);
        pcarroNA obtenerCarroPlaca(int idAgencia, int codTipo, int placa);
        void insertarAgencia(int codPais,int idAgencia,string nombre,int cantVehs);
        void muestraDetalladaAgencias();
        void muestraDetalladaTiposFlotilla(int idAgencia);
        void muestraDetalladaCarros(int idAgencia, int codTipo);
        void mostrarReservaciones();

    private:
        pagenciaNA raiz;
};

class paisNA : nodoABB {
    public:
        paisNA(int codPais);
        void insertarPais(int codPais);
        void mostrarHabitacionesReservadas();
        void mostrarCarrosReservados();
    
    private:
        int codPais;
        hotelesA hoteles;
        agenciasA agencias;

        paisNA *hijoIzq;
        paisNA *hijoDer;

    friend class paisesA;
};
typedef paisNA *ppaisNA;

class paisesA : arbolBinarioBusqueda {
    public:
        paisesA();
        ppaisNA obtenerPaisCodigo(int codPais);
        photelNA obtenerHotelCodigo(int codPais, int codHotel);
        ppisoNA obtenerPisoNum(int codPais, int codHotel, int numPiso);
        phabitacionNA obtenerHabitacionCod(int codPais, int codHotel, int numPiso, int codHab);
        void insertarPais(int codPais);
        void insertarHotel(int codPais, int codHotel, string nombre, int cantEstrellas);
        void insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs);
        void insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab);
        listaSimple obtenerDatosHotel(int codPais, int codHotel);
        void modificarDatoHotel(int codPais, int codHotel, string dato, int opcion);
        listaSimple obtenerDatosPiso(int codPais, int codHotel, int numPiso);
        void modificarDatoPiso(int codPais, int codHotel, int numPiso, string dato, int opcion);
        listaSimple obtenerDatosHabitacion(int codPais, int codHotel, int numPiso, int codHab);
        void modificarDatoHabitacion(int codPais, int codHotel, int numPiso, int codHab, string dato, int opcion);
        void muestraDetalladaHoteles(int codPais);
        void muestraDetalladaPisos(int codPais, int codHotel);
        void muestraDetalladaHabitaciones(int codPais, int codHotel, int numPiso);
        void mostrarUltimoHotel();
        void mostrarUltimoPiso();
        void mostrarUltimaHab();
        pagenciaNA obtenerAgenciaId(int codPais,int idAgencia);
        ptipoFlotillaNA obtenerTipoFlotillaCod(int codPais, int idAgencia, int codTipo);
        pcarroNA obtenerCarroPlaca(int codPais, int idAgencia, int codTipo, int placa);
        void insertarAgencia(int codPais,int idAgencia,string nombre,int cantVehs);
        void insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo);
        void insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado);
        void modificarDatoAgencia(int codPais, int idAgencia, string dato, int opcion);
        void modificarDatoTipoFlotilla(int codPais, int idAgencia, int codTipo, string dato, int opcion);
        void modificarDatoCarro(int codPais, int idAgencia, int codTipo, int placa, string dato, int opcion);
        void muestraDetalladaAgencias(int codPais);
        void muestraDetalladaTiposFlotilla(int codPais, int idAgencia);
        void muestraDetalladaCarros(int codPais, int idAgencia, int codTipo);
        void mostrarDatoCarro(int codPais, int idAgencia, int codTipo, int placa, int opcion);
        void mostrarUltimaAgencia();
        void mostrarUltimoTipoFlotilla();
        void mostrarUltimoCarro();
        void mostrarHabitacionesReservadas();
        void mostrarCarrosReservados();

    private:
        ppaisNA raiz;

        string ultimoHotel;
        string ultimoPiso;
        string ultimaHab;
        string ultimaAgencia;
        string ultimoTipoFlotilla;
        string ultimoCarro;
};

class adminHotelNA : nodoAB {
    public:
        adminHotelNA(int codigo, string nombre);
        void insertarAdminHotel(int codigo, string nombre);

    private:
        int codigo;
        string nombre;

        adminHotelNA *hijoIzq;
        adminHotelNA *hijoDer;

    friend class adminsHotelA;
};
typedef adminHotelNA *padminHotelNA;

class adminsHotelPA : paginaAB {
    public:
        adminsHotelPA();

    private:
        int cuenta;
        adminHotelNA *claves[5];
        adminsHotelPA *ramas[5];

    friend class adminsHotelA;
};
typedef adminsHotelPA *padminsHotelPA;

class adminsHotelA : arbolB{
    public:
        adminsHotelA();
        void insertarAdminHotel(int codigo, string nombre);
        string nombreAdminHotel(int codigo);
        claseResultado buscarNodo(padminHotelNA clave, padminsHotelPA p, boolean encontrado, int k);
        void inserta(padminHotelNA c1, padminsHotelPA raiz);
        claseResultado empujar(padminHotelNA c1, padminsHotelPA r, boolean empujaArriba, padminHotelNA mdna, padminsHotelPA x);
        void meterHoja(padminHotelNA x, padminsHotelPA xDer, padminsHotelPA p, int k);
        void dividirNodo(padminHotelNA x, padminsHotelPA xDer, padminsHotelPA p, int k, padminHotelNA mda, padminsHotelPA mder);

    private:
        padminHotelNA raiz;
        padminsHotelPA inicio;
        int max, min;
};

class adminAgenciaNA : nodoAB {
    public:
        adminAgenciaNA(int codigo, string nombre);
        void insertarAdminAgencia(int codigo, string nombre);

    private:
        int codigo;
        string nombre;
        adminAgenciaNA *hijoIzq;
        adminAgenciaNA *hijoDer;
    
    friend class adminsAgenciaA;
};
typedef adminAgenciaNA *padminAgenciaNA;

class adminsAgenciaPA : paginaAB{
    public:
        adminsAgenciaPA();

    private:
        int cuenta;
        adminsAgenciaPA *claves[5];
        adminsAgenciaPA *ramas[5];
        
    friend class adminsAgenciaA;
};
typedef adminsAgenciaPA *padminsAgenciaPA;

class adminsAgenciaA : arbolB{
    public:
        adminsAgenciaA();
        void insertarAdminAgencia(int codigo, string nombre);
        string nombreAdminAgencia(int codigo);
        resultado buscarNodo(pnodoAB clave, ppaginaAB p, boolean encontrado, int k);
        void inserta(pnodoAB c1, ppaginaAB raiz);
        resultado empujar(pnodoAB c1, ppaginaAB r, boolean empujaArriba, pnodoAB mdna, ppaginaAB x);
        void meterHoja(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k);
        void dividirNodo(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k, pnodoAB mda, ppaginaAB mder);

    private:
        padminAgenciaNA raiz;
};

class usuarioNA : nodoAB {
    public:
        usuarioNA(int pasaporte, string nombre);
        void insertarUsuario(int pasaporte, string nombre);

    private:
        int pasaporte;
        string nombre;
        usuarioNA *hijoIzq;
        usuarioNA *hijoDer;

    friend class usuariosA;
};
typedef usuarioNA *pusuarioNA;

class usuariosPA : paginaAB {
    public:
        usuariosPA();

    private:
        int cuenta;
        usuariosPA *claves[5];
        usuariosPA *ramas[5];
        
    friend class usuariosA;
};
typedef usuariosPA *pusuariosPA;

class usuariosA : arbolB{
    public:
        usuariosA();
        void insertarUsuario(int pasaporte, string nombre);
        string nombreUsuario(int pasaporte);
        resultado buscarNodo(pnodoAB clave, ppaginaAB p, boolean encontrado, int k);
        void inserta(pnodoAB c1, ppaginaAB raiz);
        resultado empujar(pnodoAB c1, ppaginaAB r, boolean empujaArriba, pnodoAB mdna, ppaginaAB x); //Quizás sea boolean
        void meterHoja(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k);
        void dividirNodo(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k, pnodoAB mda, ppaginaAB mder);

    private:
        pusuarioNA raiz;
};

class claseResultado{
    public:
        int entero;
        boolean booleano;
        padminHotelNA padminHotelNA;
};

#pragma endregion

#pragma region Constructores

paisNA::paisNA(int codPais){
    this->codPais = codPais;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

hotelNA::hotelNA(int codPais, int codHotel, string nombre, int cantEstrellas){
    this->codPais = codPais;
    this->codHotel = codHotel;
    this->nombre = nombre;
    this->cantEstrellas = cantEstrellas;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

pisoNA::pisoNA(int codPais, int codHotel, int numPiso, string nombre, int cantHabs){
    this->codPais = codPais;
    this->codHotel = codHotel;
    this->numPiso = numPiso;
    this->nombre = nombre;
    this->cantHabs = cantHabs;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

habitacionNA::habitacionNA(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab){
    this->codPais = codPais;
    this->codHotel = codHotel;
    this->numPiso = numPiso;
    this->codHab  = codHab;
    this->tipoCuarto = tipoCuarto;
    this->numCamas = numCamas;
    this->precioHab = precioHab;
    this->estadoHab = estadoHab;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

agenciaNA::agenciaNA(int codPais,int idAgencia,string nombre,int cantVehs){
    this->codPais = codPais;
    this->idAgencia = idAgencia;
    this->nombre = nombre;
    this->cantVehs = cantVehs;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

tipoFlotillaNA::tipoFlotillaNA(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo){
    this->codPais = codPais;
    this->idAgencia = idAgencia;
    this->codTipo = codTipo;
    this->nombre = nombre;
    this->cantCarrosTipo = cantCarrosTipo;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

carroNA::carroNA(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado){
    this->codPais = codPais;
    this->idAgencia = idAgencia;
    this->codTipo = codTipo;
    this->placa = placa;
    this->modelo = modelo;
    this->numAsientos = numAsientos;
    this->anno = anno;
    this->precio = precio;
    this->estado = estado;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

adminHotelNA::adminHotelNA(int codigo, string nombre){
    this->codigo = codigo;
    this->nombre = nombre;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

adminAgenciaNA::adminAgenciaNA(int codigo, string nombre){
    this->codigo = codigo;
    this->nombre = nombre;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

usuarioNA::usuarioNA(int pasaporte, string nombre){
    this->pasaporte = pasaporte;
    this->nombre = nombre;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

adminsHotelPA::adminsHotelPA(){
    this->cuenta = 0;
    for(int i=0;i<5;i++){
        this->claves[i] = NULL;
        this->ramas[i] = NULL; 
    }
}

adminsAgenciaPA::adminsAgenciaPA(){
    this->cuenta = 0;
    for(int i=0;i<5;i++){
        this->claves[i] = NULL;
        this->ramas[i] = NULL; 
    }
}

usuariosPA::usuariosPA(){
    this->cuenta = 0;
    for(int i=0;i<5;i++){
        this->claves[i] = NULL;
        this->ramas[i] = NULL; 
    }
}

paisesA::paisesA(){
    this->raiz = NULL;
    this->ultimoHotel = "";
    this->ultimoPiso = "";
    this->ultimaHab = "";
    this->ultimaAgencia = "";
    this->ultimoTipoFlotilla = "";
    this->ultimoCarro = "";
}

hotelesA::hotelesA(){
    this->raiz = NULL;
}

pisosA::pisosA(){
    this->raiz = NULL;
}

habitacionesA::habitacionesA(){
    this->raiz = NULL;
}

agenciasA::agenciasA(){
    this->raiz = NULL;
}

tiposFlotillaA::tiposFlotillaA(){
    this->raiz = NULL;
}

carrosA::carrosA(){
    this->raiz = NULL;
}

adminsHotelA::adminsHotelA(){
    this->max = 4;
    this->min = 2;
    this->raiz = NULL;
    this->inicio = NULL;
}

adminsAgenciaA::adminsAgenciaA(){
    this->raiz = NULL;
}

usuariosA::usuariosA(){
    this->raiz = NULL;
}

#pragma endregion

#pragma region Métodos

void paisNA::insertarPais(int codPais){
    if(codPais>this->codPais){
        if(hijoDer==NULL){
            hijoDer = new paisNA(codPais);
        }else{
            hijoDer->insertarPais(codPais);
        }
    }
    if(codPais<this->codPais){
        if(hijoIzq==NULL){
            hijoIzq = new paisNA(codPais);
        }else{
            hijoIzq->insertarPais(codPais);
        }
    }
}

void paisNA::mostrarHabitacionesReservadas(){
    hoteles.mostrarReservaciones();
    if(hijoIzq!=NULL){
        hijoIzq->mostrarHabitacionesReservadas();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarHabitacionesReservadas();
    }
}

void paisNA::mostrarCarrosReservados(){
    agencias.mostrarReservaciones();
    if(hijoIzq!=NULL){
        hijoIzq->mostrarCarrosReservados();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarCarrosReservados();
    }
}

void hotelNA::insertarHotel(int codPais, int codHotel, string nombre, int cantEstrellas){
    if(codHotel>this->codHotel){
        if(hijoDer==NULL){
            hijoDer = new hotelNA(codPais,codHotel,nombre,cantEstrellas);
        }else{
            hijoDer->insertarHotel(codPais,codHotel,nombre,cantEstrellas);
        }
    }
    if(codHotel<this->codHotel){
        if(hijoIzq==NULL){
            hijoIzq = new hotelNA(codPais,codHotel,nombre,cantEstrellas);
        }else{
            hijoIzq->insertarHotel(codPais,codHotel,nombre,cantEstrellas);
        }
    }
}

void hotelNA::muestraDatosHotel(){
    blanco();
    cout << "Codigo: " << codHotel << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Cantidad de estrellas: " <<  cantEstrellas << endl;
    gris();cout << "--------------------------------------------------" << endl << endl;
}

void hotelNA::muestraDetalladaHotel(){
    muestraDatosHotel();
    if(hijoIzq!=NULL){
        hijoIzq->muestraDetalladaHotel();
    }
    if(hijoDer!=NULL){
        hijoDer->muestraDetalladaHotel();
    }
}

void hotelNA::reservarHotel(){
    this->pisos.reservarPisos();
}

void hotelNA::mostrarReservaciones(){
    pisos.mostrarReservaciones();
    if(this->hijoIzq!=NULL){
        this->hijoIzq->mostrarReservaciones();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->mostrarReservaciones();
    }
}

void pisoNA::insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs){
    if(numPiso>this->numPiso){
        if(hijoDer==NULL){
            hijoDer = new pisoNA(codPais,codHotel,numPiso,nombre,cantHabs);
        }else{
            hijoDer->insertarPiso(codPais,codHotel,numPiso,nombre,cantHabs);
        }
    }
    if(numPiso<this->numPiso){
        if(hijoIzq==NULL){
            hijoIzq = new pisoNA(codPais,codHotel,numPiso,nombre,cantHabs);
        }else{
            hijoIzq->insertarPiso(codPais,codHotel,numPiso,nombre,cantHabs);
        }
    }
}

void pisoNA::muestraDatosPiso(){
    blanco();
    cout << "Numero de piso: " << numPiso << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Cantidad de habitaciones: " << cantHabs << endl;
    gris(); cout << "--------------------------------------------------" << endl << endl;
}

void pisoNA::muestraDetalladaPiso(){
    muestraDatosPiso();
    if(hijoIzq!=NULL){
        hijoIzq->muestraDetalladaPiso();
    }
    if(hijoDer!=NULL){
        hijoDer->muestraDetalladaPiso();
    }
}

void pisoNA::reservarPiso(){
    this->habitaciones.reservarHabitaciones();
    if(this->hijoIzq!=NULL){
        this->hijoIzq->reservarPiso();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->reservarPiso();
    }
}

void pisoNA::mostrarReservaciones(){
    habitaciones.mostrarReservaciones();
    if(hijoIzq!=NULL){
        hijoIzq->mostrarReservaciones();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarReservaciones();
    }
}

void habitacionNA::insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab){
    if(codHab>this->codHab){
        if(hijoDer==NULL){
            hijoDer = new habitacionNA(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
        }else{
            hijoDer->insertarHabitacion(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
        }
    }
    if(codHab<this->codHab){
        if(hijoIzq==NULL){
            hijoIzq = new habitacionNA(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
        }else{
            hijoIzq->insertarHabitacion(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
        }
    }
}

void habitacionNA::mostrarDatosHabitacion(){
    blanco();
    cout << "Codigo de habitacion: " << codHab << endl;
    cout << "Tipo de cuarto: " << tipoCuarto << endl;
    cout << "Numero de camas: " << numCamas << endl;
    cout << "Precio de habitacion: " << precioHab << endl;
    cout << "Estado de habitacion: " << estadoHab << " (";
    if(estadoHab=="L") cout << "Libre";
    if(estadoHab=="R") cout << "Reservado";
    if(estadoHab=="O") cout << "Ocupado";
    cout << ")" << endl;
    gris();cout << "--------------------------------------------------" << endl << endl;
}

void habitacionNA::muestraDetalladaHabitacion(){
    mostrarDatosHabitacion();
    if(hijoIzq!=NULL){
        hijoIzq->muestraDetalladaHabitacion();
    }
    if(hijoDer!=NULL){
        hijoDer->muestraDetalladaHabitacion();
    }
}

void habitacionNA::reservarHabitacion(){
    this->estadoHab = "R";
    if(this->hijoIzq!=NULL){
        this->hijoIzq->reservarHabitacion();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->reservarHabitacion();
    }
}

void habitacionNA::mostrarReservaciones(){
    if(estadoHab=="R"){
        blanco(); cout << "Codigo de pais: " << codPais << endl << "Codigo de Hotel: " << codHotel << endl << "Numero de piso: " << numPiso << endl;
        mostrarDatosHabitacion(); azul();
    }
    if(hijoIzq!=NULL){
        hijoIzq->mostrarReservaciones();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarReservaciones();
    }
}

void agenciaNA::insertarAgencia(int codPais,int idAgencia,string nombre,int cantVehs){
    if(idAgencia>this->idAgencia){
        if(hijoDer==NULL){
            hijoDer = new agenciaNA(codPais, idAgencia, nombre, cantVehs);
        }else{
            hijoDer->insertarAgencia(codPais, idAgencia, nombre, cantVehs);
        }
    }
    if(idAgencia<this->idAgencia){
        if(hijoIzq==NULL){
            hijoIzq = new agenciaNA(codPais, idAgencia, nombre, cantVehs);
        }else{
            hijoIzq->insertarAgencia(codPais, idAgencia, nombre, cantVehs);
        }
    }
}

void agenciaNA::insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo){
    tiposFlotilla.insertarTipoFlotilla(codPais,idAgencia,codTipo,nombre,cantCarrosTipo);
}

void agenciaNA::modificarDatoAgencia(string dato, int opcion){
    if(opcion==1){
        this->nombre = dato;
    }
    if(opcion==2){
        this->cantVehs = StrToNum(dato);
    }
}

void agenciaNA::muestraDatosAgencia(){
    blanco();
    cout << endl << "Identificacion: " << this->idAgencia << endl;
    cout << "Nombre: " << this->nombre << endl;
    cout << "Cantidad de Vehiculos: " << this->cantVehs << endl;
    gris(); cout << "--------------------------------------------------" << endl;
}

void agenciaNA::muestraDetalladaAgencia(){
    muestraDatosAgencia();
    if(this->hijoIzq!=NULL){
        this->hijoIzq->muestraDetalladaAgencia();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->muestraDetalladaAgencia();
    }
}

void agenciaNA::reservarAgencia(){
    this->tiposFlotilla.reservarTiposFlotilla();
}

void agenciaNA::mostrarReservaciones(){
    tiposFlotilla.mostrarReservaciones();
    if(hijoIzq!=NULL){
        hijoIzq->mostrarReservaciones();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarReservaciones();
    }
}

void tipoFlotillaNA::insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo){
    if(codTipo>this->codTipo){
        if(hijoDer==NULL){
            hijoDer = new tipoFlotillaNA(codPais, idAgencia, codTipo, nombre, cantCarrosTipo);
        }else{
            hijoDer->insertarTipoFlotilla(codPais, idAgencia, codTipo, nombre, cantCarrosTipo);
        }
    }
    if(codTipo<this->codTipo){
        if(hijoIzq==NULL){
            hijoIzq = new tipoFlotillaNA(codPais, idAgencia, codTipo, nombre, cantCarrosTipo);
        }else{
            hijoIzq->insertarTipoFlotilla(codPais, idAgencia, codTipo, nombre, cantCarrosTipo);
        }
    }
}

void tipoFlotillaNA::insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado){
    carros.insertarCarro(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
}

void tipoFlotillaNA::modificarDatoTipoFlotilla(string dato, int opcion){
    if(opcion==1){
        this->nombre = dato;
    }
    if(opcion==2){
        this->cantCarrosTipo = StrToNum(dato);
    }
}

void tipoFlotillaNA::muestraDatosTipoFlotilla(){
    blanco();
    cout << "Codigo de tipo: " << this->codTipo << endl;
    cout << "Nombre: " << this->nombre << endl;
    cout << "Cantidad de carros: " << this->cantCarrosTipo << endl;
    gris(); cout << "--------------------------------------------------" << endl << endl;
}

void tipoFlotillaNA::muestraDetalladaTipoFlotilla(){
    muestraDatosTipoFlotilla();
    if(this->hijoIzq!=NULL){
        this->hijoIzq->muestraDatosTipoFlotilla();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->muestraDatosTipoFlotilla();
    }
}

void tipoFlotillaNA::reservarTipoFlotilla(){
    this->carros.reservarCarros();
    if(this->hijoIzq!=NULL){
        this->hijoIzq->reservarTipoFlotilla();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->reservarTipoFlotilla();
    }
}

void tipoFlotillaNA::mostrarReservaciones(){
    carros.mostrarReservaciones();
    if(hijoIzq!=NULL){
        hijoIzq->mostrarReservaciones();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarReservaciones();
    }
}

void carroNA::insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado){
    if(placa>this->placa){
        if(hijoDer==NULL){
            hijoDer = new carroNA(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
        }else{
            hijoDer->insertarCarro(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
        }
    }
    if(placa<this->placa){
        if(hijoIzq==NULL){
            hijoIzq = new carroNA(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
        }else{
            hijoIzq->insertarCarro(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
        }
    }
}

void carroNA::modificarDatoCarro(string dato, int opcion){
    if(opcion==1){
        this->numAsientos = StrToNum(dato);
    }
    if(opcion==2){
        this->precio = StrToNum(dato);
    }
    if(opcion==3){
        this->estado = dato;
    }
}

void carroNA::mostrarDatosCarro(){
    blanco();
    cout << "Placa: " << this->placa << endl;
    cout << "Modelo: " << this->modelo << endl;
    cout << "Numero de asientos: " << this->numAsientos << endl;
    cout << "Año: " << this->anno << endl;
    cout << "Precio del carro: " << this->precio << endl;
    cout << "Estado del carro: " << this->estado << " (";
    if(this->estado=="L") cout << "Libre";
    if(this->estado=="R") cout << "Reservado";
    if(this->estado=="O") cout << "Ocupado";
    cout << ")" << endl;
    gris(); cout << "-------------------------" << endl;
}

void carroNA::muestraDetalladaCarro(){
    mostrarDatosCarro();
    if(this->hijoIzq!=NULL){
        this->hijoIzq->muestraDetalladaCarro();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->muestraDetalladaCarro();
    }
}

void carroNA::mostrarDatoCarro(int opcion){
    gris(); cout << endl << "------------------------------" << endl; blanco();
    if(opcion==1) cout << "Modelo: " << this->modelo << endl;
    if(opcion==2) cout << "Año: " << this->anno << endl;
    if(opcion==3) cout << "Cantidad de asientos: " << this->numAsientos << endl;
    if(opcion==4) cout << "Precio: " << this->precio << endl;
    if(opcion==5){
        cout << "Estado: " << this->estado << " (";
        if(this->estado=="L") cout << "Libre";
        if(this->estado=="R") cout << "Reservado";
        if(this->estado=="O") cout << "Ocupado";
        cout << ")" << endl;
    }
    gris();cout << "------------------------------" << endl; azul();
}

string carroNA::obtenerEstadoCarro(){
    return estado; 
}

void carroNA::reservarCarro(){
    this->estado = "R";
    if(this->hijoIzq!=NULL){
        this->hijoIzq->reservarCarro();
    }
    if(this->hijoDer!=NULL){
        this->hijoDer->reservarCarro();
    }
}

void carroNA::mostrarRerservaciones(){
    if(estado=="R"){
        blanco(); cout << "Codigo de pais: " << codPais << endl << "Identificacion de agencia: " << idAgencia << endl << "Codigo de tipo de flotilla: " << codTipo << endl;
        mostrarDatosCarro(); azul();
    }
    if(hijoIzq!=NULL){
        hijoIzq->mostrarRerservaciones();
    }
    if(hijoDer!=NULL){
        hijoDer->mostrarRerservaciones();
    }
}

void adminHotelNA::insertarAdminHotel(int codigo, string nombre){
    if(codigo>this->codigo){
        if(hijoDer==NULL){
            hijoDer = new adminHotelNA(codigo,nombre);
        }else{
            hijoDer->insertarAdminHotel(codigo,nombre);
        }
    }
    if(codigo<this->codigo){
        if(hijoIzq==NULL){
            hijoIzq = new adminHotelNA(codigo,nombre);
        }else{
            hijoIzq->insertarAdminHotel(codigo,nombre);
        }
    }
}

void adminAgenciaNA::insertarAdminAgencia(int codigo, string nombre){
    if(codigo>this->codigo){
        if(hijoDer==NULL){
            hijoDer = new adminAgenciaNA(codigo,nombre);
        }else{
            hijoDer->insertarAdminAgencia(codigo,nombre);
        }
    }
    if(codigo<this->codigo){
        if(hijoIzq==NULL){
            hijoIzq = new adminAgenciaNA(codigo,nombre);
        }else{
            hijoIzq->insertarAdminAgencia(codigo,nombre);
        }
    }
}

void usuarioNA::insertarUsuario(int pasaporte, string nombre){
    if(pasaporte>this->pasaporte){
        if(hijoDer==NULL){
            hijoDer = new usuarioNA(pasaporte,nombre);
        }else{
            hijoDer->insertarUsuario(pasaporte,nombre);
        }
    }
    if(pasaporte<this->pasaporte){
        if(hijoIzq==NULL){
            hijoIzq = new usuarioNA(pasaporte,nombre);
        }else{
            hijoIzq->insertarUsuario(pasaporte,nombre);
        }
    }
}

void paisesA::insertarPais(int codPais){
    if(raiz==NULL){
        raiz = new paisNA(codPais);
    }else{
        raiz->insertarPais(codPais);
    }
}

ppaisNA paisesA::obtenerPaisCodigo(int codPais){
    ppaisNA temp = raiz;
    while(temp!=NULL){
        if(codPais==temp->codPais){
            break;
        }
        else if(codPais<temp->codPais){
            temp = temp->hijoIzq;
        }
        else if(codPais>temp->codPais){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

photelNA paisesA::obtenerHotelCodigo(int codPais, int codHotel){
    return obtenerPaisCodigo(codPais)->hoteles.obtenerHotelCodigo(codHotel);
}

ppisoNA paisesA::obtenerPisoNum(int codPais, int codHotel, int numPiso){
    return obtenerPaisCodigo(codPais)->hoteles.obtenerPisoNum(codHotel, numPiso);
}

phabitacionNA paisesA::obtenerHabitacionCod(int codPais, int codHotel, int numPiso, int codHab){
    return obtenerPaisCodigo(codPais)->hoteles.obtenerHabitacionCod(codHotel, numPiso, codHab);
}

void paisesA::insertarHotel(int codPais, int codHotel, string nombre, int cantEstrellas){
    if(obtenerHotelCodigo(codPais,codHotel)==NULL){
        ultimoHotel = to_string(codPais)+"|"+to_string(codHotel);
    }
    obtenerPaisCodigo(codPais)->hoteles.insertarHotel(codPais, codHotel, nombre, cantEstrellas);
}

void paisesA::insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs){
    if(obtenerPisoNum(codPais,codHotel,numPiso)==NULL){
        ultimoPiso = to_string(codPais)+"|"+to_string(codHotel)+"|"+to_string(numPiso);
    }
    obtenerPaisCodigo(codPais)->hoteles.insertarPiso(codPais,codHotel,numPiso,nombre,cantHabs);
}

void paisesA::insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab){
    if(obtenerHabitacionCod(codPais,codHotel,numPiso,codHab)==NULL){
        ultimaHab = to_string(codPais)+"|"+to_string(codHotel)+"|"+to_string(numPiso)+"|"+to_string(codHab);
    }
    obtenerPaisCodigo(codPais)->hoteles.insertarHabitacion(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
}

listaSimple paisesA::obtenerDatosHotel(int codPais, int codHotel){
    return obtenerPaisCodigo(codPais)->hoteles.obtenerDatos(codHotel);
}

void paisesA::modificarDatoHotel(int codPais, int codHotel, string dato, int opcion){
    obtenerPaisCodigo(codPais)->hoteles.modificarDato(codHotel,dato,opcion);
}

listaSimple paisesA::obtenerDatosPiso(int codPais, int codHotel, int numPiso){
    return obtenerPaisCodigo(codPais)->hoteles.obtenerDatosPiso(codHotel,numPiso);
}

void paisesA::modificarDatoPiso(int codPais, int codHotel, int numPiso, string dato, int opcion){
    obtenerPaisCodigo(codPais)->hoteles.modificarDatoPiso(codHotel,numPiso,dato,opcion);
}

listaSimple paisesA::obtenerDatosHabitacion(int codPais, int codHotel, int numPiso, int codHab){
    return obtenerPaisCodigo(codPais)->hoteles.obtenerDatosHabitacion(codHotel,numPiso,codHab);
}

void paisesA::modificarDatoHabitacion(int codPais, int codHotel, int numPiso, int codHab, string dato, int opcion){
    obtenerPaisCodigo(codPais)->hoteles.modificarDatoHabitacion(codHotel,numPiso,codHab,dato,opcion);
}

void paisesA::muestraDetalladaHoteles(int codPais){
    obtenerPaisCodigo(codPais)->hoteles.muestraDetalladaHoteles();
}

void paisesA::muestraDetalladaPisos(int codPais, int codHotel){
    obtenerPaisCodigo(codPais)->hoteles.muestraDetalladaPisos(codHotel);
}

void paisesA::muestraDetalladaHabitaciones(int codPais, int codHotel, int numPiso){
    obtenerPaisCodigo(codPais)->hoteles.muestraDetalladaHabitaciones(codHotel,numPiso);
}

void paisesA::mostrarUltimoHotel(){
    if(ultimoHotel!=""){
        listaSimple ids = dividirString(ultimoHotel,"|");
        blanco();
        cout << endl << "Codigo de pais: " << ids.obtenerValorPos(1) << endl;
        obtenerHotelCodigo(StrToNum(ids.obtenerValorPos(1)),StrToNum(ids.obtenerValorPos(2)))->muestraDatosHotel();
    }else{
        rosado(); cout << "No hay hoteles registrados" << endl;
    }
    azul();
}

void paisesA::mostrarUltimoPiso(){
    if(ultimoPiso!=""){
        listaSimple ids = dividirString(ultimoPiso,"|");
        blanco();
        cout << endl << "Codigo de pais: " << ids.obtenerValorPos(1) << endl << "Codigo de hotel: " << ids.obtenerValorPos(2) << endl;
        obtenerPisoNum(StrToNum(ids.obtenerValorPos(1)),StrToNum(ids.obtenerValorPos(2)),StrToNum(ids.obtenerValorPos(3)))->muestraDatosPiso();
    }else{
        rosado(); cout << "No hay pisos ingresados" << endl;
    }
    azul();
}

void paisesA::mostrarUltimaHab(){
    if(ultimaHab!=""){
        listaSimple ids = dividirString(ultimaHab,"|");
        blanco();
        cout << endl << "Codigo de pais: " << ids.obtenerValorPos(1) << endl << "Codigo de hotel: " << ids.obtenerValorPos(2) << endl << "Numero de piso: " << ids.obtenerValorPos(3) << endl;
        obtenerHabitacionCod(StrToNum(ids.obtenerValorPos(1)),StrToNum(ids.obtenerValorPos(2)),StrToNum(ids.obtenerValorPos(3)),StrToNum(ids.obtenerValorPos(4)))->mostrarDatosHabitacion();
    }else{
        rosado(); cout << "No hay habitaciones registradas" << endl;
    }
    azul();
}

pagenciaNA paisesA::obtenerAgenciaId(int codPais,int idAgencia){
    return obtenerPaisCodigo(codPais)->agencias.obtenerAgenciaId(idAgencia);
}

ptipoFlotillaNA paisesA::obtenerTipoFlotillaCod(int codPais, int idAgencia, int codTipo){
    return obtenerPaisCodigo(codPais)->agencias.obtenerTipoFlotillaCod(idAgencia,codTipo);
}

pcarroNA paisesA::obtenerCarroPlaca(int codPais, int idAgencia, int codTipo, int placa){
    return obtenerPaisCodigo(codPais)->agencias.obtenerCarroPlaca(idAgencia,codTipo,placa);
}

void paisesA::insertarAgencia(int codPais,int idAgencia,string nombre,int cantVehs){
    if(obtenerAgenciaId(codPais,idAgencia)==NULL){
        ultimaAgencia = to_string(codPais)+"|"+to_string(idAgencia);
    }
    obtenerPaisCodigo(codPais)->agencias.insertarAgencia(codPais,idAgencia,nombre,cantVehs);
}

void paisesA::insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo){
    if(obtenerTipoFlotillaCod(codPais,idAgencia,codTipo)==NULL){
        ultimoTipoFlotilla = to_string(codPais)+"|"+to_string(idAgencia)+"|"+to_string(codTipo);
    }
    obtenerAgenciaId(codPais,idAgencia)->insertarTipoFlotilla(codPais,idAgencia,codTipo,nombre,cantCarrosTipo);
}

void paisesA::insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado){
    if(obtenerCarroPlaca(codPais,idAgencia,codTipo,placa)==NULL){
        ultimoCarro = to_string(codPais)+"|"+to_string(idAgencia)+"|"+to_string(codTipo)+"|"+to_string(placa);
    }
    obtenerTipoFlotillaCod(codPais,idAgencia,codTipo)->insertarCarro(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
}

void paisesA::modificarDatoAgencia(int codPais, int idAgencia, string dato, int opcion){
    obtenerAgenciaId(codPais,idAgencia)->modificarDatoAgencia(dato,opcion);
}

void paisesA::modificarDatoTipoFlotilla(int codPais, int idAgencia, int codTipo, string dato, int opcion){
    obtenerTipoFlotillaCod(codPais,idAgencia,codTipo)->modificarDatoTipoFlotilla(dato,opcion);
}

void paisesA::modificarDatoCarro(int codPais, int idAgencia, int codTipo, int placa, string dato, int opcion){
    obtenerCarroPlaca(codPais,idAgencia,codTipo,placa)->modificarDatoCarro(dato,opcion);
}

void paisesA::muestraDetalladaAgencias(int codPais){
    obtenerPaisCodigo(codPais)->agencias.muestraDetalladaAgencias();
}

void paisesA::muestraDetalladaTiposFlotilla(int codPais, int idAgencia){
    obtenerPaisCodigo(codPais)->agencias.muestraDetalladaTiposFlotilla(idAgencia);
}

void paisesA::muestraDetalladaCarros(int codPais, int idAgencia, int codTipo){
    obtenerPaisCodigo(codPais)->agencias.muestraDetalladaCarros(idAgencia,codTipo);
}

void paisesA::mostrarDatoCarro(int codPais, int idAgencia, int codTipo, int placa, int opcion){
    obtenerCarroPlaca(codPais,idAgencia,codTipo,placa)->mostrarDatoCarro(opcion);
}

void paisesA::mostrarUltimaAgencia(){
    if(ultimaAgencia!=""){
        listaSimple ids = dividirString(ultimaAgencia,"|");
        blanco();
        cout << endl << "Codigo de pais: " << ids.obtenerValorPos(1);
        obtenerAgenciaId(StrToNum(ids.obtenerValorPos(1)),StrToNum(ids.obtenerValorPos(2)))->muestraDatosAgencia(); cout << endl;
    }else{
        rosado(); cout << "No hay agencias registradas" << endl;
    }
    azul();
}

void paisesA::mostrarUltimoTipoFlotilla(){
    if(ultimoTipoFlotilla!=""){
        listaSimple ids = dividirString(ultimoTipoFlotilla,"|");
        blanco();
        cout << endl << "Identificacion de agencia " << ids.obtenerValorPos(1) << ", codigo de pais: " << ids.obtenerValorPos(2) << endl;
        obtenerTipoFlotillaCod(StrToNum(ids.obtenerValorPos(1)),StrToNum(ids.obtenerValorPos(2)),StrToNum(ids.obtenerValorPos(3)))->muestraDatosTipoFlotilla(); cout << endl;
    }else{
        rosado(); cout << "No hay tipos de flotilla registrados" << endl;
    }
    azul();
}

void paisesA::mostrarUltimoCarro(){
    if(ultimoCarro!=""){
        listaSimple ids = dividirString(ultimoCarro,"|");
        blanco();
        cout << endl << "Codigo de tipo de flotilla " << ids.obtenerValorPos(1) << ", identificacion de agencia " << ids.obtenerValorPos(2) << ", codigo de pais: " << ids.obtenerValorPos(3) << endl;
        obtenerCarroPlaca(StrToNum(ids.obtenerValorPos(1)),StrToNum(ids.obtenerValorPos(2)),StrToNum(ids.obtenerValorPos(3)),StrToNum(ids.obtenerValorPos(4)))->mostrarDatosCarro(); cout << endl;
    }else{
        rosado(); cout << "No day carros registrados" << endl;
    }
    azul();
}

void paisesA::mostrarHabitacionesReservadas(){
    celeste(); cout << endl << "Habitaciones reservadas:" << endl << endl;
    if(raiz!=NULL){
        raiz->mostrarHabitacionesReservadas();
    }
}

void paisesA::mostrarCarrosReservados(){
    celeste(); cout << endl << "Carros reservados: " << endl << endl; azul();
    if(raiz!=NULL){
        raiz->mostrarCarrosReservados();
    }
    cout << endl;
}

void hotelesA::insertarHotel(int codPais, int codHotel, string nombre, int cantEstrellas){
    if(raiz==NULL){
        raiz = new hotelNA(codPais, codHotel, nombre, cantEstrellas);
    }else{
        raiz->insertarHotel(codPais, codHotel, nombre, cantEstrellas);
    }
}

photelNA hotelesA::obtenerHotelCodigo(int codigo){
    photelNA temp = raiz;
    while(temp!=NULL){
        if(codigo==temp->codHotel){
            break;
        }
        else if(codigo<temp->codHotel){
            temp = temp->hijoIzq;
        }
        else if(codigo>temp->codHotel){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

ppisoNA hotelesA::obtenerPisoNum(int codHotel, int numPiso){
    return obtenerHotelCodigo(codHotel)->pisos.obtenerPisoNum(numPiso);
}

phabitacionNA hotelesA::obtenerHabitacionCod(int codHotel, int numPiso, int codHab){
    return obtenerHotelCodigo(codHotel)->pisos.obtenerHabitacionCod(numPiso, codHab);
}

void hotelesA::insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs){
    obtenerHotelCodigo(codHotel)->pisos.insertarPiso(codPais,codHotel,numPiso,nombre,cantHabs);
}

void hotelesA::insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab){
    obtenerHotelCodigo(codHotel)->pisos.insertarHabitacion(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
}

listaSimple hotelesA::obtenerDatos(int codPais){
    photelNA hotel = obtenerHotelCodigo(codPais);
    listaSimple res;
    res.insertarFinal(to_string(hotel->codPais));
    res.insertarFinal(to_string(hotel->codHotel));
    res.insertarFinal(hotel->nombre);
    res.insertarFinal(to_string(hotel->cantEstrellas));
    return res;
}

void hotelesA::modificarDato(int codHotel, string dato, int opcion){
    photelNA hotel = obtenerHotelCodigo(codHotel);
    if(opcion==1){
        hotel->nombre = dato;
    }
    if(opcion==2){
        hotel->cantEstrellas = StrToNum(dato);
    }
}

listaSimple hotelesA::obtenerDatosPiso(int codHotel,int numPiso){
    return obtenerHotelCodigo(codHotel)->pisos.obtenerDatos(numPiso);
}

void hotelesA::modificarDatoPiso(int codHotel, int numPiso, string dato, int opcion){
    obtenerHotelCodigo(codHotel)->pisos.modificarDato(numPiso,dato,opcion);
}

listaSimple hotelesA::obtenerDatosHabitacion(int codHotel, int numPiso, int codHab){
    return obtenerHotelCodigo(codHotel)->pisos.obtenerDatosHabitacion(numPiso,codHab);
}

void hotelesA::modificarDatoHabitacion(int codHotel, int numPiso, int codHab, string dato, int opcion){
    obtenerHotelCodigo(codHotel)->pisos.modificarDatoHabitacion(numPiso,codHab,dato,opcion);
}

void hotelesA::muestraDetalladaHoteles(){
    if(raiz!=NULL){
        celeste(); cout << endl << "Hoteles de pais " << raiz->codPais << " :" << endl << endl;
        raiz->muestraDetalladaHotel();
    }else{
        rosado(); cout << "No hay hoteles registrados" << endl;
    }
    azul();
}

void hotelesA::muestraDetalladaPisos(int codHotel){
    obtenerHotelCodigo(codHotel)->pisos.muestraDetalladaPisos();
}

void hotelesA::muestraDetalladaHabitaciones(int codHotel, int numPiso){
    obtenerHotelCodigo(codHotel)->pisos.muestraDetalladaHabitaciones(numPiso);
}

void hotelesA::mostrarReservaciones(){
    if(raiz!=NULL){
        raiz->mostrarReservaciones();
    }
}

ppisoNA pisosA::obtenerPisoNum(int numPiso){
    ppisoNA temp = raiz;
    while(temp!=NULL){
        if(numPiso==temp->numPiso){
            break;
        }
        else if(numPiso<temp->numPiso){
            temp = temp->hijoIzq;
        }
        else if(numPiso>temp->numPiso){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

phabitacionNA pisosA::obtenerHabitacionCod(int numPiso, int codHab){
    return obtenerPisoNum(numPiso)->habitaciones.obtenerHabitacionCod(codHab);
}

void pisosA::insertarPiso(int codPais, int codHotel, int numPiso, string nombre, int cantHabs){
    if(raiz==NULL){
        raiz = new pisoNA(codPais,codHotel,numPiso,nombre,cantHabs);
    }else{
        raiz->insertarPiso(codPais,codHotel,numPiso,nombre,cantHabs);
    }
}

void pisosA::insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab){
    obtenerPisoNum(numPiso)->habitaciones.insertarHabitacion(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
}

listaSimple pisosA::obtenerDatos(int numPiso){
    ppisoNA piso = obtenerPisoNum(numPiso);
    listaSimple res;
    res.insertarFinal(to_string(piso->codPais));
    res.insertarFinal(to_string(piso->codHotel));
    res.insertarFinal(to_string(piso->numPiso));
    res.insertarFinal(piso->nombre);
    res.insertarFinal(to_string(piso->cantHabs));
    return res;
}

void pisosA::modificarDato(int numPiso, string dato, int opcion){
    ppisoNA piso = obtenerPisoNum(numPiso);
    if(opcion==1){
        piso->nombre = dato;
    }
    if(opcion==2){
        piso->cantHabs = StrToNum(dato);
    }
}

listaSimple pisosA::obtenerDatosHabitacion(int numPiso, int codHab){
    return obtenerPisoNum(numPiso)->habitaciones.obtenerDatos(codHab);
}

void pisosA::modificarDatoHabitacion(int numPiso, int codHab, string dato, int opcion){
    obtenerPisoNum(numPiso)->habitaciones.modificarDato(codHab,dato,opcion);
}

void pisosA::muestraDetalladaPisos(){
    if(raiz!=NULL){
        celeste(); cout << endl << "Pisos de hotel " << raiz->codHotel << " de pais " << raiz->codPais << " :" << endl << endl;
        raiz->muestraDetalladaPiso();
    }else{
        rosado(); cout << "No hay pisos registrados" << endl;
    }
    azul();
}

void pisosA::muestraDetalladaHabitaciones(int numPiso){
    obtenerPisoNum(numPiso)->habitaciones.muestraDetalladaHabitaciones();
}

void pisosA::reservarPisos(){
    if(raiz!=NULL){
        raiz->reservarPiso();
    }
}

void pisosA::mostrarReservaciones(){
    if(raiz!=NULL){
        raiz->mostrarReservaciones();
    }
}

phabitacionNA habitacionesA::obtenerHabitacionCod(int codHab){
    phabitacionNA temp = raiz;
    while(temp!=NULL){
        if(codHab==temp->codHab){
            break;
        }
        else if(codHab<temp->codHab){
            temp = temp->hijoIzq;
        }
        else if(codHab>temp->codHab){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

void habitacionesA::insertarHabitacion(int codPais, int codHotel, int numPiso, int codHab, string tipoCuarto, int numCamas, int precioHab, string estadoHab){
    if(raiz==NULL){
        raiz = new habitacionNA(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
    }else{
        raiz->insertarHabitacion(codPais, codHotel, numPiso, codHab, tipoCuarto, numCamas, precioHab, estadoHab);
    }
}

listaSimple habitacionesA::obtenerDatos(int codHab){
    listaSimple res;
    phabitacionNA habitacion = obtenerHabitacionCod(codHab);
    res.insertarFinal(to_string(habitacion->codPais));
    res.insertarFinal(to_string(habitacion->codHotel));
    res.insertarFinal(to_string(habitacion->numPiso));
    res.insertarFinal(to_string(habitacion->codHab));
    res.insertarFinal(habitacion->tipoCuarto);
    res.insertarFinal(to_string(habitacion->numCamas));
    res.insertarFinal(to_string(habitacion->precioHab));
    res.insertarFinal(habitacion->estadoHab);
    return res;
}

void habitacionesA::modificarDato(int codHab,string dato,int opcion){
    phabitacionNA habitacion = obtenerHabitacionCod(codHab);
    if(opcion==1){
        habitacion->tipoCuarto = dato;
    } 
    if(opcion==2){
        habitacion->numCamas = StrToNum(dato);
    }
    if(opcion==3){
        habitacion->precioHab = StrToNum(dato);
    }
    if(opcion==4){
        habitacion->estadoHab = dato;
    }
}

void habitacionesA::muestraDetalladaHabitaciones(){
    if(raiz!=NULL){
        celeste(); cout << endl << "Habitaciones de piso " << raiz->numPiso << " de hotel " << raiz->codHotel << " de pais " << raiz->codPais << " :" << endl << endl;
        raiz->muestraDetalladaHabitacion();
    }else{
        rosado(); cout << "No hay habitaciones registradas" << endl;
    }
    azul();
}

void habitacionesA::reservarHabitaciones(){
    if(raiz!=NULL){
        raiz->reservarHabitacion();
    }
}

void habitacionesA::mostrarReservaciones(){
    if(raiz!=NULL){
        raiz->mostrarReservaciones();
    }
}

pagenciaNA agenciasA::obtenerAgenciaId(int idAgencia){
    pagenciaNA temp = raiz;
    while(temp!=NULL){
        if(idAgencia==temp->idAgencia){
            break;
        }
        else if(idAgencia<temp->idAgencia){
            temp = temp->hijoIzq;
        }
        else if(idAgencia>temp->idAgencia){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

ptipoFlotillaNA agenciasA::obtenerTipoFlotillaCod(int idAgencia,int codTipo){
    return obtenerAgenciaId(idAgencia)->tiposFlotilla.obtenerTipoFlotillaCod(codTipo);
}

pcarroNA agenciasA::obtenerCarroPlaca(int idAgencia, int codTipo, int placa){
    return obtenerAgenciaId(idAgencia)->tiposFlotilla.obtenerCarroPlaca(codTipo,placa);
}

void agenciasA::insertarAgencia(int codPais,int idAgencia,string nombre,int cantVehs){
    if(raiz==NULL){
        raiz = new agenciaNA(codPais, idAgencia, nombre, cantVehs);
    }else{
        raiz->insertarAgencia(codPais, idAgencia, nombre, cantVehs);
    }
}

void agenciasA::muestraDetalladaAgencias(){
    if(raiz!=NULL){
        celeste(); cout << endl << "Agencias de pais " << raiz->codPais << " :" << endl;
        raiz->muestraDetalladaAgencia();
        cout << endl;
    }else{
        rosado(); cout << "No hay agencias registradas" << endl;
    }
    azul();
}

void agenciasA::muestraDetalladaTiposFlotilla(int idAgencia){
    obtenerAgenciaId(idAgencia)->tiposFlotilla.muestraDetalladaTiposFlotilla();
}

void agenciasA::muestraDetalladaCarros(int idAgencia, int codTipo){
    obtenerAgenciaId(idAgencia)->tiposFlotilla.muestraDetalladaCarros(codTipo);
}

void agenciasA::mostrarReservaciones(){
    if(raiz!=NULL){
        raiz->mostrarReservaciones();
    }
}

pcarroNA tiposFlotillaA::obtenerCarroPlaca(int codTipo,int placa){
    return obtenerTipoFlotillaCod(codTipo)->carros.obtenerCarroPlaca(placa);
}

ptipoFlotillaNA tiposFlotillaA::obtenerTipoFlotillaCod(int codTipo){
    ptipoFlotillaNA temp = raiz;
    while(temp!=NULL){
        if(codTipo==temp->codTipo){
            break;
        }
        else if(codTipo<temp->codTipo){
            temp = temp->hijoIzq;
        }
        else if(codTipo>temp->codTipo){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

void tiposFlotillaA::insertarTipoFlotilla(int codPais, int idAgencia, int codTipo, string nombre, int cantCarrosTipo){
    if(raiz==NULL){
        raiz = new tipoFlotillaNA(codPais, idAgencia, codTipo, nombre, cantCarrosTipo);
    }else{
        raiz->insertarTipoFlotilla(codPais, idAgencia, codTipo, nombre, cantCarrosTipo);
    }
}

void tiposFlotillaA::muestraDetalladaTiposFlotilla(){
    if(raiz!=NULL){
        celeste(); cout << endl << "Tipos de flotilla de agencia " << raiz->idAgencia << " de pais " << raiz->codPais << " :" << endl << endl;
        raiz->muestraDetalladaTipoFlotilla();
    }else{
        rosado(); cout << "No hay tipos de flotilla registrados" << endl;
    }
    azul();
}

void tiposFlotillaA::muestraDetalladaCarros(int codTipo){
    obtenerTipoFlotillaCod(codTipo)->carros.muestraDetalladaCarros();
}

void tiposFlotillaA::reservarTiposFlotilla(){
    if(raiz!=NULL){
        raiz->reservarTipoFlotilla();
    }
}

void tiposFlotillaA::mostrarReservaciones(){
    if(raiz!=NULL){
        raiz->mostrarReservaciones();
    }
}

pcarroNA carrosA::obtenerCarroPlaca(int placa){
    pcarroNA temp = raiz;
    while(temp!=NULL){
        if(placa==temp->placa){
            break;
        }
        else if(placa<temp->placa){
            temp = temp->hijoIzq;
        }
        else if(placa>temp->placa){
            temp = temp->hijoDer;
        }
    }
    return temp;
}

void carrosA::insertarCarro(int codPais,int idAgencia,int codTipo,int placa,string modelo,int numAsientos,int anno,int precio,string estado){
    if(raiz==NULL){
        raiz = new carroNA(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
    }else{
        raiz->insertarCarro(codPais,idAgencia,codTipo,placa,modelo,numAsientos,anno,precio,estado);
    }
}

void carrosA::muestraDetalladaCarros(){
    if(raiz!=NULL){
        celeste(); cout << endl << "Carros de tipos de flotilla " << raiz->codTipo << " de agencia " << raiz->idAgencia << " de pais " << raiz->codPais << " : " << endl << endl;
        raiz->muestraDetalladaCarro();
        cout << endl;
    }else{
        rosado(); cout << "No hay carros registrados" << endl;
    }
    azul();
}

void carrosA::reservarCarros(){
    if(raiz!=NULL){
        raiz->reservarCarro();
    }
}

void carrosA::mostrarReservaciones(){
    if(raiz!=NULL){
        raiz->mostrarRerservaciones();
    }
}

void adminsHotelA::insertarAdminHotel(int codigo, string nombre){
    if(raiz==NULL){
        raiz = new adminHotelNA(codigo, nombre);
    }else{
        raiz->insertarAdminHotel(codigo, nombre);
    }
}

string adminsHotelA::nombreAdminHotel(int codigo){
    padminHotelNA temp = raiz;
    while(temp!=NULL){
        if(codigo<temp->codigo){
            temp = temp->hijoIzq;
        }
        else if(codigo>temp->codigo){
            temp = temp->hijoDer;
        }
        else if(codigo==temp->codigo){
            return temp->nombre;
        }
    }
    return "";
}

claseResultado adminsHotelA::buscarNodo(padminHotelNA clave, padminsHotelPA p, boolean encontrado, int k){
    claseResultado res;
    if(clave->codigo<p->claves[1]->codigo){
        encontrado = false;
        k = 0;
    }else{
        k = p->cuenta;
        while((clave->codigo<p->claves[k]->codigo) && k>1){
            k--;
        }
        encontrado = clave->codigo==p->claves[k]->codigo;
    }
    res.booleano = encontrado;
    res.entero = k;
    return res;
}

void adminsHotelA::inserta(padminHotelNA c1, padminsHotelPA raiz){
    padminHotelNA x;
    padminsHotelPA xr = NULL, p = NULL;
    claseResultado res = empujar(c1, raiz, false, x, xr);
    boolean empujarArriba = res.booleano;
    x = res.padminHotelNA;
    if(empujarArriba){
        padminsHotelPA p = new adminsHotelPA();
        p->cuenta = 1;
        p->claves[1] = x;
        p->ramas[0] = raiz;
        p->ramas[1] = xr;
        raiz = p;
        this->inicio = raiz;
    }
}

claseResultado adminsHotelA::empujar(padminHotelNA c1, padminsHotelPA r, boolean empujaArriba, padminHotelNA mdna, padminsHotelPA xr){
    claseResultado res;
    int k;
    boolean esta = false;
    if(r==NULL){
        empujaArriba = true;
        mdna = c1;
        xr = NULL;
        res.padminHotelNA = mdna;
    }else{
        res = buscarNodo(c1, r, esta, k);
        esta = res.booleano; 
        k = res.entero;
        if(esta){
            cout << "elemento repetido" << endl;
        }else{
            res = empujar(c1, r->ramas[k], empujaArriba, mdna, xr);
            empujaArriba = res.booleano;
            if(empujaArriba){
                if(r->cuenta<max){
                    empujaArriba = false;
                    meterHoja(mdna, xr, r, k);
                }else{
                    empujaArriba = true;
                    dividirNodo(mdna, xr, r, k, mdna, xr);
                }
            }
        }
    }
    res.booleano = empujaArriba;
    return res;
}

void adminsHotelA::meterHoja(padminHotelNA x, padminsHotelPA xDer, padminsHotelPA p, int k){
    for(int i=p->cuenta;i>k+1;i--){
        p->claves[i+1] = p->claves[i];
        p->ramas[i+1] = p->ramas[i]; 
    }
    p->claves[k+1] = x;
    p->ramas[k+1] = xDer;
    p->cuenta++;
}

void adminsHotelA::dividirNodo(padminHotelNA x, padminsHotelPA xDer, padminsHotelPA p, int k, padminHotelNA mda, padminsHotelPA mder){
    int posmda;
    if(k<=min){
        posmda = min;
    }else{
        posmda = min+1;
    }
    mder = new adminsHotelPA();
    for(int i=posmda+1;i<=max;i++){
        mder->claves[i-posmda] = p->claves[i];
        mder->ramas[i-posmda] = p->ramas[i];
    }
    mder->cuenta = max-posmda;
    p->cuenta = posmda;
    if(k<=min){
        meterHoja(x,xDer,p,k);
    }else{
        meterHoja(x,xDer,mder,k-posmda);
    }
    mda = p->claves[p->cuenta];
    mder->ramas[0] = p->ramas[p->cuenta];
    p->cuenta++;
}

void adminsAgenciaA::insertarAdminAgencia(int codigo, string nombre){
    if(raiz==NULL){
        raiz = new adminAgenciaNA(codigo, nombre);
    }else{
        raiz->insertarAdminAgencia(codigo, nombre);
    }
}

string adminsAgenciaA::nombreAdminAgencia(int codigo){
    padminAgenciaNA temp = raiz;
    while(temp!=NULL){
        if(codigo<temp->codigo){
            temp = temp->hijoIzq;
        }
        else if(codigo>temp->codigo){
            temp = temp->hijoDer;
        }
        else if(codigo==temp->codigo){
            return temp->nombre;
        }
    }
    return "";
}

void usuariosA::insertarUsuario(int pasaporte, string nombre){
    if(raiz==NULL){
        raiz = new usuarioNA(pasaporte, nombre);
    }else{
        raiz->insertarUsuario(pasaporte, nombre);
    }
}

string usuariosA::nombreUsuario(int pasaporte){
    pusuarioNA temp = raiz;
    while(temp!=NULL){
        if(pasaporte<temp->pasaporte){
            temp = temp->hijoIzq;
        }
        else if(pasaporte>temp->pasaporte){
            temp = temp->hijoDer;
        }
        else if(pasaporte==temp->pasaporte){
            return temp->nombre;
        }
    }
    return "";
}

#pragma endregion

#endif
