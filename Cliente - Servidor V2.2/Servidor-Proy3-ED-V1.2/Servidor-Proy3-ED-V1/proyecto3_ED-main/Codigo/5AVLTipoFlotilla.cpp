
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

//falta implementar la funcion de borrarNodo()

#ifndef _ARBOLAACARROS_H
#define	_ARBOLAACARROS_H
#include "6AACarros.cpp"
#endif

#include <iostream>
#include <stdlib.h>

using namespace std;


class NodoTipoFlotilla {
   public:
    ArbolAA_Carros* carro;
    
    NodoTipoFlotilla(int CT, char* nom, int CdCT){
      carro = new ArbolAA_Carros();
      CodTipo = CT;
      CantidaddCarrosTipo = CdCT;

      for (int i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

      }
      Izquierda = NULL;
      Derecha =NULL;
      Padre = NULL;
    
    }

      string mostrar(){
         string espacio = "|";
         return to_string(CodTipo) + espacio + string(Nombre) + espacio + to_string(CantidaddCarrosTipo) + espacio;
    }

 private:
    int CodTipo;
    int CantidaddCarrosTipo;
    char Nombre[30] = "\000";
    int FactorBalance = 0;
    NodoTipoFlotilla *Izquierda;
    NodoTipoFlotilla *Derecha;
    NodoTipoFlotilla *Padre;
    friend class ArbolAVL_Flotilla;
};
typedef NodoTipoFlotilla *pnodotipoflotilla;

class ArbolAVL_Flotilla {
   public:
    ArbolAVL_Flotilla() { primero = NULL; }
    ~ArbolAVL_Flotilla();
    
    int getCodTipo(int &valor, pnodotipoflotilla aux);
    int getCantidaddCarrosTipo(int &valor, pnodotipoflotilla aux);
    int getNombre(char* nombre, pnodotipoflotilla aux);

    int setCodTipo(int valor, pnodotipoflotilla aux);
    int setCantidaddCarrosTipo(int valor, pnodotipoflotilla aux);
    int setNombre(char* nombre, pnodotipoflotilla aux);

    pnodotipoflotilla getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isCodTipoRepetido(int valor);
    int insertarNodo(int CT, char* nom, int CdCT);
    void MostrarNodo(pnodotipoflotilla aux);
    string Mostrar();
    pnodotipoflotilla getNodo(int valor);
    bool getNodo(pnodotipoflotilla &recibir, int valor);
    int borrarNodo(pnodotipoflotilla nodo);
    int borrarNodo(int valor);
    
   private:

    bool arbolVacio() { return primero == NULL; }
    void corregirArbol(pnodotipoflotilla nodo);
     void correccionBorrado(pnodotipoflotilla nodo);
    pnodotipoflotilla getNodo(int valor, pnodotipoflotilla aux);
    int getFactorBalance(pnodotipoflotilla aux);
    void MostrarInorde(pnodotipoflotilla aux);
    void Mostrar(pnodotipoflotilla aux);
    int isCodTipoRepetido(int valor, pnodotipoflotilla aux);
    int insertarNodo(int CT, char* nom, int CdCT, pnodotipoflotilla aux);
    void rotarIzq(pnodotipoflotilla nodo, pnodotipoflotilla nododerecha);
    void rotarDer(pnodotipoflotilla nodo, pnodotipoflotilla nodoizquierda);
    void rotarIzqIzq(pnodotipoflotilla pnodo, pnodotipoflotilla pnododerecha);
    void rotarDerDer(pnodotipoflotilla pnodo, pnodotipoflotilla pnododerecha);
    void borrarArbol(pnodotipoflotilla node);
    void swapNodos(pnodotipoflotilla nodo1, pnodotipoflotilla nodo2);

    int borrarNodo(pnodotipoflotilla nodo, pnodotipoflotilla aux, bool& encontrado);
    pnodotipoflotilla MINValor(pnodotipoflotilla hijoderecha);
    pnodotipoflotilla MAXValor(pnodotipoflotilla hijoIzquierda);

    pnodotipoflotilla primero;
    pnodotipoflotilla ultimonodo;
   
};


ArbolAVL_Flotilla :: ~ArbolAVL_Flotilla(){
   
  borrarArbol(primero);
  primero = NULL;

}

void ArbolAVL_Flotilla :: borrarArbol(pnodotipoflotilla node) {
   if (node == NULL){
      return;
   } 
  
   
   borrarArbol(node->Izquierda); 
   borrarArbol(node->Derecha); 
     
   delete node;
}


void ArbolAVL_Flotilla :: corregirArbol(pnodotipoflotilla nodo){

// funcion que corrige el balance del arbol despues de una insercion

  pnodotipoflotilla padre = NULL;
  bool direccion;

  while ((nodo != primero) ){


    padre = nodo->Padre;
    //actualizamos el factor balance del nodo padre
    if (padre->Derecha == nodo){
      padre->FactorBalance++;
      direccion = true;

    } else {
      padre->FactorBalance--;
      direccion = false;
    }


    //revisamos el factor balance del nodo padre
    if (abs(padre->FactorBalance) == 2){
      //revisamos el factor balance del nodo hijo

      //nodo hijo es derecha del padre
      if (direccion){

        //nodo recien insertado es derecha del nodo hijo
        if (nodo->FactorBalance == 1){
          rotarIzq(padre, nodo);
          padre->FactorBalance = 0;
          nodo->FactorBalance = 0;
          break;
        
        } else {

          //nodo recien insertado es izquierda del nodo
          rotarDerDer(padre, nodo);
          padre->FactorBalance = 0;
          nodo->FactorBalance = 0;
          //nodo recien insertado mantinen su factorbalance
          break;

        }
                
      
      } else {

        // nodo hijo es izquierda del padre


        //nodo recien insertado es derecha del nodo hijo
        if (nodo->FactorBalance == 1){
          rotarIzqIzq(padre, nodo);
          padre->FactorBalance = 0;
          nodo->FactorBalance = 0;
          //nodo recien insertado mantinen su factorbalance
          break;

        } else {

          //nodo hijo avanza a la izquierda
          rotarDer(padre, nodo);
          padre->FactorBalance = 0;
          nodo->FactorBalance = 0;
          break;

        }
      }  
    }

    nodo = nodo->Padre;

  }
}

void ArbolAVL_Flotilla :: correccionBorrado(pnodotipoflotilla nodo){

   // el valor de "nodo" es el puntero padre del nodo que fue eliminado.
   // adicionalmente, este puntero ya fue alterado su factor balance, por lo tanto
   // esta funcion balancea del (incluyendo al abuelo) del abuelo en adelante
   // hasta llegar a la raiz

   pnodotipoflotilla aux;



   if (abs(nodo->FactorBalance) == 1){
      // en este caso la altura del se mantiene igual y por lo tanto no se requiere ninguna correccion
      return;
   }

   while (nodo != NULL){

      // el nodo borrado desbalanceo al padre
      if (nodo->FactorBalance == 2){

         aux = nodo->Derecha;

         //nodo recien borrado es izquierdo del nodo 
         if (aux->FactorBalance == 1){
            rotarIzq(nodo, aux);
            nodo->FactorBalance = 0;
            aux->FactorBalance = 0;

         } else {

            //nodo recien insertado es izquierda del nodo
            rotarDerDer(nodo, aux);
            nodo->FactorBalance = 0;
            aux->FactorBalance = 0;

         }

         // ajustamos el factor balance del padre
         if (nodo->Padre != NULL){

            if (nodo->Padre->Derecha == nodo){
               //el nodo borrado se encuentra del lado derecho
               // por lo tanto factorbalance -(+1)
               nodo->Padre->FactorBalance--;
            } else {
               //el nodo borrado se encuentra del lado izqiuerdo
               // por lo tanto factorbalance -(-1)
               nodo->Padre->FactorBalance++;
            }
         }
         
      } else if (nodo->FactorBalance == -2){
      
         aux = nodo->Izquierda;

            //nodo recien borrado es derecho del nodo
         if (aux->FactorBalance == 1){
            rotarIzqIzq(nodo, aux);
            nodo->FactorBalance = 0;
            aux->FactorBalance = 0;

         } else {

            //nodo hijo avanza a la izquierda
            rotarDer(nodo, aux);
            nodo->FactorBalance = 0;
            aux->FactorBalance = 0;

         }
      
         // ajustamos el factor balance del padre
         if (nodo->Padre != NULL){

            if (nodo->Padre->Derecha == nodo){
               //el nodo borrado se encuentra del lado derecho
               // por lo tanto factorbalance -(+1)
               nodo->Padre->FactorBalance--;
            } else {
               //el nodo borrado se encuentra del lado izqiuerdo
               // por lo tanto factorbalance -(-1)
               nodo->Padre->FactorBalance++;
            }
         }
      }
      nodo = nodo->Padre;
   }
}


int ArbolAVL_Flotilla :: insertarNodo(int CT, char* nom, int CdCT, pnodotipoflotilla aux){

   //inserta un nodo. Busca su pocicision de forma reursiva

   if (CT < aux->CodTipo){ //revisamos que sea menor

      if (aux->Izquierda != NULL){ //preguntamos si el puntero es nulo
         return insertarNodo(CT, nom, CdCT, aux->Izquierda);
            
        } else {
            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Izquierda = new NodoTipoFlotilla(CT, nom, CdCT);
            aux->Izquierda->Padre = aux;
            ultimonodo = aux->Izquierda;
            corregirArbol(aux->Izquierda);
            return 1;
        
        }
  
   } else if (CT > aux->CodTipo){ //revisamos que sea mayor

        if (aux->Derecha != NULL){ //preguntamos si el puntero es nulo
            return insertarNodo(CT, nom, CdCT, aux->Derecha);

        } else {
            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Derecha = new NodoTipoFlotilla(CT, nom, CdCT);
            aux->Derecha->Padre = aux;
            ultimonodo = aux->Derecha;
            corregirArbol(aux->Derecha);
            return 1;
        
        }
   }
   return-4;
}
int ArbolAVL_Flotilla :: insertarNodo(int CT, char* nom, int CdCT){

   // funcion inicializadora de todo el proceso para la insercion de un nodo

   if (primero == NULL){
      primero = new NodoTipoFlotilla(CT, nom, CdCT);
      ultimonodo = primero;
      return 1;
   }
    
   int condicion = isCodTipoRepetido(CT); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodotipoflotilla aux = primero;

   return insertarNodo(CT, nom, CdCT, aux);

}

void ArbolAVL_Flotilla :: rotarIzqIzq(pnodotipoflotilla pnodo, pnodotipoflotilla pnodoizquierda){

   //rotacion doble izquierda.
   //esta rotacion esta implementada de forma directa,
   //esto significa que no se realizan rotaciones derecha o izquierda
   //,sino, una sola rotacion doble izquierda

   //pnodo es el abuelo
   //pnodoizquierda es el padre 
    
    pnodo->Izquierda = pnodoizquierda->Derecha->Derecha;
    
    if (pnodo->Izquierda != NULL){
        pnodo->Izquierda->Padre = pnodo;
    }
    
    
    
    pnodoizquierda->Derecha->Derecha = pnodo;
    
    //hay que actualizar el padre de pnodo pues ahora es pnodoizquierda->Derecha
    //pero aun no pues ocuparemos al padre de pnodo (que contiene actualmente)
    
    //reusamos la variable pnodo para indicar al hijo
    pnodo= pnodoizquierda->Derecha;
    
    
    //regalamos un hijo
    pnodoizquierda->Derecha = pnodo->Izquierda;
    
    if (pnodoizquierda->Derecha != NULL){
       //actualizamos el "Padre" del hijo regalado
        pnodoizquierda->Derecha->Padre = pnodoizquierda;
    }


    
    pnodo->Izquierda = pnodoizquierda;

    pnodoizquierda->Padre = pnodo;

    pnodo->Padre = pnodo->Derecha->Padre;
    pnodo->Derecha->Padre = pnodo;

   // actualizamos el puntero "Padre"
   // o encaso de trabajar en la raiz
   // actualizamos el puntero a la raiz

    if (pnodo->Derecha == primero){
        primero = pnodo;
    }
    pnodo->Padre->Izquierda = pnodo;

}
void ArbolAVL_Flotilla :: rotarDerDer(pnodotipoflotilla pnodo, pnodotipoflotilla pnododerecha){

   //rotacion doble derecha.
   //esta rotacion esta implementada de forma directa,
   //esto significa que no se realizan rotaciones derecha o izquierda
   //,sino, una sola rotacion doble derecha

   //pnodo es el abuelo
   //pnododerecha es el padre 

    pnodo->Derecha = pnododerecha->Izquierda->Izquierda;//regalamos nodo izquierdo del hijo

    if (pnodo->Derecha != NULL){
        pnodo->Derecha->Padre = pnodo;
    }

    pnododerecha->Izquierda->Izquierda = pnodo; //hijo apunta al abuelo

    pnodo= pnododerecha->Izquierda; //reutilizamo variable

    pnododerecha->Izquierda = pnodo->Derecha; //regalamos nodo derecha del hijo

    if (pnododerecha->Izquierda != NULL){
        pnododerecha->Izquierda->Padre = pnododerecha;
    }


    pnodo->Derecha = pnododerecha;

    pnododerecha->Padre = pnodo;
    pnodo->Padre = pnodo->Izquierda->Padre;
    pnodo->Izquierda->Padre = pnodo;


    if (pnodo->Izquierda == primero){
        primero = pnodo;
        return;
    }
    pnodo->Padre->Derecha = pnodo;

}
void ArbolAVL_Flotilla :: rotarIzq(pnodotipoflotilla pnodo, pnodotipoflotilla pnododerecha){
    
   //pnodo es el abuelo
   //pnododerecha es el padre 

    pnodo->Derecha=pnododerecha->Izquierda;

    //actualizamos el puntero de padre en el nodo que regalo pnododerecha
    if (pnodo->Derecha != NULL ){
        pnodo->Derecha->Padre = pnodo;
    }

    pnododerecha->Izquierda=pnodo;

    //actualizamos el puntero de padre en el nodoizquierda segun su valor en pnodo
    pnododerecha->Padre = pnodo->Padre;


    pnodo->Padre = pnododerecha;


    //nos informa que la rotacion ocurrio en la raiz y por lo tanto hay que moverla
    if (pnododerecha->Izquierda == primero){
        primero = pnododerecha;
        return;
    }
    pnododerecha->Padre->Derecha = pnododerecha;
    
}
void ArbolAVL_Flotilla :: rotarDer(pnodotipoflotilla pnodo, pnodotipoflotilla pnodoizquierda){
    
   //pnodo es el abuelo
   //pnododerecha es el padre 

    pnodo->Izquierda = pnodoizquierda->Derecha;
    
    //actualizamos el puntero de padre en el nodo que regalo pnodoizquierda
    if (pnodo->Izquierda != NULL ){
        pnodo->Izquierda->Padre = pnodo;
    }
    

    pnodoizquierda->Derecha = pnodo;

    //actualizamos el puntero de padre en el nodoizquierda segun su valor en pnodo
    pnodoizquierda->Padre = pnodo->Padre;

    pnodo->Padre = pnodoizquierda;



    //nos informa que la rotacion ocurrio en la raiz y por lo tanto hay que moverla
    if (pnodoizquierda->Derecha == primero){
        primero = pnodoizquierda;
    }
    pnodoizquierda->Padre->Izquierda = pnodoizquierda;
}

int ArbolAVL_Flotilla :: isCodTipoRepetido(int valor){ // me informa que el nodo ya existe o que no existe

   //Funcion inicializadora de una busqueda recursiva por el valor indicado en la estructura

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3
   // si la estructura esta vacia retorna -1

    pnodotipoflotilla aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->CodTipo == valor){
        return -3;

    } else if (valor < aux->CodTipo){
        return isCodTipoRepetido(valor, aux->Izquierda);

    } else if (valor > aux->CodTipo){
        return isCodTipoRepetido(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolAVL_Flotilla :: isCodTipoRepetido(int valor, pnodotipoflotilla aux){ // me informa que el nodo ya existe o que no existe

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->CodTipo == valor){
        return -3;

    } else if (valor < aux->CodTipo){
        return isCodTipoRepetido(valor, aux->Izquierda);

    } else if (valor > aux->CodTipo){
        return isCodTipoRepetido(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolAVL_Flotilla :: MostrarInorde(pnodotipoflotilla aux){
   //funcion recursiva auxiliar muestras todos los nodos contenidos en la estructura en inorden
   if (aux == NULL){
      return;
   }
   MostrarInorde(aux->Izquierda);
   Mostrar(aux);
   MostrarInorde(aux->Derecha);
}

string infoFlotillas;
string ArbolAVL_Flotilla :: Mostrar(){
   //Muestra toda la informacion contenida en la estructura  de manera inorden
   infoFlotillas = "";
   pnodotipoflotilla aux = primero;
   if (aux != NULL){
      MostrarInorde(aux);
   }
   return infoFlotillas;
}

void ArbolAVL_Flotilla :: Mostrar(pnodotipoflotilla aux){
   //imprime en pantalla los valores de la informacion  del nodo indicado
   string espacio = "|";
   infoFlotillas += to_string(aux->CodTipo) + espacio + string(aux->Nombre) + espacio + to_string(aux->CantidaddCarrosTipo) + espacio;
}

void ArbolAVL_Flotilla :: MostrarNodo(pnodotipoflotilla aux){

   //Permite imprimir la informacion del nodo recibido

  if (aux == NULL){
    cout<<"Error: Puntero nulo\n";
    return;
  
  }

  char espacio[] = "; ";

  cout << aux->CodTipo << espacio << aux->Nombre << espacio << aux->CantidaddCarrosTipo << "  >>" << endl;


}

bool ArbolAVL_Flotilla :: getNodo(pnodotipoflotilla &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodotipoflotilla aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodotipoflotilla ArbolAVL_Flotilla :: getNodo(int valor){

//funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodotipoflotilla aux = primero;
   
   return getNodo(valor, aux);


}
pnodotipoflotilla ArbolAVL_Flotilla :: getNodo(int valor, pnodotipoflotilla aux){

//funcion recursiva que busca por el puntero con su identificacion == valor

   pnodotipoflotilla temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->CodTipo){
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

pnodotipoflotilla ArbolAVL_Flotilla :: getultimoNodoInsertado(){
   return ultimonodo;
}

int ArbolAVL_Flotilla :: borrarNodo(pnodotipoflotilla nodo){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar


  bool encontrado = false;
  pnodotipoflotilla aux = primero;


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
int ArbolAVL_Flotilla :: borrarNodo(int valor){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodotipoflotilla aux = primero;


    //validacion de la existencia del nodo a borrar
	if (isCodTipoRepetido(valor) == -3){
		//solamente entra si el valor no existe
		return -4;
	}
	
	pnodotipoflotilla nodo = getNodo(valor);

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}

int ArbolAVL_Flotilla :: borrarNodo(pnodotipoflotilla nodo, pnodotipoflotilla aux, bool& encontrado){

   //nodo nunca sera null

   int i;
   pnodotipoflotilla min;
   pnodotipoflotilla max;
   char a[] = "a";
   pnodotipoflotilla borrar = new NodoTipoFlotilla(1,a,1);

   if ((aux == NULL)){
     return -1;
   }
  
   // es menor lo que busco?
   if (aux->CodTipo > nodo->CodTipo){
      i = borrarNodo(nodo, aux->Izquierda, encontrado);

   // es mayor lo que busco
   } else if (aux->CodTipo < nodo->CodTipo){
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
            aux->FactorBalance--;
	
        	} else {

        	   delete borrar;
        	   aux->Izquierda = NULL;
            aux->FactorBalance++;

        	}

        	encontrado = false;
         correccionBorrado(aux);
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
            primero->FactorBalance = 0; // solamente ocurre cuando existe solo 2 nodos y como hemos borrado la raiz; solo queda 1 nodo
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        		return 1;
	    	}

        	if (aux->Derecha == nodo){

        		aux->Derecha = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
            aux->Derecha->Padre = aux;
            aux->FactorBalance--;
        	   delete borrar;
	
        	} else {

        	   aux->Izquierda = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
            aux->Izquierda->Padre = aux;
            aux->FactorBalance++;
        	   delete borrar;

        	}

         correccionBorrado(aux);
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
            primero->FactorBalance = 0; // solamente ocurre cuando existe solo 2 nodos y como hemos borrado la raiz; solo queda 1 nodo
				delete borrar; // borramos la raiz
				encontrado = false; // la dejamos en falso
        		return 1;
	    	}

        	if (aux->Derecha == nodo){

        		aux->Derecha = nodo->Izquierda;
            aux->Derecha->Padre = aux;
            aux->FactorBalance--;
            delete borrar;
            
         } else {

            aux->Izquierda = nodo->Izquierda;
            aux->Izquierda->Padre = aux;
            aux->FactorBalance++;
            delete borrar;

        	}

         correccionBorrado(aux);
        	encontrado = false;
        	return 1;
      
      
    	}
      
    	// el nodo tiene hijos de ambos lados

    	min = MINValor(nodo->Derecha); // retorna el nodo a remplazar
    	max = MAXValor(nodo->Izquierda); // retorna el nodo a remplazar

      //por default se utilizara el maxValor.
      //cuando este se acabe, entonces el nodo a borrar no tendra hijos izquierdos y por lo tanto no entrara aqui

      bool segundoBorrado = false;
      int factor;
      swapNodos(max, nodo); //solamente cambia las relaciones de los 2 nodos no sus contenidos
      factor = max->FactorBalance;
      max->FactorBalance = nodo->FactorBalance;
      nodo->FactorBalance = factor;
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
        correccionBorrado(max);
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
pnodotipoflotilla ArbolAVL_Flotilla ::  MINValor(pnodotipoflotilla hijoderecha){ 
   
   // requiere que el nodo tenga un puntero a su padre

   //recibe la posicion del nodo a la derecha de forma inicial
   // recibe la posicion del nodo a la izquierda de manera recursiva

   //retorna el nodo menor;
   //retorna null si el nodo min no existe

   pnodotipoflotilla temp;

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
pnodotipoflotilla ArbolAVL_Flotilla ::  MAXValor(pnodotipoflotilla hijoIzquierda){
   
   // requiere que el nodo tenga un puntero a su padre
   
   //recibe la posicion del nodo a la izquierda de forma inicial
   // recibe la posicion del nodo a la derecha de manera recursiva

   //retorna el nodo mayor;
   //retorna null si el nodo max no existe

   pnodotipoflotilla temp;

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

void ArbolAVL_Flotilla :: swapNodos(pnodotipoflotilla nodo1, pnodotipoflotilla nodo2){

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
   

  pnodotipoflotilla temp1;
  pnodotipoflotilla temp2;

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


int ArbolAVL_Flotilla :: getCodTipo(int &valor, pnodotipoflotilla aux){

  if (aux == NULL){
    return -4;

  }
  
  valor = aux->CodTipo;
  return 1;
}
int ArbolAVL_Flotilla :: getCantidaddCarrosTipo(int &valor, pnodotipoflotilla aux){

    if (aux == NULL){
    return -4;

  }
  valor = aux->CantidaddCarrosTipo;
  return 1;
}
int ArbolAVL_Flotilla :: getNombre(char* nombre, pnodotipoflotilla aux){

   int i;

  if (aux == NULL){
    return -4;

  }
   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}

int ArbolAVL_Flotilla :: setCodTipo(int valor, pnodotipoflotilla aux){

  if (aux == NULL){
    return -4;

  }
  aux->CodTipo = valor;
  return 1;
}
int ArbolAVL_Flotilla :: setCantidaddCarrosTipo(int valor, pnodotipoflotilla aux){

    if (aux == NULL){
    return -4;

  }
  aux->CantidaddCarrosTipo = valor;
  return 1;
}
int ArbolAVL_Flotilla :: setNombre(char* nombre, pnodotipoflotilla aux){ // restringido por buffer de la clase. nombre dado debe terminar con '\000'

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


