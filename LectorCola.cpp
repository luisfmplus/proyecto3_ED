
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class NodoAnalisis {
   public:
    NodoAnalisis(char *v)
    {
      int i = 0;
      for (i = 0; i < sizeof(valor); i++){
        valor[i] = v[i];
      }
       siguiente = NULL;
    }

NodoAnalisis(char *v, NodoAnalisis * signodo)
    {
    
      int i = 0;
      for (i = 0; i < sizeof(valor); i++){
        valor[i] = v[i];
      }
      siguiente = signodo;
    }

   private:
    char valor [100] = "\000";
    int particion = 0;
    NodoAnalisis *siguiente = NULL;
        
   friend class LectorCola;
};

typedef NodoAnalisis *pnodoanalisis;

class LectorCola {
   public:
    LectorCola(int numero);
    ~LectorCola();
    
    int getParticion();
    void cambiarParticion(bool c);
    int calcularParticion(char* f); //rango:: 1->infinito
    void getValor(int numero, int &destino); //regresara int
    double getValor(double numero); //regresara doubles
    void getValor(char numero, char* buffer); // regresara los char*
    void leerArchivo(char* v);
    int transformarint(char* fp);
    double transformardouble(char* fp);
    void InsertarFinal(char* f);
    void BorrarInicio();
    bool ListaVacia() { return primero == NULL; } 
    int largoLista();
    
   private:
    pnodoanalisis primero;
    ifstream file;
  
};

LectorCola :: LectorCola(int numero){

  primero =  NULL;
  char textoPais[] = "Datos\\Paises.txt";
  char textoHoteles[] = "Datos\\Hoteles.txt";
  char textoPisos[] = "Datos\\PisosHotel.txt";
  char textoHabitas[] = "Datos\\Habitaciones.txt";
  char textoAgencias[] = "Datos\\Agencias.txt";
  char textoFlotillas[] = "Datos\\TipoFlotilla.txt";
  char textoCarros[] = "Datos\\Carros.txt";
  char textoUsuario[] = "Datos\\Usuarios.txt";
  char textoAdminH[] = "Datos\\AdministradorH.txt";
  char textoAdminA[] = "Datos\\AdministradorA.txt";

  switch (numero){

  case 0:
    leerArchivo(textoPais);
    break;

  case 1:
    leerArchivo(textoHoteles);
    break;
  case 2:
    leerArchivo(textoPisos);
    break;
  case 3:
    leerArchivo(textoHabitas);
    break;
  case 4:
    leerArchivo(textoAgencias);
    break;
  case 5:
    leerArchivo(textoFlotillas);
    break;
  case 6:
    leerArchivo(textoCarros);
    break;
  case 7:
    leerArchivo(textoUsuario);
    break;
  case 8:
    leerArchivo(textoAdminH);
    break;
  case 9:
    leerArchivo(textoAdminA);
    break;

  default:
    leerArchivo(textoHoteles); // requiere que lo leido termine en '\000'
    break;
  }

}

LectorCola::~LectorCola()
{
   pnodoanalisis aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   
}

int LectorCola::largoLista(){
    int cont=0;

    pnodoanalisis aux;
    aux = primero;
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

int LectorCola :: calcularParticion(char* f){ //rango:: 1->infinito, requiere que lo leido termine en '\000'
  int j = 0;

  for (int i = 0; f[i] != '\000'; i++){
    if (f[i] == ';'){
      j++;
    }
  }
  return j + 1;
}

void LectorCola :: InsertarFinal(char* f){ // requiere que lo leido termine en '\000'

  if (ListaVacia()){
   primero = new NodoAnalisis(f);
   //primero->siguiente=NULL; en la misma declaracion
   primero->particion = calcularParticion(f);

  } else{ 
    pnodoanalisis aux = primero;

    while ( aux->siguiente != NULL){
      aux= aux->siguiente;
    }
      aux->siguiente = new NodoAnalisis(f);   
      aux->siguiente->particion = calcularParticion(f);
  }
}
 
void LectorCola::BorrarInicio(){
  if (ListaVacia()){
    cout << "No hay elementos en la lista:" << endl;
    
  }else if (primero->siguiente == NULL) { //nodo unico
      pnodoanalisis temp=primero;
      primero= NULL;
      delete temp;

  } else {
    pnodoanalisis aux = primero;
    primero=primero->siguiente;     
		aux->siguiente=NULL;           
    delete aux;

  }
}

int LectorCola :: getParticion(){

  pnodoanalisis aux = primero;
  return aux->particion;

}

void LectorCola :: cambiarParticion(bool c){

  pnodoanalisis aux = primero;
  if (c){
    aux->particion = aux->particion + 1;
    return;
  }
  aux->particion = aux->particion + 1;
  return;
}

void LectorCola :: leerArchivo(char* v){ // contiene buffer de 100, requiere que lo que se leera termine en '\000'

  char temp [100]= "\000";//buffer
  pnodoanalisis aux;


  file.open (v);
  if (file.fail() || file.eof()){
    cout << "archivo no existe o esta vacio"<< endl;
    return;
  }
  file.getline(temp,sizeof(temp));

  if (temp[0] != '\000'){
    InsertarFinal(temp);

  }
  
    while(!file.eof()) {
      file.getline(temp,sizeof(temp));
      if (temp[0] != '\000'){
        InsertarFinal(temp);

      }
    }
	  file.close();
}

int LectorCola ::  transformarint(char* fp){ //requiere que fp contenga solo numeros

  int j = 0;
  int i;

  for ( i = 0; fp[i]!='\000'; i++){
    
    j = (10*j)+(fp[i]-48);
  }
  return j;
}

double LectorCola ::  transformardouble(char* fp){ //requiere que fp contenga solo numeros (pendiente)

  double j = 0;
  int k = 1;
  int i;

  for ( i = 0; i < sizeof(fp); i++){
    
    j = (k*j)+(fp[i]-48);
    k*=10;
  }
  return j;
}

void LectorCola :: getValor(int numero, int &destino){ //contine buffer de 12

  /*numero = numero de la particion que se quiere
  destino = variable donde se guardara el numero*/

  int i = 0;
  int j = 1; //movimiento partición
  int k = 0; 
  char buffer[12] = "\000";
  char test;

  if (numero == 0){
    numero = 1 ;

  } else if((numero <= -1) || (numero > getParticion())){ 
    destino = -1;
    return;

  } else { 

    while (j <= numero){ // movimiento en las particiones
      test = 192; // reinicio de test

      for(i=0; ((test != ';') && (test != '\000')) ;k++){ // lector

        test = primero->valor[k];
        if(test == ';' || test == '\n' || test == ' '){ //ignoramos estos simbolos en el buffer
          continue;

        }
        buffer[i] = primero->valor[k];
        i = (i+1)%12;
      }
      buffer[i] = '\000'; //define el limite de lo leido
      j++; //aumentamos la particion
    }
  } 

  for ( i = 0; buffer[i] != '\000'; i++){ // es toda la expresion un numero entero?

    if(buffer[i]>=48 && buffer[i] <= 57){
      continue;

    }
    destino = -1;
    return; //no

  }
  destino = transformarint(buffer);
  return; //si

}

double LectorCola :: getValor(double numero){ //(pendiente)

int i = 0;
int j = 0; //movimiento partición
int k = 0; 
char buffer[12];
char test;

if (numero == 0){
  numero = 1 ;

} else if((numero <= -1) || (numero > getParticion())){ 
  return -1;

} else { 

  while (j <= numero){ 

    for(i=0; test != ';' ;k++){ 
    
      test = primero->valor[k];
      if(test == ';' || test == '\n' || test == ' '){
        continue;

      }
      buffer[i] = primero->valor[k];
      i = (i+1)%12;
    }
    buffer[i] = '\000';
    j++;
  }
}

if(buffer[0]>=48 && buffer[0] <= 57){
  return transformardouble(buffer); 

}
return -1; 
}

void LectorCola :: getValor(char numero, char* buffer){

int i = 0;
int j = 1; //movimiento partición
int k = 0; 
char test;

if (numero == 0){
  numero = 1 ;

} else if((numero <= -1) || (numero > getParticion())){ 

  buffer[0] = '\000';
} else { 

  while (j <= numero){ 
    test = 192;

    for(i=0; ((test != ';') && (test != '\000')) ;k++){ 
    
      test = primero->valor[k];
      if(test == ';' || test == '\n'){
        continue;

      }
      buffer[i] = primero->valor[k];
      i++;
    }
    buffer[i] = '\000';
    j++;
  }
} 

for ( i = 0; buffer[i] != '\000'; i++){ // es toda la expresion un numero entero?

  if(buffer[i]>=48 && buffer[i] <= 57){
    continue;

  }
  return; //no

}

buffer[0] = '\000';
return; //si
}
