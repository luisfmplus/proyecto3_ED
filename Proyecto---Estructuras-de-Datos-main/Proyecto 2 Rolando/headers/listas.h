#ifndef INSTANCIASLISTAS_H
#define INSTANCIASLISTAS_H

#include "colores.h"

//nodo de lista simple
class nodoLS{
	public:
	    nodoLS(string v);
	    nodoLS(string v, nodoLS * signodo);
	    
    private:
	    string valor;
    	nodoLS *siguiente;

    friend class listaSimple;
};

typedef nodoLS *pnodoLS; //definición de puntero de nodo de lista simple

//definición de lista simple, con sus métodos y atributos
class listaSimple{
    public:
    	listaSimple();
        void insertarFinal(string v);
        bool listaVacia();
        void borrarUltimo();
        int largoLista();
        string obtenerValorPos(int pos);
        void mostrar();

    private:
		pnodoLS primero;
};

//nodo de lista doble
class nodoLD{
    public:
        nodoLD();
        nodoLD(nodoLD * signodo);

    private:
        nodoLD *siguiente;
        nodoLD *anterior;
    
    friend class listaDoble;
};

typedef nodoLD *pnodoLD; //definición de nodo de lista simple

//lista doble
class listaDoble{
    public:
        listaDoble();
    
    private:
        pnodoLD primero;
};

//nodo de lista doble circular
class nodoLDC{
    public:
        nodoLDC();
        nodoLDC(nodoLDC * signodo);

    private:
        nodoLDC *siguiente;
        nodoLDC *anterior;
  
   friend class listaDobleCircular;
};

typedef nodoLDC *pnodoLDC; //puntero de nodo de lista doble circular

//lista doble circular
class listaDobleCircular{
    public:
        listaDobleCircular();

    private:
        pnodoLDC primero;
};

//nodo de lista circular
class nodoLC{
    public:		
	    nodoLC();
		nodoLC(nodoLC * signodo);

	private:
    	nodoLC *siguiente;
    
	friend class listaCircular;
};

typedef nodoLC *pnodoLC; //puntero de nodo de lista doble circular

//lista doble circular
class listaCircular{
	public:
	    listaCircular();

    private:
    	pnodoLC primero;
};

//construtor de nodo de lista simple, establece su valor y el puntero siguiente en NULL
nodoLS::nodoLS(string v){
	valor = v;
	siguiente = NULL;
}

//segundo construtor de nodo de lista simple, establece su valor y el puntero siguiente apunta a otro nodo
nodoLS::nodoLS(string v, nodoLS * signodo) {
	valor = v;
	siguiente = signodo;
}

//construtor de lista simple, establece el puntero primero en NULL
listaSimple::listaSimple(){
    primero = NULL;
}

//indica si la lista simple está vacía, devolviendo un valor booleano
bool listaSimple::listaVacia(){
    return primero == NULL;
}

//inserta un elemento nuevo al final de la lista simple
void listaSimple::insertarFinal(string v){
   	if (listaVacia())
     	primero = new nodoLS(v);
   	else{
		pnodoLS aux = primero;
        while ( aux->siguiente != NULL)
        	aux= aux->siguiente;
        aux->siguiente=new nodoLS(v);
    }    
}

//borra el último elemento contenido en la lista simple
void listaSimple::borrarUltimo(){
	if (listaVacia()){
    	cout << "No hay elementos en la lista, no se puede borrar final" << endl;
   }else{
        if(primero->siguiente == NULL) {
            primero= NULL;
        } else {
        	pnodoLS aux = primero;
            while (aux->siguiente->siguiente != NULL) {
            	aux = aux->siguiente;
            }    
            pnodoLS temp = aux->siguiente;
            aux->siguiente= NULL;    
            delete temp;
        }
    }
}

//devuelve la cantidad de elementos contenidos en la lista simple
int listaSimple::largoLista(){
    int cont=0;
    pnodoLS aux;
    aux = primero;
    if(listaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        	aux=aux->siguiente;
        	cont++;
    	}
    	return cont;
    }
}

//devuelve el valor de un nodo de la lista ubicado en una cierta posición
string listaSimple::obtenerValorPos(int pos){
	pnodoLS temp = primero;
	int cont = 1;
    string resultado = "";
	while (temp!=NULL){
		if(pos==cont){
		    resultado = temp->valor;
            break;
		}
		temp = temp->siguiente;
		cont++;
	}
    return resultado;
}

//muestra el  valor contenido de todos los nodos de la lista simple
void listaSimple::mostrar(){
    nodoLS *aux;
   	if (primero== NULL)
    	cout << "No hay elementos, no se puede mostrar"<<endl;  
   	else{
   		aux = primero;
		while(aux) {
			cout << aux->valor << "-> ";
		    aux = aux->siguiente;
		}
		cout << endl;
   	}
}

//construtor de nodo de lista doble, establece el puntero siguiente y anterior en NULL    
nodoLD::nodoLD(){
    siguiente = NULL;
    anterior = NULL;
}

//segundo construtor de nodo de lista doble, establece el puntero siguiente en otro nodo de lista doble
nodoLD::nodoLD(nodoLD * signodo){
    siguiente = signodo;
}

//construtor de lista doble, establece el puntero primero en NULL
listaDoble::listaDoble(){
    primero =  NULL;
}

//construtor de nodo de lista doble circular, establece el puntero siguiente y anterior en NULL
nodoLDC::nodoLDC(){
    siguiente = NULL;
    anterior =NULL;
}

//segundo construtor de nodo de lista doble circular, establece el puntero siguiente en otro nodo de lista doble circular
nodoLDC::nodoLDC(nodoLDC * signodo){
    siguiente = signodo;
}

//construtor de lista doble circular, establece el puntero primero en NULL
listaDobleCircular::listaDobleCircular(){
    primero = NULL;
}

//construtor de nodo de lista circular, establece el puntero siguiente en NULL
nodoLC::nodoLC(){
	siguiente = NULL;
}

//segundo construtor de nodo de lista circular, establece el puntero siguiente en NULL
nodoLC::nodoLC(nodoLC * signodo){
	siguiente = signodo;
}

//constructor de lista circular, establece el primero en NULL
listaCircular::listaCircular(){
    primero =  NULL;
}

#endif