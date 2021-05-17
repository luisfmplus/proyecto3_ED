
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general


  actualizarFlotilla se define en el archivo Flotilla

*/

//falta implementar la funcion de borrarNodo()

#include <iostream>
using namespace std;

class NodoCarro {
   public:

    
    
    NodoCarro(int Pl, char Mod [30], int NA, int A, int PC, char EdC){
      Placa = Pl;
      NumeroAsientos = NA;
      Ano = A;
      PrecioCarro = PC;
      EstadodelCarro = EdC;

      for (int i = 0; Mod[i] != '\000' &&  i < sizeof(Modelo) ; i++){
          Modelo[i] = Mod[i];

       }

      Derecha = NULL;
      Izquierda =NULL;
      Padre = NULL;
    
    }

    NodoCarro(int Pl, char Mod [30], int NA, int A, int PC){
      Placa = Pl;
      NumeroAsientos = NA;
      Ano = A;
      PrecioCarro = PC;
      EstadodelCarro = 'L';

      for (int i = 0; Mod[i] != '\000' &&  i < sizeof(Modelo) ; i++){
          Modelo[i] = Mod[i];

       }

      Derecha = NULL;
      Izquierda =NULL;
      Padre = NULL;
    
    }


 private:
    int Placa;
    char Modelo [30] = "\000";
    int NumeroAsientos;
    int Ano;
    int PrecioCarro;
    char EstadodelCarro;
    int nivel = 1;
    NodoCarro *Padre;
    NodoCarro *Izquierda;
    NodoCarro *Derecha;
    friend class ArbolAA_Carros;
};
typedef NodoCarro *pnodocarro;

class ArbolAA_Carros {
   public:
    ArbolAA_Carros() {primero = NULL;}
    ~ArbolAA_Carros();
    
    int getPlaca(int &valor, pnodocarro aux);
    int getModelo(char *nombre, pnodocarro aux);
    int getNumeroAsientos(int &valor, pnodocarro aux);
    int getAno(int &valor, pnodocarro aux);
    int getPrecioCarro(int &valor, pnodocarro aux);
    int getEstadodelCarro(char &valor, pnodocarro aux);

    int setPlaca(int valor, pnodocarro aux);
    int setModelo(char *nombre, pnodocarro aux);
    int setNumeroAsientos(int valor, pnodocarro aux);
    int setAno(int valor, pnodocarro aux);
    int setPrecioCarro(int valor, pnodocarro aux);
    int setEstadodelCarro(char valor, pnodocarro aux);

    
    pnodocarro getultimoNodoInsertado();
    int insertarNodo(int Pl, char Mod [30], int NA, int A, int PC, char EdC);
    int insertarNodo(int Pl, char Mod [30], int NA, int A, int PC);
    void MostrarNodo(pnodocarro aux);
    void Mostrar();
    pnodocarro getNodo(int valor);
    int borrarNodo(pnodocarro nodo);

   private:

    bool arbolVacio() { return primero == NULL; }
    int isPlacaRepetido(int valor);
    int isPlacaRepetido(int valor, pnodocarro aux);
    void MostrarInorde(pnodocarro aux);
    void Mostrar(pnodocarro aux);
    bool getNodo(pnodocarro &recibir, int valor);
    pnodocarro getNodo(int valor, pnodocarro aux);
    int insertarNodo(int Pl, char Mod [30], int NA, int A, int PC, char EdC, pnodocarro aux, int& resultado);
    int insertarNodo(int Pl, char Mod [30], int NA, int A, int PC, pnodocarro aux, int& resultado);
    pnodocarro torcion(pnodocarro aux);
    pnodocarro division(pnodocarro aux);
    pnodocarro primero;
    pnodocarro ultimonodo;
   
};

ArbolAA_Carros :: ~ArbolAA_Carros(){

}
   
int ArbolAA_Carros :: insertarNodo(int Pl, char Mod [30], int NA, int A, int PC, char EdC){

  pnodocarro aux = primero;
  int resultado = -4;

  if (primero == NULL){
    //creacion del primer nodo y por lo tanto no se hace nada especial

    primero = new NodoCarro(Pl,Mod,NA,A,PC,EdC);
    setEstadodelCarro(EdC, primero);
    ultimonodo = primero;
    return 1;
  }

  //revisamos que el valor a insertar no exista aun

   int condicion = isPlacaRepetido(Pl); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }
  
  //nos vamos a la funcion recursiva. de esta forma insertamos el nodo como en un ABB.


  insertarNodo(Pl, Mod, NA, A, PC, EdC, aux, resultado);
  return resultado;
  
}
int ArbolAA_Carros :: insertarNodo(int Pl, char Mod [30], int NA, int A, int PC){

  pnodocarro aux = primero;
  int resultado = -4;

  if (primero == NULL){
    
    primero = new NodoCarro(Pl,Mod,NA,A,PC);
    return 1;
  }

  if (Pl == primero->Placa){
    return -3;
  }
  
  insertarNodo(Pl, Mod, NA, A, PC, aux, resultado);
  return resultado;
  
}
int ArbolAA_Carros :: insertarNodo(int Pl, char Mod [30], int NA, int A, int PC, char EdC, pnodocarro aux, int& resultado){

  // tenemos asegurado que:
  // Pl no esta repetido,
  // que el primer nodo ya existe

  //int resultado; permitira almacenar el resultado de la operacion

  //nos movemos a la ubicacion correcta para la insercion
  if (Pl < aux->Placa){


    //no movemos hasta el nodo del cual debe ser hijo
    if (aux->Izquierda != NULL){
      resultado = insertarNodo(Pl, Mod, NA, A, PC, EdC, aux->Izquierda, resultado);

      // las funciones de torcion y division se aplicaran a todos los nodos, incluyendo a la raiz
      aux = torcion(aux);
      aux = division(aux);
      return resultado;
            
    } else {

      // encontramos el nodo del cual debe ser hijo
      aux->Izquierda = new NodoCarro(Pl, Mod, NA, A, PC, EdC);
      setEstadodelCarro(EdC, aux->Izquierda);
      aux->Izquierda->Padre = aux;
      ultimonodo = aux->Izquierda;
      aux = torcion(aux);

      aux = division(aux);
      
      

      return 1; //regresamos al nodo padre del nodo recien creado 
        
    }
  
  //nos movemos a la ubicacion correcta para la insercion
  } else if (Pl > aux->Placa){


    //no movemos hasta el nodo del cual debe ser hijo
    if (aux->Derecha != NULL){
      resultado = insertarNodo(Pl, Mod, NA, A, PC, EdC, aux->Derecha, resultado);

      // las funciones de torcion y division se aplicaran a todos los nodos, incluyendo a la raiz
      aux = torcion(aux);
      aux = division(aux);
      return resultado;

    } else {

      // encontramos el nodo del cual debe ser hijo
      aux->Derecha = new NodoCarro(Pl, Mod, NA, A, PC, EdC);
      setEstadodelCarro(EdC, aux->Derecha);
      aux->Derecha->Padre = aux;
      ultimonodo = aux->Derecha;
      aux = torcion(aux);

      aux = division(aux);
      return 1;
        
    }
  }

  return-4;
}
int ArbolAA_Carros :: insertarNodo(int Pl, char Mod [30], int NA, int A, int PC, pnodocarro aux, int& resultado){
  // tenemos asegurado que:
  // Pl no esta repetido,
  // que el primer nodo ya existe

  //int resultado; permitira almacenar el resultado de la operacion

  //nos movemos a la ubicacion correcta para la insercion
  if (Pl < aux->Placa){


    //no movemos hasta el nodo del cual debe ser hijo
    if (aux->Izquierda != NULL){
      resultado = insertarNodo(Pl, Mod, NA, A, PC, aux->Izquierda, resultado);

      // las funciones de torcion y division se aplicaran a todos los nodos, incluyendo a la raiz
      aux = torcion(aux);
      aux = division(aux);
      return resultado;
            
    } else {

      // encontramos el nodo del cual debe ser hijo
      aux->Izquierda = new NodoCarro(Pl, Mod, NA, A, PC);
      aux->Izquierda->Padre = aux;
      ultimonodo = aux->Izquierda;
      aux = torcion(aux);

      aux = division(aux);
      
      

      return 1; //regresamos al nodo padre del nodo recien creado 
        
    }
  
  //nos movemos a la ubicacion correcta para la insercion
  } else if (Pl > aux->Placa){


    //no movemos hasta el nodo del cual debe ser hijo
    if (aux->Derecha != NULL){
      resultado = insertarNodo(Pl, Mod, NA, A, PC, aux->Derecha, resultado);

      // las funciones de torcion y division se aplicaran a todos los nodos, incluyendo a la raiz
      aux = torcion(aux);
      aux = division(aux);
      return resultado;

    } else {

      // encontramos el nodo del cual debe ser hijo
      aux->Derecha = new NodoCarro(Pl, Mod, NA, A, PC);
      aux->Derecha->Padre = aux;
      ultimonodo = aux->Derecha;
      aux = torcion(aux);

      aux = division(aux);
      return 1;
        
    }
  }

  return-4;
}

pnodocarro ArbolAA_Carros :: torcion(pnodocarro aux){

  //nunca recibe el nodo recien insertado. sino todos los nodos en orden hasta llegar a la raiz


  pnodocarro temp;
  bool enRaiz = false;

  if (aux == primero){
    //identifica que estamos en la raiz
    enRaiz = true;    
  }
  
  if (aux == NULL){
    return NULL;
  
  } else if (aux->Izquierda == NULL){
    return aux;
  
  } else if (aux->Izquierda->nivel == aux->nivel) {

    // realizamos la torcion

    temp = aux->Izquierda;
    aux->Izquierda = temp->Derecha;

    if (aux->Izquierda != NULL){
      aux->Izquierda->Padre = aux;
    }
    temp->Derecha = aux;
    temp->Padre = aux->Padre;
    aux->Padre = temp;


    //actualizamos a primero
    if (enRaiz){
      primero = temp;
      return temp;
    }
    
    // torcion es en un hijo derecha
    if (temp->Padre->Derecha == aux){
      temp->Padre->Derecha = temp;
      return temp;
    }

    // torcion es en un hijo izquierda
    temp->Padre->Izquierda = temp;
    return temp;
  }
  return aux;

}
pnodocarro ArbolAA_Carros :: division(pnodocarro aux) {

  pnodocarro temp;
  bool enRaiz = false;

  if (aux == primero){
    enRaiz = true;    
  }

  if (aux == NULL){
    return NULL;
  } else if (aux->Derecha == NULL || aux->Derecha->Derecha == NULL){
    return aux;
  
  } else if (aux->Derecha->Derecha->nivel == aux->nivel){

    // realizamos la division

    temp = aux->Derecha;
    aux->Derecha = temp->Izquierda;

    if (aux->Derecha != NULL){
      aux->Derecha->Padre = aux;
    }
    temp->Izquierda = aux;
    temp->nivel++;
    
    temp->Padre = aux->Padre;
    aux->Padre = temp;


    // actualizamos primero
    if (enRaiz){
      primero = temp;
      return temp;
    }

    // el nodo era hijo derecho
    if (temp->Padre->Derecha == aux){
      temp->Padre->Derecha = temp;
      return temp;
    }
    
    //el nodo era hijo izquierdo
    temp->Padre->Izquierda = temp;
    return temp;
  }
  return aux;

}

pnodocarro ArbolAA_Carros :: getultimoNodoInsertado(){
  return ultimonodo;
}

int ArbolAA_Carros :: isPlacaRepetido(int valor){ // me informa que el nodo ya existe o que no existe

   //Funcion inicializadora de una busqueda recursiva por el valor indicado en la estructura

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3
   // si la estructura esta vacia retorna -1

    pnodocarro aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->Placa == valor){
        return -3;

    } else if (valor < aux->Placa){
        return isPlacaRepetido(valor, aux->Izquierda);

    } else if (valor > aux->Placa){
        return isPlacaRepetido(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolAA_Carros :: isPlacaRepetido(int valor, pnodocarro aux){ // me informa que el nodo ya existe o que no existe

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->Placa == valor){
        return -3;

    } else if (valor < aux->Placa){
        return isPlacaRepetido(valor, aux->Izquierda);

    } else if (valor > aux->Placa){
        return isPlacaRepetido(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolAA_Carros :: MostrarInorde(pnodocarro aux){

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
void ArbolAA_Carros :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodocarro aux = primero;
   
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todos los Carros\n"<< endl;
   
   
   MostrarInorde(aux);

}
void ArbolAA_Carros :: Mostrar(pnodocarro aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->Placa << espacio << aux->Modelo << espacio << aux->NumeroAsientos << espacio;
   cout << aux->Ano << espacio << aux->PrecioCarro << aux->EstadodelCarro << espacio <<"  >>" << endl;


}
void ArbolAA_Carros :: MostrarNodo(pnodocarro aux){

   //Permite imprimir la informacion del nodo recibido

   if (aux == NULL){
      cout<<"Error: Puntero nulo\n";
      return;
   }

   char espacio[] = "; ";

   cout << aux->Placa << espacio << aux->Modelo << espacio << aux->NumeroAsientos << espacio;
   cout << aux->Ano << espacio << aux->PrecioCarro<< espacio << aux->EstadodelCarro << espacio <<"  >>" << endl;


}

bool ArbolAA_Carros :: getNodo(pnodocarro &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodocarro aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodocarro ArbolAA_Carros :: getNodo(int valor){

//funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodocarro aux = primero;
   
   return getNodo(valor, aux);


}
pnodocarro ArbolAA_Carros :: getNodo(int valor, pnodocarro aux){

//funcion recursiva que busca por el puntero con su identificacion == valor

   pnodocarro temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->Placa){
      //encontro el puntero
      return aux;
   }

   temp = getNodo(valor, aux->Izquierda);

   if (temp != NULL){
      //pertenece al hijo izquierda del nodo actual
      return temp;
   }

   temp = getNodo(valor, aux->Derecha);

   if (temp != NULL){
      //pertenece al hijo derecha del nodo actual
      return temp;
   }

   // no lo encontro en toda la estructura
   return NULL;
}


int ArbolAA_Carros :: borrarNodo(pnodocarro nodo){

  if (nodo == NULL){
    return -1;
  }
  
  //implementacion del borrado
  return 1;

}

int ArbolAA_Carros :: getPlaca(int &valor, pnodocarro aux){

  if (aux == NULL){
    return -4;
  }
  
  valor = aux->Placa;
  return 1;
}
int ArbolAA_Carros :: getModelo(char *nombre, pnodocarro aux){

  int i;

  if (aux == NULL){
    return -4;
  }

  for (i = 0; i < sizeof(aux->Modelo); i++) {
     nombre[i] = aux->Modelo[i];
  }
  return 1;
}
int ArbolAA_Carros :: getNumeroAsientos(int &valor, pnodocarro aux){

    if (aux == NULL){
    return -4;
  
  }
  valor = aux->NumeroAsientos;
  return 1;
}
int ArbolAA_Carros :: getAno(int &valor, pnodocarro aux){

    if (aux == NULL){
    return -4;
  
  }
  valor = aux->Ano;
  return 1;
}
int ArbolAA_Carros :: getPrecioCarro(int &valor, pnodocarro aux){

    if (aux == NULL){
    return -4;
  
  }
  valor = aux->PrecioCarro;
  return 1;
}
int ArbolAA_Carros :: getEstadodelCarro(char &valor, pnodocarro aux){

  if (aux == NULL){
  return -4;
  
  }
  valor = aux->EstadodelCarro;
  return 1;
}

int ArbolAA_Carros :: setPlaca(int valor, pnodocarro aux){

  if (aux == NULL){
  return -4;
  
  }
   aux->Placa = valor; // asignacion del valor en el nodo pos
   return 1;
}
int ArbolAA_Carros :: setModelo(char *nombre, pnodocarro aux){ // restringido por buffer de la clase y nombre debe terminar con '\000'

  int i;

  if (aux == NULL){
    return -4;
  
  }

   for (i = 0; (i < sizeof(aux->Modelo)); i++) { // limpieamos la variable
      aux->Modelo[i] = '\000';
   }

   for (i = 0; ((nombre[i]!= '\000') && (i < sizeof(aux->Modelo))); i++) { // asignamos valor
      aux->Modelo[i] = nombre[i];
   }
   return 1;
}
int ArbolAA_Carros :: setNumeroAsientos(int valor, pnodocarro aux){

  if (aux == NULL){
    return -4;
  
  }
   aux->NumeroAsientos = valor;
   return 1;
}
int ArbolAA_Carros :: setAno(int valor, pnodocarro aux){

  if (aux == NULL){
    return -4;
  
  }
   aux->Ano = valor;
   return 1;
}
int ArbolAA_Carros :: setPrecioCarro(int valor, pnodocarro aux){

  if (aux == NULL){
    return -4;
  
  }
   aux->PrecioCarro = valor;
   return 1;
}
int ArbolAA_Carros :: setEstadodelCarro(char valor, pnodocarro aux){
  
  if (aux == NULL){
    return -4;
  
  }

  if (valor == 'R' || valor == 'r'){
    aux->EstadodelCarro = 'R';
    return 1;

  } else if (valor == 'L' || valor == 'l'){
    aux->EstadodelCarro = 'L';
    return 1;

  }  else if (valor == 'O' || valor == 'o'){
    aux->EstadodelCarro = 'O';
    return 1;

  }
  return -4;
}





