#ifndef INSTANCIASCLASESLISTAS_H
#define INSTANCIASCLASESLISTAS_H

#include "listas.h" //Se llama al header que posee los tipos de listas y los colores de consola

class paisNL : nodoLDC{
    public:
        paisNL(int codPais, string nombre);

    private:
        int codPais;
        string nombre;

        paisNL *anterior;
        paisNL *siguiente;

    friend class paisesL;
};
typedef paisNL *ppaisNL;

class paisesL : listaDobleCircular{
    public:
        paisesL();
        bool listaVacia();
        ppaisNL obtenerPaisCodigo(int codPais);
        void insertarPais(int codPais, string nombre);
        void eliminarPais(int codPais);
        int obtenerPosPaisCodigo(int codPais);
        string nombrePaisCodigo(int codPais);
        void modificarNombrePais(int codPais, string nuevoNombre);
        void muestraDetalladaPaises();

    private:
        ppaisNL primero;
};

//En los constructores se asignan los parámetros del objeto de determinada clase y en los destructores se eliminan los nodos dentro de la lista y si el nodo que elimina posee una lista también elimina sus elementos

paisNL::paisNL(int codPais, string nombre){
    this->codPais = codPais;
    this->nombre = nombre;
    this->anterior = NULL;
    this->siguiente = NULL;
}

paisesL::paisesL(){
    this->primero = NULL;
}

bool paisesL::listaVacia(){
    return primero==NULL;
}

ppaisNL paisesL::obtenerPaisCodigo(int codPais){
    ppaisNL temp = primero;
    if(temp!=NULL){ 
        while(temp->siguiente!=primero){
            if(temp->codPais==codPais){
                return temp;
            }
            temp = temp->siguiente;
            temp->siguiente->anterior = temp;
        }
        if(temp->codPais==codPais) return temp;
    }
    return NULL;
}

void paisesL::insertarPais(int codPais, string nombre){
    if (listaVacia()){
        primero = new paisNL(codPais,nombre);
        primero->anterior = primero;
        primero->siguiente = primero;
    }else{
        if(obtenerPaisCodigo(codPais)==NULL){
            ppaisNL nuevo = new paisNL(codPais,nombre);
            ppaisNL temp = primero;
            while(temp->siguiente!=primero){
                temp = temp->siguiente;
                temp->anterior = primero->anterior;
            }
            nuevo->anterior = primero->anterior;
            nuevo->siguiente = primero->anterior->siguiente;
            primero->anterior->siguiente = nuevo;
            primero->anterior = nuevo;
        }
    }
}

int paisesL::obtenerPosPaisCodigo(int codPais){
    int cont=0 , pos=0;
    ppaisNL temp = primero;
    while(temp->siguiente!=primero){
        cont++;
        if(temp->codPais==codPais){
            pos = cont;
        }
        temp = temp->siguiente;
    }
    if(temp->codPais==codPais) pos = cont+1;
    return pos;
}

void paisesL::eliminarPais(int codPais){
    int pos = obtenerPosPaisCodigo(codPais);
    if(!listaVacia()){
        if(pos>0){
            if(pos==1){
                if (primero->siguiente == primero){
                    ppaisNL temp = primero;
                    primero = NULL;
                    delete temp;
                }else{
                    ppaisNL aux = primero->anterior;
                    ppaisNL temp = primero;
                    aux->siguiente = primero->siguiente;
                    primero = primero->siguiente; 
                    primero->anterior = aux;
                    delete temp;
                }
            }else{
                int cont = 2;
                ppaisNL aux =  primero;
                while(cont<pos){
                    aux=aux->siguiente;
                    cont++;
                }
                ppaisNL temp = aux->siguiente;
                aux->siguiente=aux->siguiente->siguiente;
                aux->siguiente->anterior=aux;
                delete temp;
            }
        }
    }
}

string paisesL::nombrePaisCodigo(int codPais){
    ppaisNL temp = primero;
    if(temp!=NULL){ 
        while(temp->siguiente!=primero){
            if(temp->codPais==codPais){
                return temp->nombre;
            }
            temp = temp->siguiente;
            temp->siguiente->anterior = temp;
        }
        if(temp->codPais==codPais) return temp->nombre;
    }
    return "";
}

void paisesL::modificarNombrePais(int codPais, string nuevoNombre){
    ppaisNL temp = obtenerPaisCodigo(codPais);
    temp->nombre = nuevoNombre;
    temp->anterior->siguiente = temp;
    temp->siguiente->anterior = temp;
}

void paisesL::muestraDetalladaPaises(){
    ppaisNL temp = primero;
    if(temp!=NULL){
        celeste(); cout << endl << "Paises:" << endl << endl;
        while(temp->siguiente!=primero){
            blanco();
            cout << "Codigo: " << temp->codPais << endl;
            cout << "Nombre: " << temp->nombre << endl;
            gris(); cout << "-------------------------" << endl;
            temp = temp->siguiente;
        }
        blanco();
        cout << "Codigo: " << temp->codPais << endl;
        cout << "Nombre: " << temp->nombre << endl;
        gris(); cout << "-------------------------" << endl << endl;
    }else{
        rosado(); cout << endl << "No hay paises registrados" << endl << endl;
    }
    azul();
}

#endif