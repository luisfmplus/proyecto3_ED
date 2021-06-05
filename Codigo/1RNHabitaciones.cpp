
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
    int borrarNodo(int valor);


   private:

    bool arbolVacio() { return primero == NULL; }
    void corregirInsercion(pnodohabitacion nodo);
    void corregirBorrado(pnodohabitacion nodo, bool direccion);
    int getCasoColor(pnodohabitacion nodo, bool direccion);
    pnodohabitacion getNodo(int valor, pnodohabitacion aux);
    void MostrarInorde(pnodohabitacion aux);
    void Mostrar(pnodohabitacion aux);
    int isCodHabitacionRepetido(int valor, pnodohabitacion aux);
    int insertarNodo(int CH, char* TC, int NC, int PH, char EH, pnodohabitacion aux);
    int insertarNodo(int CH, char* TC, int NC, int PH, pnodohabitacion aux);
    void rotarIzq(pnodohabitacion nodo, pnodohabitacion nododerecha);
    void rotarDer(pnodohabitacion nodo, pnodohabitacion nodoizquierda);
    void rotarIzqIzq(pnodohabitacion pnodo, pnodohabitacion pnododerecha);
    void rotarDerDer(pnodohabitacion pnodo, pnodohabitacion pnodoizquierda);
    void borrarArbol(pnodohabitacion node);

    int borrarNodo(pnodohabitacion nodo, pnodohabitacion aux, bool& encontrado);
    pnodohabitacion MINValor(pnodohabitacion hijoderecha);
    pnodohabitacion MAXValor(pnodohabitacion hijoIzquierda);
    void swapNodos(pnodohabitacion nodo1, pnodohabitacion nodo2);

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

void ArbolRN_Habitaciones :: corregirInsercion(pnodohabitacion nodo){

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

int ArbolRN_Habitaciones :: getCasoColor(pnodohabitacion nodo, bool direccion){

   //recibe el nodo padre del nodo recien eliminado
   // siendo este "nodo"
   // el nodo borrado siempre es negro por definicion
   // retornara un numero int que corresponde con todos los tipos de casos existentes
   // retornara -4 si "nodo" es nulo
   
   int i = 100; // retornara i si no identifico el caso color
   bool nietoI_N;
   bool nietoD_N;
   bool bisnietoI_N;
   bool bisnietoD_N;

   if (nodo == NULL){
      return -4;
   }

   if (direccion){ // la procedencia del nodo borrado es derecha

      if (nodo->Color == 'R'){ //padre es rojo

         if ((nodo->Izquierda->Izquierda == NULL) || (nodo->Izquierda->Izquierda->Color == 'N') ){ // el nieto izquierdo negro
            nietoI_N = true;
         
         }

         if ((nodo->Izquierda->Derecha == NULL) || (nodo->Izquierda->Derecha->Color == 'N') ){ //el nieto derecho negro
            nietoD_N = true;
         }


         if (nietoD_N && nietoI_N ){
            // tenemos: PR, HN, nieDN y nieIN
            //por lo tanto tenemos caso1
            return 1;
         }

         if (!nietoI_N){ // es el nieto izquierdo rojo?
            // tenemos: PR, HN, nieDN/R y nieIR
            // por lo tanto tenemos caso 2
            return 2;
         }

         if (!nietoD_N){ // es el nieto derecho rojo?
            // tenemos: PR, HN, nieDR y nieIN/R
            // por lo tanto tenemos caso 5
            return 5;
         }
         
         
      }

      // el nodo padre es negro

      if (nodo->Izquierda->Color == 'R'){ // el hermano es rojo
         
      
         if ((nodo->Izquierda->Izquierda == NULL) || (nodo->Izquierda->Izquierda->Color == 'N') ){ // el nieto izquierdo negro
            nietoI_N = true;
         
         }

         if ((nodo->Izquierda->Derecha == NULL) || (nodo->Izquierda->Derecha->Color == 'N') ){ //el nieto derecho negro
            nietoD_N = true;
         }
      
      
         if ((nodo->Izquierda->Derecha->Derecha == NULL) || (nodo->Izquierda->Derecha->Derecha->Color == 'N')){
            bisnietoD_N = true;
         }

         if ((nodo->Izquierda->Derecha->Izquierda == NULL) || (nodo->Izquierda->Derecha->Izquierda->Color == 'N')){
            bisnietoD_N = true;
         }
         
         if (bisnietoD_N && bisnietoI_N){
            // tenemos: PN, HR, nieIN, nieDN, bisnieIN y bisnieDN
            // por lo tanto nenemos caso 3
            return 3;
         }
         

         if (!bisnietoI_N){ // es el bisnieto izquierdo rojo
            // tenemos: PN, HR, nieIN, nieDN, bisnieIR y bisnieDR/N
            // por lo tanto tenemos caso 4
            return 4;

         }
         
      }

      // el hermano es negro y el padre tambien es negro

      if ((nodo->Izquierda->Izquierda == NULL) || (nodo->Izquierda->Izquierda->Color == 'N') ){ // el nieto izquierdo negro
         nietoI_N = true;
      
      }

      if ((nodo->Izquierda->Derecha == NULL) || (nodo->Izquierda->Derecha->Color == 'N') ){ //el nieto derecho negro
         nietoD_N = true;
      }


      if (!nietoI_N){
         // tenemos: PN, HN, nieIR y nieDN/R
         // por lo tanto caso 7
         return 7;
      }

      if (!nietoD_N){
         // tenemos: PN, HN, nieDR y nieIN/R
         // por lo tanto caso 5
         return 5;
      }
      
      if (nietoD_N && nietoI_N){
         // tenemos: PN, HN, nieDN y nieIN
         // por lo tanto caso 6

         return 6;
      }
      

      return i;
      
   }

      if (nodo->Color == 'R'){ //padre es rojo

         if ((nodo->Derecha->Izquierda == NULL) || (nodo->Derecha->Izquierda->Color == 'N') ){ // el nieto izquierdo negro
            nietoI_N = true;
         
         }

         if ((nodo->Derecha->Derecha == NULL) || (nodo->Derecha->Derecha->Color == 'N') ){ //el nieto derecho negro
            nietoD_N = true;
         }


         if (nietoD_N && nietoI_N ){
            // tenemos: PR, HN, nieDN y nieIN
            //por lo tanto tenemos caso1
            return 1;
         }

         if (!nietoD_N){ // es el nieto derecho rojo?
            // tenemos: PR, HN, nieDR y nieIN/R
            // por lo tanto tenemos caso 2
            return 2;
         }

         if (!nietoI_N){ // es el nieto izquierdo rojo?
            // tenemos: PR, HN, nieDN/R y nieIR
            // por lo tanto tenemos caso 5
            return 5;
         }
         
      }

      // el nodo padre es negro

      if (nodo->Derecha->Color == 'R'){ // el hermano es rojo
         
      
         if ((nodo->Derecha->Izquierda == NULL) || (nodo->Derecha->Izquierda->Color == 'N') ){ // el nieto izquierdo negro
            nietoI_N = true;
         
         }

         if ((nodo->Derecha->Derecha == NULL) || (nodo->Derecha->Derecha->Color == 'N') ){ //el nieto derecho negro
            nietoD_N = true;
         }
      
      
         if ((nodo->Derecha->Izquierda->Derecha == NULL) || (nodo->Derecha->Izquierda->Derecha->Color == 'N')){
            bisnietoD_N = true;
         }

         if ((nodo->Derecha->Izquierda->Izquierda == NULL) || (nodo->Derecha->Izquierda->Izquierda->Color == 'N')){
            bisnietoD_N = true;
         }
         
         if (bisnietoD_N && bisnietoI_N){
            // tenemos: PN, HR, nieIN, nieDN, bisnieIN y bisnieDN
            // por lo tanto nenemos caso 3
            return 3;
         }
         

         if (!bisnietoD_N){ // es el bisnieto derecho rojo
            // tenemos: PN, HR, nieIN, nieDN, bisnieIN/R y bisnieDR
            // por lo tanto tenemos caso 4
            return 4;

         }
         
      }

      // el hermano es negro y el padre tambien es negro

      if ((nodo->Izquierda->Izquierda == NULL) || (nodo->Izquierda->Izquierda->Color == 'N') ){ // el nieto izquierdo negro
         nietoI_N = true;
      
      }

      if ((nodo->Izquierda->Derecha == NULL) || (nodo->Izquierda->Derecha->Color == 'N') ){ //el nieto derecho negro
         nietoD_N = true;
      }


      if (!nietoD_N){
         // tenemos: PN, HN, nieDR y nieIN/R
         // por lo tanto caso 7
         return 7;
      }

      if (!nietoI_N){
         // tenemos: PN, HN, nieIR y nieDN/R
         // por lo tanto caso 7
         return 5;
      }

      if (nietoD_N && nietoI_N){
         // tenemos: PN, HN, nieDN y nieIN
         // por lo tanto caso 6

         return 6;
      }
      

      return i;

} 

void ArbolRN_Habitaciones :: corregirBorrado(pnodohabitacion nodo, bool direccion){

   //recibe el nodo padre del nodo borrado y la direccion de procedencia
   // direccion = true == derecha 


   bool ya_arreglado = false;
   char col;
   int numero_caso;
   pnodohabitacion temp = NULL;
   pnodohabitacion hermano_D;
   pnodohabitacion hermano_I;

   while (nodo != NULL){
      
      if (temp != NULL){
         //cambiamos el valor de direccion
    
         if (nodo->Derecha == temp){
         direccion = true;

         } else {
           direccion = false;

         }
      }

      numero_caso = getCasoColor(nodo, direccion);

      if (direccion){

         hermano_I = nodo->Izquierda;

         switch (numero_caso){

            case 1: // intercambiamos colores de Padre y Hermano
               col = nodo->Color;
               nodo->Color = hermano_I->Color;
               hermano_I->Color = col;
               ya_arreglado = true;
               break;

            case 2:
               hermano_I->Color = 'R';
               nodo->Color = 'N';
               hermano_I->Izquierda->Color = 'N';
               rotarDer(nodo,hermano_I);
               ya_arreglado = true;
               break;

            case 3:
               hermano_I->Derecha->Color = 'R';
               hermano_I->Color = 'N';
               rotarDer(nodo, hermano_I);
               ya_arreglado = true;
               break;

            case 4:
               hermano_I->Derecha->Izquierda->Color = 'N';
               rotarDerDer(nodo, hermano_I);
               ya_arreglado = true;
               break;

            case 5:
               hermano_I->Derecha->Color = 'N';
               nodo->Color = 'N';
               rotarDerDer(nodo, hermano_I);
               ya_arreglado = true;
               break;

            case 6:
               hermano_I->Color = 'R';
               // le pasamos el problema al nodo abuelo

               break;

            case 7:
               hermano_I->Izquierda->Color = 'N';
               rotarDer(nodo, hermano_I);
               ya_arreglado = true;
               break;

            default:

               getchar();
               break;
         }

      } else {

         hermano_D = nodo->Derecha;

         switch (numero_caso){

            case 1: // intercambiamos colores de Padre y Hermano
               col = nodo->Color;
               nodo->Color = hermano_D->Color;
               hermano_D->Color = col;
               ya_arreglado = true;
               break;

            case 2:
               hermano_D->Color = 'R';
               nodo->Color = 'N';
               hermano_D->Derecha->Color = 'N';
               rotarIzq(nodo,hermano_D);
               ya_arreglado = true;
               break;

            case 3:
               hermano_D->Izquierda->Color = 'R';
               hermano_D->Color = 'N';
               rotarIzq(nodo, hermano_D);
               ya_arreglado = true;
               break;

            case 4:
               hermano_D->Izquierda->Derecha->Color = 'N';
               rotarIzqIzq(nodo,hermano_D);
               ya_arreglado = true;
               break;

            case 5:
               hermano_D->Izquierda->Color = 'N';
               nodo->Color = 'N';
               rotarIzqIzq(nodo, hermano_D);
               ya_arreglado = true;
               break;

            case 6:
               hermano_D->Color = 'R';

               break;

            case 7:
               hermano_D->Derecha->Color = 'N';
               rotarIzq(nodo, hermano_D);
               ya_arreglado = true;
               break;

            default:

               getchar();
               break;
         }

      }
      
      if (ya_arreglado){
         break;
      }
      temp = nodo;
      nodo = nodo->Padre;
   }
   

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
            corregirInsercion(aux->Izquierda);
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
            corregirInsercion(aux->Derecha);
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
            corregirInsercion(aux->Izquierda);
            return 1;
        
        }
  
   } else if (CH > aux->CodHabitacion){

        if (aux->Derecha != NULL){
            return insertarNodo(CH, TC, NC, PH, aux->Derecha);

        } else {

            aux->Derecha = new NodoHabitacion(CH, TC, NC, PH);
            aux->Derecha->Padre = aux;
            ultimonodo = aux->Derecha;
            corregirInsercion(aux->Derecha);
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
        return;
    } 

   if (pnodo->Padre->Derecha == pnodo->Derecha){
      pnodo->Padre->Derecha = pnodo;
      return;
   }
   pnodo->Padre->Izquierda = pnodo;

}
void ArbolRN_Habitaciones :: rotarDerDer(pnodohabitacion pnodo, pnodohabitacion pnodoizquierda){

   //rotacion doble derecha.
   //esta rotacion esta implementada de forma directa,
   //esto significa que no se realizan rotaciones derecha o izquierda
   //,sino, una sola rotacion doble derecha

   //pnodo es el abuelo
   //pnodoizquierda es el padre 

    pnodo->Derecha = pnodoizquierda->Izquierda->Izquierda;//regalamos nodo izquierdo del hijo

    if (pnodo->Derecha != NULL){
        pnodo->Derecha->Padre = pnodo;
    }

    pnodoizquierda->Izquierda->Izquierda = pnodo; //hijo apunta al abuelo

    pnodo= pnodoizquierda->Izquierda; //reutilizamo variable

    pnodoizquierda->Izquierda = pnodo->Derecha; //regalamos nodo derecha del hijo

    if (pnodoizquierda->Izquierda != NULL){
        pnodoizquierda->Izquierda->Padre = pnodoizquierda;
    }


    pnodo->Derecha = pnodoizquierda;

    pnodoizquierda->Padre = pnodo;
    pnodo->Padre = pnodo->Izquierda->Padre;
    pnodo->Izquierda->Padre = pnodo;


   if (pnodo->Izquierda == primero){
      primero = pnodo;
      return;
   }

   if (pnodo->Padre->Derecha == pnodo->Izquierda){
      pnodo->Padre->Derecha = pnodo;
      return;
   }
   pnodo->Padre->Izquierda = pnodo;
    
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

   if (pnododerecha->Padre->Derecha == pnododerecha->Izquierda){
      pnododerecha->Padre->Derecha = pnododerecha;
      return;
   }
   pnododerecha->Padre->Izquierda = pnododerecha;
    
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
        return;
    }

   if (pnodoizquierda->Padre->Derecha == pnodoizquierda->Derecha){
      pnodoizquierda->Padre->Derecha = pnodoizquierda;
      return;
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

int ArbolRN_Habitaciones :: borrarNodo(pnodohabitacion nodo){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar


  bool encontrado = false;
  pnodohabitacion aux = primero;


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

int ArbolRN_Habitaciones :: borrarNodo(int valor){
   
// retorna
	// -4 = no se puede borrar; no existe
	// 1 = se logro borrar

  int i;
  bool encontrado = false;
  pnodohabitacion aux = primero;


    //validacion de la existencia del nodo a borrar
	if (isCodHabitacionRepetido(valor) == -3){
		//solamente entra si el valor no existe
		return -4;
	}
	
	pnodohabitacion nodo = getNodo(valor);

   i = borrarNodo(nodo, aux, encontrado);

   //hacemos la repeticion para el caso de raiz == nodo
   if (encontrado){
     //la funcion borrarNodoAux cambiara el valor de encontrado solamente si ocupamos borrar a la raiz
	  // y por lo tanto solamente entrara aquí cuando se requiera borrar la raiz
	  i = borrarNodo(nodo, aux, encontrado);
    }

   return i;

}

int ArbolRN_Habitaciones :: borrarNodo(pnodohabitacion nodo, pnodohabitacion aux, bool& encontrado){

   //nodo nunca sera null

   int i;
   bool direccion;
   pnodohabitacion min;
   pnodohabitacion max;
   pnodohabitacion borrar;

   if ((aux == NULL)){
     return -1;
   }
  
   // es menor lo que busco?
   if (aux->CodHabitacion > nodo->CodHabitacion){
      i = borrarNodo(nodo, aux->Izquierda, encontrado);

   // es mayor lo que busco
   } else if (aux->CodHabitacion < nodo->CodHabitacion){
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

      if (nodo->Color == 'R'){
         if (aux->Derecha == nodo){
            //min y max son NULL, ya que el nodo a borrar es una hoja

            delete borrar;
            aux->Derecha = NULL;
            direccion = true;

         } else {

      	   delete borrar;
      	   aux->Izquierda = NULL;
            direccion = false;
         }

         encontrado = false;
         return 1;
      }
      

      // borramos un nodo hoja negro

      if (aux->Derecha == nodo){
         //min y max son NULL, ya que el nodo a borrar es una hoja

         delete borrar;
         aux->Derecha = NULL;
         direccion = true;

      } else {

      	delete borrar;
      	aux->Izquierda = NULL;
         direccion = false;
      }
      
      encontrado = false;
      corregirBorrado(aux, direccion);
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
         primero->Color = 'N';
			delete borrar; // borramos la raiz
			encontrado = false; // la dejamos en falso

         return 1;
	   }

      if (nodo->Color == 'R'){
         // esta situacion es imposible
         if (aux->Derecha == nodo){

            aux->Derecha = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
            aux->Derecha->Padre = aux;
            direccion = true;
            delete borrar;
	
         } else {

            aux->Izquierda = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
            aux->Izquierda->Padre = aux;
            direccion = false;
            delete borrar;

         }

         encontrado = false;
         return 1;

      }
      
      // por lo tanto el nodo es negro. eso implica que su hijo es rojo y por lo tanto no es necesario llamar a correccion

      if (aux->Derecha == nodo){

         aux->Derecha = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
         aux->Derecha->Padre = aux;
         aux->Derecha->Color = nodo->Color; // esto siempre sera negro
         direccion = true;
         delete borrar;
	
      } else {

         aux->Izquierda = nodo->Derecha;//no requiere actualizar puntero izquierdo, ya que por definicion el nodo->Izquierda == NULL
         aux->Izquierda->Padre = aux;
         aux->Izquierda->Color = nodo->Color;// esto siempre sera negro
         direccion = false;
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
         // solamente ocurre cuando existen solamente 2 nodos

			primero = nodo->Izquierda; //raiz a nulo
         primero->Padre = nodo->Padre;
         primero->Color = 'N';
			delete borrar; // borramos la raiz
			encontrado = false; // la dejamos en falso
         return 1;
	   }

      if (nodo->Color == 'R'){
         // esta situacion es imposible

         if (aux->Derecha == nodo){
         
           aux->Derecha = nodo->Izquierda;
           aux->Derecha->Padre = aux;
           direccion = true;
           delete borrar;

         } else {

           aux->Izquierda = nodo->Izquierda;
           aux->Izquierda->Padre = aux;
           direccion = false;
           delete borrar;

         }
         encontrado = false;
         return 1;

      }

      // por lo tanto el nodo es negro. eso implica que su hijo es rojo y por lo tanto no es necesario llamar a correccion

      if (aux->Derecha == nodo){
      
        aux->Derecha = nodo->Izquierda;
        aux->Derecha->Padre = aux;
        aux->Derecha->Color = nodo->Color; // esto siempre sera negro
        direccion = true;
        delete borrar;

      } else {

        aux->Izquierda = nodo->Izquierda;
        aux->Izquierda->Padre = aux;
        aux->Izquierda->Color = nodo->Color; // esto siempre sera negro
        direccion = false;
        delete borrar;

      }

      encontrado = false;
      return 1;
      
    	}
      
    	// el nodo tiene hijos de ambos lados

      borrar = nodo;

    	min = MINValor(nodo->Derecha); // retorna el nodo a remplazar
    	max = MAXValor(nodo->Izquierda); // retorna el nodo a remplazar

      //por default se utilizara el maxValor.
      //cuando este se acabe, entonces el nodo a borrar no tendra hijos izquierdos y por lo tanto no entrara aqui

      bool segundoBorrado = false;
      char col;
      swapNodos(max, nodo);

      col = nodo->Color;
      nodo->Color = max->Color;
      max->Color = col;
      // cuando realizamos este cambio de color, logramos mantener los colores en sus posiciones correctas y asi no cambiar ningun color 

      //recordatorio; la funcion intercambia solamente las conexiones de los nodos, el nodo a borrar sigue siendo "nodo"

      // usamos "max->Izquierda" como punto de partida, ya que sabemos que la ubicacion original del nodo "max", se encuentra
      // en el subarbol izquierdo de "nodo", pero al intercambiar las conexiones, el puntero de ese subarbol izquierdo se encuentra en "max"
      
      if (max->Izquierda == nodo){
        // el nodo a borrar es el hijo adyacente y este no puede tener hijos derechos
        // esta condicional es de alta importancia, ya que protege de una excepcion con la cual el algoritmo no puede lidiar
        // de forma ordenada y limpia


         if (nodo->Color == 'R'){ //caso: PN, HX, NR
            // nodo se encuentra en una hoja, por lo tanto solamente se borra

            max->Izquierda = NULL;
            delete borrar;
            encontrado = false;
            return 1;
            
         }

         // el nodo es color negro y puede tiene 0 o 1 hijos
         // de tener un hijo este es siempre es el izquierdo y siempre sera rojo

         if (nodo->Izquierda != NULL){
            
            max->Izquierda = nodo->Izquierda;
            nodo->Izquierda->Color = nodo->Color; // esto es siempre 'n' 
            delete borrar;
            encontrado = false;
            return 1;

         }

         // el nodo a borrar es negro y no tiene hijos
         // por lo tanto deberemos aplicar la correccion de borrado de hojas negras


        max->Izquierda = NULL;
        
        delete borrar;
        corregirBorrado(max, false);
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
pnodohabitacion ArbolRN_Habitaciones :: MINValor(pnodohabitacion hijoderecha){ 
   
   // requiere que el nodo tenga un puntero a su padre

   //recibe la posicion del nodo a la derecha de forma inicial
   // recibe la posicion del nodo a la izquierda de manera recursiva

   //retorna el nodo menor;
   //retorna null si el nodo min no existe

   pnodohabitacion temp;

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
pnodohabitacion ArbolRN_Habitaciones :: MAXValor(pnodohabitacion hijoIzquierda){
   
   // requiere que el nodo tenga un puntero a su padre
   
   //recibe la posicion del nodo a la izquierda de forma inicial
   // recibe la posicion del nodo a la derecha de manera recursiva

   //retorna el nodo mayor;
   //retorna null si el nodo max no existe

   pnodohabitacion temp;

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

void ArbolRN_Habitaciones :: swapNodos(pnodohabitacion nodo1, pnodohabitacion nodo2){

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
   

  pnodohabitacion temp1;
  pnodohabitacion temp2;

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

