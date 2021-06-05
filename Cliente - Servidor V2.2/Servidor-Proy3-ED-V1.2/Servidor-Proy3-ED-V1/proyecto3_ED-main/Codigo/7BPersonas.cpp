
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

//falta implementar la funcion de borrarNodo()
//modificaciones en: abcdefg

#include <iostream>
using namespace std;

class PaginaNodoPersona;

class NodoPersona {
   public:
    
    
    NodoPersona(int Pas, char* nom){
      Identificador = Pas;

      for (int i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

       }

      Izquierda = NULL;
      Derecha =NULL;
    
    }

 private:
    int Identificador;
    char Nombre[30] = "\000";
    PaginaNodoPersona *Izquierda;
    PaginaNodoPersona *Derecha;
    friend class ArbolB_Persona;
    friend class PaginaNodoPersona;
};
typedef NodoPersona *pnodopersona;


class PaginaNodoPersona {
   public:
    
    PaginaNodoPersona(){}

    pnodopersona pnodo = NULL;
    PaginaNodoPersona *siguiente = NULL;
    PaginaNodoPersona *anterior = NULL;


  PaginaNodoPersona* crearPaginaVacia(int tamano){

    //crea una pagina del tamanno indicado y devuelve su puntero

    PaginaNodoPersona * aux = NULL;
    PaginaNodoPersona * ante = NULL;
    PaginaNodoPersona * sigue = NULL;

    if ((tamano <= 0) || (tamano%2 ==1)){
      return NULL;

    }

    aux = new PaginaNodoPersona(NULL,NULL);
    ante = aux;

    for (int i = 1; i < tamano; i++){
      sigue = new PaginaNodoPersona(NULL,ante);
      ante = sigue;
    }
    
  return aux;

  }

  PaginaNodoPersona* clonarPagina(PaginaNodoPersona* aux){

    // crear un pagina identica a la recibida y devuelve su ubicacion

    PaginaNodoPersona* temp = aux;
    PaginaNodoPersona* aux2 = aux;
    PaginaNodoPersona*temp2 = NULL;

    int i;

    if (temp == NULL){
      return NULL;
    }
    

    for ( i = 1; temp->siguiente != NULL; i++){
      temp = temp->siguiente;
    }
    
    temp = crearPaginaVacia(i);

    temp2 = temp;

    while (aux2 != NULL){
      temp2->pnodo = aux2->pnodo;

      temp2 = temp2->siguiente;
      aux2 = aux2->siguiente;
    }

    return temp;

  }

  void dividirPagina(PaginaNodoPersona* Izquierda, PaginaNodoPersona* Derecha){

    //Dividimos los contenidos de la pagina Izquierda.
    //La mitad menor a la izquierda y la mitad mayor a la derecha
    //La pagina Derecha tiene que venir vacia


    PaginaNodoPersona* aux = Izquierda;
    PaginaNodoPersona* temp = Derecha;

    if ((aux == NULL) || (temp == NULL)){
      return;
    }
    
    int tamanoIzquierda = tamanoMax(aux);
    int i;
    int j = 0;
    

    //aux queda en el primer elemento de la mitad mayor
    for (i = 0; i < (tamanoIzquierda/2); i++){
      aux = aux->siguiente;
    }
    
    //hacemos la asignacion y borrado
    for (i; i > 0; i--){
      temp->pnodo = aux->pnodo;
      aux->pnodo = NULL;

      temp = temp->siguiente;
      aux = aux->siguiente;
    }
    



  }

  int tamanoMax(PaginaNodoPersona* entrada){

    PaginaNodoPersona* aux = entrada;

    int i;

    for ( i = 0; aux != NULL; i++){
      aux = aux->siguiente;
    }
    
    return i;

  }

  int tamanoUsado(PaginaNodoPersona* entrada){

    PaginaNodoPersona* aux = entrada;

    int i;
    int j = 0;

    for ( i = 0; aux != NULL; i++){
      if (aux->pnodo != NULL){
        j++;
      
      }
      aux = aux->siguiente;

    }
    
    return j;

  }

 private:

    PaginaNodoPersona(pnodopersona Elemento, PaginaNodoPersona* ante ){

      pnodo = Elemento;
      anterior = ante;

      if (ante != NULL){
        ante->siguiente = this;
      }
    
    }

    PaginaNodoPersona( PaginaNodoPersona* ante ){

      pnodo = NULL;
      anterior = ante;

      if (ante != NULL){
        ante->siguiente = this;
      }
    
    }

    
};



class ArbolB_Persona {
   public:
    ArbolB_Persona(int tamano) { primero = NULL; tamanoPaginas = tamano;}
    ~ArbolB_Persona();
        
    int getIdentificador(int &valor, pnodopersona aux);
    int getNombre(char *nombre, pnodopersona aux);
    string getNombre(int codigo);

    int setIdentificador(int valor, pnodopersona aux);
    int setNombre(char *nombre, pnodopersona aux);

    pnodopersona getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isIdentificadorRepetido(int valor);
    int insertarNodo(int pasport, char* nom);
    void MostrarNodo(pnodopersona aux);
    void Mostrar();
    pnodopersona getNodo(int valor);
    bool getNodo(pnodopersona &recibir, int valor);
    int borrarNodo(pnodopersona nodo);
    
   private:

    bool arbolVacio() { return primero == NULL; }

    pnodopersona getNodo(int valor, pnodopersona aux);
    pnodopersona getNodo(int valor, PaginaNodoPersona* aux);
    void MostrarInorde(PaginaNodoPersona* aux);
    void MostrarInorde(pnodopersona aux);
    void Mostrar(pnodopersona aux);
    int isIdentificadorRepetido(int valor, pnodopersona aux);
    int isIdentificadorRepetido(int valor, PaginaNodoPersona* aux);
    int insertarNodo(int pasport, char* nom, PaginaNodoPersona* aux);
    int insertarNodo(int pasport, char* nom, pnodopersona aux);
    void borrarArbol(PaginaNodoPersona* pagina);
    void borrarArbol(pnodopersona nodo);

    int insertarNodo(PaginaNodoPersona*& raiz, pnodopersona nodo);
    int empujar(pnodopersona nodo, PaginaNodoPersona*aux, bool& empujararriba, pnodopersona& X, PaginaNodoPersona*& Xr);
    PaginaNodoPersona* buscarNodo(pnodopersona nodo, PaginaNodoPersona*aux, int& k);
    int meterHoja(pnodopersona nodo, PaginaNodoPersona* Xr, PaginaNodoPersona* aux, int k);
    int dividirNodo(pnodopersona nodo,pnodopersona& X,PaginaNodoPersona*& Xr, PaginaNodoPersona* aux, int k);

    PaginaNodoPersona* primero;
    pnodopersona ultimonodo;
    int tamanoPaginas = 4;
   
};




ArbolB_Persona :: ~ArbolB_Persona(){

  borrarArbol(primero);
  primero == NULL;

}

void ArbolB_Persona :: borrarArbol(PaginaNodoPersona* pagina) {
   
   if (pagina == NULL){
      return;
   } 

   PaginaNodoPersona* aux = pagina->siguiente;
   PaginaNodoPersona* temp;
  
    // si aux == NULL, significa que la pagina tiene solamente un nodo
    // adicionalmente no entra en el while

    while (aux != NULL){
      //este while omite al ultimo puntero, por lo tanto se repite una vez mas afuera del mismo

      borrarArbol(pagina->pnodo); 
      temp = pagina; //
      aux = aux->siguiente;
      pagina = pagina->siguiente;
      delete temp;
      

    }

  //al ser esta pocision en la pagina, no ocupamos a los punteros adionales
  borrarArbol(pagina->pnodo);  
  delete pagina;
} 
void ArbolB_Persona :: borrarArbol(pnodopersona nodo) {
   if (nodo == NULL){
      return;
   } 
  
   borrarArbol(nodo->Izquierda); 
   borrarArbol(nodo->Derecha); 
     
   delete nodo;
} 


int ArbolB_Persona :: insertarNodo(int pasport, char* nom){

  
  PaginaNodoPersona* aux = primero;

  if (aux == NULL){
    //Arbol vacio y pagina en nulo
    aux = aux->crearPaginaVacia(tamanoPaginas);
    aux->pnodo = new NodoPersona(pasport,nom);
    ultimonodo = aux->pnodo;
    primero = aux;
    return 1;
  
  }

  if (isIdentificadorRepetido(pasport) == -3 ){
    //el elemento a insertar ya esta en el arbol
    return-3;
  }
  

  //inicio de la llamadas recursivas

  pnodopersona temp = new NodoPersona(pasport, nom);

  int i = insertarNodo(aux, temp);
  

  // actualizamos el puntero de primero
  if (aux != primero ){
    
    primero = aux;

  }
  
  return i;
  
}
int ArbolB_Persona :: insertarNodo(PaginaNodoPersona*& raiz, pnodopersona nodo){

  //al usar aux el cambio es local
  //al usar raiz el cambio es mas global

  //esta diferencia nos permite alterar al puntero "aux" con el valor de primero,
  // y nunca arriesgar la modificacion de primero
  PaginaNodoPersona* aux = raiz;
  bool empujararriba = false;
  pnodopersona X = NULL;
  PaginaNodoPersona* Xr = NULL;

  int i = empujar(nodo, aux, empujararriba, X, Xr);

  // creamos la nueva cabeza
  if (empujararriba){
    aux = aux->crearPaginaVacia(tamanoPaginas);
    aux->pnodo = X;
    aux->pnodo->Izquierda = raiz;
    aux->pnodo->Derecha = Xr;
    raiz = aux;
    return 1;

  }
  return i;
}


int ArbolB_Persona :: empujar(pnodopersona nodo, PaginaNodoPersona*aux, bool& empujararriba, pnodopersona& X, PaginaNodoPersona*& Xr){

  int k = 0;

  //pagina existe?
  if (aux == NULL){
    empujararriba = true;
    X = nodo;
    Xr = NULL;

  } else {

    PaginaNodoPersona*posicion = buscarNodo(nodo,aux,k); //busca la pagina donde se deberia insertar si esta existe 

    //pocision es el puntero de la siguiente pagina a revisar
    //este puntero puede ser nulo o no

    int i = empujar(nodo, posicion, empujararriba, X, Xr);

    if (empujararriba){
      
      if (aux->tamanoMax(aux) > aux->tamanoUsado(aux)){
        empujararriba = false;

        //resulta que pocision esta nulo si entra aqui
        i = meterHoja(X, Xr, aux ,k);
      
      } else {
        //entra a aqui si la pagina en la que queremos insertar esta llena
        empujararriba = true;
         i = dividirNodo(nodo, X, Xr,aux,k);


      }
      
    }
    return i;
  }
  return -2;
}

PaginaNodoPersona* ArbolB_Persona ::  buscarNodo(pnodopersona nodo, PaginaNodoPersona*aux, int& k){

  //esta funcion me devuelve la pocision del puntero en el ultimo nodo mayor que el valor a buscar
  // y la ubicacion de la pagina por la cual bajar
  // k = 0; bajamos a aux.pnodo.izquierda
  // k = 1; bajamos a aux.pnodo.derecha
  // k > 1; aux se mueve a la ubicacion correcta y aux.pnodo.derecha es por donde bajamos
  // k es un recordatorio de cual puntero devolvi
  
  if (nodo->Identificador < aux->pnodo->Identificador){

  k = 0;

  } else {

    k = aux->tamanoUsado(aux);


    //dejamos a aux en el ultimo puntero a pnodo no null
    for (int i = k; i > 1 ; i--){
      aux = aux->siguiente;
    }
    

    while ((nodo->Identificador < aux->pnodo->Identificador) && (k>1)){
      aux = aux->anterior;
      k--;
    }
    
    return aux->pnodo->Derecha;

  }
  return aux->pnodo->Izquierda;

}


int ArbolB_Persona ::  meterHoja(pnodopersona X, PaginaNodoPersona* Xr, PaginaNodoPersona* aux, int k){

//cuando entramos en esta funcion resulta que la pagina en la que insertaremos la informacion
// no esta llena. eso significa que la pagina actual es recien creada o tiene menos del maximo

//usando k sabemos cuantas pocisiones tenemos que correr

  int usado = aux->tamanoUsado(aux);

  //movemos el puntero al primer nodo vacio porque este tendra el valor del nuevo dato
  // el del dato anterior
  while (aux->pnodo != NULL){
    aux = aux->siguiente;
  }

  if (k == usado){
    //le asignamos el dato nuevo a ese nodo vacio

    aux->pnodo = X;
    aux->pnodo->Derecha = Xr;
    return 1;

  }
  
  while (k < usado){
    
    // asignamos el valor anterior al nodo actual
    aux->pnodo = aux->anterior->pnodo;

    //movemos el nodo actual al anterior
    aux = aux->anterior;
    usado--;
  }

  
  //le asignamos a el nodo actual el valor nuevo
  aux->pnodo = X;
  aux->pnodo->Derecha = Xr;
  aux->pnodo->Izquierda= aux->siguiente->pnodo->Izquierda;//abcdefg
  aux->siguiente->pnodo->Izquierda = NULL;//abcdefg


  return 1;

}


int ArbolB_Persona ::  dividirNodo(pnodopersona nodo,pnodopersona& X,PaginaNodoPersona*& Xr, PaginaNodoPersona* aux, int k){

  //aclaracion de la funcion

  // Esta funcion esta basada en la que la profesora nos entrego y enseño,
  // sin embargo, debido a la circunstancia de que la pagina puede hacerse de cualquier tamanno
  // deseado es que la funcion se ve muy diferente


  int maximo = aux->tamanoMax(aux);

  if (X == nodo){
    // la division esta ocurriendo en una hoja o
    // lo que se quiere insertar inicialmente esta en el centro
    // en ambos casos, implica que el nodo a insertar no tiene ningun hijo

    PaginaNodoPersona* temp = new PaginaNodoPersona(); 
    temp = temp->crearPaginaVacia(tamanoPaginas);
    aux->dividirPagina(aux, temp);

    if (k <= ((maximo/2)-1) ){
      // cuando entra aqui se debe subir el ultimo valor no nulo de la lista aux
      // y se debe insertar el valor de "nodo" en su pocision correspondiente en esa lista

      PaginaNodoPersona* sosten = aux;//abcdefg
      while (aux->pnodo != NULL){//abcdefg
        aux = aux->siguiente;
      }

      pnodopersona valorSubir = aux->anterior->pnodo;
      aux->anterior->pnodo = NULL;

      aux = sosten;//abcdefg

      meterHoja(nodo,NULL,aux,k);

      X = valorSubir;
      Xr = temp;

    } else if (k >= ((maximo/2)+1) ){
      // cuando entra aqui se debe subir el primer valor no nulo de la lista temp
      // y se debe insertar el valor de "nodo" en su pocision correspondiente en esa lista

      pnodopersona valorSubir = temp->pnodo;
      temp->pnodo = NULL;

      //arreglamos el orden de los datos pues ahora estan:
      // [0,x,x1,x2]

      PaginaNodoPersona* Sosten = temp;

      while (temp->siguiente != NULL){
        temp = temp->siguiente;
        temp->anterior->pnodo = temp->pnodo;
      }

      temp->pnodo = NULL;
      temp = Sosten;

      //finaliza el arreglo



      meterHoja(nodo,NULL,temp,(k-((maximo/2)+1)));

      X = valorSubir;
      Xr = temp;

    } else {

      //el nodo a insertar esta en la mitad

      X = nodo;
      Xr = temp;

    }


  } else {

    // el valor de X no es nulo, por lo tanto nuestro numero en nodo, ya fue insertado en alguna hoja
    // o resulta que la hoja se dividio y nodo estaba en el centro y por lo tanto subio,
    // en cualquier caso, ignoramos a nodo

    //el hecho de entrar aqui, significa que el valor en X no pudo ser insertado en la pagina pues esta esta llena

    PaginaNodoPersona* temp = new PaginaNodoPersona();
    temp = temp->crearPaginaVacia(tamanoPaginas);
    aux->dividirPagina(aux, temp);

    if (k <= ((maximo/2)-1) ){
      // cuando entra aqui se debe subir el ultimo valor no nulo de la lista aux
      // y se debe insertar el valor de X en su pocision correspondiente en esa lista

      PaginaNodoPersona* sosten = aux;//abcdefg
      while (aux->pnodo != NULL){//abcdefg
        aux = aux->siguiente;
      }

      pnodopersona valorSubir = aux->anterior->pnodo;
      aux->anterior->pnodo = NULL;

      aux = sosten;//abcdefg

      meterHoja(X,Xr,aux,k);
      temp->pnodo->Izquierda = valorSubir->Derecha;
      X = valorSubir;
      Xr = temp;

    } else if (k >= ((maximo/2)+1) ){
      // cuando entra aqui se debe subir el primer valor no nulo de la lista temp
      // y se debe insertar el valor de X en su pocision correspondiente en esa lista

      pnodopersona valorSubir = temp->pnodo;
      temp->pnodo = NULL;

      //arreglamos el orden de los datos pues ahora estan:
      // [0,x,x1,x2]

      PaginaNodoPersona* Sosten = temp;

      while (temp->siguiente != NULL){
        temp = temp->siguiente;
        temp->anterior->pnodo = temp->pnodo;
      }

      temp->pnodo = NULL;
      temp = Sosten;

      //finaliza el arreglo

      meterHoja(X,Xr,temp,(k-((maximo/2)+1)));
      temp->pnodo->Izquierda = valorSubir->Derecha;
      X = valorSubir;
      Xr = temp;

    } else {

      //el nodo a insertar esta en la mitad

      //antes de actualizar volver a actualizar los valores de X y Xr 
      //debemos asignarle el puntero Xr a 

      temp->pnodo->Izquierda = Xr;

      X = nodo;
      Xr = temp;

    }


  }
    
  return -2;
}
  


int ArbolB_Persona :: isIdentificadorRepetido(int valor){ // me informa que el nodo ya existe o que no existe

   //Funcion inicializadora de una busqueda recursiva por el valor indicado en la estructura

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3
   // si la estructura esta vacia retorna -1

  PaginaNodoPersona* aux = primero;

  if (arbolVacio() ){
      return -1;
  }

  int i;

  while (aux != NULL){
    
    i = isIdentificadorRepetido(valor, aux->pnodo);

    if (i == -3){
      return -3;
    }
    
    aux = aux->siguiente;
  }
  

  return-2;

}
int ArbolB_Persona :: isIdentificadorRepetido(int valor, pnodopersona aux){ // me informa que el nodo ya existe o que no existe

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->Identificador == valor){
        return -3;

    } else if (valor < aux->Identificador){
        return isIdentificadorRepetido(valor, aux->Izquierda);

    } else if (valor > aux->Identificador){
        return isIdentificadorRepetido(valor, aux->Derecha);
    
    }
   return-4;
}
int ArbolB_Persona :: isIdentificadorRepetido(int valor, PaginaNodoPersona* aux){ // me informa que el nodo ya existe o que no existe



  // se cumple si llegamos a una pagina hoja vacia
  if (aux == NULL){
    return -2;
  }
  
  int temp;

    while (aux != NULL){
      //aux == NULL si se acabaron los elementos de la pagina

      temp = isIdentificadorRepetido(valor, aux->pnodo); 

      if (temp == -3){
        return -3;
      }
      
      aux = aux->siguiente;
    }

  return -2;
} 


void ArbolB_Persona :: MostrarInorde(pnodopersona aux){

   //funcion recursiva auxiliar
   //muestras todos los nodos contenidos en la estructura
   //en inorden

   if (aux == NULL){
      return;
   }

   MostrarInorde(aux->Izquierda);
   Mostrar(aux);
   MostrarInorde(aux->Derecha);


}
void ArbolB_Persona :: MostrarInorde(PaginaNodoPersona* aux){

//permite el paso intermediario de la pagina

   if (aux == NULL){
      return;
   }

  while (aux != NULL){
    // mostramos todos los valores de la pagina
    MostrarInorde(aux->pnodo);
    aux = aux->siguiente;
  }
  
}
void ArbolB_Persona :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   PaginaNodoPersona* aux = primero;
   
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

  if (aux->pnodo == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todas la Informacion\n"<< endl; //abcdefg
   
   
   MostrarInorde(aux);

}
void ArbolB_Persona :: Mostrar(pnodopersona aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->Identificador << espacio << aux->Nombre << "  >>" << endl;


}
void ArbolB_Persona :: MostrarNodo(pnodopersona aux){

   //Permite imprimir la informacion del nodo recibido

   if (aux == NULL){
      cout<<"Error: Puntero nulo\n";
      return;
   }

   char espacio[] = "; ";

   cout << aux->Identificador << espacio << aux->Nombre << "  >>" << endl;


}


bool ArbolB_Persona :: getNodo(pnodopersona &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   PaginaNodoPersona* aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodopersona ArbolB_Persona :: getNodo(int valor){
  
  //funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   PaginaNodoPersona* aux = primero;
   
   return getNodo(valor, aux);


}

pnodopersona ArbolB_Persona :: getNodo(int valor, PaginaNodoPersona* aux){

  // funcion intermediaria que nos permite transcurrir por los valrores de la pagina

  if (aux == NULL){
    return NULL;
  }
  
  pnodopersona temp;

    while (aux != NULL){
      //aux == NULL solamente cuando hayamos acabado con todos los valores 

      temp = getNodo(valor, aux->pnodo); 

      if (temp != NULL){
        return temp;
      }
      
      aux = aux->siguiente;
    }

  return NULL;
} 
pnodopersona ArbolB_Persona :: getNodo(int valor, pnodopersona aux){

  //funcion recursiva que busca por el puntero con su identificacion == valor

   pnodopersona temp = NULL;
   
   if (aux == NULL){
      return NULL;
   }
   
   if (valor == aux->Identificador){
      return aux;
   }

   temp = getNodo(valor, aux->Izquierda);

   if (temp != NULL){
      return temp;
   }

   temp = getNodo(valor, aux->Derecha);

   if (temp != NULL){
      return temp;
   }

   return NULL;
}


pnodopersona ArbolB_Persona :: getultimoNodoInsertado(){
   return ultimonodo;
}

int ArbolB_Persona :: borrarNodo(pnodopersona nodo){
  
  if (nodo == NULL){
    return -1;
  }
  
  //implementacion del borrado
  return 1;
}

int ArbolB_Persona :: getIdentificador(int &valor, pnodopersona aux){

  if (aux == NULL){
    return -4;

  }
  valor = aux->Identificador;
  return 1;
}
int ArbolB_Persona :: getNombre(char *nombre, pnodopersona aux){

  int i;

  if (aux == NULL){
    return -4;

  }

   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}

string ArbolB_Persona::getNombre(int codigo){
  pnodopersona nodo = getNodo(codigo);
  if(nodo==NULL){
    return "NULL";
  }
  return string(nodo->Nombre);
}

int ArbolB_Persona :: setIdentificador(int valor, pnodopersona aux){

  if (aux == NULL){
    return -4;

  }
  aux->Identificador = valor;
  return 1;
}
int ArbolB_Persona :: setNombre(char *nombre, pnodopersona aux){

  int i;

  if (aux == NULL){
    return -4;

  }

   for (i = 0; (i < sizeof(aux->Nombre)); i++) { // limpieamos la variable
      aux->Nombre[i] = '\000';
   }

   for (i = 0; ((nombre[i]!= '\000') && (i < sizeof(aux->Nombre))); i++) { // asignamos valor
      aux->Nombre[i] = nombre[i];
   }
   return 1;
}

