
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
    void Mostrar();
    pnodotipoflotilla getNodo(int valor);
    bool getNodo(pnodotipoflotilla &recibir, int valor);
    int borrarNodo(pnodotipoflotilla nodo);

    
   private:

    bool arbolVacio() { return primero == NULL; }
    void corregirArbol(pnodotipoflotilla nodo);
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
void ArbolAVL_Flotilla :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodotipoflotilla aux = primero;
   
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todas las Flotillas\n"<< endl;
   
   
   MostrarInorde(aux);

}
void ArbolAVL_Flotilla :: Mostrar(pnodotipoflotilla aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->CodTipo << espacio << aux->Nombre << espacio << aux->CantidaddCarrosTipo << "  >>" << endl;


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

int ArbolAVL_Flotilla ::  borrarNodo(pnodotipoflotilla nodo){
  
  if (nodo == NULL){
    return -1;
  }
  
  //implementacion del borrado
  return 1;
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


