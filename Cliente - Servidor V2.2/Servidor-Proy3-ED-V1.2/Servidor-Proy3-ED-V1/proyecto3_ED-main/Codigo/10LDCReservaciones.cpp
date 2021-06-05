
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/
#include <string>
#include <iostream>
#include "ArbolesBinarios.h"
using namespace std;

void escribirArchivo(string nombreArchivo, string texto){
	ofstream archivo((nombreArchivo+".txt").c_str());
	if(archivo.fail()){
		cout << "No se pudo abrir el archivo " << nombreArchivo << " para limpiar" << endl;
	}else{
		archivo << texto;
	}
	archivo.close();
}


class NodoLDCReservaciones {
   public:
    
    int CodigoPais = -1;
    int Codigo_AH = -1;
    int Codigo_FP = -1;
    int Codigo_CH = -1;
    
    NodoLDCReservaciones(int CP, int CAH, int CFP, int CCH, pnodocarro nodo, string pasaport){
      
      CodigoPais = CP;
      Codigo_AH = CAH;
      Codigo_FP = CFP;
      Codigo_CH = CCH;
      CarRes = nodo;
      HabRes = NULL;
      pasaporte=pasaport;
      codigoReserva="";

      siguiente = NULL;
      anterior =NULL;
    
    }

    NodoLDCReservaciones(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo, string pasaport){
      
      CodigoPais = CP;
      Codigo_AH = CAH;
      Codigo_FP = CFP;
      Codigo_CH = CCH;
      HabRes = nodo;
      CarRes = NULL;
      pasaporte=pasaport;
      codigoReserva="";

      siguiente = NULL;
      anterior =NULL;
    
    }

    NodoLDCReservaciones(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodoH,pnodocarro nodoC, string pasaport){
      
      CodigoPais = CP;
      Codigo_AH = CAH;
      Codigo_FP = CFP;
      Codigo_CH = CCH;
      HabRes = nodoH;
      CarRes=nodoC;
      pasaporte=pasaport;
      codigoReserva="";

      siguiente = NULL;
      anterior =NULL;
    
    }

 private:
    
    string codigoReserva;
    pnodocarro CarRes;
    pnodohabitacion HabRes;
    string pasaporte;
    NodoLDCReservaciones *siguiente;
    NodoLDCReservaciones *anterior;
    friend class LDCReservaciones;
};
typedef NodoLDCReservaciones *pnodoldCReservaciones;

class LDCReservaciones {
   public:
    LDCReservaciones() { primero = NULL; }
    ~LDCReservaciones();
    

    bool ListaVacia() { return primero == NULL; }
    int largoLista();
    void generarCodigoReserva(pnodoldCReservaciones nodoReserva);
    void reservasPendientes(string pasaporte);
    string generarFactura(string codigoReserva);
    string pagarReservacion(string codigoReserva);
    int InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo, string pasaporte);
    int InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodocarro nodo,string pasaporte);
    int InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodocarro nodoC,pnodohabitacion nodoH,string pasaporte);
   
    void cancelarReservacion(string codigo);
    void eliminaciones(int identificacion, int variable);
    int BorrarFinal();
    int BorrarInicio();
    int BorrarPosicion(int pos);
    int BorrarPosicion(pnodoldCReservaciones nodo);
    int BorrarPosicion(pnodocarro nodo);
    int BorrarPosicion(pnodohabitacion nodo);
    void BorrarReservacion(string reservacion);

    string MostrarHotel();
    string MostrarAgencia();
    void Mostrar(int pos);
    string MostrarNodo(pnodoldCReservaciones aux ,pnodocarro nodo);
    string MostrarNodo(pnodoldCReservaciones aux ,pnodohabitacion nodo);
    bool repetido(int valor);
    bool repetido(pnodocarro nodo);
    bool repetido(pnodohabitacion nodo);
    bool existeCodigoR(string valor);

    pnodoldCReservaciones retornarpunteroC(int codigoCarro);
    pnodoldCReservaciones retornarpunteroH(int codigohHbitacion);
    pnodoldCReservaciones retornarpunteroFP(int codigo, int opcion);
    pnodoldCReservaciones retornarpunteroAH(int codigo, int opcion);
    pnodoldCReservaciones retornarpunteroPais(int codigo);
    pnodoldCReservaciones retornarpunteroReserva(string codigo);

    int buscarCodigoPais(int valor);
    pnodoldCReservaciones getNodo(int pos);
    
    int getCodigoPais(int &valor, int pos);
    int getNombre(char *nombre, int pos);

    int setCodigoPais(int valor, int pos);
    int setNombre(char *nombre, int pos);

    int setCodAH(int valor, pnodoldCReservaciones aux);
    int setCodFP(int valor, pnodoldCReservaciones aux);
    int setCodCH(int valor, pnodoldCReservaciones aux);
    int getCodAH(int &valor, pnodoldCReservaciones aux);
    int getCodFP(int &valor, pnodoldCReservaciones aux);
    int getCodCH(int &valor, pnodoldCReservaciones aux);
    int getCodigoPais(int &valor, pnodoldCReservaciones aux);
    int setCodigoPais(int valor, pnodoldCReservaciones aux);

    
   private:
    pnodoldCReservaciones primero;
   
};


LDCReservaciones :: ~LDCReservaciones(){
   pnodoldCReservaciones aux;
   
  while(primero) {

    if (primero->siguiente == primero) { //caso nodo unico
      aux = primero;
      primero= NULL;
      delete aux;
      continue;
    
    }
      aux = primero;
      primero = primero->siguiente;
      primero->anterior=aux->anterior;
      aux->anterior->siguiente=primero;
      delete aux;
   
   }
}

int LDCReservaciones :: largoLista()
{
    int cont=1;

    pnodoldCReservaciones aux = primero;
    if(ListaVacia())
    {
        return 0;
    }
    else
    {
        while(aux->siguiente!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

/*void LDCReservaciones::BorrarReservacionHabitacion(int codHabitacion){
  if (ListaVacia()){
    return;
  }else{
    	pnodoldCReservaciones aux=primero;
    	if(primero->HabRes->getCodHabitacion()==codHabitacion){//primero
    		aux=primero->siguiente;
        aux->anterior=primero->anterior;
    		delete primero;
    		primero=aux;
    		return;
		}
		while(aux->siguiente->HabRes->getCodHabitacion()==codHabitacion){
      aux=aux->siguiente;
    }
		pnodoldCReservaciones temp=aux->siguiente;
    aux->siguiente=aux->siguiente->siguiente;
    aux->siguiente->anterior=aux;
    delete temp;
		
  }
    return;
}*/

void LDCReservaciones::cancelarReservacion(string codigo){
  pnodoldCReservaciones nodo = retornarpunteroReserva(codigo);
  if(nodo->CarRes==NULL){
    nodo->HabRes->setEstadoHabitacion('L');
  }
  else if(nodo->HabRes==NULL){
    nodo->CarRes->setEstadodelCarro('L');
  }else if(nodo->CarRes!=NULL && nodo->HabRes!=NULL){
    nodo->HabRes->setEstadoHabitacion('L');
    nodo->CarRes->setEstadodelCarro('L');
  }
  BorrarPosicion(nodo);
}

bool LDCReservaciones::existeCodigoR(string valor){
  pnodoldCReservaciones aux = primero;

  if (aux == NULL){ //no hay nodo
    return false;

  } else if (aux->siguiente == primero){ //caso nodo unico
    
    if (valor == aux->codigoReserva){
      return true;
    }
    return false;

  }
  if (valor == aux->codigoReserva){ //evalua al primer nodo
    return true;
  }

  aux = aux->siguiente;

  while (aux != primero){ //2° nodo >> en adelante
    if (valor == aux->codigoReserva){
      return true;

    }
    aux = aux->siguiente;
  }
  return false;
}

/*Eliminaciones
variable:
0-Carro
1-habitacion
2-flotilla
3-piso
4-Hotel
5-Agencia
6-Pais
*/
void LDCReservaciones::eliminaciones(int identificacion, int variable){
  if (variable==0){//carro
    BorrarPosicion(retornarpunteroC(identificacion));
  }
  else if(variable==1){//habitacion
    BorrarPosicion(retornarpunteroH(identificacion));
  }
  else if(variable==2){//eliminar flotilla
    pnodoldCReservaciones aux=primero;
    while(aux){
      pnodoldCReservaciones borrar=retornarpunteroFP(identificacion,0);
      if(borrar==NULL){
        break;
      }
      BorrarPosicion(borrar);
      if(aux==primero){
        break;
      }
      aux=aux->siguiente;
    }
  }
  else if(variable==3){//eliminar piso
    pnodoldCReservaciones aux=primero;
    while(aux){
      pnodoldCReservaciones borrar=retornarpunteroFP(identificacion,1);
      if(borrar==NULL){
        break;
      }
      BorrarPosicion(borrar);
      if(aux==primero){
        break;
      }
      aux=aux->siguiente;
    }
  }
  else if(variable==4){//eliminar Hotel
    pnodoldCReservaciones aux=primero;
    while(aux){
      pnodoldCReservaciones borrar=retornarpunteroAH(identificacion,0);
      if(borrar==NULL){
        break;
      }
      BorrarPosicion(borrar);
      if(aux==primero){
        break;
      }
      aux=aux->siguiente;
    }
  }
  else if(variable==5){//eliminar Agencia
    pnodoldCReservaciones aux=primero;
    while(aux){
      pnodoldCReservaciones borrar=retornarpunteroAH(identificacion,1);
      if(borrar==NULL){
        break;
      }
      BorrarPosicion(borrar);
      if(aux==primero){
        break;
      }
      aux=aux->siguiente;
    }
  }
  else if(variable==6){//eliminar pais
    pnodoldCReservaciones aux=primero;
    while(aux){
      pnodoldCReservaciones borrar=retornarpunteroPais(identificacion);
      if(borrar==NULL){
        break;
      }
      BorrarPosicion(borrar);
      if(aux==primero){
        break;
      }
      aux=aux->siguiente;
    }
  }   
}



int LDCReservaciones::InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodocarro nodoC,pnodohabitacion nodoH,string pasaporte){
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodoH,nodoC, pasaporte);
    primero->anterior=primero;
    primero->siguiente=primero;
    generarCodigoReserva(primero);
    return 1;

  } else if (!repetido(nodoC) && !repetido(nodoH)) {
    pnodoldCReservaciones nuevo=new NodoLDCReservaciones (CP, CAH, CFP, CCH, nodoH, nodoC, pasaporte);
    generarCodigoReserva(nuevo);
    nuevo->siguiente=primero;
    nuevo->anterior= primero->anterior;
    primero->anterior->siguiente=nuevo;
    nuevo->siguiente->anterior=nuevo;
    primero= nuevo;
    return 1;

  }
  return -3;
}

int LDCReservaciones::InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo, string pasaporte){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo, pasaporte);
    primero->anterior=primero;
    primero->siguiente=primero;
    generarCodigoReserva(primero);
    return 1;

  } else if (!repetido(nodo)) {
    pnodoldCReservaciones nuevo=new NodoLDCReservaciones (CP, CAH, CFP, CCH, nodo,pasaporte);
    generarCodigoReserva(nuevo);
    nuevo->siguiente=primero;
    nuevo->anterior= primero->anterior;
    primero->anterior->siguiente=nuevo;
    nuevo->siguiente->anterior=nuevo;
    primero= nuevo;
    return 1;

  }
  return -3;
}

int LDCReservaciones :: InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodocarro nodo, string pasaporte){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo, pasaporte);
    primero->anterior=primero;
    primero->siguiente=primero;
    generarCodigoReserva(primero);
    return 1;

  } else if (!repetido(nodo)) {
    pnodoldCReservaciones nuevo=new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo,pasaporte);
    generarCodigoReserva(nuevo);
    nuevo->siguiente=primero;
    nuevo->anterior= primero->anterior;
    primero->anterior->siguiente=nuevo;
    nuevo->siguiente->anterior=nuevo;
    primero= nuevo;
    return 1;

  }
  return -3;
}

int LDCReservaciones :: BorrarFinal(){
    
    if (ListaVacia()){
      return -1;
    
    } else if (primero->siguiente == primero) { //caso nodo unico
        pnodoldCReservaciones temp= primero;
        primero= NULL;
        delete temp;

    } else {
      pnodoldCReservaciones aux = primero->anterior; //ultimo
      pnodoldCReservaciones temp = aux->anterior; //penultimo
      temp->siguiente = primero;
      primero->anterior = temp;
      delete aux;
      /*pnodoldCReservaciones aux = primero;
      while (aux->siguiente->siguiente != primero)
           aux = aux->siguiente;
      pnodoldCReservaciones temp = aux->siguiente;
      aux->siguiente= primero;
      primero->anterior=aux;
      delete temp;*/
  }
  return 1;
}
int LDCReservaciones :: BorrarInicio(){

  if (ListaVacia()) {
    return -1;
    
  } else if (primero->siguiente == primero) { //caso nodo unico
    pnodoldCReservaciones temp= primero;
    primero= NULL;
    delete temp;

  } else {
    pnodoldCReservaciones aux = primero->anterior;
    pnodoldCReservaciones temp= primero;
    aux->siguiente=primero->siguiente;
    primero=primero->siguiente; 
    primero->anterior=aux;
    delete temp;
  }
  return 1;
}
int LDCReservaciones :: BorrarPosicion(int pos){
    
  if(ListaVacia()){
    return -1;

  } else if((pos>largoLista())||(pos<0)){
    return -2;
  
  } else if(pos==1 || pos == 0){
    return BorrarInicio();
  
  } else {
    int cont=2;
    pnodoldCReservaciones aux=  primero;
    
    while(cont<pos){
      aux=aux->siguiente;
      cont++;

    }
    pnodoldCReservaciones temp = aux->siguiente;
    aux->siguiente=aux->siguiente->siguiente;
    aux->siguiente->anterior=aux;
    delete temp;
  }
  return 1;
}
int LDCReservaciones :: BorrarPosicion(pnodoldCReservaciones nodo){
    
  if(ListaVacia()){
    return -1;
  }

  
  pnodoldCReservaciones aux = primero;
  pnodoldCReservaciones temp;

  if (aux == nodo){
    
    temp = aux->anterior;
    temp->siguiente = aux->siguiente;
    aux->siguiente->anterior = temp;

    if (aux->siguiente == aux){
      primero = NULL;
    } else {
    
    primero = aux->siguiente;
    }
    
    delete aux;
    
    return 1;
  }



  while (aux->siguiente != primero){
    //le preguntamos a todos los nodos excepto el ultimo

    if (aux == nodo){
      
      temp = aux->anterior;
      temp->siguiente = aux->siguiente;
      aux->siguiente->anterior = temp;
      delete aux;
      
      return 1;
    }

    aux = aux->siguiente;
  }
  
  //le preguntamos al ultimo nodo
  if (aux == nodo){
    
    temp = aux->anterior;
    temp->siguiente = aux->siguiente;
    aux->siguiente->anterior = temp;
    delete aux;
    
    return 1;
  }

  return 1;
}
int LDCReservaciones :: BorrarPosicion(pnodocarro nodo){
    
  if(ListaVacia()){
    return -1;
  }

  
  pnodoldCReservaciones aux = primero;
  pnodoldCReservaciones temp;

  while (aux->siguiente != primero){
    //le preguntamos a todos los nodos excepto el ultimo

    if (aux->CarRes == nodo){
      
      temp = aux->anterior;
      temp->siguiente = aux->siguiente;
      aux->siguiente->anterior = temp;
      delete aux;
      
      return 1;
    }

    aux = aux->siguiente;
  }
  
  //le preguntamos al ultimo nodo
  if (aux->CarRes == nodo){
    
    temp = aux->anterior;
    temp->siguiente = aux->siguiente;
    aux->siguiente->anterior = temp;
    delete aux;
    
    return 1;
  }

  return -4;
}
int LDCReservaciones :: BorrarPosicion(pnodohabitacion nodo){
    
  if(ListaVacia()){
    return -1;
  }

  
  pnodoldCReservaciones aux = primero;
  pnodoldCReservaciones temp;

  while (aux->siguiente != primero){
    //le preguntamos a todos los nodos excepto el ultimo

    if (aux->HabRes == nodo){
      
      temp = aux->anterior;
      temp->siguiente = aux->siguiente;
      aux->siguiente->anterior = temp;
      delete aux;
      
      return 1;
    }

    aux = aux->siguiente;
  }
  
  //le preguntamos al ultimo nodo
  if (aux->HabRes == nodo){
    
    temp = aux->anterior;
    temp->siguiente = aux->siguiente;
    aux->siguiente->anterior = temp;
    delete aux;
    
    return 1;
  }

  return -4;
}

string LDCReservaciones :: MostrarAgencia(){
    string reservacionAgencia = "";
    try {
        pnodoldCReservaciones aux = primero;
        if (aux != NULL){
            while(aux->siguiente != primero) {
                if (aux->CarRes == NULL){
                  aux = aux->siguiente;
                  continue;
                }
                reservacionAgencia += MostrarNodo(aux, aux->CarRes);
                aux = aux->siguiente;
            }
            if (aux->CarRes != NULL){
                reservacionAgencia += MostrarNodo(aux, aux->CarRes);
            }
        }
        return reservacionAgencia;
    }
    catch (exception ex) {
        return reservacionAgencia;
    }
}

string LDCReservaciones :: MostrarHotel(){
  string reservacionHotel = "";
    pnodoldCReservaciones aux = primero;
    if (aux != NULL){
        while(aux->siguiente != primero) {
            if (aux->HabRes == NULL){
                aux = aux->siguiente;
                continue;
            }
            reservacionHotel += MostrarNodo(aux, aux->HabRes);
            aux = aux->siguiente;
        }
        if (aux->HabRes != NULL){
            reservacionHotel += MostrarNodo(aux, aux->HabRes);
        }
    }
    return reservacionHotel;
}

void LDCReservaciones :: Mostrar(int pos){

  pnodoldCReservaciones aux = primero;
  int temp;
  char espacio = ';';
   
  if (aux == NULL){
    cout<< endl <<"lista vacia"<<endl;
    return;

  } else if (pos > largoLista()|| pos <= -1){
    cout <<endl <<"nodo no disponible"<<endl;
    return;

  }
   
  if (pos > 0){
    pos--;

  }
  temp = pos + 1;

  while(pos!=0) {
      aux = aux->siguiente;
      pos--;

   }
  printf("\nInformacion del nodo %d; Usuario\n\n",temp);
  cout << aux->CodigoPais << espacio << " -> " << endl;
}
string LDCReservaciones :: MostrarNodo(pnodoldCReservaciones aux ,pnodocarro nodo){
    ArbolAA_Carros temp;
    if (nodo != NULL && aux != NULL){
        /*cout << "\nCodigo Pais: " << aux->CodigoPais << "\n";
        cout << "Codigo Agencia: " << aux->Codigo_AH << "\n";
        cout << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
        cout << "Codigo Carro: " << aux->Codigo_CH << "\n";*/
        return aux->codigoReserva + "|" + aux->pasaporte + "|" + to_string(aux->CodigoPais) + "|" + to_string(aux->Codigo_AH) + "|" + to_string(aux->Codigo_FP) + "|" + temp.MostrarNodo(nodo);
    }
}

string LDCReservaciones :: MostrarNodo(pnodoldCReservaciones aux ,pnodohabitacion nodo){
    ArbolRN_Habitaciones temp;
    if (nodo != NULL && aux != NULL){
        /*cout << "\nCodigo Pais: " << aux->CodigoPais << "\n";
        cout << "Codigo Hotel: " << aux->Codigo_AH << "\n";
        cout << "Codigo Piso: " << aux->Codigo_FP << "\n";
        cout << "Codigo Habitacion: " << aux->Codigo_CH << "\n";*/
        return aux->codigoReserva + "|" + aux->pasaporte + "|" + to_string(aux->CodigoPais) + "|" + to_string(aux->Codigo_AH) + "|" + to_string(aux->Codigo_FP) + "|" + temp.MostrarNodo(nodo);
    }
}

bool LDCReservaciones :: repetido(int valor){

  pnodoldCReservaciones aux = primero;

  if (aux == NULL){ //no hay nodo
    return false;

  } else if (aux->siguiente == primero){ //caso nodo unico
    
    if (valor == aux->CodigoPais){
      return true;

    }
    return false;

  }
  if (valor == aux->CodigoPais){ //evalua al primer nodo
    return true;

  }
  
  aux = aux->siguiente;

  while (aux != primero){ //2° nodo >> en adelante
    if (valor == aux->CodigoPais){
      return true;

    }
    aux = aux->siguiente;
  }
  return false;
}
bool LDCReservaciones :: repetido(pnodocarro nodo ){

  pnodoldCReservaciones aux = primero;

  if (aux == NULL){ //no hay nodo
    return false;

  } else if (aux->siguiente == primero){ //caso nodo unico
    
    if (nodo == aux->CarRes){
      return true;

    }
    return false;

  }
  if (nodo == aux->CarRes){ //evalua al primer nodo
    return true;

  }
  
  aux = aux->siguiente;

  while (aux != primero){ //2° nodo >> en adelante
    if (nodo == aux->CarRes){
      return true;

    }
    aux = aux->siguiente;
  }
  return false;
}
bool LDCReservaciones :: repetido(pnodohabitacion nodo ){

  pnodoldCReservaciones aux = primero;

  if (aux == NULL){ //no hay nodo
    return false;

  } else if (aux->siguiente == primero){ //caso nodo unico
    
    if (nodo == aux->HabRes){
      return true;

    }
    return false;

  }
  if (nodo == aux->HabRes){ //evalua al primer nodo
    return true;

  }
  
  aux = aux->siguiente;

  while (aux != primero){ //2° nodo >> en adelante
    if (nodo == aux->HabRes){
      return true;

    }
    aux = aux->siguiente;
  }
  return false;
}
pnodoldCReservaciones LDCReservaciones :: retornarpunteroC(int codigoCarro){

  pnodoldCReservaciones aux = primero;
  while(aux){
    if(aux->CarRes->getPlaca()==codigoCarro){
      return aux;
    }
    aux=aux->siguiente;
    if(aux==primero){
      break;
    }
  }
  return NULL;
  
}
pnodoldCReservaciones LDCReservaciones::retornarpunteroH(int codigoHabitacion){
  pnodoldCReservaciones aux = primero;
  while(aux){
    if(aux->HabRes->getCodHabitacion()==codigoHabitacion){
      return aux;
    }
    aux=aux->siguiente;
    if(aux==primero){
      break;
    }
  }
  return NULL;
}

pnodoldCReservaciones LDCReservaciones::retornarpunteroFP(int codigo, int opcion){//flotilla y pisos
  pnodoldCReservaciones aux = primero;
  while(aux){
    if(opcion==0){//flotilla
      if(aux->Codigo_FP==codigo&& aux->CarRes!=NULL){
        return aux;
      }
    }else{//pisos
      if(aux->Codigo_FP==codigo){
        return aux;
      }
    }
    aux=aux->siguiente;
    if(aux==primero){
      break;
    }
  }
  return NULL;
}

pnodoldCReservaciones LDCReservaciones::retornarpunteroAH(int codigo, int opcion){//Hotel y agencia
  pnodoldCReservaciones aux = primero;
  while(aux){
    if(opcion==0){//hotel
      if(aux->Codigo_AH==codigo&& aux->HabRes!=NULL){
        return aux;
      }
    }else{//agencia
      if(aux->Codigo_AH==codigo){
        return aux;
      }
    }
    aux=aux->siguiente;
    if(aux==primero){
      break;
    }
  }
  return NULL;
}

pnodoldCReservaciones LDCReservaciones::retornarpunteroPais(int codigo){//pais
  pnodoldCReservaciones aux = primero;
  while(aux){
    if(aux->CodigoPais==codigo){
       return aux; 
    }
    aux=aux->siguiente;
    if(aux==primero){
      break;
    }
  }
  return NULL;
}

pnodoldCReservaciones LDCReservaciones::retornarpunteroReserva(string codigo){
  pnodoldCReservaciones aux = primero;
  while(aux){
    if(aux->codigoReserva==codigo){
       return aux; 
    }
    aux=aux->siguiente;
    if(aux==primero){
      break;
    }
  }
  return NULL;
}

pnodoldCReservaciones LDCReservaciones :: getNodo(int valor){

  pnodoldCReservaciones aux = primero;

  while (aux->siguiente != primero){
    
    //retorna el valor si lo encontro
    //no retorna el ultimo nodo
    if (aux->CodigoPais == valor){
      return aux;
    }

    aux = aux->siguiente;
  }
  
  //retorna el ultimo nodo
  if (aux->CodigoPais == valor){
    return aux;
  }
  
  //no lo encontro
  return NULL;

}

int LDCReservaciones :: buscarCodigoPais(int valor){ //devuelve la pocicion del nodo

  pnodoldCReservaciones aux = primero;
  int i;

  if (aux == NULL){ //no hay nodo
    return -4;

  } else if (aux->siguiente == primero){ //caso nodo unico
    if (valor == aux->CodigoPais){
      return 1;

    }
    return -4;

  }

  if (valor == aux->CodigoPais){ //evalua al primer nodo
    return 1;

  }
  
  aux = aux->siguiente;
  i = 2;

  while (aux != primero){ //2° nodo >> en adelante
    if (valor == aux->CodigoPais){
      return i;

    }
    i++;
    aux = aux->siguiente;
  }
  return -4;
}

int LDCReservaciones :: getCodigoPais(int &valor, int pos){

  pnodoldCReservaciones aux = primero;
  int i;

  if (pos <= -1 || pos > largoLista()) {
    return -2;

  } else if (ListaVacia()) {
    return -1;

  } else if (pos == 0 || pos == 1) {
    pos = 1;

  }
   
  for (i = 2; i <= pos; i++){
    aux=aux->siguiente;

  }
  valor = aux->CodigoPais;
  return 1;
}
int LDCReservaciones :: setCodigoPais(int valor, int pos){

  pnodoldCReservaciones aux = primero;
  int i;

  if (pos <= -1 || pos > largoLista()) {
    return -2;

  } else if (ListaVacia()) {
    return -1;

  } else if (repetido(valor)) {
      return -3;

  } else if (pos == 0 || pos == 1) {
    pos = 1;

  }
   
  for (i = 2; i <= pos; i++){
      aux=aux->siguiente;

  }
  aux->CodigoPais = valor;
  return 1;
}


int LDCReservaciones :: getCodigoPais(int &valor, pnodoldCReservaciones aux){

  if (aux == NULL){
    return -2;
  }
  
  valor = aux->CodigoPais;
  return 1;
}
int LDCReservaciones :: getCodAH(int &valor, pnodoldCReservaciones aux){

  if (aux == NULL){
    return -2;
  }
  
  valor = aux->Codigo_AH;
  return 1;
}
int LDCReservaciones :: getCodFP(int &valor, pnodoldCReservaciones aux){

  if (aux == NULL){
    return -2;
  }
  
  valor = aux->Codigo_FP;
  return 1;
}
int LDCReservaciones :: getCodCH(int &valor, pnodoldCReservaciones aux){

  if (aux == NULL){
    return -2;
  }
  
  valor = aux->Codigo_CH;
  return 1;
}


int LDCReservaciones :: setCodigoPais(int valor, pnodoldCReservaciones aux){


  if (aux == NULL){

    return -2;

  }

  aux->CodigoPais = valor;
  return 1;
}
int LDCReservaciones :: setCodAH(int valor, pnodoldCReservaciones aux){


  if (aux == NULL){

    return -2;

  }

  aux->CodigoPais = valor;
  return 1;
}
int LDCReservaciones :: setCodFP(int valor, pnodoldCReservaciones aux){


  if (aux == NULL){

    return -2;

  }

  aux->CodigoPais = valor;
  return 1;
}
int LDCReservaciones :: setCodCH(int valor, pnodoldCReservaciones aux){


  if (aux == NULL){

    return -2;

  }

  aux->CodigoPais = valor;
  return 1;
}

//generar el codigo para la reservacion
int cantidadReservasA=0;
int cantidadReservasH=0;
int cantidadReservasTI=0;

void LDCReservaciones::generarCodigoReserva(pnodoldCReservaciones nodoReserva){
  string codigo="";
  if (nodoReserva->HabRes == NULL){
     cantidadReservasA++;
     string num=to_string(cantidadReservasA);
     codigo="RA"+num;//caso de agencias
  }else if(nodoReserva->CarRes == NULL){
     cantidadReservasH++;
     string num=to_string(cantidadReservasH);
     codigo="RH"+num;//caso de carros
  }else if(nodoReserva->CarRes != NULL&&nodoReserva->HabRes != NULL){
     cantidadReservasTI++;
     string num=to_string(cantidadReservasTI);
     codigo="RTI"+num;//caso de todo incluido
  }
	
	nodoReserva->codigoReserva=codigo;
}

//ver reservas pendientes que tiene el cliente
void LDCReservaciones::reservasPendientes(string pasaporte){
	pnodoldCReservaciones aux=primero;
	while(aux){
		if(aux->pasaporte==pasaporte&&aux->HabRes==NULL){
			cout<<"\nEl codigo de reserva:"<<aux->codigoReserva<<"\n";
      cout<<"Reservacion del usuario: "<<aux->pasaporte<<"\n";
      cout << "Codigo Pais: " << aux->CodigoPais << "\n";
      cout << "Codigo Agencia: " << aux->Codigo_AH << "\n";
      cout << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
      cout << "Codigo Carro: " << aux->Codigo_CH << "\n";
      cout<<"Precio de la reservacion: "<<aux->CarRes->getPrecioCarro()<<endl;
		}
    else if(aux->pasaporte==pasaporte&&aux->CarRes==NULL){
      cout<<"\nEl codigo de reserva:"<<aux->codigoReserva<<"\n";
      cout<<"Reservacion del usuario: "<<aux->pasaporte<<"\n";
      cout << "Codigo Pais: " << aux->CodigoPais << "\n";
      cout << "Codigo Hotel: " << aux->Codigo_AH << "\n";
      cout << "Codigo Piso: " << aux->Codigo_FP << "\n";
      cout << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
      cout<<"Precio de la reservacion: "<<aux->HabRes->getPrecioHabitacion()<<endl;
    }
    else if(aux->pasaporte==pasaporte&&aux->CarRes!=NULL&&aux->HabRes!=NULL){
      cout<<"\nEl codigo de reserva:"<<aux->codigoReserva<<"\n";
      cout<<"Reservacion del usuario: "<<aux->pasaporte<<"\n";
      cout << "Codigo Pais: " << aux->CodigoPais << "\n";
      cout << "Codigo Agencia: " << aux->Codigo_AH << "\n";
      cout << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
      cout << "Codigo Carro: " << aux->Codigo_CH << "\n";
      cout << "Codigo Hotel: " << aux->Codigo_AH << "\n";
      cout << "Codigo Piso: " << aux->Codigo_FP << "\n";
      cout << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
      int precio=aux->HabRes->getPrecioHabitacion()+aux->CarRes->getPrecioCarro();
      cout<< "Precio de la reservacion: "<<(precio-(precio*0.1))<<endl;
    }
		aux=aux->siguiente;
    if(aux==primero){
      break;
    }
	}
}

string LDCReservaciones::pagarReservacion(string codigoReserva){
    pnodoldCReservaciones aux = primero;
	  while(aux!=NULL && aux->siguiente!=primero){
        if(aux->codigoReserva==codigoReserva){
            if(aux->HabRes==NULL){
                return "1|Reservacion de carro de "+to_string(aux->CarRes->getPrecioCarro())+" pagada";
            }
            if(aux->CarRes==NULL){
                return "1|Reservacion de habitacion de "+to_string(aux->HabRes->getPrecioHabitacion())+" pagada";
            }
            if(aux->CarRes!=NULL && aux->HabRes!=NULL){
                return "1|Reservacion de habitacion y carro de "+to_string((aux->HabRes->getPrecioHabitacion()+aux->CarRes->getPrecioCarro())*0.9);
            }  
         }
         aux = aux->siguiente;
     }
     if(aux->HabRes==NULL){
      return "1|Reservacion de carro de "+to_string(aux->CarRes->getPrecioCarro())+" pagada";
            }
            if(aux->CarRes==NULL){
                return "1|Reservacion de habitacion de "+to_string(aux->HabRes->getPrecioHabitacion())+" pagada";
            }
            if(aux->CarRes!=NULL && aux->HabRes!=NULL){
                return "1|Reservacion de habitacion y carro de "+to_string((aux->HabRes->getPrecioHabitacion()+aux->CarRes->getPrecioCarro())*0.9);
            } 
     return "0|No se encontro el codigo ingresado";
}

string LDCReservaciones::generarFactura(string codigoReserva){
  string resultado;
	//ofstream factura;
	//factura.open(/*"Reservaciones/"+*/codigoReserva+".txt");
	pnodoldCReservaciones aux = primero;
	while(aux!=NULL && aux->siguiente!=primero){
		if(aux->codigoReserva==codigoReserva&&aux->HabRes==NULL){
			// factura<<"Codigo Reserva: "<<aux->codigoReserva<<endl;
			// factura<<"Pasaporte: "<<aux->pasaporte<<endl;
			// factura << "Codigo Pais: " << aux->CodigoPais << "\n";
      // factura << "Codigo Agencia: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Carro: " << aux->Codigo_CH << "\n";
      pnodocarro carro=aux->CarRes;
			// factura<<"Total a pagar: "<<carro->getPrecioCarro();
			// factura.close();
      //eliminar de la lista
      //resultado = "1|Factura generada con exito";
			resultado = "Codigo Reserva: " + aux->codigoReserva + "\n" + "Pasaporte: " + aux->pasaporte + "\n" + "Codigo Pais: " + to_string(aux->CodigoPais) + "\n" + "Codigo Agencia: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Flotilla: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Carro: " + to_string(aux->Codigo_CH) + "\n" + "Total a pagar: " + to_string(carro->getPrecioCarro());
			eliminaciones(aux->CarRes->getPlaca(),0);
      escribirArchivo(codigoReserva,resultado);
      return "1|"+resultado;
		}
    else if(aux->codigoReserva==codigoReserva&&aux->CarRes==NULL){
      // factura<<"Codigo Reserva: "<<aux->codigoReserva<<endl;
			// factura<<"Pasaporte: "<<aux->pasaporte<<endl;
      // factura << "Codigo Pais: " << aux->CodigoPais << "\n";
      // factura << "Codigo Hotel: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Piso: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
      // factura<<"Total a pagar: "<<aux->HabRes->getPrecioHabitacion();
      // factura.close();
			//eliminar(aux->placa);
      //resultado = "1|Factura generada con exito";
			resultado = "Codigo Reserva: " + aux->codigoReserva + "\n" + "Pasaporte: " + aux->pasaporte + "\n" + "Codigo Pais: " + to_string(aux->CodigoPais) + "\n" + "Codigo Hotel: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Piso: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Habitacion: " + to_string(aux->Codigo_CH) + "\n" + "Total a pagar: " + to_string(aux->HabRes->getPrecioHabitacion());
      eliminaciones(aux->HabRes->getCodHabitacion(),1);
      escribirArchivo(codigoReserva,resultado);
      return "1|"+resultado;
    }
    else if(aux->codigoReserva==codigoReserva&&aux->CarRes!=NULL&&aux->HabRes!=NULL){
      // factura<<"\nEl codigo de reserva:"<<aux->codigoReserva<<"\n";
      // factura<<"Pasaporte: "<<aux->pasaporte<<"\n";
      // factura << "Codigo Pais: " << aux->CodigoPais << "\n";
      // factura << "Codigo Agencia: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Carro: " << aux->Codigo_CH << "\n";
      // factura << "Codigo Hotel: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Piso: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
      int precio=aux->HabRes->getPrecioHabitacion()+aux->CarRes->getPrecioCarro();
      // factura<<"Total a pagar: "<<(precio-(precio*0.1))<<endl;
      // factura.close();
			//eliminar(aux->placa);
      //resultado = "1|Factura generada con exito";
			resultado = "Codigo Reserva: " + aux->codigoReserva + "\n" + "Pasaporte: " + aux->pasaporte + "\n" + "Codigo Pais: " + to_string(aux->CodigoPais) + "Codigo Agencia: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Flotilla: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Carro: " + to_string(aux->Codigo_CH) + "\n" + "Codigo Hotel: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Piso: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Habitacion: " + to_string(aux->Codigo_CH) + "\n" + "Total a pagar: " + to_string((precio-(precio*0.1)));
      eliminaciones(aux->HabRes->getCodHabitacion(),1);
      escribirArchivo(codigoReserva,resultado);
      return "1|"+resultado;
    }
		aux=aux->siguiente;
	}
  if(aux->codigoReserva==codigoReserva&&aux->HabRes==NULL){
			// factura<<"Codigo Reserva: "<<aux->codigoReserva<<endl;
			// factura<<"Pasaporte: "<<aux->pasaporte<<endl;
			// factura << "Codigo Pais: " << aux->CodigoPais << "\n";
      // factura << "Codigo Agencia: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Carro: " << aux->Codigo_CH << "\n";
       pnodocarro carro=aux->CarRes;
			// factura<<"Total a pagar: "<<carro->getPrecioCarro();
			// factura.close();
      //eliminar de la lista
      //resultado = "1|Factura generada con exito";
			resultado = "Codigo Reserva: " + aux->codigoReserva + "\n" + "Pasaporte: " + aux->pasaporte + "\n" + "Codigo Pais: " + to_string(aux->CodigoPais) + "\n" + "Codigo Agencia: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Flotilla: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Carro: " + to_string(aux->Codigo_CH) + "\n" + "Total a pagar: " + to_string(carro->getPrecioCarro());
			eliminaciones(aux->CarRes->getPlaca(),0);
      escribirArchivo(codigoReserva,resultado);
      return "1|"+resultado;
		}
    else if(aux->codigoReserva==codigoReserva&&aux->CarRes==NULL){
      // factura<<"Codigo Reserva: "<<aux->codigoReserva<<endl;
			// factura<<"Pasaporte: "<<aux->pasaporte<<endl;
      // factura << "Codigo Pais: " << aux->CodigoPais << "\n";
      // factura << "Codigo Hotel: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Piso: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
      // factura<<"Total a pagar: "<<aux->HabRes->getPrecioHabitacion();
      // factura.close();
			//eliminar(aux->placa);
      //resultado = "1|Factura generada con exito";
			resultado = "Codigo Reserva: " + aux->codigoReserva + "\n" + "Pasaporte: " + aux->pasaporte + "\n" + "Codigo Pais: " + to_string(aux->CodigoPais) + "\n" + "Codigo Hotel: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Piso: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Habitacion: " + to_string(aux->Codigo_CH) + "\n" + "Total a pagar: " + to_string(aux->HabRes->getPrecioHabitacion());
      eliminaciones(aux->HabRes->getCodHabitacion(),1);
      escribirArchivo(codigoReserva,resultado);
      return "1|"+resultado;
    }
    else if(aux->codigoReserva==codigoReserva&&aux->CarRes!=NULL&&aux->HabRes!=NULL){
      // factura<<"\nEl codigo de reserva:"<<aux->codigoReserva<<"\n";
      // factura<<"Pasaporte: "<<aux->pasaporte<<"\n";
      // factura << "Codigo Pais: " << aux->CodigoPais << "\n";
      // factura << "Codigo Agencia: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Carro: " << aux->Codigo_CH << "\n";
      // factura << "Codigo Hotel: " << aux->Codigo_AH << "\n";
      // factura << "Codigo Piso: " << aux->Codigo_FP << "\n";
      // factura << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
      int precio=aux->HabRes->getPrecioHabitacion()+aux->CarRes->getPrecioCarro();
      // factura<<"Total a pagar: "<<(precio-(precio*0.1))<<endl;
      // factura.close();
			//eliminar(aux->placa);
      //resultado = "1|Factura generada con exito";
			resultado = "Codigo Reserva: " + aux->codigoReserva + "\n" + "Pasaporte: " + aux->pasaporte + "\n" + "Codigo Pais: " + to_string(aux->CodigoPais) + "Codigo Agencia: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Flotilla: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Carro: " + to_string(aux->Codigo_CH) + "\n" + "Codigo Hotel: " + to_string(aux->Codigo_AH) + "\n" + "Codigo Piso: " + to_string(aux->Codigo_FP) + "\n" + "Codigo Habitacion: " + to_string(aux->Codigo_CH) + "\n" + "Total a pagar: " + to_string((precio-(precio*0.1)));
      eliminaciones(aux->HabRes->getCodHabitacion(),1);
      escribirArchivo(codigoReserva,resultado);
      return "1|"+resultado;
    }
  return "0|No se encontro una reservacion con el codigo indicado";
}
