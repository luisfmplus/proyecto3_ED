
/*
   Manejo de errores.
   1 = todo bien
   -1 = lista vacia
   -2 = fuera de rango
   -3 = repetido
   -4 = error en general

*/

//falta implementar la funcion de borrarNodo()

#include <iostream>
using namespace std;


class NodoHabitacion {
   public:

    NodoHabitacion(int CH, char* TC, int NC, int PH, char EH) {
       
       CodHabitacion = CH;
       NumeroCamas = NC;
       PrecioHabitacion = PH;
       EstadoHab = EH;
       Color = 'R';
       Derecha = NULL;
       Izquierda = NULL;
       Padre = NULL;
		int i;
       for (i = 0; ((TC[i] != '\000') && (i < sizeof(TipoCuarto))); i++){
          TipoCuarto[i] = TC[i];
       }
       
       
       Derecha = NULL;
       Izquierda = NULL;
    }

    NodoHabitacion(int CH, char* TC, int NC, int PH) {
       
       CodHabitacion = CH;
       NumeroCamas = NC;
       PrecioHabitacion = PH;
       EstadoHab = 'L';
       Color = 'R';
       Derecha = NULL;
       Izquierda = NULL;
       Padre = NULL;
	   int i;
       for (i = 0; ((TC[i] != '\000') && (i < sizeof(TipoCuarto))); i++){
          TipoCuarto[i] = TC[i];
       }
       
       
       Derecha = NULL;
       Izquierda = NULL;
    }
    int getPrecioHabitacion(){
       return PrecioHabitacion;
    }
    int getCodHabitacion(){
       return CodHabitacion;
    }

    void setEstadoHabitacion(char var){
       this->EstadoHab=var;
    }
    

   private:
    int CodHabitacion;
    char TipoCuarto [30] = "\000";
    int NumeroCamas;
    int PrecioHabitacion;
    char EstadoHab;
    char Color;
    NodoHabitacion *Derecha;
    NodoHabitacion *Izquierda;
    NodoHabitacion *Padre;
    
        
   friend class ArbolRN_Habitaciones;
};

typedef NodoHabitacion *pnodohabitacion;

class ArbolRN_Habitaciones {
   public:
    

    ArbolRN_Habitaciones() { primero =  NULL;}
    ~ArbolRN_Habitaciones();

    int getCodHabitacion(int& variable, pnodohabitacion aux);
    int getTipoCuarto(char* nombre, pnodohabitacion aux);
    int getNumeroCamas(int& variable, pnodohabitacion aux);
    int getPrecioHabitacion(int& variable, pnodohabitacion aux);
    int getEstadoHab(char& variable, pnodohabitacion aux);

    int setCodHabitacion(int valor, pnodohabitacion aux);
    int setTipoCuarto(char* nombre, pnodohabitacion aux);
    int setNumeroCamas(int valor, pnodohabitacion aux);
    int setPrecioHabitacion(int valor, pnodohabitacion aux);
    int setEstadoHab(char valor, pnodohabitacion aux);


    pnodohabitacion getultimoNodoInsertado();
    bool isArbolVacio() { return arbolVacio(); }
    int isCodHabitacionRepetido(int valor);
    int insertarNodo(int CH, char* TC, int NC, int PH, char EH);
    int insertarNodo(int CH, char* TC, int NC, int PH);
    void MostrarNodo(pnodohabitacion aux);
    void Mostrar();
    pnodohabitacion getNodo(int valor);
    bool getNodo(pnodohabitacion &recibir, int valor);
    int borrarNodo(pnodohabitacion nodo);


   private:

    bool arbolVacio() { return primero == NULL; }
    void corregirArbol(pnodohabitacion nodo);
    pnodohabitacion getNodo(int valor, pnodohabitacion aux);
    void MostrarInorde(pnodohabitacion aux);
    void Mostrar(pnodohabitacion aux);
    int isCodHabitacionRepetido(int valor, pnodohabitacion aux);
    int insertarNodo(int CH, char* TC, int NC, int PH, char EH, pnodohabitacion aux);
    int insertarNodo(int CH, char* TC, int NC, int PH, pnodohabitacion aux);
    void rotarIzq(pnodohabitacion nodo, pnodohabitacion nododerecha);
    void rotarDer(pnodohabitacion nodo, pnodohabitacion nodoizquierda);
    void rotarIzqIzq(pnodohabitacion pnodo, pnodohabitacion pnododerecha);
    void rotarDerDer(pnodohabitacion pnodo, pnodohabitacion pnododerecha);
    void borrarArbol(pnodohabitacion node);

    pnodohabitacion primero;
    pnodohabitacion ultimonodo;
  
};

ArbolRN_Habitaciones :: ~ArbolRN_Habitaciones()
{
   borrarArbol(primero);
   primero = NULL;
   
}

void ArbolRN_Habitaciones :: borrarArbol(pnodohabitacion node) {
   if (node == NULL){
      return;
   } 
  
   
   borrarArbol(node->Izquierda); 
   borrarArbol(node->Derecha); 
     
   delete node;
} 

void ArbolRN_Habitaciones :: corregirArbol(pnodohabitacion nodo){

   // material de referencia>> https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/

   pnodohabitacion padre = NULL;
   pnodohabitacion abuelo = NULL;
   pnodohabitacion tio = NULL;
   char colorTemp;

   while ((nodo != primero) && (nodo->Color != 'N') && (nodo->Padre->Color == 'R')){

      padre = nodo->Padre;
      abuelo = padre->Padre;


      /*  Caso : A
          padre = abuelo->Izquierda
          tio = abuelo->Derecha
          hijo = padre->Izquierda
       
             (a)
           /     \
        (p)       (t)
       /   \     /   \
      (h)
      
      */
      if (padre == abuelo->Izquierda){
  
         tio = abuelo->Derecha;
  
         /* Caso : 1
            El tio y el padre, ambos son color rojo
            por lo tanto solamente se cambian de color
         */
         if (tio != NULL && tio->Color == 'R'){

            abuelo->Color = 'R';
            padre->Color = 'N';
            tio->Color = 'N';
            nodo = abuelo;
            
         } else {

            /* Caso : 2
               el tio es negro
               e, hijo = padre->Derechar
               (doble rotacion izquierda)
            */
            if (nodo == padre->Derecha){

               rotarIzqIzq(abuelo, padre);
               colorTemp = abuelo->Color;
               abuelo->Color = nodo->Color;
               nodo->Color = colorTemp;

            } else {
  
               /* Caso : 3
                  el tio es negro
                  e, hijo = padre->Izquierda
                  (rotacion derecha) 
               */
               rotarDer(abuelo,padre);
               colorTemp = abuelo->Color;
               abuelo->Color = padre->Color;
               padre->Color = colorTemp;
               nodo = padre;
               
            }
         }

      } else {

         /*  Caso : B
         padre = abuelo->Derecha
         tio = abuelo->Izquierda
         hijo = padre->Derecha

                (a)
              /     \
           (t)       (p)
          /   \     /   \
                         (h)
      
         */
    
         tio = abuelo->Izquierda;
  
         /*  Caso : 1
            El tio y el padre, ambos son color rojo
            por lo tanto solamente se cambian de color
          */
         if ((tio != NULL) && (tio->Color == 'R')){

            abuelo->Color = 'R';
            padre->Color = 'N';
            tio->Color = 'N';
            nodo = abuelo;
         
         } else {
               
            /* Caso : 2
               el tio es negro
               e, hijo = padre->izquierda
               (doble rotacion derecha)
            */
            if (nodo == padre->Izquierda){

               rotarDerDer(abuelo, padre);
               colorTemp = abuelo->Color;
               abuelo->Color = nodo->Color;
               nodo->Color = colorTemp;
         
            } else {

               /* Caso : 3
                  el tio es negro
                  e, hijo = padre->derecha
                  (rotacion izquierda)
               */
               rotarIzq(abuelo,padre);
               colorTemp = padre->Color;
               padre->Color = abuelo->Color;
               abuelo->Color = colorTemp;
               nodo = padre;
            }
         }
      }
   }

   primero->Color = 'N';

}

int ArbolRN_Habitaciones :: insertarNodo(int CH, char* TC, int NC, int PH, char EH, pnodohabitacion aux){

   //inserta un nodo. Busca su pocicision de forma reursiva
    
   if (CH < aux->CodHabitacion){ //revisamos que sea menor

      if (aux->Izquierda != NULL){//preguntamos si el puntero es nulo
         return insertarNodo(CH, TC, NC, PH, EH, aux->Izquierda);
            
        } else {

            // cuando entra estamos en un nodo con su hijo izquierdo == NULL
            aux->Izquierda = new NodoHabitacion(CH, TC, NC, PH, EH);
            aux->Izquierda->Padre = aux;
            ultimonodo = aux->Izquierda;
            corregirArbol(aux->Izquierda);
            return 1;
        
        }
  
   } else if (CH > aux->CodHabitacion){//revisamos que sea mayor

        if (aux->Derecha != NULL){//preguntamos si el puntero es nulo
            return insertarNodo(CH, TC, NC, PH, EH, aux->Derecha);

        } else {

            //cuando entra estamos en un nodo con su hijo derecha == NULL
            aux->Derecha = new NodoHabitacion(CH, TC, NC, PH, EH);
            aux->Derecha->Padre = aux;
            ultimonodo = aux->Derecha;
            corregirArbol(aux->Derecha);
            return 1;
        
        }
   }
   return-4;
}
int ArbolRN_Habitaciones :: insertarNodo(int CH, char* TC, int NC, int PH, char EH){

   // creamos al primer nodo (raiz)
   // al ser la raiz siempre negra, podemos dejar la raiz inmediatamente negra
   // apesar de ser un nuevo nodo
   if (primero == NULL){
      primero = new NodoHabitacion(CH, TC, NC, PH, EH);
      ultimonodo = primero;
      primero->Color = 'N';
      return 1;
   }
    
   int condicion = isCodHabitacionRepetido(CH); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodohabitacion aux = primero;

   return insertarNodo(CH, TC, NC, PH, EH, aux);

}
int ArbolRN_Habitaciones :: insertarNodo(int CH, char* TC, int NC, int PH){

   // creamos al primer nodo (raiz)
   // al ser la raiz siempre negra, podemos dejar la raiz inmediatamente negra
   // apesar de ser un nuevo nodo
   if (primero == NULL){
      primero = new NodoHabitacion(CH, TC, NC, PH);
      ultimonodo = primero;
      primero->Color = 'N';
      return 1;
   }
    
   int condicion = isCodHabitacionRepetido(CH); //buscamos por repetidos

   //el valor ya existe en el arbol
   if (condicion == -3){
      return -3;
    
   }

   pnodohabitacion aux = primero;

   return insertarNodo(CH, TC, NC, PH, aux);

}
int ArbolRN_Habitaciones :: insertarNodo(int CH, char* TC, int NC, int PH, pnodohabitacion aux){

    
   if (CH < aux->CodHabitacion){

      if (aux->Izquierda != NULL){
         return insertarNodo(CH, TC, NC, PH, aux->Izquierda);
            
        } else {

            aux->Izquierda = new NodoHabitacion(CH, TC, NC, PH);
            aux->Izquierda->Padre = aux;
            ultimonodo = aux->Izquierda;
            corregirArbol(aux->Izquierda);
            return 1;
        
        }
  
   } else if (CH > aux->CodHabitacion){

        if (aux->Derecha != NULL){
            return insertarNodo(CH, TC, NC, PH, aux->Derecha);

        } else {

            aux->Derecha = new NodoHabitacion(CH, TC, NC, PH);
            aux->Derecha->Padre = aux;
            ultimonodo = aux->Derecha;
            corregirArbol(aux->Derecha);
            return 1;
        
        }
   }
   return-4;
}

void ArbolRN_Habitaciones :: rotarIzqIzq(pnodohabitacion pnodo, pnodohabitacion pnodoizquierda){

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
    
    //hay que actualizar el "Padre" de pnodo pues este ahora deberia ser pnodoizquierda->Derecha
    //pero aun no, pues ocuparemos al "Padre" de pnodo (que contiene actualmente)
    
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
void ArbolRN_Habitaciones :: rotarDerDer(pnodohabitacion pnodo, pnodohabitacion pnododerecha){

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
void ArbolRN_Habitaciones :: rotarIzq(pnodohabitacion pnodo, pnodohabitacion pnododerecha){
    
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
void ArbolRN_Habitaciones :: rotarDer(pnodohabitacion pnodo, pnodohabitacion pnodoizquierda){
    
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

int ArbolRN_Habitaciones :: isCodHabitacionRepetido(int valor){ // me informa que el nodo ya existe o que no existe

   //Funcion inicializadora de una busqueda recursiva por el valor indicado en la estructura

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3
   // si la estructura esta vacia retorna -1


    pnodohabitacion aux = primero;

    if (arbolVacio() ){
        return -1;
    }

    if (aux->CodHabitacion == valor){
        return -3;

    } else if (valor < aux->CodHabitacion){
        return isCodHabitacionRepetido(valor, aux->Izquierda);

    } else if (valor > aux->CodHabitacion){
        return isCodHabitacionRepetido(valor, aux->Derecha);
    
    }
return-4;
}
int ArbolRN_Habitaciones :: isCodHabitacionRepetido(int valor, pnodohabitacion aux){ // me informa que el nodo ya existe o que no existe

   //buscamos de forma recursiva si el valor se encuentra en la estructura
   // si no la encuentra, retornara -2
   // si encuentra el valor retornara -3

    //se cumple si llegamos a una hoja
    if (aux == NULL){
        return -2;
    }
    
    if (aux->CodHabitacion == valor){
        return -3;

    } else if (valor < aux->CodHabitacion){
        return isCodHabitacionRepetido(valor, aux->Izquierda);

    } else if (valor > aux->CodHabitacion){
        return isCodHabitacionRepetido(valor, aux->Derecha);
    
    }
   return-4;
}

void ArbolRN_Habitaciones :: MostrarInorde(pnodohabitacion aux){

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
void ArbolRN_Habitaciones :: Mostrar(){

   //Muestra toda la informacion contenida en la estructura 
   // de manera inorden

   pnodohabitacion aux = primero;
   
   if (aux == NULL){
      cout<< "\nArbol vacio"<<endl;
      return;
   }

   cout << "\nMostrando todas las Habitaciones\n"<< endl;
   
   MostrarInorde(aux);

}
void ArbolRN_Habitaciones :: Mostrar(pnodohabitacion aux){

   //imprime en pantalla los valores de la informacion 
   //del nodo indicado

   char espacio[] = "; ";

   cout << aux->CodHabitacion << espacio << aux->TipoCuarto << espacio << aux->NumeroCamas << espacio;
   cout << aux->PrecioHabitacion << espacio << aux->EstadoHab << "  >>" << endl;


}
void ArbolRN_Habitaciones :: MostrarNodo(pnodohabitacion aux){

   //Permite imprimir la informacion del nodo recibido

   if (aux == NULL){
      cout<<"Error: Puntero nulo\n";
      return;
   }

   char espacio[] = "; ";

   cout << aux->CodHabitacion << espacio << aux->TipoCuarto << espacio << aux->NumeroCamas << espacio;
   cout << aux->PrecioHabitacion << espacio << aux->EstadoHab << "  >>" << endl;


}

bool ArbolRN_Habitaciones :: getNodo(pnodohabitacion &recibir, int valor){

   //retorna la ubicacion del nodo con el valor de identificacion == valor
   // e informa si la obtencion del mismo fue exitosa o fallida

   pnodohabitacion aux = primero;
   
   recibir = getNodo(valor, aux);

   if (recibir == NULL){
      //obtencion fallida
      return false;
   }
   //obtencion exitosa
   return true;


}
pnodohabitacion ArbolRN_Habitaciones :: getNodo(int valor){

   //funcion inicializadora de la funcion recursiva para obtener el puntero con su identificacion == valor

   pnodohabitacion aux = primero;
   
   return getNodo(valor, aux);


}
pnodohabitacion ArbolRN_Habitaciones :: getNodo(int valor, pnodohabitacion aux){

   //funcion recursiva que busca por el puntero con su identificacion == valor

   pnodohabitacion temp = NULL;
   
   if (aux == NULL){
      //no lo encontro
      return NULL;
   }
   

   if (valor == aux->CodHabitacion){
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

pnodohabitacion ArbolRN_Habitaciones :: getultimoNodoInsertado(){
   return ultimonodo;
}

int ArbolRN_Habitaciones ::  borrarNodo(pnodohabitacion nodo){

   //funcion por implementar

   if (nodo == NULL){
      return -1;
   }
  
   //implementacion del borrado
   return 1;

}


int ArbolRN_Habitaciones :: getCodHabitacion(int& variable, pnodohabitacion aux){

   if (aux == NULL){
      return -4;

   }

   variable = aux->CodHabitacion;

   return 1;
}
int ArbolRN_Habitaciones :: getTipoCuarto(char* nombre, pnodohabitacion aux){

   int i;

   if (aux == NULL){
      return -4;

   }
   for (i = 0; i < sizeof(aux->TipoCuarto); i++) {
      nombre[i] = aux->TipoCuarto[i];
   }
   return 1;
}
int ArbolRN_Habitaciones :: getNumeroCamas(int& variable, pnodohabitacion aux){

   if (aux == NULL){
      return -4;

   }

   variable =aux->NumeroCamas;
   return 1;
}
int ArbolRN_Habitaciones :: getPrecioHabitacion(int& variable, pnodohabitacion aux){

   if (aux == NULL){
      return -4;

   }
   variable = aux->PrecioHabitacion;
   return 1;
}
int ArbolRN_Habitaciones :: getEstadoHab(char& variable, pnodohabitacion aux){

   if (aux == NULL){
      return -4;

   }
   variable = aux->EstadoHab;
   return 1;
}


int ArbolRN_Habitaciones :: setCodHabitacion(int valor, pnodohabitacion aux){

   if (aux == NULL){
      return -4;
      
   }
   aux->CodHabitacion = valor; // asignacion del valor en el nodo
   return 1;
}
int ArbolRN_Habitaciones :: setTipoCuarto(char* nombre, pnodohabitacion aux){ // restringido por buffer de la clase y nombre debe terminar con '\000'

   int i;

   if (aux == NULL){
      return -4;
      
   }

   for (i = 0; (i < sizeof(aux->TipoCuarto)); i++) { // limpieamos la variable
      aux->TipoCuarto[i] = '\000';
   }

   for (i = 0; ((nombre[i]!= '\000') && (i < sizeof(aux->TipoCuarto))); i++) { // asignamos valor
      aux->TipoCuarto[i] = nombre[i];
   }
   return 1;
}
int ArbolRN_Habitaciones :: setNumeroCamas(int valor, pnodohabitacion aux){

   if (aux == NULL){
      return -4;
      
   }
   aux->NumeroCamas = valor;
   return 1;
}
int ArbolRN_Habitaciones :: setPrecioHabitacion(int valor, pnodohabitacion aux){

   if (aux == NULL){
      return -4;
      
   }
   aux->PrecioHabitacion = valor;
   return 1;
}
int ArbolRN_Habitaciones :: setEstadoHab(char valor, pnodohabitacion aux){

   if (aux == NULL){
      return -4;
      
   }

   if (valor == 'R' || valor == 'r'){
      aux->EstadoHab = 'R';
      return 1;

   } else if (valor == 'L' || valor == 'l'){
      aux->EstadoHab = 'L';
      return 1;

   }  else if (valor == 'O' || valor == 'o'){
      aux->EstadoHab = 'O';
      return 1;

   }
   return -4;
}

