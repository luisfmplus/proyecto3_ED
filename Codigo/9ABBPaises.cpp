
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


class NodoABBPais {
   public:

    ArbolABB_Hoteles* Hoteles;
    ArbolABB_Agencias* Agencias;

    NodoABBPais(int CH, char* nom) {
       Hoteles = new ArbolABB_Hoteles();
       Agencias = new ArbolABB_Agencias();
       CodPais = CH;

       for (int i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

       }
       Izquierda = NULL;
       Derecha =NULL;
    }


   private:
    int CodPais;
    char Nombre [30] = "\000";
    NodoABBPais *Izquierda;
    NodoABBPais *Derecha;
    
        
   friend class ArbolABB_Paises;
};

typedef NodoABBPais *pnodoabbpais;



class ArbolABB_Paises {
   public:
    ArbolABB_Paises() { primero = NULL; }
    ~ArbolABB_Paises();
    
    int getCodPais(int& variable, pnodoabbpais aux);
    int getNombre(char* nombre, pnodoabbpais aux);

    int setCodPais(int valor, pnodoabbpais aux);
    int setNombre(char* nombre, pnodoabbpais aux);

    pnodoabbpais getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isCodPais(int valor);
    int insertarNodo(int CH,char* nom);
    void MostrarNodo(pnodoabbpais aux);
    void Mostrar();
    pnodoabbpais getNodo(int valor);
    bool getNodo(pnodoabbpais &recibir, int valor);
    int borrarNodo(pnodoabbpais nodo);
    int borrarNodo(int valor);

    
   private:

    bool arbolVacio() { return primero == NULL; }
    pnodoabbpais getNodo(int valor, pnodoabbpais aux);
    void MostrarInorde(pnodoabbpais aux);
    void Mostrar(pnodoabbpais aux);
    int isCodPais(int valor, pnodoabbpais aux);
    int insertarNodo(int CH,char* nom, pnodoabbpais aux);
    void borrarArbol(pnodoabbpais node);
    int borrarNodo(pnodoabbpais nodo, pnodoabbpais aux, bool& encontrado);
    pnodoabbpais minValor(pnodoabbpais hijoderecha);
    pnodoabbpais maxValor(pnodoabbpais hijoIzquierda);

    pnodoabbpais primero;
    pnodoabbpais ultimonodo;
  
};



ArbolABB_Paises :: ~ArbolABB_Paises(){

  borrarArbol(primero);
  primero = NULL;
   
}



void ArbolABB_Paises :: borrarArbol(pnodoabbpais node) {
   
   if (node == NULL){
      return;
   } 
  
   
   borrarArbol(node->Izquierda); 
   borrarArbol(node->Derecha); 
     
   delete node;
}



int ArbolABB_Paises :: insertarNodo(int CH,char* nom, pnodoabbpais aux){

//inserta un nodo. Busca su pocicision de forma reursiva
    
   if (CH < aux->CodPais){//revisamos que sea menor

      if (aux->Izquierda != NULL){//preguntamos si el puntero es nulo
         return insertarNodo(CH, nom, aux->Izquierda);
            
        } else {
            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Izquierda = new NodoABBPais(CH, nom);
            ultimonodo = aux->Izquierda;
            return 1;
        
        }
  
   } else if (CH > aux->CodPais){ //revisamos que sea mayor

        if (aux->Derecha != NULL){ //preguntamos si el puntero es nulo
            return insertarNodo(CH, nom, aux->Derecha);

        } else {
            //cuando entra estamos en un nodo con su hijo derecha == NULL
            aux->Derecha = new NodoABBPais(CH, nom);
            ultimonodo = aux->Derecha;
            return 1;
        
        }
   }
   return-4;
}
int ArbolABB_Paises :: insertarNodo(int CH,char* nom){


   if (primero == NULL){
      primero = new NodoABBPais(CH, nom);
      ultimonodo = primero;
      return 1;
   }
    
   int condicion = isCodPais(CH); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodoabbpais aux = primero;

   return insertarNodo(CH, nom, aux);

}

int ArbolABB_Paises :: isCodPais(int valor){ // me informa que el nodo ya existe o que no existe

    pnodoabbpais aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->CodPais == valor){
        return -3;

    } else if (valor < aux->CodPais){
        return isCodPais(valor, aux->Izquierda);

    } else if (valor > aux->CodPais){
        return isCodPais(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolABB_Paises :: isCodPais(int valor, pnodoabbpais aux){ // me informa que el nodo ya existe o que no existe

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->CodPais == valor){
        return -3;

    } else if (valor < aux->CodPais){
        return isCodPais(valor, aux->Izquierda);

    } else if (valor > aux->CodPais){
        return isCodPais(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolABB_Paises :: MostrarInorde(pnodoabbpais aux){

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
void ArbolABB_Paises :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodoabbpais aux = primero;
   
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todos los Pisos\n"<< endl;
   
   
   MostrarInorde(aux);

}
void ArbolABB_Paises :: Mostrar(pnodoabbpais aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->CodPais << espacio << aux->Nombre << espacio << "  >>" << endl;


}
void ArbolABB_Paises :: MostrarNodo(pnodoabbpais aux){

   //Permite imprimir la informacion del nodo recibido

  if (aux == NULL){
    cout<<"Error: Puntero nulo\n";
    return;
  
  }

  char espacio[] = "; ";

  cout << aux->CodPais << espacio << aux->Nombre << espacio << "  >>" << endl;


}

bool ArbolABB_Paises :: getNodo(pnodoabbpais &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodoabbpais aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodoabbpais ArbolABB_Paises :: getNodo(int valor){

   //funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodoabbpais aux = primero;
   
   return getNodo(valor, aux);


}
pnodoabbpais ArbolABB_Paises :: getNodo(int valor, pnodoabbpais aux){

//funcion recursiva que busca por el puntero con su identificacion == valor

   pnodoabbpais temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->CodPais){
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

pnodoabbpais ArbolABB_Paises :: getultimoNodoInsertado(){
   return ultimonodo;
}

int ArbolABB_Paises :: borrarNodo(pnodoabbpais nodo){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodoabbpais aux = primero;


   //validacion de la existencia del nodo a borrar
	if (nodo == NULL){
      //solamente entra a quí si el "nodo" es nulo
      //nodo existe y por lo tanto se puede borrar
      return -4;
   }
   

    i =borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}
int ArbolABB_Paises :: borrarNodo(int valor){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodoabbpais aux = primero;


    //validacion de la existencia del nodo a borrar
	if (isCodPais(valor) == -3){
		//solamente entra si el valor no existe
		return -4;
	}
	
	pnodoabbpais nodo = getNodo(valor);

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}
int ArbolABB_Paises :: borrarNodo(pnodoabbpais nodo, pnodoabbpais aux, bool& encontrado){

   //nodo nunca sera null

   int i;
   pnodoabbpais min;
   pnodoabbpais max;
   pnodoabbpais borrar;

   if ((aux == NULL)){
     return -1;
   }
  
   // es menor lo que busco?
   if (aux->CodPais > nodo->CodPais){
       i = borrarNodo(nodo, aux->Izquierda, encontrado);

   // es mayor lo que busco
   } else if (aux->CodPais < nodo->CodPais){
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
pnodoabbpais ArbolABB_Paises ::  minValor(pnodoabbpais hijoderecha){ 
   
   //recibe la posicion del nodo a la derecha de forma inicial
   // recibe la posicion del nodo a la izquierda de manera recursiva

   //retorna el nodo padre del nodo menor;
   //retorna null si el nodo min no existe
   //retorna null si el nodo padre del nodo min es el nodo a eliminar

   pnodoabbpais temp;

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
pnodoabbpais ArbolABB_Paises ::  maxValor(pnodoabbpais hijoIzquierda){

   //recibe la posicion del nodo a la izquierda de forma inicial
   // recibe la posicion del nodo a la derecha de manera recursiva

   //retorna el nodo padre del nodo mayor;
   //retorna null si el nodo max no existe
   //retorna null si: el nodo padre del nodo max es el nodo a eliminar

   pnodoabbpais temp;

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



int ArbolABB_Paises :: getCodPais(int& variable, pnodoabbpais aux){

   if (aux == NULL){
      return -4;
   }
   
      variable = aux->CodPais;
      return 1;
}
int ArbolABB_Paises :: getNombre(char* nombre, pnodoabbpais aux){

   int i;

   if (aux == NULL){
      return -4;
   }
   

   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}

int ArbolABB_Paises :: setCodPais(int valor, pnodoabbpais aux){

   if (aux == NULL){
      return -4;
   }
   
   aux->CodPais = valor; // asignacion del valor en el nodo pos
   return 1;
}
int ArbolABB_Paises :: setNombre(char* nombre, pnodoabbpais aux){ // restringido por buffer de la clase. nombre dado debe terminar con '\000'

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

