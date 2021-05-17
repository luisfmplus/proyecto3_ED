
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
    void Mostrar();
    pnodohotel getNodo(int valor);
    bool getNodo(pnodohotel &recibir, int valor);
    int borrarNodo(pnodohotel nodo);

    
   private:

    bool arbolVacio() { return primero == NULL; }
    pnodohotel getNodo(int valor, pnodohotel aux);
    void MostrarInorde(pnodohotel aux);
    void Mostrar(pnodohotel aux);
    int isCodHotel(int valor, pnodohotel aux);
    int insertarNodo(int CH,char* nom, int est, pnodohotel aux);
    void borrarArbol(pnodohotel node);

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
void ArbolABB_Hoteles :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodohotel aux = primero;
   
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todos los Pisos\n"<< endl;
   
   
   MostrarInorde(aux);

}
void ArbolABB_Hoteles :: Mostrar(pnodohotel aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->CodHotel << espacio << aux->Nombre << espacio << aux->CantidadEstrellas << "  >>" << endl;


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
   
   if (nodo == NULL){
      return -1;
   }
  
   //implementacion del borrado
   return 1;
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
