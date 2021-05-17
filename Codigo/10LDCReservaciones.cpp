
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

#include <iostream>
#include "ArbolesBinarios.h"
using namespace std;



    

class NodoLDCReservaciones {
   public:
    
    int CodigoPais = -1;
    int Codigo_AH = -1;
    int Codigo_FP = -1;
    int Codigo_CH = -1;
    
    NodoLDCReservaciones(int CP, int CAH, int CFP, int CCH, pnodocarro nodo){
      
      CodigoPais = CP;
      Codigo_AH = CAH;
      Codigo_FP = CFP;
      Codigo_CH = CCH;
      CarRes = nodo;
      HabRes = NULL;

      siguiente = NULL;
      anterior =NULL;
    
    }

    NodoLDCReservaciones(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo){
      
      CodigoPais = CP;
      Codigo_AH = CAH;
      Codigo_FP = CFP;
      Codigo_CH = CCH;
      HabRes = nodo;
      CarRes = NULL;

      siguiente = NULL;
      anterior =NULL;
    
    }




 private:
    

    pnodocarro CarRes;
    pnodohabitacion HabRes;

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

    int InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo);
    int InsertarFinal(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo);
    int InsertarPos (int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo, int pos);
    int InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodocarro nodo);
    int InsertarFinal(int CP, int CAH, int CFP, int CCH, pnodocarro nodo);
    int InsertarPos (int CP, int CAH, int CFP, int CCH, pnodocarro nodo, int pos);

    int BorrarFinal();
    int BorrarInicio();
    int BorrarPosicion(int pos);
    int BorrarPosicion(pnodoldCReservaciones nodo);
    int BorrarPosicion(pnodocarro nodo);
    int BorrarPosicion(pnodohabitacion nodo);

    void MostrarHotel();
    void MostrarAgencia();
    void Mostrar(int pos);
    void MostrarNodo(pnodoldCReservaciones aux ,pnodocarro nodo);
    void MostrarNodo(pnodoldCReservaciones aux ,pnodohabitacion nodo);
    bool repetido(int valor);
    bool repetido(pnodocarro nodo);
    bool repetido(pnodohabitacion nodo);
    pnodoldCReservaciones retornarpuntero(int pos);
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

int LDCReservaciones :: InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if (!repetido(nodo)) {
    pnodoldCReservaciones nuevo=new NodoLDCReservaciones (CP, CAH, CFP, CCH, nodo);
    nuevo->siguiente=primero;
    nuevo->anterior= primero->anterior;
    primero->anterior->siguiente=nuevo;
    nuevo->siguiente->anterior=nuevo;
    primero= nuevo;
    return 1;

  }
  return -3;
}
int LDCReservaciones :: InsertarFinal(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if (!repetido(nodo)) {
    pnodoldCReservaciones nuevo = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    nuevo->anterior = primero->anterior;
    nuevo->siguiente=primero->anterior->siguiente;
    primero->anterior->siguiente=nuevo;
    primero->anterior=nuevo;
    return 1;

  }
  return -3;
}
int LDCReservaciones :: InsertarPos(int CP, int CAH, int CFP, int CCH, pnodohabitacion nodo,int pos){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if(pos <=1){
    return InsertarInicio(CP, CAH, CFP, CCH, nodo);    
    
  } else if (pos>largoLista()){
    return InsertarFinal(CP, CAH, CFP, CCH, nodo);

  } else if(!repetido(nodo)) {
    pnodoldCReservaciones aux= primero;
    int i =2;

    while((i != pos )&&(aux->siguiente!= primero)) {
      i++;
      aux=aux->siguiente;

    }
    pnodoldCReservaciones nuevo= new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    nuevo->siguiente=aux->siguiente;
    aux->siguiente=nuevo;
    aux->siguiente->anterior=aux;
    nuevo->siguiente->anterior=nuevo;
    return 1;

  }
  return -3;
}
int LDCReservaciones :: InsertarInicio(int CP, int CAH, int CFP, int CCH, pnodocarro nodo){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if (!repetido(nodo)) {
    pnodoldCReservaciones nuevo=new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    nuevo->siguiente=primero;
    nuevo->anterior= primero->anterior;
    primero->anterior->siguiente=nuevo;
    nuevo->siguiente->anterior=nuevo;
    primero= nuevo;
    return 1;

  }
  return -3;
}
int LDCReservaciones :: InsertarFinal(int CP, int CAH, int CFP, int CCH, pnodocarro nodo){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if (!repetido(nodo)) {
    pnodoldCReservaciones nuevo = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    nuevo->anterior = primero->anterior;
    nuevo->siguiente=primero->anterior->siguiente;
    primero->anterior->siguiente=nuevo;
    primero->anterior=nuevo;
    return 1;

  }
  return -3;
}
int LDCReservaciones :: InsertarPos(int CP, int CAH, int CFP, int CCH, pnodocarro nodo,int pos){
  
  if (ListaVacia()){
    primero = new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if(pos <=1){
    return InsertarInicio(CP, CAH, CFP, CCH, nodo);    
    
  } else if (pos>largoLista()){
    return InsertarFinal(CP, CAH, CFP, CCH, nodo);

  } else if(!repetido(nodo)) {
    pnodoldCReservaciones aux= primero;
    int i =2;

    while((i != pos )&&(aux->siguiente!= primero)) {
      i++;
      aux=aux->siguiente;

    }
    pnodoldCReservaciones nuevo= new NodoLDCReservaciones(CP, CAH, CFP, CCH, nodo);
    nuevo->siguiente=aux->siguiente;
    aux->siguiente=nuevo;
    aux->siguiente->anterior=aux;
    nuevo->siguiente->anterior=nuevo;
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


void LDCReservaciones :: MostrarAgencia(){
  pnodoldCReservaciones aux = primero;

  if (aux == NULL){
    cout<< endl <<"lista vacia"<<endl;
    return;
  }


  cout << "\nMostrando todas las Reservaciones\n\n";

  while(aux->siguiente != primero) {

    if (aux->CarRes == NULL){
      aux = aux->siguiente;
      continue;
    }
    
    MostrarNodo(aux, aux->CarRes);
    aux = aux->siguiente;
      
  }

  if (aux->CarRes != NULL){
    MostrarNodo(aux, aux->CarRes);
    
  }
    
}
void LDCReservaciones :: MostrarHotel(){
  pnodoldCReservaciones aux = primero;

  if (aux == NULL){
    cout<< endl <<"lista vacia"<<endl;
    return;
  }


  cout << "\nMostrando todas las Reservaciones\n\n";


  while(aux->siguiente != primero) {

    if (aux->HabRes == NULL){
      aux = aux->siguiente;
      continue;
    }
    
    MostrarNodo(aux, aux->HabRes);
    aux = aux->siguiente;
      
  }

  if (aux->HabRes != NULL){
    MostrarNodo(aux, aux->HabRes);

  }
    
    


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
  printf("\nIformacion del nodo %d; Usuario\n\n",temp);
  cout << aux->CodigoPais << espacio << " -> " << endl;
}
void LDCReservaciones :: MostrarNodo(pnodoldCReservaciones aux ,pnodocarro nodo){

  ArbolAA_Carros temp;

  if (nodo == NULL){
    cout<< "\nERROR: puntero nulo\n";
  }

  if (aux == NULL){
    cout<< "\nERROR: puntero nulo\n";
    return;
  }
  
  cout << "\nCodigo Pais: " << aux->CodigoPais << "\n";
  cout << "Codigo Agencia: " << aux->Codigo_AH << "\n";
  cout << "Codigo Flotilla: " << aux->Codigo_FP << "\n";
  cout << "Codigo Carro: " << aux->Codigo_CH << "\n";
  temp.MostrarNodo(nodo);
  


}
void LDCReservaciones :: MostrarNodo(pnodoldCReservaciones aux ,pnodohabitacion nodo){

  ArbolRN_Habitaciones temp;

  if (nodo == NULL){
    cout<< "\nERROR: puntero nulo\n";
    return;
  }

  if (aux == NULL){
    cout<< "\nERROR: puntero nulo\n";
    return;
  }


  cout << "\nCodigo Pais: " << aux->CodigoPais << "\n";
  cout << "Codigo Hotel: " << aux->Codigo_AH << "\n";
  cout << "Codigo Piso: " << aux->Codigo_FP << "\n";
  cout << "Codigo Habitacion: " << aux->Codigo_CH << "\n";
  temp.MostrarNodo(nodo);


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
pnodoldCReservaciones LDCReservaciones :: retornarpuntero(int pos){

  pnodoldCReservaciones aux = primero;
  int i = 2;

  if (pos == 0 || pos == 1){ //retorna NULL en caso de no haber nodos
    return primero;

  } else if (pos <= -1 || pos > largoLista()){
    return NULL;

  }
   
  while (i <= pos){
    aux = aux->siguiente;
    i++;

  }
  return aux;
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





