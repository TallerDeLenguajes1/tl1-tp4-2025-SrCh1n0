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
void MostrarTarea(Nodo *Tarea);
void MostrarLista(Nodo *Lista);
Nodo * BuscarTareaPorId(Nodo **Lista, int Id);
Nodo * BuscarTareaPorPalabra(Nodo **Lista, char *Palabra);
Nodo * QuitarTarea(Nodo **Lista, int Id);
void LiberarMemoria(Nodo **lista);

int main(){
    Nodo * TareasPendientes = CrearListaVacia();
    Nodo * TareasRealizadas = CrearListaVacia();
    int crearTarea = 0, tiempo, aux, id, decision;
    char *buff;
    
    do
    {
      fflush(stdin);
      printf("\n\nQue operacion desea realizar?");
      printf("\n[0]. Agregar una nueva tarea a Pendientes");
      printf("\n[1]. Transferir tareas de la lista Pendientes a Realizadas");
      printf("\n[2]. Mostrar las listas");
      printf("\n[3]. Consultar tarea por id");
      printf("\n[4]. Consultar tarea por palabra clave");
      printf("\n[5]. Cerrar programa.");
      printf("\nSeleccione una opcion: ");
      scanf("%d", &decision);
      switch (decision)
      {
      case 0:
          do
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
            if (aux != 0) crearTarea++;
          } while (aux != 0);
        break;

      case 1:
          do
          {
            fflush(stdin);
            printf("\nIngrese el id de la tarea realizada: ");
            scanf("%d", &id);
            Nodo * realizada = QuitarTarea(&TareasPendientes, id);
            InsertarTarea(&TareasRealizadas, realizada);
            
            printf("\nDesea agregar otra tarea a la lista de realizadas?\n(1 = agregar, 0 = terminar)");
            scanf("%d", &aux);
          } while (aux != 0);
        break;

      case 2:
          if (TareasPendientes != NULL || TareasRealizadas != NULL)
          {
            printf("\n\nLista de Pendientes: ");
            MostrarLista(TareasPendientes);
            printf("\n\nLista de Realizadas: ");
            MostrarLista(TareasRealizadas);
          } else
          {
            printf("\nSin tareas para mostrar");
          }   
        break;

      case 3:
          if (TareasPendientes != NULL || TareasRealizadas != NULL)
          {
              fflush(stdin);
              printf("\nIngrese el id para buscar la tarea: ");
              scanf("%d", &id);
              Nodo * TareaPorId = BuscarTareaPorId(&TareasPendientes, id);
              if (TareaPorId != NULL)
              {
                  printf("\nLa tarea esta pendiente:");
                  MostrarTarea(TareaPorId);
              } else {
                  TareaPorId = BuscarTareaPorId(&TareasRealizadas, id);
                  if (TareaPorId != NULL)
                  {
                    printf("\nLa tarea esta realizada:");
                    MostrarTarea(TareaPorId);
                  } else {
                  printf("\nNo se enontro la tarea.");
                }
              }
          } else
          {
            printf("\nSin tareas para mostrar");
          }   
        break;

      case 4:
          if (TareasPendientes != NULL || TareasRealizadas != NULL)
          {
            fflush(stdin);
            buff = (char *) malloc(300*sizeof(char));
            printf("\nIngrese una palabra clave para buscar la tarea: ");
            gets(buff);
            Nodo * TareaPorPalabra = BuscarTareaPorPalabra(&TareasPendientes, buff);
            if (TareaPorPalabra != NULL)
            {
                printf("\nLa tarea esta pendiente:");
                MostrarTarea(TareaPorPalabra);
            } else {
                TareaPorPalabra = BuscarTareaPorPalabra(&TareasRealizadas, buff);
                if (TareaPorPalabra != NULL)
                {
                  printf("\nLa tarea esta realizada:");
                  MostrarTarea(TareaPorPalabra);
                } else {
                printf("\nNo se enontro la tarea.");
              }
            }
            free(buff);
          } else
          {
            printf("\nSin tareas para mostrar");
          }  
        break;

      default:
        break;
      }

    } while (decision != 5);
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

void MostrarTarea(Nodo *Tarea){
  Nodo * Aux = Tarea;
  printf("\n-----TAREA-----");
  printf("\nId: %d", Aux->T.TareaID);
  printf("\nDescripcion: ");
  puts(Aux->T.Descripcion);
  printf("Duracion: %d\n", Aux->T.Duracion);
}

void MostrarLista(Nodo *Lista){
    Nodo * Aux = Lista;
    while (Aux)
    {
        MostrarTarea(Aux);
        Aux = Aux->siguiente;
    }
}

Nodo * BuscarTareaPorId(Nodo ** Lista,int Id){
    Nodo * Aux = *Lista;
    while (Aux && Aux->T.TareaID != Id)
    {
        Aux = Aux->siguiente;
    }
    return Aux;
}

Nodo * BuscarTareaPorPalabra(Nodo **Lista, char *Palabra){
    Nodo * Aux = *Lista;
    while (Aux && strstr(Aux->T.Descripcion, Palabra) == NULL)
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