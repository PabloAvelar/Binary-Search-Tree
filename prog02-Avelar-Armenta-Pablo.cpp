#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"

using namespace std;

typedef enum{
    SALIR,
    INSERTAR,
    PREORDER, INORDER, POSTORDER, AMPLITUD,
    BUSCAR, GUARDAR, CARGAR,
    ELIMINAR, ANULAR
}MENU;

int main(){
    int op, edad, id;
    string nombre, ciudad;

    Arbol arbol;
    arbol.inicializa();

    do{
        system("cls");

        cout<<"Contador: "<<arbol.cantidad<<endl;
        printf("\tLista simplemente ligada\n\n");

        cout<<"1) Insertar"<<endl;
        cout<<"2) Imprimir en Preorden"<<endl;
        cout<<"3) Imprimir en Inorden"<<endl;
        cout<<"4) Imprimir en Postorden"<<endl;
        cout<<"5) Imprimir en Amplitud"<<endl;
        cout<<"6) Buscar"<<endl;
        cout<<"7) Guardar"<<endl;
        cout<<"8) Cargar"<<endl;
        cout<<"9) Eliminar"<<endl;
        cout<<"10) Anular"<<endl;
        cout<<"0) Salir"<<endl;

        cin>>op;
        fflush(stdin);

        switch(op){
            case INSERTAR:
                cout<<"Nombre: ";
                getline(cin, nombre);
                cout<<"Edad: ";
                cin>>edad;
                cin.ignore(256, '\n');
                cout<<"Ciudad: ";
                getline(cin, ciudad);
                cout<<"ID: ";
                cin>>id;

                arbol.insertar(nombre, ciudad, edad, id);
                break;

            case PREORDER:
                try{
                    system("cls");
                }catch(...){
                    system("clear");
                }
                if(arbol.vacio()){
                    cout<<"No hay datos..."<<endl;
                }else{
                    arbol.preorden();
                }
                system("pause");
            break;

            case INORDER:
                try{
                    system("cls");
                }catch(...){
                    system("clear");
                }
                if(arbol.vacio()){
                    cout<<"No hay datos..."<<endl;
                }else{
                    arbol.inorden();
                }
                system("pause");
            break;

            case POSTORDER:
                try{
                    system("cls");
                }catch(...){
                    system("clear");
                }
                if(arbol.vacio()){
                    cout<<"No hay datos..."<<endl;
                }else{
                    arbol.postorden();
                }
                system("pause");
            break;

            case AMPLITUD:
                system("cls");
                arbol.amplitud();
                printf("\n");
                system("pause");

            break;

            case BUSCAR:
                system("cls");
                cout<<"ID: ";
                cin>>id;
                system("cls");
                arbol.buscar(id);
                system("pause");
            break;

            case GUARDAR:
                if(arbol.guardar()) cout<<"Se guardaron los datos correctamente."<<endl;
                else cout<<"Error: no se pudieron guardar los datos."<<endl;
                system("pause");
            break;

            case CARGAR:
                if(arbol.cargar()) cout<<"Se cargaron los datos correctamente."<<endl;
                else cout<<"Error: no se pudieron cargar los datos."<<endl;
                system("pause");
            break;

            case ELIMINAR:
                system("cls");
                if(arbol.vacio()){
                    cout<<"No hay datos..."<<endl;
                }else{
                    cout<<"ID del elemento a eliminar: ";
                    cin>>id;
                    arbol.eliminar(id);
                    system("pause");
                }
            break;

            case ANULAR:
                arbol.anular();
            break;

            fflush(stdin);
        }


    }while(op!=SALIR);

    return 0;
}
