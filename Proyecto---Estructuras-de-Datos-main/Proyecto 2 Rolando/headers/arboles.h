#ifndef ARBOLES_H
#define ARBOLES_H

#include "colores.h"

class resultado;

class nodoABB{
    public:
        nodoABB();
        nodoABB(string valor);

    private:
        string valor;
        nodoABB *hijoIzq;
        nodoABB *hijoDer;
};
typedef nodoABB *pnodoABB;

class arbolBinarioBusqueda{
    public:
        arbolBinarioBusqueda();

    private:
        pnodoABB raiz;
};

class nodoAB{
    public:
        nodoAB();
        nodoAB(int valor);

    private:
        int valor;
        nodoAB *hijoIzq;
        nodoAB *hijoDer;

    friend class arbolB;
};
typedef nodoAB *pnodoAB;

class paginaAB{
    public:
        paginaAB(){ cuenta = 0; }

    private:
        int cuenta;
        nodoAB *claves[5];
        paginaAB *ramas[5];

    friend class arbolB;
};
typedef paginaAB *ppaginaAB;

class arbolB{
    public:
        arbolB();
        resultado buscarNodo(pnodoAB clave, ppaginaAB p, boolean encontrado, int k);
        void inserta(pnodoAB c1, ppaginaAB raiz);
        resultado empujar(pnodoAB c1, ppaginaAB r, boolean empujaArriba, pnodoAB mdna, ppaginaAB x); //Quizás sea boolean
        void meterHoja(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k);
        void dividirNodo(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k, pnodoAB mda, ppaginaAB mder);

    private:
        ppaginaAB raiz;
        int max = 4; int min = 2;
};

class nodoAAVL{
    public:
        nodoAAVL();
        nodoAAVL(string valor);

    private:
        string valor;
        int factorBalance;
        nodoAAVL *hijoIzq;
        nodoAAVL *hijoDer;
        nodoAAVL *anterior;
        nodoAAVL *siguiente;
    
    friend class arbolAVL;
};
typedef nodoAAVL *pnodoAAVL;

class arbolAVL{
    public:
        arbolAVL();
        void borrar(pnodoAAVL nodoB, bool booleano);
        void borrarBalanceado(pnodoAAVL r, bool booleano, int eliminar);
        void equilibrar1(pnodoAAVL n, bool booleano);
        void equilibrar2(pnodoAAVL n, bool booleano);
        void insertarBalanceado(pnodoAAVL r, bool booleano, int x);
        void rotacionDobleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionDobleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleDerecha(pnodoAAVL n1, pnodoAAVL n2);

    private:
        bool hH;
        pnodoAAVL raiz;
        bool rojo , negro;
};

class nodoARN{
    public:
        nodoARN();
        nodoARN(string valor);

    private:
        string valor;
        nodoARN *hijoIzq;
        nodoARN *hijoDer;

    friend class arbolRojiNegro;
};
typedef nodoARN *pnodoARN;

class arbolRojiNegro{
    public:
        arbolRojiNegro();
        void borrar(pnodoAAVL nodoB, bool booleano);
        void borrarBalanceado(pnodoAAVL r, bool booleano, int eliminar);
        void equilibrar1(pnodoAAVL n, bool booleano);
        void equilibrar2(pnodoAAVL n, bool booleano);
        void insertarBalanceado(pnodoAAVL r, bool booleano, int x);
        void rotacionDobleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionDobleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleIzquierda(pnodoAAVL n1, pnodoAAVL n2);
        void rotacionSimpleDerecha(pnodoAAVL n1, pnodoAAVL n2);
        void reglaTio();
        
    private:
        pnodoARN raiz;
};

class nodoAAA{
    public:
        nodoAAA();
        nodoAAA(string valor);

    private:
        string valor;
        nodoAAA *anterior;
        nodoAAA *siguiente;
        nodoAAA *hijoIzq;
        nodoAAA *hijoDer;

    friend class arbolAA;
};
typedef nodoAAA *pnodoAAA;

class arbolAA{
    public:
        arbolAA();
        void reparto();
        void giro();

    private:
        pnodoAAA raiz;
};

class resultado{
    public:
        boolean booleano;
        int entero;
        pnodoAB nodoAB;
};

nodoABB::nodoABB(){
    this->valor = "";
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

nodoABB::nodoABB(string valor){
    this->valor = valor;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

nodoAB::nodoAB(){
    this->valor = 0;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

nodoAB::nodoAB(int valor){
    this->valor = valor;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

nodoAAVL::nodoAAVL(){
    this->valor = "";
    this->factorBalance = 0;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
    this->anterior = NULL;
    this->siguiente = NULL;
}

nodoAAVL::nodoAAVL(string valor){
    this->valor = valor;
    this->factorBalance = 0;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
    this->anterior = NULL;
    this->siguiente = NULL;
}

nodoARN::nodoARN(){
    this->valor = "";
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

nodoARN::nodoARN(string valor){
    this->valor = valor;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

nodoAAA::nodoAAA(){
    this->anterior = NULL;
    this->siguiente = NULL;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
    this->valor = "";
}

nodoAAA::nodoAAA(string valor){
    this->anterior = NULL;
    this->siguiente = NULL;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
    this->valor = valor;
}

arbolBinarioBusqueda::arbolBinarioBusqueda(){
    this->raiz = NULL;
}

arbolB::arbolB(){
    this->raiz = NULL;
}

arbolAVL::arbolAVL(){
    this->raiz = NULL;
}

arbolRojiNegro::arbolRojiNegro(){
    this->raiz = NULL;
}

arbolAA::arbolAA(){
    this->raiz = NULL;
}

resultado arbolB::buscarNodo(pnodoAB clave, ppaginaAB p, boolean encontrado, int k){
    resultado res;
    if(clave->valor<p->claves[1]->valor){
        encontrado = false;
        k = 0;
    }else{
        k = p->cuenta;
        while((clave->valor<p->claves[k]->valor) && k>1){
            k--;
        }
        encontrado = clave->valor==p->claves[k]->valor;
    }
    res.booleano = encontrado;
    res.entero = k;
    return res;
}

void arbolB::inserta(pnodoAB c1, ppaginaAB raiz){
    pnodoAB x;
    ppaginaAB xr = NULL, p = NULL;
    resultado res = empujar(c1, raiz, false, x, xr);
    boolean empujarArriba = res.booleano;
    x = res.nodoAB;
    if(empujarArriba){
        ppaginaAB p = new paginaAB();
        p->cuenta = 1;
        p->claves[1] = x;
        p->ramas[0] = raiz;
        p->ramas[1] = xr;
        raiz = p;
        this->raiz = raiz;
    }
}

resultado arbolB::empujar(pnodoAB c1, ppaginaAB r, boolean empujaArriba, pnodoAB mdna, ppaginaAB xr){
    resultado res;
    int k;
    boolean esta = false;
    if(r==NULL){
        empujaArriba = true;
        mdna = c1;
        xr = NULL;
        res.nodoAB = mdna;
    }else{
        res = buscarNodo(c1, r, esta, k);
        esta = res.booleano; 
        k = res.entero;
        if(esta){
            cout << "elemento repetido" << endl;
        }else{
            res = empujar(c1, r->ramas[k], empujaArriba, mdna, xr);
            empujaArriba = res.booleano;
            if(empujaArriba){
                if(r->cuenta<max){
                    empujaArriba = false;
                    meterHoja(mdna, xr, r, k);
                }else{
                    empujaArriba = true;
                    dividirNodo(mdna, xr, r, k, mdna, xr);
                }
            }
        }
    }
    res.booleano = empujaArriba;
    return res;
}

void arbolB::meterHoja(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k){
    for(int i=p->cuenta;i>k+1;i--){
        p->claves[i+1] = p->claves[i];
        p->ramas[i+1] = p->ramas[i]; 
    }
    p->claves[k+1] = x;
    p->ramas[k+1] = xDer;
    p->cuenta++;
}

void arbolB::dividirNodo(pnodoAB x, ppaginaAB xDer, ppaginaAB p, int k, pnodoAB mda, ppaginaAB mder){
    int posmda;
    if(k<=min){
        posmda = min;
    }else{
        posmda = min+1;
    }
    mder = new paginaAB();
    for(int i=posmda+1;i<=max;i++){
        mder->claves[i-posmda] = p->claves[i];
        mder->ramas[i-posmda] = p->ramas[i];
    }
    mder->cuenta = max-posmda;
    p->cuenta = posmda;
    if(k<=min){
        meterHoja(x,xDer,p,k);
    }else{
        meterHoja(x,xDer,mder,k-posmda);
    }
    mda = p->claves[p->cuenta];
    mder->ramas[0] = p->ramas[p->cuenta];
    p->cuenta++;
}

#endif