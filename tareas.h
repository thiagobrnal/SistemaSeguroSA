#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void altaTarea(struct tareas **inicio, int idOpcion);
void bajaTarea(struct tareas **inicio, int id);
void modificarTarea(struct tareas *inicio);
void listarTareas(struct tareas *inicio);
struct tareas *nuevoNodo(int id, int idOpcion, int orden, struct tiempo duracion);
void sumaHorasMinutosTareas(int idOpcion, struct tareas *ini);


// Función para crear un nuevo nodo de la lista doblemente enlazada
struct tareas* nuevoNodo(int id, int idOpcion, int orden, int hora, int minuto) {
	
    struct tareas* nodo = (struct tareas*)malloc(sizeof(struct tareas));
    
    if (nodo == NULL) {
        return NULL;
    } else {
        nodo->id = id;
        nodo->idOpcion = idOpcion;
        nodo->orden = orden;
        nodo->duracion.hora = hora;
        nodo->duracion.minuto = minuto;
        nodo->ant = NULL;
        nodo->sgte = NULL;
    }
    return nodo;
}

void altaTarea(struct tareas **ini, int idOpcion) {
    struct tareas *n = NULL;
    int ultId = 0;

    FILE *arch1 = fopen("tareas.dat", "a+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo tareas.dat");
        return;
    }

    fread(&tareas, sizeof(tareas), 1, arch1);
    while (!feof(arch1)) {
        ultId = tareas.id;
        fread(&tareas, sizeof(tareas), 1, arch1);
    }

    tareas.id = ultId + 1;
	fflush(stdin);
	
	tareas.idOpcion=idOpcion;
	fflush(stdin);
	
    // Leer datos
    printf("Ingrese el orden de la tarea: ");
    scanf("%d", &tareas.orden);
    fflush(stdin);

    printf("Ingrese la hora de duracion: ");
    scanf("%d", &tareas.duracion.hora);
    fflush(stdin);

    printf("Ingrese los minutos de duracion: ");
    scanf("%d", &tareas.duracion.minuto);
    fflush(stdin);
	
    
    fwrite(&tareas, sizeof(tareas), 1, arch1);
    printf("\nTarea cargada exitosamente\n");

    // Crear el nodo
    n = nuevoNodo(tareas.id, tareas.idOpcion, tareas.orden, tareas.duracion.hora, tareas.duracion.minuto);
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

// Funcion para calcular la suma de las horas y minutos de las tareas asociadas a un idOpcion
void sumaHorasMinutosTareas(int idOpcion, struct tareas *ini) {
    int sumaHoras = 0;
    int sumaMinutos = 0;
    struct tareas *temp = ini;
    
    while (temp != NULL) {
        if (temp->idOpcion == idOpcion) {
            sumaHoras += temp->duracion.hora;
            sumaMinutos += temp->duracion.minuto;
        }
        temp = temp->sgte;
    }
    
    // Ajustar la suma de minutos si supera 60
    sumaHoras += sumaMinutos / 60;
    sumaMinutos %= 60;

    printf("%d horas %d minutos", sumaHoras, sumaMinutos);
}

