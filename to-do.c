#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{

    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100

}typedef Tarea;

struct Nodo{

    Tarea T;
    Nodo *Siguiente;

}typedef Nodo;

Nodo *CrearListaVacia();

int main(){

    Nodo * Inicio = CrearListaVacia();
    return 0;
}

Nodo *CrearListaVacia(){

    return NULL;

}