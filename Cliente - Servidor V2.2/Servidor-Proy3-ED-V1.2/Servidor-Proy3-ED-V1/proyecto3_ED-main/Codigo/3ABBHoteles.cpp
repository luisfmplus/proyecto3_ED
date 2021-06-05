
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

//falta implementar la funcion de borrarNodo()

#ifndef _ARBOLAVLPISOS_H
#define	_ARBOLAVLPISOS_H
#include "2AVLPisosHoteles.cpp"
#endif

#include <iostream>

using namespace std;

class NodoHotel {
   public:

   ArbolAVL_Pisos* piso;

    NodoHotel(int CH, char* nom, int est) {
       piso = new ArbolAVL_Pisos();
       CodHotel = CH;
       CantidadEstrellas = est;

       for (int i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

       }
       Izquierda = NULL;
       Derecha =NULL;
    }

   string getInfoHotel(){
      return to_string(CodHotel)+"|"+string(Nombre)+"|"+to_string(CantidadEstrellas)+"|";
   }


   private:
    int CodHotel;
    char Nombre [30] = "\000";
    int CantidadEstrellas;
    NodoHotel *Izquierda;
    NodoHotel *Derecha;
    
        
   friend class ArbolABB_Hoteles;
};

typedef NodoHotel *pnodohotel;



class ArbolABB_Hoteles {
   public:
    ArbolABB_Hoteles() { primero = NULL; }
    ~ArbolABB_Hoteles();
    
    int getCodHotel(int& variable, pnodohotel aux);
    int getNombre(char* nombre, pnodohotel aux);
    int getCantidadEstrellas(int &variable, pnodohotel aux);

    int setCodHotel(int valor, pnodohotel aux);
    int setNombre(char* nombre, pnodohotel aux);
    int setCantidadestrellas(int valor, pnodohotel aux);

    pnodohotel getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isCodHotel(int valor);
    int insertarNodo(int CH,char* nom, int est);
    void MostrarNodo(pnodohotel aux);
    string Mostrar();
    pnodohotel getNodo(int valor);
    bool getNodo(pnodohotel &recibir, int valor);
    int borrarNodo(pnodohotel nodo);
    int borrarNodo(int valor);

    
   private:

    bool arbolVacio() { return primero == NULL; }
    pnodohotel getNodo(int valor, pnodohotel aux);
    void MostrarInorde(pnodohotel aux);
    void Mostrar(pnodohotel aux);
    int isCodHotel(int valor, pnodohotel aux);
    int insertarNodo(int CH,char* nom, int est, pnodohotel aux);
    void borrarArbol(pnodohotel node);
    int borrarNodo(pnodohotel nodo, pnodohotel aux, bool& encontrado);
    pnodohotel minValor(pnodohotel hijoderecha);
    pnodohotel maxValor(pnodohotel hijoIzquierda);

    pnodohotel primero;
    pnodohotel ultimonodo;
  
};



ArbolABB_Hoteles :: ~ArbolABB_Hoteles(){

  borrarArbol(primero);
  primero = NULL;
   
}



void ArbolABB_Hoteles :: borrarArbol(pnodohotel node) {
   
   if (node == NULL){
      return;
   } 
  
   
   borrarArbol(node->Izquierda); 
   borrarArbol(node->Derecha); 
     
   delete node;
}


int ArbolABB_Hoteles :: insertarNodo(int CH,char* nom, int est, pnodohotel aux){

   //inserta un nodo. Busca su pocicision de forma reursiva

   if (CH < aux->CodHotel){ //revisamos que sea menor

      if (aux->Izquierda != NULL){ //preguntamos si el puntero es nulo
         return insertarNodo(CH, nom, est, aux->Izquierda);
            
        } else {

            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Izquierda = new NodoHotel(CH, nom, est);
            ultimonodo = aux->Izquierda;
            return 1;
        
        }
  
   } else if (CH > aux->CodHotel){//revisamos que sea mayor

        if (aux->Derecha != NULL){//preguntamos si el puntero es nulo
            return insertarNodo(CH, nom, est, aux->Derecha);

        } else {
            //cuando entra estamos en un nodo con su hijo derecha == NULL
            aux->Derecha = new NodoHotel(CH, nom, est);
            ultimonodo = aux->Derecha;
            return 1;
        
        }
   }
   return-4;
}
int ArbolABB_Hoteles :: insertarNodo(int CH,char* nom, int est){


   if (primero == NULL){
      primero = new NodoHotel(CH, nom, est);
      ultimonodo = primero;
      return 1;
   }
    
   int condicion = isCodHotel(CH); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodohotel aux = primero;

   return insertarNodo(CH, nom, est, aux);

}

int ArbolABB_Hoteles :: isCodHotel(int valor){ // me informa que el nodo ya existe o que no existe

    pnodohotel aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->CodHotel == valor){
        return -3;

    } else if (valor < aux->CodHotel){
        return isCodHotel(valor, aux->Izquierda);

    } else if (valor > aux->CodHotel){
        return isCodHotel(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolABB_Hoteles :: isCodHotel(int valor, pnodohotel aux){ // me informa que el nodo ya existe o que no existe

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->CodHotel == valor){
        return -3;

    } else if (valor < aux->CodHotel){
        return isCodHotel(valor, aux->Izquierda);

    } else if (valor > aux->CodHotel){
        return isCodHotel(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolABB_Hoteles :: MostrarInorde(pnodohotel aux){
   //funcion recursiva auxiliar muestras todos los nodos contenidos en la estructura en inorden
   if (aux == NULL){
      return;
   }
   MostrarInorde(aux->Izquierda);
   Mostrar(aux);
   MostrarInorde(aux->Derecha);
}

string infoHoteles;
string ArbolABB_Hoteles :: Mostrar(){
   //Muestra toda la informacion contenida en la estructura  de manera inorden
   pnodohotel aux = primero;
   infoHoteles = "";
   if (aux == NULL){
      return infoHoteles;
   }
   MostrarInorde(aux);
   return infoHoteles;
}

void ArbolABB_Hoteles :: Mostrar(pnodohotel aux){
   //imprime en pantalla los valores de la informacion  del nodo indicado
   string espacio = "|";
   infoHoteles += to_string(aux->CodHotel) + espacio + string(aux->Nombre) + espacio + to_string(aux->CantidadEstrellas) + espacio;
}

void ArbolABB_Hoteles :: MostrarNodo(pnodohotel aux){

   //Permite imprimir la informacion del nodo recibido

  if (aux == NULL){
    cout<<"Error: Puntero nulo\n";
    return;
  
  }

  char espacio[] = "; ";

  cout << aux->CodHotel << espacio << aux->Nombre << espacio << aux->CantidadEstrellas << "  >>" << endl;


}

bool ArbolABB_Hoteles :: getNodo(pnodohotel &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodohotel aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodohotel ArbolABB_Hoteles :: getNodo(int valor){

   //funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodohotel aux = primero;
   
   return getNodo(valor, aux);


}
pnodohotel ArbolABB_Hoteles :: getNodo(int valor, pnodohotel aux){

   //funcion recursiva que busca por el puntero con su identificacion == valor

   pnodohotel temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->CodHotel){
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

pnodohotel ArbolABB_Hoteles :: getultimoNodoInsertado(){
   return ultimonodo;
}

int ArbolABB_Hoteles :: borrarNodo(pnodohotel nodo){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodohotel aux = primero;


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
int ArbolABB_Hoteles :: borrarNodo(int valor){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodohotel aux = primero;


    //validacion de la existencia del nodo a borrar
	if (isCodHotel(valor) == -3){
		//solamente entra si el valor no existe
		return -4;
	}
	
	pnodohotel nodo = getNodo(valor);

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}
int ArbolABB_Hoteles :: borrarNodo(pnodohotel nodo, pnodohotel aux, bool& encontrado){

   //nodo nunca sera null

   int i;
   pnodohotel min;
   pnodohotel max;
   pnodohotel borrar;

   if ((aux == NULL)){
     return -1;
   }
  
   // es menor lo que busco?
   if (aux->CodHotel > nodo->CodHotel){
      i = borrarNodo(nodo, aux->Izquierda, encontrado);

   // es mayor lo que busco
   } else if (aux->CodHotel < nodo->CodHotel){
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
pnodohotel ArbolABB_Hoteles ::  minValor(pnodohotel hijoderecha){ 
   
   //recibe la posicion del nodo a la derecha de forma inicial
   // recibe la posicion del nodo a la izquierda de manera recursiva

   //retorna el nodo padre del nodo menor;
   //retorna null si el nodo min no existe
   //retorna null si el nodo padre del nodo min es el nodo a eliminar

   pnodohotel temp;

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
pnodohotel ArbolABB_Hoteles ::  maxValor(pnodohotel hijoIzquierda){

   //recibe la posicion del nodo a la izquierda de forma inicial
   // recibe la posicion del nodo a la derecha de manera recursiva

   //retorna el nodo padre del nodo mayor;
   //retorna null si el nodo max no existe
   //retorna null si: el nodo padre del nodo max es el nodo a eliminar

   pnodohotel temp;

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


int ArbolABB_Hoteles :: getCodHotel(int& variable, pnodohotel aux){

   if (aux == NULL){
      return -4;
   }
   
      variable = aux->CodHotel;
      return 1;
}
int ArbolABB_Hoteles :: getNombre(char* nombre, pnodohotel aux){

   int i;

   if (aux == NULL){
      return -4;
   }
   

   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}
int ArbolABB_Hoteles :: getCantidadEstrellas(int &variable, pnodohotel aux){

   if (aux == NULL){
      return -4;
   }
   
      variable = aux->CantidadEstrellas;
      return 1;
}

int ArbolABB_Hoteles :: setCodHotel(int valor, pnodohotel aux){

   if (aux == NULL){
      return -4;
   }
   
   aux->CodHotel = valor; // asignacion del valor en el nodo pos
   return 1;
}
int ArbolABB_Hoteles :: setNombre(char* nombre, pnodohotel aux){ // restringido por buffer de la clase. nombre dado debe terminar con '\000'

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
int ArbolABB_Hoteles :: setCantidadestrellas(int valor, pnodohotel aux){

   if (aux == NULL){
      return -4;
   }
   
   aux->CantidadEstrellas = valor;
   return 1;
}
