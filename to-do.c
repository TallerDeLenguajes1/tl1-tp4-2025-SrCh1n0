#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo * siguiente;
}typedef Nodo;

Nodo *CrearListaVacia();
Nodo *AgregarTarea(int tarea, char *buff, int duracion);
void InsertarNodo(Nodo **Start , Nodo *Nodo);
void MostrarLista(Nodo *Start);
void LiberarMemoria(Nodo **Start);

int main(){

    Nodo * TareasPendientes = CrearListaVacia();
    int crearTarea = 0, tiempo, aux;
    char *buff;
    while (crearTarea >= 0)
    {
        buff = (char *) malloc(300*sizeof(char));
        printf("Ingrese una descripcion de la tarea: ");
        fflush(stdin);
        gets(buff);
        printf("Ingrese la duracion (Entre 10 y 100): ");
        scanf("%d", &tiempo);
        InsertarNodo(&TareasPendientes, AgregarTarea((1000 + crearTarea), buff, tiempo));
        free(buff);
        printf("Desea agregar una nueva tarea?(1 = agregar, 0 = terminar la carga): ");
        scanf("%d", &aux);
        if (aux == 0)
        {
            crearTarea = -1;
        } else {
            crearTarea++;
        }
    }
    MostrarLista(TareasPendientes);
    LiberarMemoria(&TareasPendientes);
    printf("\nTodo listo.");
    return 0;
}

Nodo *CrearListaVacia(){

    return NULL;

}

Nodo *AgregarTarea(int tarea, char *buff, int duracion){

    Nodo * nodo = (Nodo *) malloc(sizeof(Nodo));
    nodo->T.TareaID = tarea;
    int tamCadena = strlen(buff);
    nodo->T.Descripcion = (char *)malloc((tamCadena + 1) * sizeof(char));
    strcpy(nodo->T.Descripcion, buff);
    nodo->T.Duracion = duracion;
    nodo->siguiente = NULL;
    return nodo;
}

void InsertarNodo(Nodo **Start, Nodo *Nodo)
{
    Nodo->siguiente = *Start;
    *Start = Nodo ;
}

void MostrarLista(Nodo *Start){
    Nodo * Aux = Start;
  while (Aux)
  {
    printf("\n-----TAREA-----");
    printf("\nId: %d", Aux->T.TareaID);
    printf("\nDescripcion: ");
    puts(Aux->T.Descripcion);
    printf("\nDuracion: %d", Aux->T.Duracion);
    Aux = Aux->siguiente;
  }
}

void LiberarMemoria(Nodo **Start){
Nodo ** Aux = Start;
  while (*Aux) {
    Nodo * temp = *Aux;
    *Aux = (*Aux)->siguiente;
    free(temp);
  }
}