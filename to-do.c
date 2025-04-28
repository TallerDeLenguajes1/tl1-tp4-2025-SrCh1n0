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
Nodo * BuscarNodo(Nodo **Start, int dato);
Nodo * QuitarNodo(Nodo ** Start,int dato);
void LiberarMemoria(Nodo **Start);

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
      InsertarNodo(&TareasPendientes, AgregarTarea((1000 + crearTarea), buff, tiempo));
      free(buff);
      printf("\nDesea agregar una nueva tarea?(1 = agregar, 0 = terminar la carga): ");
      scanf("%d", &aux);
      if (aux == 0)
      {
          crearTarea = -1;
      } else {
          crearTarea++;
      }
    }
    
    Nodo * TareasRealizadas = CrearListaVacia();
    int moverTarea;
    do
    {
      Nodo * TareasRealizadas = CrearListaVacia();
      printf("\nIngrese el id de la tarea realizada: ");
      scanf("%d", &id);
      Nodo * realizada = BuscarNodo(&TareasPendientes, id);
      InsertarNodo(&TareasRealizadas, realizada);
      QuitarNodo(&TareasPendientes, id);
      printf("\nDesea agregar otra tarea a la lista de realizadas?(1 = agregar, 0 = terminar)");
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

void MostrarLista(Nodo *Tareas){
    Nodo * Aux = Tareas;
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

Nodo * BuscarNodo(Nodo ** Start,int dato){
    Nodo * Aux = *Start;
  while (Aux && Aux->T.TareaID != dato)
  {
    Aux = Aux->siguiente;
  }
  return Aux;
}

Nodo * QuitarNodo(Nodo ** Tarea, int dato) {
  Nodo ** aux = Tarea;  // Usamos un puntero doble para apuntar al puntero actual.
  
  // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.
  while (*aux != NULL && (*aux)->T.TareaID != dato) {
      aux = &(*aux)->siguiente;
  }

  // Si encontramos el nodo con el dato especificado, lo quitamos de la lista y retornamos al programa para su posterior eliminación.
  if (*aux) {
      Nodo *temp = *aux;  // Guardamos el nodo a eliminar en una variable temporal.
      *aux = (*aux)->siguiente;  // Desvinculamos el nodo de la lista.
      temp->siguiente =NULL; // Ponemos en NULL el puntero siguiente para asegura no llevar vinculos por fuera de la lista
      return temp;
  }
  return NULL;
}

void LiberarMemoria(Nodo **Start){
Nodo ** Aux = Start;
  while (*Aux) {
    Nodo * temp = *Aux;
    *Aux = (*Aux)->siguiente;
    free(temp);
  }
}