#ifndef NODO_H
#define NODO_H
#define TIPO_DATO string
#include <iostream>

using namespace std;

class Nodo{
private:
    TIPO_DATO nombre;
    TIPO_DATO ciudad;
    int edad;
    int id;

    public:
    Nodo *izq;
    Nodo *der;
    Nodo *padre;

    Nodo *sig; //Para cuando se use la cola nomas, igual es un nodo cualquiera esa madre
    int aux;

    void insertar(Nodo *, TIPO_DATO, TIPO_DATO ciudad, int, int);

    void preorden(Nodo *, int);
    void inorden(Nodo *, int);
    void postorden(Nodo *, int);
    void amplitud(Nodo *);

    Nodo *buscar(Nodo *, int);
    Nodo *eliminar(Nodo *);
    void anular(Nodo *, int);
    Nodo *minimo(Nodo *);
    Nodo *reemplazar(Nodo *, Nodo *);
    void destruirNodo(Nodo *);

    // Setters y Getters
    void setId(Nodo *, int);
    void setNombre(Nodo *, TIPO_DATO);
    void setCiudad(Nodo *, TIPO_DATO);
    void setEdad(Nodo *, int);

    int getId(Nodo *);
    TIPO_DATO getNombre(Nodo *);
    TIPO_DATO getCiudad(Nodo *);
    int getEdad(Nodo *);
};

// Setters y Getters de Nodo
void Nodo::setId(Nodo *nodo, int x){
    nodo->id = x;
}

void Nodo::setNombre(Nodo *nodo, TIPO_DATO x){
    nodo->nombre = x;
}

void Nodo::setCiudad(Nodo *nodo, TIPO_DATO x){
    nodo->ciudad = x;
}

void Nodo::setEdad(Nodo *nodo, int x){
    nodo->edad = x;
}

int Nodo::getId(Nodo *nodo){
    return nodo->id;
}

int Nodo::getEdad(Nodo *nodo){
    return nodo->edad;
}

TIPO_DATO Nodo::getNombre(Nodo *nodo){
    return nodo->nombre;
}

TIPO_DATO Nodo::getCiudad(Nodo *nodo){
    return nodo->ciudad;
}



//Operaciones con Nodo

Nodo *Nodo::buscar(Nodo *arbol, int dato){
    //Busqueda binaria no recursiva
    bool ENCONTRADO = false;
    while(!ENCONTRADO && arbol){
        if(dato < arbol->getId(arbol)){
            arbol = arbol->izq;
        }else if(dato > arbol->getId(arbol)){
            arbol = arbol->der;
        }else if (dato == arbol->getId(arbol)){
            ENCONTRADO = true;
            break;
        }
    }

    return arbol;
}

void Nodo::insertar(Nodo *arbol, TIPO_DATO nombre, TIPO_DATO ciudad, int edad, int id){
    if(id < arbol->getId(arbol)){
        if(arbol->izq != nullptr){
            insertar(arbol->izq, nombre, ciudad, edad, id);
        }else{
            Nodo *aux = new Nodo();
            aux->padre = arbol;

            aux->setId(aux, id);
            aux->setNombre(aux, nombre);
            aux->setCiudad(aux, ciudad);
            aux->setEdad(aux, edad);

            arbol->izq = aux;
        }
    }else{
        if(arbol->der != nullptr){
            insertar(arbol->der, nombre, ciudad, edad, id);
        }else{
            Nodo *aux = new Nodo();
            aux->padre = arbol;

            aux->setId(aux, id);
            aux->setNombre(aux, nombre);
            aux->setCiudad(aux, ciudad);
            aux->setEdad(aux, edad);

            arbol->der = aux;
        }
    }
}

Nodo *Nodo::minimo(Nodo *arbol){
    if(arbol == nullptr){
        return nullptr;
    }
    if(arbol->izq){
        return minimo(arbol->izq); //parte más izq posible
    }else{
        return arbol;
    }
}

Nodo *Nodo::reemplazar(Nodo *arbol, Nodo *nuevoNodo){
    if(arbol->padre){
            if(arbol->padre->der){
            if(arbol->id == arbol->padre->der->id)
                arbol->padre->der = nuevoNodo;
        }

        if(arbol->padre->izq){
                if(arbol->id == arbol->padre->izq->id){
                    arbol->padre->izq = nuevoNodo;
                }
        }

    }

    if(nuevoNodo){
        nuevoNodo->padre = arbol->padre;
    }

    return nuevoNodo;

}

void Nodo::destruirNodo(Nodo *nodo){
    nodo->izq = nullptr;
    nodo->der = nullptr;

    delete nodo;
}

Nodo *Nodo::eliminar(Nodo *elemento){
    Nodo *aux;

    if(elemento){
        if(elemento->izq && elemento->der){ //Si tiene dos hijos
            Nodo *menor = minimo(elemento->der);
            aux = menor;

            elemento->id = menor->id;
            elemento->nombre = menor->nombre;
            elemento->edad = menor->edad;
            elemento->ciudad = menor->ciudad;

            eliminar(menor);
        }else if(elemento->izq){ //si tiene solo un hijo izq
            aux = reemplazar(elemento, elemento->izq);
            destruirNodo(elemento);
        }else if(elemento->der){ //si solo tiene un hijo der
            aux = reemplazar(elemento, elemento->der);
            destruirNodo(elemento);
        }else{ //si no tiene hijos
            aux = reemplazar(elemento, nullptr);
            destruirNodo(elemento);
        }
    }

    return aux;
}

void Nodo::preorden(Nodo *arbol, int nivel){
    if(nivel!=0) cout<<"\xc3";
    for(int i=0; i<nivel; i++){
        cout<<"\xc4";
    }

    cout<<arbol->getId(arbol)<<endl;

    if(arbol->izq != nullptr) arbol->izq->preorden(arbol->izq, nivel+1);
    if(arbol->der != nullptr) arbol->der->preorden(arbol->der, nivel+1);


}

void Nodo::inorden(Nodo *arbol, int nivel){
    if(arbol->izq != nullptr) inorden(arbol->izq, nivel+1);
    if(nivel!=0) cout<<"\xc3";
    for(int i=0; i<nivel; i++){
        cout<<"\xc4";
    }

    if(arbol){
        cout<<arbol->getId(arbol)<<endl;

    }

    if(arbol->der != nullptr) inorden(arbol->der, nivel+1);

}

void Nodo::anular(Nodo *arbol, int nivel){
    //Anula con recorrido de postorden
    if(arbol->izq != nullptr) anular(arbol->izq, nivel+1);
    if(arbol->der != nullptr) anular(arbol->der, nivel+1);

    delete arbol;
    cout<<"Eliminando..."<<endl;
}

void Nodo::postorden(Nodo *arbol, int nivel){
    if(arbol->izq != nullptr) postorden(arbol->izq, nivel+1);
    if(arbol->der != nullptr) postorden(arbol->der, nivel+1);

    if(nivel!=0) cout<<"\xc3";
    for(int i=0; i<nivel; i++){
        cout<<"\xc4";
    }

    cout<<arbol->getId(arbol)<<endl;

}




#endif // NODO_H
