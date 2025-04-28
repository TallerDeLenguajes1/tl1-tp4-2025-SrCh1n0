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
Nodo *AgregarTarea(int id, char *buff, int duracion);
void InsertarTarea(Nodo **Lista , Nodo *Tarea);
void MostrarLista(Nodo *Lista);
Nodo * BuscarTarea(Nodo **Tarea, int Id);
Nodo * QuitarTarea(Nodo **Tarea, int Id);
void LiberarMemoria(Nodo **lista);

int main(){
    Nodo * TareasPendientes = CrearListaVacia();
    int crearTarea = 0, tiempo, aux, id;
    char *buff;
    while (crearTarea >= 0)
    {
      buff = (char *) malloc(300*sizeof(char));
      printf("\nIngrese una descripcion de la tarea: ");
      fflush(stdin);
      gets(buff);
      printf("\nIngrese la duracion (Entre 10 y 100): ");
      scanf("%d", &tiempo);
      InsertarTarea(&TareasPendientes, AgregarTarea((1000 + crearTarea), buff, tiempo));
      free(buff);
      printf("\nDesea agregar una nueva tarea?\n(1 = agregar, 0 = terminar la carga): ");
      scanf("%d", &aux);
      if (aux == 0)
      {
          crearTarea = -1;
      } else {
          crearTarea++;
      }
    }
    printf("\n\nLista de Pendientes: ");
    MostrarLista(TareasPendientes);
    Nodo * TareasRealizadas = CrearListaVacia();
    int moverTarea;
    do
    {
      fflush(stdin);
      printf("\nIngrese el id de la tarea realizada: ");
      scanf("%d", &id);
      Nodo * realizada = QuitarTarea(&TareasPendientes, id);
      InsertarTarea(&TareasRealizadas, realizada);
      
      printf("\nDesea agregar otra tarea a la lista de realizadas?\n(1 = agregar, 0 = terminar)");
      scanf("%d", &moverTarea);
    } while (moverTarea != 0);

    printf("\n\nLista de Pendientes: ");
    MostrarLista(TareasPendientes);
    printf("\n\nLista de Realizadas: ");
    MostrarLista(TareasRealizadas);

    LiberarMemoria(&TareasPendientes);
    LiberarMemoria(&TareasRealizadas);
    printf("\nTodo listo.");
    return 0;
}

Nodo *CrearListaVacia(){

    return NULL;

}

Nodo *AgregarTarea(int id, char *buff, int duracion){

    Nodo * nodo = (Nodo *) malloc(sizeof(Nodo));
    nodo->T.TareaID = id;
    int tamCadena = strlen(buff);
    nodo->T.Descripcion = (char *)malloc((tamCadena + 1) * sizeof(char));
    strcpy(nodo->T.Descripcion, buff);
    nodo->T.Duracion = duracion;
    nodo->siguiente = NULL;
    return nodo;
}

void InsertarTarea(Nodo **Lista, Nodo *Tarea)
{
    Tarea->siguiente = *Lista;
    *Lista = Tarea ;
}

void MostrarLista(Nodo *Lista){
  Nodo * Aux = Lista;
  while (Aux)
  {
    printf("\n-----TAREA-----");
    printf("\nId: %d", Aux->T.TareaID);
    printf("\nDescripcion: ");
    puts(Aux->T.Descripcion);
    printf("Duracion: %d\n", Aux->T.Duracion);
    Aux = Aux->siguiente;
  }
}

Nodo * BuscarTarea(Nodo ** Tarea,int Id){
    Nodo * Aux = *Tarea;
  while (Aux && Aux->T.TareaID != Id)
  {
    Aux = Aux->siguiente;
  }
  return Aux;
}

Nodo * QuitarTarea(Nodo **Tarea, int Id)
{
    Nodo *nodoAux = (*Tarea);
    Nodo *nodoAnt = NULL;
    while (nodoAux != NULL && nodoAux->T.TareaID != Id)
    {
        nodoAnt = nodoAux;
        nodoAux = nodoAux->siguiente;
    }
    if (nodoAux != NULL)
    {
        if (nodoAux == (*Tarea))
        {
            (*Tarea) = nodoAux->siguiente;
        }
        else
        {
            nodoAnt->siguiente = nodoAux->siguiente;
        }
        nodoAux->siguiente = NULL;
    }
    return (nodoAux);
}

void LiberarMemoria(Nodo **Lista){
Nodo ** Aux = Lista;
  while (*Aux) {
    Nodo * temp = *Aux;
    *Aux = (*Aux)->siguiente;
    free(temp);
  }
}