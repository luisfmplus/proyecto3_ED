
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

//falta implementar la funcion de borrarNodo()

#ifndef _ARRBOLAVLFLOTILLAS_H
#define	_ARRBOLAVLFLOTILLAS_H
#include "5AVLTipoFlotilla.cpp"
#endif

#include <iostream>

using namespace std;



class NodoAgencia {
   public:
    ArbolAVL_Flotilla* flotilla;

    NodoAgencia(int IA, char* nom, int CdV) {
       flotilla = new ArbolAVL_Flotilla();
       IdentidadAg = IA;
       CantidadVehiculos = CdV;

       for (int i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

       }
       Izquierda = NULL;
       Derecha =NULL;
    }

      string mostrar(){
         string espacio = "|";
         return to_string(IdentidadAg) + espacio + string(Nombre) + espacio + to_string(CantidadVehiculos) + espacio;
      }


   private:
    int IdentidadAg;
    char Nombre [30] = "\000";
    int CantidadVehiculos;
    NodoAgencia *Izquierda;
    NodoAgencia *Derecha;
    
        
   friend class ArbolABB_Agencias;
};

typedef NodoAgencia *pnodoAgencia;



class ArbolABB_Agencias {
   public:
    ArbolABB_Agencias() { primero = NULL; }
    ~ArbolABB_Agencias();
    
    int getIdentidadAg(int& variable, pnodoAgencia aux);
    int getNombre(char* nombre, pnodoAgencia aux);
    int getCantidadVehiculos(int &variable, pnodoAgencia aux);

    int setIdentidadAg(int valor, pnodoAgencia aux);
    int setNombre(char* nombre, pnodoAgencia aux);
    int setCantidadVehiculos(int valor, pnodoAgencia aux);

    pnodoAgencia getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isIdentidadAgRepetido(int valor);
    int insertarNodo(int IA,char* nom, int CdV);
    void MostrarNodo(pnodoAgencia aux);
    string Mostrar();
    pnodoAgencia getNodo(int valor);
    bool getNodo(pnodoAgencia &recibir, int valor);
    int borrarNodo(pnodoAgencia nodo);
    int borrarNodo(int valor);
    
   private:

    bool arbolVacio() { return primero == NULL; }
    pnodoAgencia getNodo(int valor, pnodoAgencia aux);
    int getFactorBalance(pnodoAgencia aux);
    void MostrarInorde(pnodoAgencia aux);
    void Mostrar(pnodoAgencia aux);
    int isIdentidadAgRepetido(int valor, pnodoAgencia aux);
    int insertarNodo(int IA,char* nom, int CdV, pnodoAgencia aux);
    void borrarArbol(pnodoAgencia node);

    int borrarNodo(pnodoAgencia nodo, pnodoAgencia aux, bool& encontrado);
    pnodoAgencia minValor(pnodoAgencia hijoderecha);
    pnodoAgencia maxValor(pnodoAgencia hijoIzquierda);

    pnodoAgencia primero;
    pnodoAgencia ultimonodo;
  
};



ArbolABB_Agencias :: ~ArbolABB_Agencias(){

  borrarArbol(primero);
  primero = NULL;
   
}



void ArbolABB_Agencias :: borrarArbol(pnodoAgencia node) {
   
   if (node == NULL){
      return;
   } 
  
   
   borrarArbol(node->Izquierda); 
   borrarArbol(node->Derecha); 
     
   delete node;
}



int ArbolABB_Agencias :: insertarNodo(int IA,char* nom, int CdV, pnodoAgencia aux){

   //inserta un nodo. Busca su pocicision de forma reursiva
    
   if (IA < aux->IdentidadAg){ //revisamos que sea menor

      if (aux->Izquierda != NULL){ //preguntamos si el puntero es nulo
         return insertarNodo(IA, nom, CdV, aux->Izquierda);
            
        } else {

            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Izquierda = new NodoAgencia(IA, nom, CdV);
            ultimonodo = aux->Izquierda;
            return 1;
        
        }
  
   } else if (IA > aux->IdentidadAg){//revisamos que sea mayor

        if (aux->Derecha != NULL){
            return insertarNodo(IA, nom, CdV, aux->Derecha);

        } else {

            //cuando entra estamos en un nodo con su hijo derecha == NULL
            aux->Derecha = new NodoAgencia(IA, nom, CdV);
            ultimonodo = aux->Derecha;
            return 1;
        
        }
   }
   return-4;
}
int ArbolABB_Agencias :: insertarNodo(int IA,char* nom, int CdV){


   if (primero == NULL){
      primero = new NodoAgencia(IA, nom, CdV);
      ultimonodo = primero;
      return 1;
   }
    
   int condicion = isIdentidadAgRepetido(IA); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodoAgencia aux = primero;

   return insertarNodo(IA, nom, CdV, aux);

}

int ArbolABB_Agencias :: isIdentidadAgRepetido(int valor){ // me informa que el nodo ya existe o que no existe

    pnodoAgencia aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->IdentidadAg == valor){
        return -3;

    } else if (valor < aux->IdentidadAg){
        return isIdentidadAgRepetido(valor, aux->Izquierda);

    } else if (valor > aux->IdentidadAg){
        return isIdentidadAgRepetido(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolABB_Agencias :: isIdentidadAgRepetido(int valor, pnodoAgencia aux){ // me informa que el nodo ya existe o que no existe

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->IdentidadAg == valor){
        return -3;

    } else if (valor < aux->IdentidadAg){
        return isIdentidadAgRepetido(valor, aux->Izquierda);

    } else if (valor > aux->IdentidadAg){
        return isIdentidadAgRepetido(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolABB_Agencias :: MostrarInorde(pnodoAgencia aux){
   //funcion recursiva auxiliar muestras todos los nodos contenidos en la estructura en inorden
   if (aux == NULL){
      return;
   }
   MostrarInorde(aux->Izquierda);
   Mostrar(aux);
   MostrarInorde(aux->Derecha);
}

string infoAgencias;
string ArbolABB_Agencias :: Mostrar(){
   //Muestra toda la informacion contenida en la estructura  de manera inorden
   infoAgencias = "";
   pnodoAgencia aux = primero;
   if (aux != NULL){
      MostrarInorde(aux);
   }
   return infoAgencias;
}

void ArbolABB_Agencias :: Mostrar(pnodoAgencia aux){
   string espacio = "|";
   infoAgencias += to_string(aux->IdentidadAg) + espacio + string(aux->Nombre) + espacio + to_string(aux->CantidadVehiculos) + espacio;
}

void ArbolABB_Agencias :: MostrarNodo(pnodoAgencia aux){

   //Permite imprimir la informacion del nodo recibido

  if (aux == NULL){
    cout<<"Error: Puntero nulo\n";
    return;
  
  }

  char espacio[] = "; ";

  cout << aux->IdentidadAg << espacio << aux->Nombre << espacio << aux->CantidadVehiculos << "  >>" << endl;


}

bool ArbolABB_Agencias :: getNodo(pnodoAgencia &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodoAgencia aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodoAgencia ArbolABB_Agencias :: getNodo(int valor){

   //funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodoAgencia aux = primero;
   
   return getNodo(valor, aux);


}
pnodoAgencia ArbolABB_Agencias :: getNodo(int valor, pnodoAgencia aux){

   //funcion recursiva que busca por el puntero con su identificacion == valor

   pnodoAgencia temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->IdentidadAg){
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

pnodoAgencia ArbolABB_Agencias :: getultimoNodoInsertado(){
   return ultimonodo;
}


int ArbolABB_Agencias :: borrarNodo(pnodoAgencia nodo){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodoAgencia aux = primero;


   //validacion de la existencia del nodo a borrar
	if (nodo == NULL){
      //solamente entra a quí si el "nodo" es nulo
      //nodo existe y por lo tanto se puede borrar
      return -4;
   }
   

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}
int ArbolABB_Agencias :: borrarNodo(int valor){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodoAgencia aux = primero;


    //validacion de la existencia del nodo a borrar
	if (isIdentidadAgRepetido(valor) == -3){
		//solamente entra si el valor no existe
		return -4;
	}
	
	pnodoAgencia nodo = getNodo(valor);

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  borrarNodo(nodo, aux, encontrado);
    }

   return i;

}
int ArbolABB_Agencias :: borrarNodo(pnodoAgencia nodo, pnodoAgencia aux, bool& encontrado){

   //nodo nunca sera null

   int i;
   pnodoAgencia min;
   pnodoAgencia max;
   pnodoAgencia borrar;

   if ((aux == NULL)){
     return -1;
   }
  
   // es menor lo que busco?
   if (aux->IdentidadAg > nodo->IdentidadAg){
      i = borrarNodo(nodo, aux->Izquierda, encontrado);

   // es mayor lo que busco
   } else if (aux->IdentidadAg < nodo->IdentidadAg){
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

				primero = NULL; //raiz a nulo
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        		return 1;
	    	}

        	if (aux->Derecha == nodo){
        	    //min y max son NULL, ya que el nodo a borrar es una hoja

        	    delete borrar;
        	    aux->Derecha = NULL;
	
        	} else {

        	    delete borrar;
        	    aux->Izquierda = NULL;

        	}

        	encontrado = false;
        	return 1;

    	}
      
    	if (nodo->Izquierda == NULL){
        	// el nodo a borrar tiene un hijo del lado derecho y no del lado izquirdo

        	borrar = nodo;

			if (nodo == primero){
				// trabajamos en la raiz

				primero = nodo->Derecha; //raiz a nulo
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        		return 1;
	    	}

        	if (aux->Derecha == nodo){

        		aux->Derecha = nodo->Derecha;
        	    delete borrar;
	
        	} else {

        	    aux->Izquierda = nodo->Derecha;
        	    delete borrar;

        	}

        	encontrado = false;
        	return 1;
	
    	}
      
    	if (nodo->Derecha == NULL){
        	// el nodo a borrar tiene un hijo del lado izquierdo y no del lado derecho

        	borrar = nodo;

			if (nodo == primero){
				// trabajamos en la raiz

				primero = nodo->Izquierda; //raiz a nulo
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        		return 1;
	    	}

        	if (aux->Derecha == nodo){

        		aux->Derecha = nodo->Izquierda;
            	delete borrar;
            
         	} else {

            	aux->Izquierda = nodo->Izquierda;
            	delete borrar;

        	}

        	encontrado = false;
        	return 1;
      
      
    	}
      
    	// el nodo tiene hijos de ambos lados

    	min = minValor(nodo->Derecha);
    	max = maxValor(nodo->Izquierda);

    	if (max == NULL){
        	//significa que el hijo izquierdo es el numero mayor

        	borrar = nodo;

			if (nodo == primero){
				// trabajamos en la raiz

				primero = nodo->Izquierda; //raiz al mayor hijo izquierdo
				primero->Derecha = nodo->Derecha; // actualizamos el puntero derecha
				encontrado = false; // la dejamos en falso
        		delete borrar; // borramos el nodo
				return 1;
	    	}

        	if (aux->Derecha == nodo){

        	    aux->Derecha = nodo->Izquierda;
				aux->Derecha->Derecha = nodo->Derecha;
        	    delete borrar;
	
        	} else {

        	    aux->Izquierda = nodo->Izquierda;
				aux->Izquierda->Derecha = nodo->Derecha;
        	    delete borrar;

        	}


    	} else if(min == NULL){
        	//significa que el hijo derecho es el numero menor

        	borrar = nodo;

			if (nodo == primero){
				// trabajamos en la raiz

				primero = nodo->Derecha; //raiz al menor hijo derecho
				primero->Izquierda = nodo->Izquierda; // actualizamos el puntero izquierda
				encontrado = false; // la dejamos en falso
        		delete borrar; // borramos el nodo
				return 1;
	    	}

        	if (aux->Derecha == nodo){

            	aux->Derecha = nodo->Derecha;
				aux->Derecha->Izquierda = nodo->Izquierda;
            	delete borrar;
            
        	} else {

            	aux->Izquierda = nodo->Derecha;
				aux->Izquierda->Izquierda = nodo->Izquierda;
            	delete borrar;

        	}



      	} else {
         	//en ambas hijos tiene mas nodos que 1
         	//por default se utilizara el maxValor.
         	//cuando este se acabe, entonces el nodo a borrar no tendra hijos izquierdos y por lo tanto no entrara aqui

         	borrar = nodo;

			if (nodo == primero){
				// trabajamos en la raiz

				primero = max->Derecha; //raiz al mayor hijo izquierdo
				max->Derecha = NULL; // el padre del nodo hoja le dejamos el hijo en nulo
				primero->Derecha = nodo->Derecha;
				primero->Izquierda = nodo->Izquierda;
				encontrado = false; // la dejamos en falso
        		delete borrar; // borramos el nodo
				return 1;
	    	}

        	if (aux->Derecha == nodo){

            	aux->Derecha = max->Derecha; //movemos el nodo hoja a su nueva posicion
        	    max->Derecha = NULL; // dejamos el padre de ese nodo hoja en nulo
				aux->Derecha->Derecha = nodo->Derecha; // le actualizamos su puntero derecha
				aux->Derecha->Izquierda = nodo->Izquierda; // le actualizamos el puntero izquierda
        	    delete borrar;
	
        	} else {

        	    aux->Izquierda = max->Derecha; //movemos el nodo hoja a su nueva posicion
        	    max->Derecha = NULL; // dejamos el padre de ese nodo hoja en nulo
				aux->Izquierda->Derecha = nodo->Derecha; // le actualizamos su puntero derecha
				aux->Izquierda->Izquierda = nodo->Izquierda; // le actualizamos el puntero izquierda
        	    delete borrar;

        	}
      	}

    	encontrado = false;
    	return 1;
      
  	}
   
	return i;
}

//busca al padre del nodo remplazador
pnodoAgencia ArbolABB_Agencias ::  minValor(pnodoAgencia hijoderecha){ 
   
   //recibe la posicion del nodo a la derecha de forma inicial
   // recibe la posicion del nodo a la izquierda de manera recursiva

   //retorna el nodo padre del nodo menor;
   //retorna null si el nodo min no existe
   //retorna null si el nodo padre del nodo min es el nodo a eliminar

   pnodoAgencia temp;

   if (hijoderecha == NULL){
      return NULL;
   }
   
   //no vamos al ultimo nodo a la izquierda del nodo inicial
   temp = minValor(hijoderecha->Izquierda);

   //cuando llegamos al nodo nulo me devolvera la pocision del nodo anterioR al nulo
   //osea, este es el nodo de menor valor
   

   if (temp != NULL){
      return temp;
      
   }


   //al utilizar este if; forzamos al algoritmo a devolver el padre del minimo
   if (hijoderecha->Izquierda == NULL){
      //esto solo sucede en el nodo de valor minimo;
      return NULL;
   }
   
   
   return hijoderecha;


}

//busca al padre del nodo remplazador
pnodoAgencia ArbolABB_Agencias ::  maxValor(pnodoAgencia hijoIzquierda){

   //recibe la posicion del nodo a la izquierda de forma inicial
   // recibe la posicion del nodo a la derecha de manera recursiva

   //retorna el nodo padre del nodo mayor;
   //retorna null si el nodo max no existe
   //retorna null si: el nodo padre del nodo max es el nodo a eliminar

   pnodoAgencia temp;

   if (hijoIzquierda == NULL){
      return NULL;
   }
   
   //no vamos al ultimo nodo a la izquierda del nodo inicial
   temp = maxValor(hijoIzquierda->Derecha);

   //cuando llegamos al nodo nulo me devolvera la pocision del nodo anterio al nulo
   //osea, este es el nodo de mayor valor
   if (temp != NULL){
      return temp;
      
   }

   //al utilizar este if; forzamos al algoritmo a devolver el padre del maximo
   if (hijoIzquierda->Derecha == NULL){
      //esto solo sucede en el nodo de valor maximo;
      return NULL;
   }

   return hijoIzquierda;

}


int ArbolABB_Agencias :: getIdentidadAg(int& variable, pnodoAgencia aux){

   if (aux == NULL){
      return -4;
   }
   
      variable = aux->IdentidadAg;
      return 1;
}
int ArbolABB_Agencias :: getNombre(char* nombre, pnodoAgencia aux){

   int i;

   if (aux == NULL){
      return -4;
   }
   

   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}
int ArbolABB_Agencias :: getCantidadVehiculos(int &variable, pnodoAgencia aux){

   if (aux == NULL){
      return -4;
   }
   
      variable = aux->CantidadVehiculos;
      return 1;
}



int ArbolABB_Agencias :: setIdentidadAg(int valor, pnodoAgencia aux){

   if (aux == NULL){
      return -4;
   }
   
   aux->IdentidadAg = valor; // asignacion del valor en el nodo pos
   return 1;
}
int ArbolABB_Agencias :: setNombre(char* nombre, pnodoAgencia aux){ // restringido por buffer de la clase. nombre dado debe terminar con '\000'

   int i;

   if (aux == NULL){
      return -4;
   }
   

   for (i = 0; (i < sizeof(aux->Nombre)); i++) { // limpiamos la variable
      aux->Nombre[i] = '\000';
   }

   for (i = 0; ((nombre[i]!= '\000') && (i < sizeof(aux->Nombre))); i++) { // asignamos valor
      aux->Nombre[i] = nombre[i];
   }
   return 1;
}
int ArbolABB_Agencias :: setCantidadVehiculos(int valor, pnodoAgencia aux){

   if (aux == NULL){
      return -4;
   }
   
   aux->CantidadVehiculos = valor;
   return 1;
}
