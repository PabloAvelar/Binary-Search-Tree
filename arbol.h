#ifndef ARBOL_H
#define ARBOL_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#define TIPO_DATO string
#include "nodo.h"
#include "cola_abb.h"

using namespace std;

/// AQUI COMIENZA EL ARBOL YA BIEN

class Arbol{
    //private:
    public:
    Nodo *raiz;
    int aux;
    int cantidad;

    void inicializa();
    bool vacio();
    void insertar(TIPO_DATO, TIPO_DATO, int, int);
    void eliminar(int);
    void buscar(int); //Busca el ID del nodo
    void preorden();
    void inorden();
    void postorden();
    void amplitud();

    void anular();

    bool guardar();
    bool cargar();
};

//Operaciones con Arbol

void Arbol::inicializa(){
    raiz = nullptr;
}

bool Arbol::vacio(){
    return raiz==nullptr;
}


void Arbol::insertar(TIPO_DATO nombre, TIPO_DATO ciudad, int edad, int id){
    if(vacio()){
        raiz = new Nodo();
        raiz->setNombre(raiz, nombre);
        raiz->setCiudad(raiz, ciudad);
        raiz->setEdad(raiz, edad);
        raiz->setId(raiz, id);

        cantidad++;
    }else{
        raiz->insertar(raiz, nombre, ciudad, edad, id);
        cantidad++;
    }
}

void Arbol::eliminar(int dato){
    if(!vacio()){
        Nodo *arbol = raiz->buscar(raiz, dato);
        if(!arbol){
            cout<<"No se encontro el nodo"<<endl;
            return;
        }

        Nodo *aux = raiz->eliminar(arbol);
        system("pause");
        if(aux && !aux->padre){
            raiz = aux;
        }
        cantidad--;
    }else{
        cout<<"No hay elementos..."<<endl;
    }
}

void Arbol::anular(){
    system("cls");
    if(!vacio()){
        raiz->anular(raiz, 0);
        if(!raiz->padre){
            raiz = nullptr;
            delete raiz;
        }
        cout<<"Arbol anulado!"<<endl;
        system("pause");
        cantidad=0;
    }else{
        cout<<"No hay elementos..."<<endl;
        system("pause");
    }


}

void Arbol::preorden(){
    printf("\n\nPreorden:\n");
    if(!vacio()){
        raiz->preorden(raiz, 0); //Comienza desde el cero. Es recursivo.
    }
}

void Arbol::inorden(){
    printf("\n\nInorden:\n");
    if(!vacio()){
        raiz->inorden(raiz, 0); //Comienza desde el cero. Es recursivo.
    }
}

void Arbol::postorden(){
    printf("\n\nPostorden:\n");
    if(!vacio()){
        raiz->postorden(raiz, 0);
    }
}

void Arbol::buscar(int id){
    if(!vacio()){
       Nodo *nodo = raiz->buscar(raiz, id);
       if(nodo){
        cout<<"ID: "<<nodo->getId(nodo)<<endl;
        cout<<"Nombre: "<<nodo->getNombre(nodo)<<endl;
        cout<<"Edad: "<<nodo->getEdad(nodo)<<endl;
        cout<<"Ciudad: "<<nodo->getCiudad(nodo)<<endl;
        return;
       }
    }

    cout<<"No se ha encontrado el ID."<<endl;
}

bool Arbol::guardar(){
    /// Se hace una cola para guardar cada nodo mediante un recorrido por amplitud
    int edad, id, i=0;
    string nombre, ciudad;
    Nodo *aux = raiz;
    Cola cola;
    cola.inicializa();
    // constructor
    ofstream archivo("file01.txt", ios::out);

    if(archivo.fail()) return false;

    cola.encolar(aux);
    while(cola.frente && i<cantidad){
        aux = cola.frente;
        //TIPO_DATO nombre, TIPO_DATO ciudad, int edad, int id
        archivo << aux->getNombre(aux) << '|' << aux->getCiudad(aux) << '|' << aux->getEdad(aux) << '|' << aux->getId(aux) << '|' << '*';
        cola.desencolar();
        i++;

        if(aux->izq) cola.encolar(aux->izq);
        if(aux->der) cola.encolar(aux->der);
    }

    archivo.close();

    return true;

}

bool Arbol::cargar(){
    ifstream archivo;
    string registro;
    int i;
    bool flag = false;

    archivo.open("file01.txt", ios::in);
    if(archivo.fail()) return flag;

    archivo.seekg(0, archivo.end);
    int length = archivo.tellg();   // Para el tamaño del buffer
    archivo.seekg(0, archivo.beg);

    /// Creacion del buffer
    char *buffer = new char[length];
    archivo.read(buffer, length);
    string campos[4];

    /// Se convierte el buffer en formato de flujo de cadena
    stringstream cadena(buffer);

    while(getline(cadena, registro, '*') && !cadena.eof()){
        try{
            stringstream cadena_reg(registro);
            i=0;
            while(getline(cadena_reg, campos[i], '|')) i++;

            insertar(campos[0], campos[1], stoi(campos[2]), stoi(campos[3]));
            flag = true;
        }catch(...){
            flag = false;
        }
    }

    return flag;
}

void Arbol::amplitud(){
    if(!vacio()){
        printf("\n\nAmplitud:\n");
        Nodo *aux = raiz;
        int i=0;
        Cola cola;

        cola.inicializa();
        if(aux){
            cola.encolar(aux);
            while(cola.frente && i<cantidad){
                aux = cola.frente;
                cout<<"["<<   aux->getId(aux)  <<"] -> ";
                cola.desencolar();
                i++;
                if(aux->izq) cola.encolar(aux->izq);
                if(aux->der) cola.encolar(aux->der);

            }
            // Limpiando en caso de haber algo en la cola.
            while(cola.frente) cola.desencolar();
        }
    }else cout<<"No hay datos..."<<endl;
}

#endif
