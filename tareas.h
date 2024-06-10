#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void altaTarea(struct tareas **ini, int idOpcion);
void bajaTarea(int idOpcion, struct tareas **ini);
void modificarTarea(struct tareas *ini, int idOpcion);
void listarTareas(struct tareas *ini);
struct tareas *nuevoNodo(int id, int idOpcion, int orden, struct tiempo duracion);
void sumaHorasMinutosTareas(int idOpcion, struct tareas *ini);

void buscarTareasPorId(int idOpcion,struct tareas *rc);


// Función para crear un nuevo nodo de la lista doblemente enlazada
struct tareas* nuevoNodo(int id, int idOpcion, int orden, int hora, int minuto) {
	
    struct tareas* nodo = (struct tareas*)malloc(sizeof(struct tareas));
    
    if (nodo == NULL) {
        return NULL;
    } else {
        nodo->id = id;
        nodo->idOpcion = idOpcion;
        nodo->orden = orden;
        nodo->estado = 1;
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
    do{
    	printf("Ingrese el orden de la tarea: ");
    	scanf("%d", &tareas.orden);
    	fflush(stdin);
        if(tareas.orden < 0){
            printf("intente de nuevo con un numero valido mayor a 0.\n");
		}
	}while(tareas.orden < 0);
    

    do{
    	printf("Ingrese la hora de duracion: ");
    	scanf("%d", &tareas.duracion.hora);
    	fflush(stdin);
    	if(tareas.duracion.hora < 0){
    		printf("intente de nuevo con un numero valido mayor a 0.\n");
		}
	}while(tareas.duracion.hora < 0);

    do {
        printf("Ingrese los minutos de duracion (0-59): ");
        scanf("%d", &tareas.duracion.minuto);
        fflush(stdin);

        if (tareas.duracion.minuto < 0 || tareas.duracion.minuto > 59) {
            printf("Los minutos deben estar entre 0 y 59. Intente de nuevo.\n");
        }
    } while (tareas.duracion.minuto < 0 || tareas.duracion.minuto > 59);
    
	tareas.estado = 1;
    
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

void bajaTarea(int idOp, struct tareas **ini) {
	
	int tareasEliminadas = 0;
	
    if (*ini == NULL) {
        printf("La lista de tareas esta vacia.\n");
        return;
    }
	
    struct tareas *actual = *ini;
    struct tareas *anterior = NULL;


	FILE *arch1 = fopen("tareas.dat", "r+b");
	if (arch1 == NULL) {
        printf("\nError al abrir el archivo tareas.dat");
        return;
    }else{
    	fread(&tareas, sizeof(tareas),1,arch1);
   		while (!feof(arch1)) {
   			
        	if(tareas.idOpcion == idOp){
        		fseek(arch1,sizeof(tareas)*(-1),SEEK_CUR);
        		tareas.estado = 0;
				fwrite(&tareas,sizeof(tareas),1,arch1);
				fseek(arch1, 0, SEEK_CUR);
			}
				fread(&tareas, sizeof(tareas), 1, arch1);	
    	}
		fclose(arch1);

	while (actual != NULL) {
        if (actual->idOpcion == idOp) {
            struct tareas *aEliminar = actual;
            actual = actual->sgte;

            if (anterior == NULL) {
                *ini = aEliminar->sgte;
                if (*ini != NULL) {
                    (*ini)->ant = NULL;
                }
            } else {
                anterior->sgte = aEliminar->sgte;
                if (aEliminar->sgte != NULL) {
                    aEliminar->sgte->ant = anterior;
                }
            }

            free(aEliminar);
            tareasEliminadas++;
        } else {
            anterior = actual;
            actual = actual->sgte;
        }
    }

    if (tareasEliminadas > 0) {
        printf("Se eliminaron %d tareas con idOpcion %d.\n", tareasEliminadas, idOp);
    } else {
        printf("No se encontraron tareas con idOpcion %d.\n", idOp);
    }
    	
	}
	
}

void modificarTarea(struct tareas *ini, int idOp) {
    struct tareas *actual = ini;
    int id = 0;
	listarTareas(ini);
    printf("Ingrese id Tarea para modificar\n");
    scanf("%d", &id);
    fflush(stdin);
    if(id == 0){
    	return;
	}

    while ((actual != NULL) && (actual->id != id || actual->idOpcion != idOp)) {
        actual = actual->sgte;
    }

    if (actual == NULL) {
        printf("La tarea con ID %d e ID Opcion %d no se encontro en la lista.\n", id,idOp);
        return;
    }
	int bandM=1,band=0;
	char opcion;
	while (bandM!= 0){
		
    	printf("¿Qué desea modificar?\n");
    	printf("1. Orden de la tarea\n");
    	printf("2. Duracion de la tarea\n");
    	printf("0. Salir\n");
    	printf("Seleccione una opcion: ");
    	scanf("%c", &opcion);
    	fflush(stdin);

   		switch (opcion) {
    		case'0':
    			printf("Saliendo del menu de modificacion.\n");
    			bandM=0;
    			break;
        	case '1':{
        		do{
        			printf("Ingrese el nuevo orden de la tarea: ");
            		scanf("%d", &actual->orden);
            		fflush(stdin);
            		if(actual->orden < 0){
            			printf("intente de nuevo con un numero valido mayor a 0.\n");
					}
				}while(actual->orden < 0);
           		break;
           }
        	case '2':{ 
            	do{
    				printf("Ingrese la hora de duracion: ");
    				scanf("%d", &actual->duracion.hora);
    				fflush(stdin);
    				if(tareas.duracion.hora < 0){
    					printf("intente de nuevo con un numero valido mayor a 0.\n");
					}
				}while(actual->duracion.hora < 0);
            	do {
        			printf("Ingrese los minutos de duracion (0-59): ");
        			scanf("%d", &actual->duracion.minuto);
        			fflush(stdin);

       			 	if (actual->duracion.minuto < 0 || actual->duracion.minuto > 59) {
            		printf("Los minutos deben estar entre 0 y 59. Intente de nuevo.\n");
        			}
    			} while (actual->duracion.minuto < 0 || actual->duracion.minuto > 59);
            	break;
        	}
        	default:
            	printf("Opcion no valida.\n");
            	break;
    	}
	}
	
    FILE *arch1 = fopen("tareas.dat", "r+b");
	if (arch1 == NULL) {
        printf("\nError al abrir el archivo tareas.dat");
        return;
    }else{
    	fread(&tareas, sizeof(tareas),1,arch1);
   		while ((!feof(arch1)) && (band ==0)) {
   			
        	if(tareas.id == id){
        		tareas.orden = actual->orden;
        		tareas.duracion.hora = actual->duracion.hora;
        		tareas.duracion.minuto = actual->duracion.minuto;
        		fseek(arch1,sizeof(tareas)*(-1),SEEK_CUR);
				fwrite(&tareas,sizeof(tareas),1,arch1);
				band=1;
			}else{
				fread(&tareas, sizeof(tareas), 1, arch1);	
			}
    	}
		fclose(arch1);
	}
}

void listarTareas(struct tareas *ini) {
    if (ini == NULL) {
        printf("La lista de tareas esta vacia.\n");
        return;
    }

    struct tareas *temp = ini;
    while (temp != NULL) {
        printf("ID: %d, ID de Opcion: %d, Orden: %d, Duracion: %dh %dm\n", temp->id, temp->idOpcion, temp->orden, temp->duracion.hora, temp->duracion.minuto);
        temp = temp->sgte;
    }
}

void buscarTareasPorId(int idOpcion,struct tareas *rc) {
	printf("\n\n\t\tTareas:");
    while (rc != NULL) {
    	if(rc->idOpcion == idOpcion){
    		printf("\n\tID: %d, ID de Opcion: %d, Orden: %d, Duracion: %dh %dm", rc->id, rc->idOpcion, rc->orden, rc->duracion.hora, rc->duracion.minuto);	
		}
        rc = rc->sgte;
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

