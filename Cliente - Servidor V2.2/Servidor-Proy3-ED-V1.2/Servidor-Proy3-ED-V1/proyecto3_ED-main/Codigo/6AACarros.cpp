
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

    string mostrar(){
      string espacio = "|";
      return to_string(Placa) + espacio + string(Modelo) + espacio + to_string(NumeroAsientos) + espacio + to_string(Ano) + espacio + to_string(PrecioCarro) + espacio + EstadodelCarro + espacio;
    }

     int getPrecioCarro(){
      return this->PrecioCarro;
    }
    int getPlaca(){
      return this->Placa;
    }

    void setEstadodelCarro(char var){
      this->EstadodelCarro=var;
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
    string MostrarNodo(pnodocarro aux);
    string Mostrar();
    pnodocarro getNodo(int valor);
    int borrarNodo(pnodocarro nodo);
    int borrarNodo(int valor);


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
    void correccionBorrado(pnodocarro aux, bool direccion);
    void bajarNivelNodos(pnodocarro aux);

    int borrarNodo(pnodocarro nodo, pnodocarro aux, bool& encontrado);
    pnodocarro MINValor(pnodocarro hijoderecha);
    pnodocarro MAXValor(pnodocarro hijoIzquierda);
    void swapNodos(pnodocarro nodo1, pnodocarro nodo2);

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

void ArbolAA_Carros :: bajarNivelNodos(pnodocarro aux) {

  int niv = aux->nivel;
  pnodocarro temp = aux;

  while (1){
    //aux = aux->Izquierda; eso se traduce a:
    aux = aux->Padre;

    if (aux == NULL){
      aux = temp;
      break;
    }

    if (niv != aux->nivel){
      aux = temp;
      break;
    }
    temp = aux;

  }

  // el valor de aux es el primer nodo con nivel equivalente al nodo recibido
  // por lo tanto pueden haber mas nodos con el mismo nivel a la derecha de este nodo aux

  niv--;

  while (aux->nivel > niv){
    //aux = aux->Izquierda; eso se traduce a:

    aux->nivel--;
    aux = aux->Derecha;

    if (aux == NULL){
      break;
    }

  }
}

void ArbolAA_Carros :: correccionBorrado(pnodocarro aux, bool direccion){

  //recibimos el padre del nodo recien borrado y la direccion del hijo del borrado

  pnodocarro temp = NULL;

  if ((aux->nivel == 1) && direccion){
    // se borro hijo derecho del padre y este hijo era hoja

    // esta eliminacion no requiere nunca correccion del arbol.
    return;
  }

  while (aux != NULL){
    
    if (temp != NULL){
      //cambiamos el valor de direccion
    
      if (aux->Derecha == temp){
        direccion = true;

      } else {
        direccion = false;

      }
    }
    
    if (direccion){
      //direccion de procedencia derecha
      
      if (aux->nivel == 1){
        //se deja igual el nivel

      } else if (aux->nivel > (aux->Derecha->nivel + 1)){
        // si entra significa que existe una diferencia mayor a 2 de nivel
        bajarNivelNodos(aux);

      }
    
    } else {
      //direccion de procedencia izquierda
      
      if (aux->nivel == 1){
        //se deja igual el nivel
        // es imposible que pase este if

      } else if (aux->Izquierda == NULL){
        // si entra significa que no tiene hijo izquierda
        bajarNivelNodos(aux);

      } else if (aux->nivel > (aux->Izquierda->nivel + 1)){
        // si entra la diferencia de altura es mayor a 1
        bajarNivelNodos(aux);
      }
      

    }

    aux = torcion(aux);
    torcion(aux->Derecha);
    if (aux->Derecha != NULL){
      torcion(aux->Derecha->Derecha);
    }
    
    aux = division(aux);
    division(aux->Derecha);


    temp = aux;

    // nos movemos al nodo padre
    aux = aux->Padre;

  }
  
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
   //funcion recursiva auxiliar muestras todos los nodos contenidos en la estructura en inorden
   if (aux == NULL){
      return;
   }
   MostrarInorde(aux->Izquierda);
   Mostrar(aux);
   MostrarInorde(aux->Derecha);
}

string infoCarros;
string ArbolAA_Carros :: Mostrar(){
   //Muestra toda la informacion contenida en la estructura de manera inorden
   pnodocarro aux = primero;
   infoCarros = "";
   if (aux != NULL){
    MostrarInorde(aux);
   }
  return infoCarros;
}

void ArbolAA_Carros :: Mostrar(pnodocarro aux){
   //imprime en pantalla los valores de la informacion del nodo indicado
   string espacio = "|";
   infoCarros += to_string(aux->Placa) + espacio + string(aux->Modelo) + espacio + to_string(aux->NumeroAsientos) + espacio + to_string(aux->Ano) + espacio + to_string(aux->PrecioCarro) + espacio + aux->EstadodelCarro + espacio;
}

string ArbolAA_Carros :: MostrarNodo(pnodocarro aux){
    //Permite imprimir la informacion del nodo recibido
    try {
      if (aux != NULL){
        string espacio = "|";
        return to_string(aux->Placa) + espacio + string(aux->Modelo) + espacio + to_string(aux->NumeroAsientos) + espacio + to_string(aux->Ano) + espacio + to_string(aux->PrecioCarro) + espacio + aux->EstadodelCarro + espacio;
      }
    }
    catch (exception exp) {
        return "";
    }
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
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar


  bool encontrado = false;
  pnodocarro aux = primero;


   //validacion de la existencia del nodo a borrar
	if (nodo == NULL){
      //solamente entra a quí si el "nodo" es nulo
      //nodo existe y por lo tanto se puede borrar
      return -4;
   }
   

   borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  borrarNodo(nodo, aux, encontrado);
    }

   return 1;

}

int ArbolAA_Carros :: borrarNodo(int valor){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodocarro aux = primero;


    //validacion de la existencia del nodo a borrar
	if (isPlacaRepetido(valor) == -3){
		//solamente entra si el valor no existe
		return -4;
	}
	
	pnodocarro nodo = getNodo(valor);

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}

int ArbolAA_Carros :: borrarNodo(pnodocarro nodo, pnodocarro aux, bool& encontrado){

   //nodo nunca sera null

   int i;
   bool direccion;
   pnodocarro min;
   pnodocarro max;
   pnodocarro borrar;

   if ((aux == NULL)){
     return -1;
   }
  
   // es menor lo que busco?
   if (aux->Placa > nodo->Placa){
      i = borrarNodo(nodo, aux->Izquierda, encontrado);

   // es mayor lo que busco
   } else if (aux->Placa < nodo->Placa){
      i = borrarNodo(nodo, aux->Derecha, encontrado);

   } else{

      //me encuentro en el nodo a borrar

	  if (!encontrado){
			//unicamente entra aquí si encontrado = false

			encontrado = true;
      
      		//esto retornara a la llamada anterior o a la llamada principal
      		return 1;
	  
	  }
   }

	if (encontrado){
      
    //aux es el padre de nodo
   
    if (nodo->Derecha == nodo->Izquierda){
      // el nodo a borrar es una hoja

      borrar = nodo;

			if (nodo == primero){
			  // trabajamos en la raiz
        // solamente ocurre cuando solamente existe el nodo raiz

			  primero = NULL; //raiz a nulo
			  delete borrar; // borramos la raiz
			  encontrado = false; // la dejamos en falso
        return 1;
	    }

      if (aux->Derecha == nodo){
        //min y max son NULL, ya que el nodo a borrar es una hoja

        delete borrar;
        aux->Derecha = NULL;
        direccion = true;

      } else {

      	delete borrar;
      	aux->Izquierda = NULL;
        direccion = false;
      }

      encontrado = false;
      
      correccionBorrado(aux, direccion);
      return 1;

    }
      
    if (nodo->Izquierda == NULL){
      // el nodo a borrar tiene un hijo del lado derecho y no del lado izquirdo
      borrar = nodo;

			if (nodo == primero){
				// trabajamos en la raiz
        // solamente ocurre cuando existen solamente 2 nodos

				primero = nodo->Derecha; //raiz a nulo
        primero->Padre = nodo->Padre;
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        return 1;
	    }

      if (aux->Derecha == nodo){

        aux->Derecha = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
        aux->Derecha->Padre = aux;
        direccion = true;
        delete borrar;
	
      } else {

        aux->Izquierda = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
        aux->Izquierda->Padre = aux;
        direccion = false;
        delete borrar;

      }

      correccionBorrado(aux, direccion);
      encontrado = false;
      return 1;
	
    }
      
    if (nodo->Derecha == NULL){
      // el nodo a borrar tiene un hijo del lado izquierdo y no del lado derecho

      borrar = nodo;

		  if (nodo == primero){
				// trabajamos en la raiz
        // solamente ocurre cuando existen solamente 2 nodos

				primero = nodo->Izquierda; //raiz a nulo
        primero->Padre = nodo->Padre;
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        return 1;
	    }

      if (aux->Derecha == nodo){
        
      	aux->Derecha = nodo->Izquierda;
        aux->Derecha->Padre = aux;
        direccion = true;
        delete borrar;
            
      } else {
          
        aux->Izquierda = nodo->Izquierda;
        aux->Izquierda->Padre = aux;
        direccion = false;
        delete borrar;

      }

      correccionBorrado(aux, direccion);
      encontrado = false;
      return 1;
      
    	}
      
    	// el nodo tiene hijos de ambos lados

      borrar = nodo;

    	min = MINValor(nodo->Derecha); // retorna el nodo a remplazar
    	max = MAXValor(nodo->Izquierda); // retorna el nodo a remplazar

      //por default se utilizara el maxValor.
      //cuando este se acabe, entonces el nodo a borrar no tendra hijos izquierdos y por lo tanto no entrara aqui

      bool segundoBorrado = false;
      int niv;
      swapNodos(max, nodo);
      niv = nodo->nivel;
      nodo->nivel = max->nivel;
      max->nivel = niv;
      //recordatorio; la funcion intercambia solamente las conexiones de los nodos, el nodo a borrar sigue siendo "nodo"

      // usamos "max->Izquierda" como punto de partida, ya que sabemos que la ubicacion original del nodo "max", se encuentra
      // en el subarbol izquierdo de "nodo", pero al intercambiar las conexiones, el puntero de ese subarbol izquierdo se encuentra en "max"
      
      if (max->Izquierda == nodo){
        // el nodo a borrar es el hijo adyacente y este no puede tener hijos derechos
        // esta condicional es de alta importancia, ya que protege de una excepcion con la cual el algoritmo no puede lidiar
        // de forma ordenada y limpia

        max->Izquierda = nodo->Izquierda;

        if (nodo->Izquierda != NULL){
          // actualizamos el puntero padre del hijo izquierdo de nodo
          nodo->Izquierda->Padre = max;
        
        }
        
        delete borrar;
        correccionBorrado(max, false);
        encontrado = false;
        return 1;

      }
      
      borrarNodo(nodo,max->Izquierda, segundoBorrado);

    	encontrado = false;
    	return 1;
      
  	}
   
	return i;
}

//busca el nodo remplazador
pnodocarro ArbolAA_Carros :: MINValor(pnodocarro hijoderecha){ 
   
   // requiere que el nodo tenga un puntero a su padre

   //recibe la posicion del nodo a la derecha de forma inicial
   // recibe la posicion del nodo a la izquierda de manera recursiva

   //retorna el nodo menor;
   //retorna null si el nodo min no existe

   pnodocarro temp;

   if (hijoderecha == NULL){
      return NULL;
   }
   
   //no vamos al ultimo nodo a la izquierda del nodo inicial
   temp = MINValor(hijoderecha->Izquierda);

   //cuando llegamos al nodo nulo me devolvera la pocision del nodo anterioR al nulo
   //osea, este es el nodo de menor valor
   
   // se mantiene el puntero del nodo a remplazar cuando se encontro
   if (temp != NULL){
      return temp;
      
   }
      
   // se retorna el nodo a remplazar
   return hijoderecha;

}

//busca el nodo remplazador
pnodocarro ArbolAA_Carros :: MAXValor(pnodocarro hijoIzquierda){
   
   // requiere que el nodo tenga un puntero a su padre
   
   //recibe la posicion del nodo a la izquierda de forma inicial
   // recibe la posicion del nodo a la derecha de manera recursiva

   //retorna el nodo mayor;
   //retorna null si el nodo max no existe

   pnodocarro temp;

   if (hijoIzquierda == NULL){
      return NULL;
   }
   
   //no vamos al ultimo nodo a la izquierda del nodo inicial
   temp = MAXValor(hijoIzquierda->Derecha);

   //mantiene el puntero del nodo de mayor valor
   if (temp != NULL){
      return temp;
      
   }

   //retorna el nodo de mayor valor
   return hijoIzquierda;

}

void ArbolAA_Carros :: swapNodos(pnodocarro nodo1, pnodocarro nodo2){

  //esta funcion cambia todas las referencias de los punteros entre si y la del padre apuntando a el puntero
  // de forma que el nodo cambiado no afecte la intregidad del arbol

  bool enRaiz1 = false;
  bool enRaiz2 = false;
  bool hijodirecto = false;
  bool hijodirD1_2 = false;
  bool hijodirI1_2 = false;
  bool hijodirD2_1 = false;
  bool hijodirI2_1 = false;

  if (nodo1 == primero){

    enRaiz1 = true;

  }

  if (nodo2 == primero){
      
    enRaiz2 = true;

  }

  if (nodo1->Padre == nodo2){
    //el nodo2 es el padre del nodo1

    if (nodo2->Derecha == nodo1){

      hijodirD2_1 = true;

    } else {

      hijodirI2_1 = true;
    
    }
    hijodirecto = true;

  } else if (nodo2->Padre == nodo1){

    if (nodo1->Derecha == nodo2){
      hijodirD1_2 = true;
        
    } else {
      hijodirI1_2 = true;
      
    }
    hijodirecto = true;

  }
   

  pnodocarro temp1;
  pnodocarro temp2;

  temp1 = nodo1->Padre;
  temp2 = nodo2->Padre;

  if (enRaiz1){
      
    //actualizamos los punteros de los nodos padres

    primero = nodo2;
      
    if (temp2->Derecha == nodo2){
       
      temp2->Derecha = nodo1;

    } else {

      temp2->Izquierda = nodo1;

    }
      
  } else if (enRaiz2){
      
    //actualizamos los punteros de los nodos padres

    primero = nodo1;
      
    if (temp1->Derecha == nodo1){
       
      temp1->Derecha = nodo2;

    } else {

      temp1->Izquierda = nodo2;

    }

  } else if (hijodirecto){
    //tenemos un remplazo entre un nodo padre y su nodo hijo

    if (hijodirD1_2){
      // nodo2 es hijo derecho de nodo1
      nodo2->Padre = nodo1->Padre;
      nodo1->Padre = nodo2;

      if (nodo2->Padre->Derecha == nodo1){
        nodo2->Padre->Derecha = nodo2;
      
      } else {
        nodo2->Padre->Izquierda = nodo2;

      }
    
    } else if (hijodirI1_2){
      // nodo2 es hijo izquierdo de nodo1
      nodo2->Padre = nodo1->Padre;
      nodo1->Padre = nodo2;

      if (nodo2->Padre->Derecha == nodo1){
        nodo2->Padre->Derecha = nodo2;
      
      } else {
        nodo2->Padre->Izquierda = nodo2;

      }
    
    } else if (hijodirD2_1){
      // nodo1 es hijo derecho de nodo2
      nodo1->Padre = nodo2->Padre;
      nodo2->Padre = nodo1;

      if (nodo1->Padre->Derecha == nodo2){
        nodo1->Padre->Derecha = nodo1;
      
      } else {
        nodo1->Padre->Izquierda = nodo1;

      }
    
    } else if (hijodirI2_1){
      // nodo1 es hijo izquierdo de nodo2
      nodo1->Padre = nodo2->Padre;
      nodo2->Padre = nodo1;

      if (nodo1->Padre->Derecha == nodo2){
        nodo1->Padre->Derecha = nodo1;
      
      } else {
        nodo1->Padre->Izquierda = nodo1;

      }
    
    }
    
  } else {

    //solamente entra cuando se intermambian nodos no adyacentes
    //actualizamos los punteros a los padres de los nodos cambiando
    nodo1->Padre = temp2;
    nodo2->Padre = temp1;

  }

  temp1 = nodo1->Derecha;
  temp2 = nodo2->Derecha;

  if (temp1 == NULL){
      
    if (hijodirD2_1){
      // nodo1 es hijo derecho de nodo2
      nodo1->Derecha = nodo2; // no se puede hacer nodo1->Derecha = nodo2->derecha , ya que nodo2->derecha == nodo1
      nodo2->Padre = nodo1;
      nodo2->Derecha = temp1; // decimos que este puntero es nulo

    } else {
      //no requiere actualizar el padre de temp1 porque esta nulo
      nodo2->Derecha = temp1;
      nodo1->Derecha = temp2;
      //actualizamos el puntero al padre del nodo hijo
      temp2->Padre = nodo1;

    }

  } 
  
  if (temp2 == NULL){

    if (hijodirD1_2){
      // nodo2 es hijo derecho de nodo1
      nodo2->Derecha = nodo1;
      nodo1->Padre = nodo2;
      nodo1->Derecha = temp2;

    } else {
    //no requiere actualizar el padre de temp2 porque esta nulo
    nodo1->Derecha = temp2;
    nodo2->Derecha = temp1;
    //actualizamos el puntero al padre del nodo hijo
    temp1->Padre = nodo2;

    }
  }

  if ((temp1 != NULL) && (temp2 != NULL)){

    if (hijodirD1_2){
      // nodo2 es hijo derecho de nodo1
      nodo2->Derecha = nodo1;
      nodo1->Padre = nodo2;
      nodo1->Derecha = temp2;
      temp2->Padre = nodo1;

    }  else if (hijodirD2_1){
      // nodo1 es hijo derecho de nodo2
      nodo1->Derecha = nodo2; // no se puede hacer nodo1->Derecha = nodo2->derecha , ya que nodo2->derecha == nodo1
      nodo2->Padre = nodo1;
      nodo2->Derecha = temp1; // decimos que este puntero es nulo
      temp1->Padre = nodo2;

    } else {

      nodo2->Derecha = temp1;
      nodo1->Derecha = temp2;
      //actualizamos el puntero al padre de los nodo hijo
      temp2->Padre = nodo1;
      temp1->Padre = nodo2;

    }

  }

  temp1 = nodo1->Izquierda;
  temp2 = nodo2->Izquierda;

  if (temp1 == NULL){

    if (hijodirI2_1){
      // nodo1 es hijo izquierdo de nodo2
      nodo1->Izquierda = nodo2; // no se puede hacer nodo1->Derecha = nodo2->derecha , ya que nodo2->derecha == nodo1
      nodo2->Padre = nodo1;
      nodo2->Izquierda = temp1; // decimos que este puntero es nulo

    } else {

      //no requiere actualizar el padre de temp1 porque esta nulo
      nodo2->Izquierda = temp1;

      nodo1->Izquierda = temp2;
      //actualizamos el puntero al padre del nodo hijo
      temp2->Padre = nodo1;

    }

  } 
  
  if (temp2 == NULL){


    if (hijodirI1_2){
      // nodo2 es hijo izquierdo de nodo1
      nodo2->Izquierda = nodo1;
      nodo1->Padre = nodo2;
      nodo1->Izquierda = temp2;

    } else {

      //no requiere actualizar el padre de temp2 porque esta nulo
      nodo1->Izquierda = temp2;

      nodo2->Izquierda = temp1;
      //actualizamos el puntero al padre del nodo hijo
      temp1->Padre = nodo2;

    }

  }

  if ((temp1 != NULL) && (temp2 != NULL)){

    if (hijodirI1_2){
      // nodo2 es hijo derecho de nodo1
      nodo2->Izquierda = nodo1;
      nodo1->Padre = nodo2;
      nodo1->Izquierda = temp2;
      temp2->Padre = nodo1;

    }  else if (hijodirI2_1){
      // nodo1 es hijo derecho de nodo2
      nodo1->Izquierda = nodo2; // no se puede hacer nodo1->Izquierda = nodo2->Izquierda , ya que nodo2->Izquierda == nodo1
      nodo2->Padre = nodo1;
      nodo2->Izquierda = temp1; // decimos que este puntero es nulo
      temp1->Padre = nodo2;

    } else {

      nodo2->Izquierda = temp1;
      nodo1->Izquierda = temp2;
      //actualizamos el puntero al padre de los nodo hijo
      temp2->Padre = nodo1;
      temp1->Padre = nodo2;

    }

  }

   return;

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





