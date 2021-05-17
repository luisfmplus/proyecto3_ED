
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general
*/

//falta implementar la funcion de borrarNodo()

#ifndef _ARBOLRNHABITACIONES_H
#define	_ARBOLRNHABITACIONES_H
#include "1RNHabitaciones.cpp"
#endif

#include <iostream>
#include <stdlib.h>

using namespace std;


class NodoPisoHotel {
   public:
    ArbolRN_Habitaciones* habitacion;
    
    NodoPisoHotel(int NP,char* nom, int CH){
      habitacion = new ArbolRN_Habitaciones();
      NumPiso = NP;
      CantidadHabitaciones = CH;
	  int i;
      for (i = 0; nom[i] != '\000' &&  i < sizeof(Nombre) ; i++){
          Nombre[i] = nom[i];

      }
      Izquierda = NULL;
      Derecha =NULL;
      Padre = NULL;
    
    }

 private:
    int NumPiso;
    int CantidadHabitaciones;
    char Nombre[30] = "\000";
    int FactorBalance = 0;
    NodoPisoHotel *Izquierda;
    NodoPisoHotel *Derecha;
    NodoPisoHotel *Padre;
    friend class ArbolAVL_Pisos;
};
typedef NodoPisoHotel *pnodopisohotel;

class ArbolAVL_Pisos {
   public:
    ArbolAVL_Pisos() { primero = NULL; }
    ~ArbolAVL_Pisos();
    
    int getNumPiso(int &valor, pnodopisohotel aux);
    int getCantidadHabitaciones(int &valor, pnodopisohotel aux);
    int getNombre(char* nombre, pnodopisohotel aux);

    int setNumPiso(int valor, pnodopisohotel aux);
    int setCantidadHabitaciones(int valor, pnodopisohotel aux);
    int setNombre(char* nombre, pnodopisohotel aux);

    pnodopisohotel getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isNumPisoRepetido(int valor);
    int insertarNodo(int NP,char* nom, int CH);
    void MostrarNodo(pnodopisohotel aux);
    void Mostrar();
    pnodopisohotel getNodo(int valor);
    bool getNodo(pnodopisohotel &recibir, int valor);
    int borrarNodo(pnodopisohotel nodo);

    
   private:

    bool arbolVacio() { return primero == NULL; }
    void corregirArbol(pnodopisohotel nodo);
    pnodopisohotel getNodo(int valor, pnodopisohotel aux);
    int getFactorBalance(pnodopisohotel aux);
    void MostrarInorde(pnodopisohotel aux);
    void Mostrar(pnodopisohotel aux);
    int isNumPisoRepetido(int valor, pnodopisohotel aux);
    int insertarNodo(int NP,char* nom, int CH, pnodopisohotel aux);
    void rotarIzq(pnodopisohotel nodo, pnodopisohotel nododerecha);
    void rotarDer(pnodopisohotel nodo, pnodopisohotel nodoizquierda);
    void rotarIzqIzq(pnodopisohotel pnodo, pnodopisohotel pnododerecha);
    void rotarDerDer(pnodopisohotel pnodo, pnodopisohotel pnododerecha);
    void borrarArbol(pnodopisohotel node);

    pnodopisohotel primero;
    pnodopisohotel ultimonodo;
   
};


ArbolAVL_Pisos :: ~ArbolAVL_Pisos(){
   
  borrarArbol(primero);
  primero = NULL;

}

void ArbolAVL_Pisos :: borrarArbol(pnodopisohotel node) {
   if (node == NULL){
      return;
   } 
  
   
   borrarArbol(node->Izquierda); 
   borrarArbol(node->Derecha); 
     
   delete node;
}


void ArbolAVL_Pisos :: corregirArbol(pnodopisohotel nodo){

   // funcion que corrige el balance del arbol despues de una insercion


  pnodopisohotel padre = NULL;
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

int ArbolAVL_Pisos :: insertarNodo(int NP,char* nom, int CH, pnodopisohotel aux){

   //inserta un nodo. Busca su pocicision de forma reursiva
    
   if (CH < aux->NumPiso){ //revisamos que sea menor

      if (aux->Izquierda != NULL){ //preguntamos si el puntero es nulo
         return insertarNodo(NP, nom, CH, aux->Izquierda);
            
        } else {
            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Izquierda = new NodoPisoHotel(NP, nom, CH);
            aux->Izquierda->Padre = aux;
            ultimonodo = aux->Izquierda;
            corregirArbol(aux->Izquierda);
            return 1;
        
        }
  
   } else if (CH > aux->NumPiso){//revisamos que sea mayor

        if (aux->Derecha != NULL){//preguntamos si el puntero es nulo
            return insertarNodo(NP, nom, CH, aux->Derecha);

        } else {
            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Derecha = new NodoPisoHotel(NP, nom, CH);
            aux->Derecha->Padre = aux;
            ultimonodo = aux->Derecha;
            corregirArbol(aux->Derecha);
            return 1;
        
        }
   }
   return-4;
}
int ArbolAVL_Pisos :: insertarNodo(int NP,char* nom, int CH){

   // funcion inicializadora de todo el proceso para la insercion de un nodo

   if (primero == NULL){
      // es el primer nodo
      primero = new NodoPisoHotel(NP, nom, CH);
      ultimonodo = primero;
      return 1;
   }
    
   int condicion = isNumPisoRepetido(NP); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodopisohotel aux = primero;

   return insertarNodo(NP, nom, CH, aux);

}

void ArbolAVL_Pisos :: rotarIzqIzq(pnodopisohotel pnodo, pnodopisohotel pnodoizquierda){

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
void ArbolAVL_Pisos :: rotarDerDer(pnodopisohotel pnodo, pnodopisohotel pnododerecha){

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
void ArbolAVL_Pisos :: rotarIzq(pnodopisohotel pnodo, pnodopisohotel pnododerecha){
    
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
void ArbolAVL_Pisos :: rotarDer(pnodopisohotel pnodo, pnodopisohotel pnodoizquierda){
    
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

int ArbolAVL_Pisos :: isNumPisoRepetido(int valor){ // me informa que el nodo ya existe o que no existe

   //Funcion inicializadora de una busqueda recursiva por el valor indicado en la estructura

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3
   // si la estructura esta vacia retorna -1


    pnodopisohotel aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->NumPiso == valor){
        return -3;

    } else if (valor < aux->NumPiso){
        return isNumPisoRepetido(valor, aux->Izquierda);

    } else if (valor > aux->NumPiso){
        return isNumPisoRepetido(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolAVL_Pisos :: isNumPisoRepetido(int valor, pnodopisohotel aux){ // me informa que el nodo ya existe o que no existe

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->NumPiso == valor){
        return -3;

    } else if (valor < aux->NumPiso){
        return isNumPisoRepetido(valor, aux->Izquierda);

    } else if (valor > aux->NumPiso){
        return isNumPisoRepetido(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolAVL_Pisos :: MostrarInorde(pnodopisohotel aux){

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
void ArbolAVL_Pisos :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodopisohotel aux = primero;
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todos los Pisos\n"<< endl;
   
   MostrarInorde(aux);

}
void ArbolAVL_Pisos :: Mostrar(pnodopisohotel aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->NumPiso << espacio << aux->Nombre << espacio << aux->CantidadHabitaciones << "  >>" << endl;


}
void ArbolAVL_Pisos :: MostrarNodo(pnodopisohotel aux){

   //Permite imprimir la informacion del nodo recibido

  if (aux == NULL){
    cout<<"Error: Puntero nulo\n";
    return;
  
  }

  char espacio[] = "; ";

  cout << aux->NumPiso << espacio << aux->Nombre << espacio << aux->CantidadHabitaciones << "  >>" << endl;


}

bool ArbolAVL_Pisos :: getNodo(pnodopisohotel &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodopisohotel aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      return false;
   }
   return true;


}
pnodopisohotel ArbolAVL_Pisos :: getNodo(int valor){

//funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodopisohotel aux = primero;
   
   return getNodo(valor, aux);


}
pnodopisohotel ArbolAVL_Pisos :: getNodo(int valor, pnodopisohotel aux){

//funcion recursiva que busca por el puntero con su identificacion == valor


   pnodopisohotel temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->NumPiso){
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

pnodopisohotel ArbolAVL_Pisos :: getultimoNodoInsertado(){
   return ultimonodo;
}

int ArbolAVL_Pisos ::  borrarNodo(pnodopisohotel nodo){
   
   //funcion por implementar

   if (nodo == NULL){
      return -1;
   }
  
   //implementacion del borrado
   return 1;

}

int ArbolAVL_Pisos :: getNumPiso(int &valor, pnodopisohotel aux){

  if (aux == NULL){
    return -4;

  }
  
  valor = aux->NumPiso;
  return 1;
}
int ArbolAVL_Pisos :: getCantidadHabitaciones(int &valor, pnodopisohotel aux){

    if (aux == NULL){
    return -4;

  }
  valor = aux->CantidadHabitaciones;
  return 1;
}
int ArbolAVL_Pisos :: getNombre(char* nombre, pnodopisohotel aux){

   int i;

  if (aux == NULL){
    return -4;

  }
   for (i = 0; i < sizeof(aux->Nombre); i++) {
      nombre[i] = aux->Nombre[i];
   }
   return 1;
}

int ArbolAVL_Pisos :: setNumPiso(int valor, pnodopisohotel aux){

  if (aux == NULL){
    return -4;

  }
  aux->NumPiso = valor;
  return 1;
}
int ArbolAVL_Pisos :: setCantidadHabitaciones(int valor, pnodopisohotel aux){

    if (aux == NULL){
    return -4;

  }
  aux->CantidadHabitaciones = valor;
  return 1;
}
int ArbolAVL_Pisos :: setNombre(char* nombre, pnodopisohotel aux){ // restringido por buffer de la clase. nombre dado debe terminar con '\000'

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
