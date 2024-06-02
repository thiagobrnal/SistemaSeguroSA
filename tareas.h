#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "structs.h"

void altaTarea(struct tareas **inicio, int idOpcion);
void bajaTarea(struct tareas **inicio, int id);
void modificarTarea(struct tareas *inicio, int id);
void listarTareas(struct tareas *inicio);
struct tareas *nuevoNodoTarea(int id, int idOpcion, int orden, struct tiempo duracion);
int sumaHorasTareas(int idOpcion, struct tareas *inicio);
int sumaMinutosTareas(int idOpcion, struct tareas *inicio);


void altaTarea(struct tareas **inicio) {
    


    printf("Ingrese el ID de la nueva tarea: ");
    scanf("%d", &tareas.id);

    printf("Ingrese el orden de la tarea: ");
    scanf("%d", &tareas.orden);

    printf("Ingrese la hora de duracion: ");
    scanf("%d", &tareas.duracion.hora);

    printf("Ingrese los minutos de duracion: ");
    scanf("%d", &tareas.duracion.minuto);

    // idOpcion del usuario
    
    scanf("%d", &opciones.id);

    // Crear nueva tarea
    struct tareas* nuevaTarea = nuevoNodoTarea(tareas.id, opciones.id, tareas.orden, tareas.duracion);
    if (nuevaTarea == NULL) {
        return;
    }

    // Insercion en la lista doblemente enlazada
    if (*inicio == NULL) {
        *inicio = nuevaTarea;
    } else {
        struct tareas* temp = *inicio;
        while (temp->sgte != NULL) {
            temp = temp->sgte;
        }
        temp->sgte = nuevaTarea;
        nuevaTarea->ant = temp;
    }

    // Guardado en archivo
    FILE* archivo = fopen("tareas.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir el archivo tareas.dat\n");
        return;
    }
    fwrite(nuevaTarea, sizeof(struct tareas), 1, archivo);
    fclose(archivo);

    printf("Tarea registrada exitosamente.\n");
}


void bajaTarea(struct tareas **inicio, int id) {
    if (*inicio == NULL) {
        printf("La lista de tareas esta vacia.\n");
        return;
    }

    struct tareas *actual = *inicio;
    struct tareas *anterior = NULL;

    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->sgte;
    }

    if (actual == NULL) {
        printf("La tarea con ID %d no se encontro en la lista.\n", id);
        return;
    }

    if (anterior == NULL) {
        *inicio = actual->sgte;
    } else {
        anterior->sgte = actual->sgte;
        if (actual->sgte != NULL) {
            actual->sgte->ant = anterior;
        }
    }

    free(actual);
    printf("Tarea con ID %d eliminada exitosamente.\n", id);
}

void modificarTarea(struct tareas *inicio, int id) {
    struct tareas *actual = inicio;

    while (actual != NULL && actual->id != id) {
        actual = actual->sgte;
    }

    if (actual == NULL) {
        printf("La tarea con ID %d no se encontro en la lista.\n", id);
        return;
    }

    int opcion;
    printf("¿Qué desea modificar?\n");
    printf("1. ID de la tarea\n");
    printf("2. Orden de la tarea\n");
    printf("3. Duración de la tarea\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            printf("Ingrese el nuevo ID de la tarea: ");
            scanf("%d", &actual->id);
            break;
        case 2:
            printf("Ingrese el nuevo orden de la tarea: ");
            scanf("%d", &actual->orden);
            break;
        case 3:
            printf("Ingrese la nueva hora de duracion: ");
            scanf("%d", &actual->duracion.hora);
            printf("Ingrese los nuevos minutos de duración: ");
            scanf("%d", &actual->duracion.minuto);
            break;
        default:
            printf("Opcion no valida.\n");
            break;
    }
}

void listarTareas(struct tareas *inicio) {
    if (inicio == NULL) {
        printf("La lista de tareas esta vacia.\n");
        return;
    }

    printf("Lista de tareas:\n");
    struct tareas *temp = inicio;
    while (temp != NULL) {
        printf("ID: %d, ID de Opcion: %d, Orden: %d, Duracion: %dh %dm\n", temp->id, temp->idOpcion, temp->orden, temp->duracion.hora, temp->duracion.minuto);
        temp = temp->sgte;
    }
}

// Funcion para calcular la suma de las horas de las tareas asociadas a un idOpcion
int sumaHorasTareas(int idOpcion, struct tareas *inicio) {
    int sumaHoras = 0;
    struct tareas *temp = inicio;
    while (temp != NULL) {
        if (temp->idOpcion == idOpcion) {
            sumaHoras += temp->duracion.hora;
        }
        temp = temp->sgte;
    }
    return sumaHoras;
}

// Funcion para calcular la suma de los minutos de las tareas asociadas a un idOpcion
int sumaMinutosTareas(int idOpcion, struct tareas *inicio) {
    int sumaMinutos = 0;
    struct tareas *temp = inicio;
    while (temp != NULL) {
        if (temp->idOpcion == idOpcion) {
            sumaMinutos += temp->duracion.minuto;
        }
        temp = temp->sgte;
    }
    return sumaMinutos;
}


