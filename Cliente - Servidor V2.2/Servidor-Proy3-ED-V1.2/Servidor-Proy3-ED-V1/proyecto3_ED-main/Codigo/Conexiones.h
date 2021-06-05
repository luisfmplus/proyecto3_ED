#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;

//--------------------------------------------------------Nodos / Constructores ---------------------------------------------------------
class nodo{

   public:
    nodo(int v)
    {
       valor = v;
       siguiente = NULL;
    }
   private:
    int valor;
    nodo *siguiente;
    
        
   friend class lista2;
   friend class grafo;
};
typedef nodo *pnodo;

class Arista{
	public:
	Arista(int destino, int distancia)
	{
		Destino = destino;
		Distancia = distancia;
		AristaAd = NULL;
		visitado = false;
		ciclo  = false;
		
		
	}
	int Destino, Distancia;
	Arista* AristaAd;
	bool visitado;
	bool ciclo;
	
	friend class Vertice;
	friend class grafo;
	friend class pila;
	friend class cola;

};


class Vertice{
	public:
	Vertice(int codpais,string nombre ){
		CodPais  = codpais;
		Nombre = nombre;
		VerticeAd = NULL;
		AristasV = NULL;
		procesado = false;
		Visitado = false;
		
	}
	int CodPais;
	string Nombre;
	Vertice* VerticeAd;//Vertice Adyacente
	Arista* AristasV;
	bool procesado, Visitado;
	
	friend class Arista;
	friend class grafo;
	friend class pila;
	friend class cola;
};


class nodoConexion { 
	
   public:
    nodoConexion(int codpais, int CodDestino,int peso) 
    {
       codpais = codpais;
	   CodDestino = CodDestino;
       distancia = peso;
       procesado = false; 
       visitado = false;
       conexiones = NULL; // Recorrer las conexiones del vertice
       siguiente = NULL; //Avanzar al siguiente vertice
    }

   // atributos
   	bool visitado, procesado;
    int codpais, distancia, CodDestino;
    nodoConexion* conexiones;
    nodoConexion *siguiente; 

friend class grafo;
friend class pila;
friend class cola;


};
typedef nodoConexion *pnodoConexion; 

//----------------------------------------------------------Lista--------------------------------------------------------------------------------------------

class lista2 {
   public:
    lista2() { primeroL = NULL; 
				primeroC = NULL;}

    
    void InsertarVertices(int v);
    void InsertarAristas(Arista* v);
    bool ListaVacia() { return primeroL == NULL; } 
    int largoLista();
    pnodo Buscar(int pos);
    bool BuscarE(int elemento);
    void Mostrar();
    void AgregarAristas(int cod, int destino, int peso);
    
   private:
    pnodo primeroL;
    pnodoConexion primeroC;
   
};

int lista2::largoLista(){
    int cont=0;

    pnodo aux;
    aux = primeroL;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}
void lista2::Mostrar()
{
   nodo *aux;
   
   aux = primeroL;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}
/*
void lista::InsertarAristas(Arista* v)
{
   if (ListaVacia())
     primeroL = v;
   else
     { pnodo aux = primeroL;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=v;
      }    
}
*/

void lista2::AgregarAristas(int CodPais, int destino, int peso){
	if (ListaVacia())
     primeroC = new nodoConexion(CodPais,destino,peso);
   else
     { nodoConexion* aux = primeroC;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoConexion(CodPais,destino,peso);
      }  
}

void lista2::InsertarVertices(int v)
{
   if (ListaVacia())
     primeroL = new nodo(v);
   else
     { nodo* aux = primeroL;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(v);
      }    
}
/*BUSCAR UN ELEMENTO */  
pnodo lista2::Buscar(int pos)
{
  pnodo aux = primeroL;
  pnodo aux2 = new nodo(1);
  int cont = 0;
  while (aux){
  	if(cont==pos){
  		 aux2 = aux;
		  }
	cont++;
	aux=aux->siguiente;
  }
  		

  return aux2;
}

bool lista2::BuscarE(int elemento)
{
	bool existe = false;
  pnodo aux= primeroL;
  int cont = 1;
  while ((aux->siguiente!=NULL)){
  	if(aux->valor==elemento){
  			existe = true;
		  }
	aux=aux->siguiente;
  }
  		

  return existe;
}

//----------------------------------------------------------Pila----------------------------------------------------------------------------------------------

class pila 
{

public:
      	int Tope;
   		Vertice* Pila [60];

       pila(){
       Tope = -1;
       for(int i =0;i<60;i++){
         Pila[i]=0;    
           }
       }
       
      bool pilaVacia(){return Tope < 0;}        
      void push(Vertice* v); 
      void pop ();
      void imprimir();
      Vertice* tope();
};

void pila:: push (Vertice* v)
{
         if(Tope <(60-1))
         {
            Tope++;
            Pila[Tope]= v; 
           
         }
         else
             cout<<"La pila esta llena";  
}   

void pila:: pop ()
{
         if(!pilaVacia()){
            Tope--;
         }
         else{
         cout<<"La pila esta vacia";  
         }
}  

Vertice* pila::tope(){
	
	return Pila[Tope];
}

// ---------------------------------------------------------------------Cola----------------------------------------------------------------------------------
class cola 
{

   int frente;
   int fondo;

	Vertice*  Cola [60];


public:
       cola(){
       frente = 0;
       fondo = -1;
       for(int i =0;i<60;i++){
         Cola[i]=0;    
           }
       }
       
      bool ColaVacia(){return fondo < frente;}        
	  void insertar(Vertice* v); 
	  void eliminar ();
	  void imprimir();
	  Vertice* Frente();
	  friend class grafo;
};

cola Cola;
void cola:: insertar (Vertice* v)
{
         if(fondo < 60 -1){
             fondo++;
             Cola[fondo] = v; 
           
         }
         else{
         cout<<"La cola esta llena";  
         }
}   

void cola:: eliminar ()
{
         if(!ColaVacia()){
            frente++;
         }
         else{
         cout<<"La cola esta vacia";  
         }
}

void cola:: imprimir(){
     for(int i = frente;i<fondo+1;i++){
         cout<<Cola[i]<<"->"<<endl;    
           }
}

Vertice* cola::Frente(){

	return Cola[frente];
}
//GRAFO-------------------------------------------------------------------------------------------------------------------------------------
class grafo{
	public:
    grafo(){primero=NULL;}

    
    void leerPaises();
	void leerArchivoConexiones();
    void InsertarVertice(int v, string nombre);
    void AgregarConexiones(int CodigoComparar, int destino, int distancia);
    bool grafoVacia() { return primero == NULL; } 
    void borrarPosicion(int pos);
    int Validar(int cod);
    void ValidarConexo();
    
    string Anchura(int cod);
    void MarcarVisitado(int cod, int destino);
    Vertice* EncontrarVertice(int cod);
    Vertice* Visitados();
    
    string Profundidad(int cod);
    
    int Prim(int cod);
    bool AnalizarCiclo(Arista* Analisis, int conectado, lista2 W);
    Arista* ConexionesV(Vertice* PaisInicio, lista2 W);
    void MarcarCiclo(int cod, int destino);
    
    int Kurskal(int cod);
    void RecorrerGrafo();
    
    
    void Mostrar();
    void Primero();
    void Reiniciar();

    int largografo();
    void invertir();
      
   private:
    Vertice* primero; // nodoConexion *primero; tipo nodoConexion tiene derechoi direccionar un nodoConexion
   	friend class Vertice;
   	friend class Arista;
   	friend class pila;
   	friend class cola;
};
// GLOBALES
grafo Conexiones;
grafo Visitados;
grafo Procesados; // Se trabaja como la W de Prim


//-------------------------------------------------------------------Funciones------------------------------------------------------------------------------------------


int grafo::largografo(){ //largo
    int cont=0;

    Vertice* aux; //nodoConexion *aux;
    aux = primero;
    if(grafoVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->VerticeAd;
        cont++;
    }
    return cont;
    }
    
}

void grafo::leerPaises(){

  ifstream archivo;
  archivo.open("proyecto3_ED-main\\Datos\\Paises2.txt",ios::in); //abre archivo en modo lectura
  while (!archivo.eof()){
  	string texto = ""; //almacena linea del archivo
  	string w = "";  //constructor segun la descomposicion del texto
  	int cont = 0; //Posicion en el txt
  	//componentes de cada hotel
  	int codpais = 0;

  	string nombre ="";

    getline(archivo,texto);
    
    for (auto rem : texto) 
   { 
       if (rem==';') 
       { 
       		if (cont==0){
       			istringstream(w) >> codpais; //almacena el codigo del pais
           		w=""; 
            }
            
			
			cont++;
       } 
       
       else
       { 
           w=w+rem; 
       } 
   }  
	nombre = nombre+w; //almacena el nombre del hotel

 	if(Validar(codpais)==0){
 		InsertarVertice(codpais, nombre);
	 }
   	
   w="";
} 
  
  archivo.close();
}

void grafo::leerArchivoConexiones(){
  ifstream archivo;
  archivo.open("proyecto3_ED-main\\Datos\\Conexiones.txt",ios::in); //abre archivo en modo lectura
  while (!archivo.eof()){
  	string texto = ""; //almacena linea del archivo
  	string w = "";  //constructor segun la descomposicion del texto
  	int cont = 0; //Posicion en el txt
  	//componentes de cada hotel
  	int codpais, CodPais, distancia;

    getline(archivo,texto);
    
    for (auto rem : texto) 
   { 
       if (rem==';') 
       { 
       		if (cont==0){
       			istringstream(w) >> codpais; //almacena el codigo del pais
           		w=""; 
            }
            if (cont==1){
       			istringstream(w) >> CodPais; //almacena el codigo del segundo pais en la conexion
           		w=""; 
            }
            
			
			cont++;
       } 
       
       else
       { 
           w=w+rem; 
       } 
   }  
	istringstream(w) >> distancia; //almacena el codigo del segundo pais en la conexion

 	if(Conexiones.Validar(codpais)==1 && Conexiones.Validar(CodPais)==1){
 		AgregarConexiones(codpais, CodPais, distancia);
 		AgregarConexiones(CodPais, codpais, distancia);
	 }
   	
   w="";
} 
  
  archivo.close();
}

int grafo::Validar(int cod)
{
	/* 
	0 =  No existe
	1 =  Existe // Repetido
	*/
	int verificador = 0;
	if(grafoVacia()){
		return 0;
	}
	else{
	
	   Vertice* aux=primero;
	   while(aux)
	     {
	      if(cod == aux->CodPais) {
	      	verificador = 1;
	      	
		  } 
		  aux=aux->VerticeAd;               
	      
	     }
	}
      return verificador;
}  

void grafo::AgregarConexiones(int CodigoComparar, int destino, int distancia){
	Vertice* aux = primero;
	
	while(aux){
		if(aux->CodPais == CodigoComparar){
			break;
		}
		else{
			aux = aux->VerticeAd;
		}
	}
	if (aux->AristasV == NULL){
		aux->AristasV = new Arista(destino,distancia);
	}
	else{
		Arista* aux2 = aux->AristasV;
		while(aux2->AristaAd!=NULL){
			aux2 = aux2->AristaAd;
		}
		aux2->AristaAd = new Arista(destino, distancia);
		
	}
	
}
void grafo::InsertarVertice(int cod, string nombre)
{

   if (grafoVacia())
     primero = new Vertice(cod, nombre);
     
   else
     { Vertice* aux = primero;
        while ( aux->VerticeAd!=NULL)
          aux= aux->VerticeAd;
        aux->VerticeAd=new Vertice(cod, nombre);
      }    
}

void grafo:: borrarPosicion(int pos){ 
//Unicamente elimina el vertice
//Agregar la eliminacion en los demas vertices que contenian al vertice dento de las conexiones
     if(grafoVacia()){
              cout << "grafo vacia" <<endl;
    }else{
         if((pos>largografo())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==1){
        primero=primero->VerticeAd;
        }else{
          int cont=2;
            Vertice* aux=  primero;
            while(cont<pos){
             aux=aux->VerticeAd;
             cont++;
            }
            aux->VerticeAd=aux->VerticeAd->VerticeAd;
            }
        }
     }

}

void grafo::Mostrar()
{
   Vertice *aux;
   //cout<<2<<endl;
   aux = primero;
   while(aux) {
      cout << aux->CodPais<<"w ";
      if(aux->AristasV != NULL){
      	Arista* aux2 = aux->AristasV;
      	while(aux2){
      		cout<<" "<<aux2->Destino;
      		aux2 = aux2->AristaAd;
		  }
		  cout<< "-> "<<endl;
      	
	  }
	  else{
	  	cout<<"->";
	  }
      aux = aux->VerticeAd;
   }
   cout << endl;
}

void grafo::Reiniciar(){
	Vertice* aux = primero;
	while(aux){
		aux->Visitado = false;
		aux->procesado = false;
		aux = aux->VerticeAd;
		
	}
}
	
	Vertice* grafo::EncontrarVertice(int cod){
	Vertice* aux = primero;
	while(aux){
		if(aux->CodPais == cod){
			break;
		}
		else{
			aux = aux->VerticeAd;
		}
	}
	return aux;
}

void grafo::MarcarVisitado(int cod, int destino){ 
//Marca como visitada la arista
	 Vertice* inicio = Conexiones.EncontrarVertice(cod);
	 Arista *final = inicio->AristasV;
	 while(final){
	 	if (final->Destino == destino){
	 		final->visitado = true;
	 		break;
		 }
		 else{
		 	final = final->AristaAd;
		 }
	 }
}

void grafo::MarcarCiclo(int cod, int destino){ 
//Marca como visitada la arista
	 Vertice* inicio = EncontrarVertice(cod);
	 Arista *final = inicio->AristasV;
	 while(final){
	 	if (final->Destino == destino){
	 		cout<<final->Destino <<final->ciclo<<endl;
	 		final->ciclo = true;
	 		
	 		break;
		 }
		 else{
		 	final = final->AristaAd;
		 }
	 }
}

Vertice* grafo::Visitados(){
	Vertice* aux = primero;
	while(aux){
		if((aux->procesado == false)|| (aux->Visitado == false)){
			break;
		}
		else{
			aux = aux->VerticeAd;
		}
	}
	return aux;
}
// POSIBLES PAISES
/*
Pide al usuario el codigo del pais por donde se iniciara el recorrido
Devuelve un string con el orden de los paises visitados segun fueron insertados en cola
*/

// ANCHURA------------------------------------------------------------------------------------------------------------------

string grafo::Anchura(int cod){
	cola Cola;
	Vertice * aux = primero;
	string recorrido="";
		
	//Recorrido para el elemento inicial
	Vertice* verticeEncontrado = Conexiones.EncontrarVertice(cod);
	if(verticeEncontrado->AristasV ==NULL){
		recorrido = recorrido+	verticeEncontrado->Nombre+"|";
		verticeEncontrado->Visitado = true;
		verticeEncontrado->procesado = true;
		bool Gcola = false;
		while(Gcola==false){
			Vertice* nuevo = Conexiones.Visitados();
			if (nuevo->AristasV!= NULL){
				Vertice* &Nuevo = nuevo;
				Cola.insertar(Nuevo);
				nuevo->Visitado = true;
				Gcola= true;
			}
			else{
				recorrido = recorrido+	nuevo->Nombre+"|";
				nuevo->Visitado = true;
				nuevo->procesado = true;
			}
		}
	}
	else{
		recorrido = recorrido+	verticeEncontrado->Nombre+"|";
		verticeEncontrado->Visitado = true;
		verticeEncontrado->procesado = true;
		Arista* aristas = verticeEncontrado->AristasV;
		while(aristas){
			
			Vertice* Analizado = Conexiones.EncontrarVertice(aristas->Destino);
			Vertice* &VerticeAnalizado = Analizado;
			if(Analizado->Visitado ==false){ //Reviso que el vertice no haya sido visitado
				Cola.insertar(VerticeAnalizado);
				
				Analizado->Visitado = true;
			}
			aristas = aristas->AristaAd;
		}
	}
	
	
	//Recorrido para los demas vertices
	while(Cola.ColaVacia()!= true){
		int i = 0;
		Vertice* Frente = Cola.Frente();//Primer elemento de la cola

		if (Frente->AristasV==NULL){
			Frente->procesado = true;
			recorrido = recorrido+	Frente->Nombre+"|";
			Cola.eliminar();
			Vertice* nuevo = Conexiones.Visitados();
			if (nuevo!= NULL){
				Vertice* &Nuevo = nuevo;
				Cola.insertar(Nuevo);
				nuevo->Visitado = true;
			}
		}
		else{
			Arista *conexion = Frente->AristasV;
			while(conexion){
				Vertice* VerticeComprobar = Conexiones.EncontrarVertice(conexion->Destino);
				if (VerticeComprobar->Visitado == false){ //El vertice no ha sido revisado
					Cola.insertar(VerticeComprobar);
					VerticeComprobar->Visitado = true;
				}
				conexion = conexion->AristaAd;
			}
			Frente->procesado = true;
			recorrido = recorrido+	Frente->Nombre+"|";
			Cola.eliminar();
			if(Cola.ColaVacia()==true){
				Vertice* NoConexo = Conexiones.Visitados();
				if (NoConexo){
					Cola.insertar(NoConexo);
					NoConexo->Visitado = true;	
				}
				
			}
		}
		
		
		
	}
		
	cout<<recorrido<<endl;
	Reiniciar();
	return recorrido;
}
//Profundidad----------------------------------------------------------------------------------------------------------------------
string grafo::Profundidad(int cod){
	pila Pila;
	Vertice * aux = primero;
	string recorrido="";
	//Recorrido para el elemento inicial
	Vertice* verticeEncontrado = Conexiones.EncontrarVertice(cod);
	if(verticeEncontrado->AristasV ==NULL){
		recorrido = recorrido+	verticeEncontrado->Nombre+"|";
		verticeEncontrado->Visitado = true;
		verticeEncontrado->procesado = true;
		bool Gcola = false;
		while(Gcola==false){
			Vertice* nuevo = Conexiones.Visitados();
			if (nuevo->AristasV!= NULL){
				Vertice* &Nuevo = nuevo;
				Pila.push(Nuevo);
				nuevo->Visitado = true;
				Gcola= true;
			}
			else{
				recorrido = recorrido+	nuevo->Nombre+"|";
				nuevo->Visitado = true;
				nuevo->procesado = true;
			}
		}
	}
	else{
		recorrido = recorrido+	verticeEncontrado->Nombre+"|";
		verticeEncontrado->Visitado = true;
		verticeEncontrado->procesado = true;
		Arista* aristas = verticeEncontrado->AristasV;
		while(aristas){
			
			Vertice* Analizado = Conexiones.EncontrarVertice(aristas->Destino);
			Vertice* &VerticeAnalizado = Analizado;
			if(Analizado->Visitado ==false){ //Reviso que el vertice no haya sido visitado
				Pila.push(VerticeAnalizado);
				//cout<<Pila.tope()->Nombre<<" h"<<endl;
				Analizado->Visitado = true;
			}
			aristas = aristas->AristaAd;
		}
	}
	
	//Recorrido para los demas vertices
	while(Pila.pilaVacia()!= true){
		int i = 0;
		Vertice* tope = Pila.tope();//Primer elemento de la cola
		
		if (tope->AristasV==NULL){
			tope->procesado = true;
			recorrido = recorrido+	tope->Nombre+"|";
			Pila.pop();
			Vertice* nuevo = Conexiones.Visitados();
			if (nuevo!= NULL){
				Vertice* &Nuevo = nuevo;
				Pila.push(Nuevo);
				nuevo->Visitado = true;
			}
		}
		else{
			Arista *conexion = tope->AristasV;
			tope->procesado = true;
			recorrido = recorrido+	tope->Nombre+"|";
			Pila.pop();
			while(conexion){
				Vertice* VerticeComprobar = Conexiones.EncontrarVertice(conexion->Destino);
				if (VerticeComprobar->Visitado == false){ //El vertice no ha sido revisado
					Pila.push(VerticeComprobar);
					VerticeComprobar->Visitado = true;
				}
				conexion = conexion->AristaAd;
			}
			
			if(Pila.pilaVacia()==true){
				Vertice* NoConexo = Conexiones.Visitados();
				if (NoConexo){
					Pila.push(NoConexo);
					NoConexo->Visitado = true;	
				}
				
			}
		}
		
		
		
	}
	
	cout<<recorrido<<endl;
	Reiniciar();
	return recorrido;
}
//PRIM-------------------------------------------------------------------------------------------------------------------
/*
bool grafo::AnalizarCicloV2(Arista* inicio, int conectado, lista W){

		Analizar Ciclos de TODAS las aristas relacionadas
	
	Vertice* verticeI = EncontrarVertice(inicio->Destino);//B
	Arista* conexionAd = verticeI->AristasV;
	bool ciclo = false;
	while(conexionAd){
		if(conexionAd->Destino != conectado){
			if(conexionAd->ciclo == false){
				
			}
			
		}
	}
}
*/
bool grafo::AnalizarCiclo(Arista* inicio, int conectado, lista2 W){
	/*
	Analiza lps valores de las aristas considerando los hilos
	
	*/
	//cout<<"Analizar Ciclo "<<inicio->Destino<<" "<<conectado<<endl;
	Vertice* verticeI = EncontrarVertice(inicio->Destino);//B
	Arista* conexionAd = verticeI->AristasV;
	bool ciclo = false;
	while(conexionAd){
		
		if(conexionAd->Destino!=conectado){
			
			if(conexionAd->ciclo == false){
				Vertice* Comprobador = EncontrarVertice(conexionAd->Destino);//C
				if(W.BuscarE(conexionAd->Destino)){
				//verifico el ciclo
					if(conexionAd->Distancia < inicio->Distancia){
						ciclo=true;
						
						inicio->ciclo = true;
						
						cout<<"ciclo 1 "<<inicio->Destino<<conectado<<endl;
						break;
						Conexiones.MarcarCiclo(inicio->Destino, conectado);
						Conexiones.MarcarCiclo(conectado,inicio->Destino);
					}
					
					if(conexionAd->Distancia>inicio->Distancia){
						cout<<"ciclo 2 "<<inicio->Destino<<Comprobador->CodPais<<endl;
						conexionAd->ciclo = true;
						Conexiones.MarcarCiclo(inicio->Destino, Comprobador->CodPais);
						Conexiones.MarcarCiclo(Comprobador->CodPais, inicio->Destino);
					}
				
			}
			}
			
			
		}
		conexionAd= conexionAd->AristaAd;
	}
	return ciclo;
}

Arista* grafo::ConexionesV(Vertice* PaisInicio, lista2 W){
	/*Revisa las conexiones de la arista enviada como parametro
	Devuelve la de menor valor a la funcion Prim para compararla
	*/
	cout<<"Conexiones "<<PaisInicio->CodPais<<endl;
	Arista* aux = PaisInicio->AristasV;
	Arista* menor = new Arista(1,1);
	bool generaCiclo;
	while(aux){
		cout<<"Arista "<<aux->Destino<<endl;
		if(aux == PaisInicio->AristasV){
			generaCiclo = 	AnalizarCiclo(aux, PaisInicio->CodPais, W);
			if(generaCiclo==false){
				menor = aux;
			}
		}
		
		else{
			generaCiclo = 	AnalizarCiclo(aux, PaisInicio->CodPais, W);
			//cout<<"Vuelve a segundo "<<endl;
			if(generaCiclo==false){
				/* Mientras no genere ningun ciclo, se analiza el valor de la arista para saber si es menor que la anterior
				*/
				if(menor==NULL){
					
					menor = aux;
				}
				if(menor->Distancia > aux->Distancia){
					
					menor = aux;
				}
				if(menor->Distancia == aux->Distancia){
					if(W.BuscarE(aux->Distancia)==false){
						menor = aux;
					}
					
				}
				
			}
		}
		aux = aux->AristaAd;
	}

	return menor;
	
}

int grafo::Prim(int cod){
	int costo = 0;
	lista2 W; //Revisados
	int menor;
	int codigo;
	int primero;
	
	//Primer Elemento
	 
	Vertice* PrimerVertice = Conexiones.EncontrarVertice(cod);
	
	W.InsertarVertices(cod);
	PrimerVertice->Visitado = true;
	// Revisar el menor valor de sus aristas
	Arista* AristaPrimero =  PrimerVertice->AristasV;
	Arista* Menor = PrimerVertice->AristasV;
	Vertice* VerticeMenor = Conexiones.EncontrarVertice(Menor->Destino);
	while(AristaPrimero){
		
		if(AristaPrimero == PrimerVertice->AristasV){
			menor = AristaPrimero->Distancia;
		}
		if(AristaPrimero->Distancia< menor){
			menor = AristaPrimero->Distancia;
			Menor = AristaPrimero;
		}
		AristaPrimero = AristaPrimero->AristaAd;
	}
	//Saca el vertice menor y lo agrega a la lista, marcandolo como visitado
	W.InsertarVertices(Menor->Destino);
	
	MarcarVisitado(PrimerVertice->CodPais, Menor->Destino);
	MarcarVisitado(Menor->Destino,PrimerVertice->CodPais);
	VerticeMenor= EncontrarVertice(Menor->Destino);
	
	VerticeMenor->Visitado = true;
	costo = costo+menor;
	//cout<<"primer costo "<<costo<<endl;
	
	//Demas Elementos del Grafo
	/* Recorre la lista analizando las conexiones de cada una de las aristas
	El ciclo termina hasta que todos los vertices sean visitados
	
	*/
	while(W.largoLista() < Conexiones.largografo()){
		cout<<"lista W ";
		W.Mostrar();
		for(int i=0;i<W.largoLista();i++){
			codigo = W.Buscar(i)->valor;
			Vertice* VerticeComparar= Conexiones.EncontrarVertice(codigo);
			Menor = ConexionesV(VerticeComparar, W);
			//cout<<"vuelve a principal"<<endl;
			cout<<Menor->Distancia<<"Menor "<<Menor->Destino<<endl;
			primero = W.Buscar(0)->valor;
			if (Menor!=NULL){
			
				if(codigo == primero){
					menor = Menor->Distancia;
				}
				
				if(Menor->Distancia < menor){
					cout<<menor<<" "<<Menor->Distancia<<endl;
					menor = Menor->Distancia;
				}
			}	
		}
		/*Del ciclo resulta Menor -> el cual es la arista con el menor tiempo
		Se visita el vertice y se agrega a la lista
		Ademas se suma al costo total
		*/
		cout<<Menor->Destino<<" cod Destino Menor"<<endl;
		VerticeMenor = EncontrarVertice(Menor->Destino);
		
		if(W.BuscarE(Menor->Destino) == false)
			W.InsertarVertices(Menor->Destino);
			
		VerticeMenor->Visitado = true;
		menor = Menor->Distancia;
		cout<<"menor "<<menor<<endl;
		costo = costo+menor;
		cout<<"costo "<<costo<<endl;
	}
	return costo;
	
}
/* 
int grafo::Kurskal(int cod){
	
	lista Vertices;
	Conexiones.RecorrerGrafo();
	int costo;
	lista W; //Revisados
	int menor;
	int codigo;
	int primero;
	//Primer Elemento
	 
	Vertice* PrimerVertice = Conexiones.EncontrarVertice(cod);
	
	W.InsertarVertices(cod);
	PrimerVertice->Visitado = true;
	// Revisar el menor valor de sus aristas
	Arista* AristaPrimero =  PrimerVertice->AristasV;
	Arista* Menor = PrimerVertice->AristasV;
	Vertice* VerticeMenor = Conexiones.EncontrarVertice(Menor->Destino);
	while(AristaPrimero){
		
		if(AristaPrimero == PrimerVertice->AristasV){
			menor = AristaPrimero->Distancia;
		}
		if(AristaPrimero->Distancia< menor){
			menor = AristaPrimero->Distancia;
			Menor = AristaPrimero;
		}
		AristaPrimero = AristaPrimero->AristaAd;
	}
	//Saca el vertice menor y lo agrega a la lista, marcandolo como visitado
	W.InsertarVertices(Menor->Destino);
	
	MarcarVisitado(PrimerVertice->CodPais, Menor->Destino);
	MarcarVisitado(Menor->Destino,PrimerVertice->CodPais);
	VerticeMenor= EncontrarVertice(Menor->Destino);
	
	VerticeMenor->Visitado = true;
	costo = costo+menor;
	//cout<<"primer costo "<<costo<<endl;
	
	//Demas Elementos del Grafo
	/* Recorre la lista analizando las conexiones de cada una de las aristas
	El ciclo termina hasta que todos los vertices sean visitados
	
	
	while(W.largoLista() < Conexiones.largografo()){
		cout<<"lista W ";
		W.Mostrar();
		for(int i=0;i<W.largoLista();i++){
			codigo = W.Buscar(i)->valor;
			Vertice* VerticeComparar= Conexiones.EncontrarVertice(codigo);
			Menor = ConexionesV(VerticeComparar, W);
			//cout<<"vuelve a principal"<<endl;
			cout<<Menor->Distancia<<"Menor "<<Menor->Destino<<endl;
			primero = W.Buscar(0)->valor;
			if (Menor!=NULL){
			
				if(codigo == primero){
					menor = Menor->Distancia;
				}
				
				if(Menor->Distancia < menor){
					cout<<menor<<" "<<Menor->Distancia<<endl;
					menor = Menor->Distancia;
				}
			}	
		}
		/*Del ciclo resulta Menor -> el cual es la arista con el menor tiempo
		Se visita el vertice y se agrega a la lista
		Ademas se suma al costo total
		
		cout<<Menor->Destino<<" cod Destino Menor"<<endl;
		VerticeMenor = EncontrarVertice(Menor->Destino);
		
		if(W.BuscarE(Menor->Destino) == false)
			W.InsertarVertices(Menor->Destino);
			
		VerticeMenor->Visitado = true;
		menor = Menor->Distancia;
		cout<<"menor "<<menor<<endl;
		costo = costo+menor;
		cout<<"costo "<<costo<<endl;
	}
	return costo;
		
	
}*/


