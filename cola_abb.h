#ifndef COLA_ABB_H
#define COLA_ABB_H

#define TIPO_DATO string
#include "nodo.h"

using namespace std;

class NodoCola{
    public:
    NodoCola *sig;

    TIPO_DATO nombre;
    TIPO_DATO ciudad;
    int edad;
    int id;


};

class Cola{ ///Cola dinamica como auxiliar
public:
    Nodo *frente;
    Nodo *ultimo;
    int cantidad;

    void inicializa();
    void encolar(Nodo *);
    void desencolar();
    bool vacia();
};

//Operaciones con la Cola
void Cola::inicializa(){
    frente = nullptr;
    ultimo = nullptr;
    cantidad=0;
}

bool Cola::vacia(){
    return !frente;
}

void Cola::encolar(Nodo *nuevo){
    /// Se copia la informacion del nodo del arbol para el nodo de la cola
    //Nodo *nuevo = obtenerInfo(nodo);
    Nodo *aux;

    if(vacia()){
        frente = nuevo;
        ultimo = nuevo;
    }else{
        aux = nuevo;
        ultimo->sig = aux;
        ultimo = aux;
    }

    cantidad++;
}

void Cola::desencolar(){
    Nodo *aux;
    if(!vacia()){
        aux = frente;
        frente = aux->sig;
        aux = nullptr;
        delete aux;
    }

    cantidad--;
}

#endif // COLA_ABB_H
