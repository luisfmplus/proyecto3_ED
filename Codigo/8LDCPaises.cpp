
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

#include <iostream>
using namespace std;


class NodoLDCPais {
   public:
    
    
    NodoLDCPais(int Pas, char* nom){
      CodPais = Pas;

	  int i;
      for (i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

       }

      siguiente = NULL;
      anterior =NULL;
    
    }

   NodoLDCPais(int Pas, char* nom, NodoLDCPais * sigNodoPisosHoteles){
      CodPais = Pas;

	  int i;
      for (i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

      }
      siguiente = sigNodoPisosHoteles;

    }

 private:
    int CodPais;
    char Nombre[30] = "\000";
    NodoLDCPais *siguiente;
    NodoLDCPais *anterior;
    friend class LDCPaises;
};
typedef NodoLDCPais *pnodoldcpais;

class LDCPaises {
   public:
    LDCPaises() { primero = NULL; }
    ~LDCPaises();
    

    bool ListaVacia() { return primero == NULL; }
    int largoLista();

    int InsertarInicio(int Pas, char* nom);
    int InsertarFinal(int Pas, char* nom);
    int InsertarPos (int Pas, char* nom, int pos);

    int BorrarFinal();
    int BorrarInicio();
    int BorrarPosicion(int pos);
    int BorrarPosicion(pnodoldcpais nodo);

    void Mostrar();
    void Mostrar(int pos);
    bool repetido(int valor);
    pnodoldcpais retornarpuntero(int pos);
    int buscarCodPais(int valor);
    pnodoldcpais getNodo(int pos);
    
    int getCodPais(int &valor, int pos);
    int getNombre(char *nombre, int pos);

    int setCodPais(int valor, int pos);
    int setNombre(char *nombre, int pos);

    
    int getCodPais(int &valor, pnodoldcpais aux);
    int getNombre(char *nombre, pnodoldcpais aux);
    int setCodPais(int valor, pnodoldcpais aux);
    int setNombre(char *nombre, pnodoldcpais aux);

    
   private:
    pnodoldcpais primero;
   
};


LDCPaises :: ~LDCPaises(){
   pnodoldcpais aux;
   
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

int LDCPaises :: largoLista()
{
    int cont=1;

    pnodoldcpais aux = primero;
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

int LDCPaises :: InsertarInicio(int Pas, char* nom){
  
  if (ListaVacia()){
    primero = new NodoLDCPais(Pas, nom);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if (!repetido(Pas)) {
    pnodoldcpais nuevo=new NodoLDCPais (Pas, nom);
    nuevo->siguiente=primero;
    nuevo->anterior= primero->anterior;
    primero->anterior->siguiente=nuevo;
    nuevo->siguiente->anterior=nuevo;
    primero= nuevo;
    return 1;

  }
  return -3;
}
int LDCPaises :: InsertarFinal(int Pas, char* nom){
  
  if (ListaVacia()){
    primero = new NodoLDCPais(Pas, nom);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if (!repetido(Pas)) {
    pnodoldcpais nuevo = new NodoLDCPais(Pas, nom);
    nuevo->anterior = primero->anterior;
    nuevo->siguiente=primero->anterior->siguiente;
    primero->anterior->siguiente=nuevo;
    primero->anterior=nuevo;
    return 1;

  }
  return -3;
}
int LDCPaises :: InsertarPos(int Pas, char* nom,int pos){
  
  if (ListaVacia()){
    primero = new NodoLDCPais(Pas, nom);
    primero->anterior=primero;
    primero->siguiente=primero;
    return 1;

  } else if(pos <=1){
    return InsertarInicio(Pas, nom);    
    
  } else if (pos>largoLista()){
    return InsertarFinal(Pas, nom);

  } else if(!repetido(Pas)) {
    pnodoldcpais aux= primero;
    int i =2;

    while((i != pos )&&(aux->siguiente!= primero)) {
      i++;
      aux=aux->siguiente;

    }
    pnodoldcpais nuevo= new NodoLDCPais(Pas, nom);
    nuevo->siguiente=aux->siguiente;
    aux->siguiente=nuevo;
    aux->siguiente->anterior=aux;
    nuevo->siguiente->anterior=nuevo;
    return 1;

  }
  return -3;
}

int LDCPaises :: BorrarFinal(){
    
    if (ListaVacia()){
      return -1;
    
    } else if (primero->siguiente == primero) { //caso nodo unico
        pnodoldcpais temp= primero;
        primero= NULL;
        delete temp;

    } else {
      pnodoldcpais aux = primero->anterior; //ultimo
      pnodoldcpais temp = aux->anterior; //penultimo
      temp->siguiente = primero;
      primero->anterior = temp;
      delete aux;
      /*pnodoldcpais aux = primero;
      while (aux->siguiente->siguiente != primero)
           aux = aux->siguiente;
      pnodoldcpais temp = aux->siguiente;
      aux->siguiente= primero;
      primero->anterior=aux;
      delete temp;*/
  }
  return 1;
}
int LDCPaises :: BorrarInicio(){

  if (ListaVacia()) {
    return -1;
    
  } else if (primero->siguiente == primero) { //caso nodo unico
    pnodoldcpais temp= primero;
    primero= NULL;
    delete temp;

  } else {
    pnodoldcpais aux = primero->anterior;
    pnodoldcpais temp= primero;
    aux->siguiente=primero->siguiente;
    primero=primero->siguiente; 
    primero->anterior=aux;
    delete temp;
  }
  return 1;
}
int LDCPaises :: BorrarPosicion(int pos){
    
  if(ListaVacia()){
    return -1;

  } else if((pos>largoLista())||(pos<0)){
    return -2;
  
  } else if(pos==1 || pos == 0){
    return BorrarInicio();
  
  } else {
    int cont=2;
    pnodoldcpais aux=  primero;
    
    while(cont<pos){
      aux=aux->siguiente;
      cont++;

    }
    pnodoldcpais temp = aux->siguiente;
    aux->siguiente=aux->siguiente->siguiente;
    aux->siguiente->anterior=aux;
    delete temp;
  }
  return 1;
}
int LDCPaises :: BorrarPosicion(pnodoldcpais nodo){
    
  if(ListaVacia()){
    return -1;
  }

  
  pnodoldcpais aux = primero;
  pnodoldcpais temp;

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

void LDCPaises :: Mostrar(){
  pnodoldcpais aux = primero;
  char espacio = ';';

  if (aux == NULL){
    cout<< endl <<"lista vacia"<<endl;
    return;
  }

  cout << endl << "Mostrando todos los Usuarios"<< endl<< endl;
  cout << aux->CodPais << espacio << aux->Nombre << " -> " << endl;

   while(aux->siguiente != primero) {
      aux = aux->siguiente;
      cout << aux->CodPais << espacio << aux->Nombre << " -> " << endl;
      
   }
}
void LDCPaises :: Mostrar(int pos){

  pnodoldcpais aux = primero;
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
  cout << aux->CodPais << espacio << aux->Nombre << " -> " << endl;
}
bool LDCPaises :: repetido(int valor){

  pnodoldcpais aux = primero;

  if (aux == NULL){ //no hay nodo
    return false;

  } else if (aux->siguiente == primero){ //caso nodo unico
    
    if (valor == aux->CodPais){
      return true;

    }
    return false;

  }
  if (valor == aux->CodPais){ //evalua al primer nodo
    return true;

  }
  
  aux = aux->siguiente;

  while (aux != primero){ //2° nodo >> en adelante
    if (valor == aux->CodPais){
      return true;

    }
    aux = aux->siguiente;
  }
  return false;
}
pnodoldcpais LDCPaises :: retornarpuntero(int pos){

  pnodoldcpais aux = primero;
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

pnodoldcpais LDCPaises :: getNodo(int valor){

  pnodoldcpais aux = primero;

  while (aux->siguiente != primero){
    
    //retorna el valor si lo encontro
    //no retorna el ultimo nodo
    if (aux->CodPais == valor){
      return aux;
    }

    aux = aux->siguiente;
  }
  
  //retorna el ultimo nodo
  if (aux->CodPais == valor){
    return aux;
  }
  
  //no lo encontro
  return NULL;

}

int LDCPaises :: buscarCodPais(int valor){ //devuelve la pocicion del nodo

  pnodoldcpais aux = primero;
  int i;

  if (aux == NULL){ //no hay nodo
    return -4;

  } else if (aux->siguiente == primero){ //caso nodo unico
    if (valor == aux->CodPais){
      return 1;

    }
    return -4;

  }

  if (valor == aux->CodPais){ //evalua al primer nodo
    return 1;

  }
  
  aux = aux->siguiente;
  i = 2;

  while (aux != primero){ //2° nodo >> en adelante
    if (valor == aux->CodPais){
      return i;

    }
    i++;
    aux = aux->siguiente;
  }
  return -4;
}

int LDCPaises :: getCodPais(int &valor, int pos){

  pnodoldcpais aux = primero;
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
  valor = aux->CodPais;
  return 1;
}
int LDCPaises :: getNombre(char *nombre, int pos){

   pnodoldcpais aux = primero;
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

   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}

int LDCPaises :: setCodPais(int valor, int pos){

  pnodoldcpais aux = primero;
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
  aux->CodPais = valor;
  return 1;
}
int LDCPaises :: setNombre(char *nombre, int pos){

   pnodoldcpais aux = primero;
   int i;

   if (pos <= -1 || pos > largoLista()) {
      return -2;

   } else if (ListaVacia()) {
      return -1;

   } else if (pos == 0 || pos == 1) {
      pos = 1;
   }
   
   for (i = 2; i <= pos; i++){ // nos desplazamos al puntero correcto
      aux=aux->siguiente;
   }

   for (i = 0; (i < sizeof(aux->Nombre)); i++) { // limpieamos la variable
      aux->Nombre[i] = '\000';
   }

   for (i = 0; ((nombre[i]!= '\000') && (i < sizeof(aux->Nombre))); i++) { // asignamos valor
      aux->Nombre[i] = nombre[i];
   }
   return 1;
}


int LDCPaises :: getCodPais(int &valor, pnodoldcpais aux){

  if (aux == NULL){
    return -2;
  }
  
  valor = aux->CodPais;
  return 1;
}
int LDCPaises :: getNombre(char *nombre, pnodoldcpais aux){

   int i;
   
   if (aux == NULL){
     return -2;
   }
   
   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}

int LDCPaises :: setCodPais(int valor, pnodoldcpais aux){


  if (aux == NULL){

    return -2;

  }

  aux->CodPais = valor;
  return 1;
}
int LDCPaises :: setNombre(char *nombre, pnodoldcpais aux){

  int i;
   
  if (aux == NULL){
    return -2;
  }

  for (i = 0; (i < sizeof(aux->Nombre)); i++) { // limpieamos la variable
    aux->Nombre[i] = '\000';
  }

  for (i = 0; ((nombre[i]!= '\000') && (i < sizeof(aux->Nombre))); i++) { // asignamos valor
    aux->Nombre[i] = nombre[i];
  }

   return 1;
}





