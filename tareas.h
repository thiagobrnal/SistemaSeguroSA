#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "structs.h"

void altaTarea(struct tareas **inicio, int idOpcion);
void bajaTarea(struct tareas **inicio, int id);
void modificarTarea(struct tareas *inicio);
void listarTareas(struct tareas *inicio);
struct tareas *nuevoNodo(int id, int idOpcion, int orden, struct tiempo duracion);
int sumaHorasTareas(int idOpcion, struct tareas *inicio);
int sumaMinutosTareas(int idOpcion, struct tareas *inicio);

void altaTarea(struct tareas **ini, int idOpcion) {
    struct tareas *n = NULL;
    int ultId = 0;
    struct tareas tareas;

    FILE *arch1 = fopen("tareas.dat", "a+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo tareas.dat");
        return;
    }

    rewind(arch1);
    while (fread(&tareas, sizeof(tareas), 1, arch1)) {
        ultId = tareas.id;
    }

    tareas.id = ultId + 1;

    // Leer datos
    printf("Ingrese el id de la tarea: ");
    scanf("%d", &tareas.id);
    
    printf("Ingrese el orden de la tarea: ");
    scanf("%d", &tareas.orden);

    printf("Ingrese la hora de duracion: ");
    scanf("%d", &tareas.duracion.hora);

    printf("Ingrese los minutos de duracion: ");
    scanf("%d", &tareas.duracion.minuto);
	
	printf("Se cargo id desde Opciones: ");
    tareas.idOpcion=idOpcion;

    fseek(arch1, 0, SEEK_END);
    fwrite(&tareas, sizeof(tareas), 1, arch1);
    printf("\nTarea cargada exitosamente\n");

    // Crear el nodo
    n = nuevoNodo(tareas.id, tareas.idOpcion, tareas.orden, tareas.duracion);
    if (n == NULL) {
        printf("No hay memoria.\n");
        fclose(arch1);
        return;
    }

    // Insercion en la lista doblemente enlazada
    if (*ini == NULL) {
        *ini = n;
    } else {
        struct tareas *temp = *ini;
        while (temp->sgte != NULL) {
            temp = temp->sgte;
        }
        temp->sgte = n;
        n->ant = temp;
    }
    fclose(arch1);
}

void bajaTarea(struct tareas **ini, int id) {
    if (*ini == NULL) {
        printf("La lista de tareas esta vacia.\n");
        return;
    }

    struct tareas *actual = *ini;
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
        *ini = actual->sgte;
    } else {
        anterior->sgte = actual->sgte;
        if (actual->sgte != NULL) {
            actual->sgte->ant = anterior;
        }
    }

    free(actual);
    printf("Tarea con ID %d eliminada exitosamente.\n", id);
}

void modificarTarea(struct tareas *ini) {
    struct tareas *actual = ini;
    int id = 0;

    printf("Ingrese id para busqueda\n");
    scanf("%d", &id);

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

void listarTareas(struct tareas *ini) {
    if (ini == NULL) {
        printf("La lista de tareas esta vacia.\n");
        return;
    }

    printf("Lista de tareas:\n");
    struct tareas *temp = ini;
    while (temp != NULL) {
        printf("ID: %d, ID de Opcion: %d, Orden: %d, Duracion: %dh %dm\n", temp->id, temp->idOpcion, temp->orden, temp->duracion.hora, temp->duracion.minuto);
        temp = temp->sgte;
    }
}

// Funcion para calcular la suma de las horas de las tareas asociadas a un idOpcion
int sumaHorasTareas(int idOpcion, struct tareas *ini) {
    int sumaHoras = 0;
    struct tareas *temp = ini;
    while (temp != NULL) {
        if (temp->idOpcion == idOpcion) {
            sumaHoras += temp->duracion.hora;
        }
        temp = temp->sgte;
    }
    return sumaHoras;
}

// Funcion para calcular la suma de los minutos de las tareas asociadas a un idOpcion
int sumaMinutosTareas(int idOpcion, struct tareas *ini) {
    int sumaMinutos = 0;
    struct tareas *temp = ini;
    while (temp != NULL) {
        if (temp->idOpcion == idOpcion) {
            sumaMinutos += temp->duracion.minuto;
        }
        temp = temp->sgte;
    }
    return sumaMinutos;
}



