
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

    
   private:

    bool arbolVacio() { return primero == NULL; }
    pnodoabbpais getNodo(int valor, pnodoabbpais aux);
    void MostrarInorde(pnodoabbpais aux);
    void Mostrar(pnodoabbpais aux);
    int isCodPais(int valor, pnodoabbpais aux);
    int insertarNodo(int CH,char* nom, pnodoabbpais aux);
    void borrarArbol(pnodoabbpais node);

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

   if (nodo == NULL){
      return -1;
   }
  
   //implementacion del borrado
   return 1;

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

