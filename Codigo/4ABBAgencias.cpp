
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
    void Mostrar();
    pnodoAgencia getNodo(int valor);
    bool getNodo(pnodoAgencia &recibir, int valor);
    int borrarNodo(pnodoAgencia nodo);

    
   private:

    bool arbolVacio() { return primero == NULL; }
    pnodoAgencia getNodo(int valor, pnodoAgencia aux);
    int getFactorBalance(pnodoAgencia aux);
    void MostrarInorde(pnodoAgencia aux);
    void Mostrar(pnodoAgencia aux);
    int isIdentidadAgRepetido(int valor, pnodoAgencia aux);
    int insertarNodo(int IA,char* nom, int CdV, pnodoAgencia aux);
    void borrarArbol(pnodoAgencia node);

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
void ArbolABB_Agencias :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodoAgencia aux = primero;
   
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todas las Agencias\n"<< endl;
   
   
   MostrarInorde(aux);

}
void ArbolABB_Agencias :: Mostrar(pnodoAgencia aux){

   char espacio[] = "; ";

   cout << aux->IdentidadAg << espacio << aux->Nombre << espacio << aux->CantidadVehiculos << "  >>" << endl;


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


int ArbolABB_Agencias ::  borrarNodo(pnodoAgencia nodo){
  
  if (nodo == NULL){
    return -1;
  }
  
  //implementacion del borrado
  return 1;
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
