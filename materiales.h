#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Prototipos de funciones
struct materiales* nuevoNodoMaterial(int idStock, int idOpcion, int cantidad);
void altaMateriales(struct materiales **ini,int idOpcion, struct stock *Rstc);
void recorrerMateriales(struct materiales *rc);
void listarMateriales();
float precioMateriales(int idOpcion, struct materiales *rMat, struct stock *rStock);
void modificarMaterial(struct materiales *ini, int idOp, struct stock *r);
void bajaMaterial(int idOpcion, struct materiales **ini);
void buscarMaterialesPorId(int idOpcion,struct materiales *rc);
void buscarCantidadMateriales(int idOpcion, int *idStock, int *cantidadMateriales);


struct materiales* nuevoNodoMaterial(int idStock, int idOpcion, int cantidad) {
    struct materiales* nodo = (struct materiales*)malloc(sizeof(struct materiales));
    if (nodo == NULL) {
        return NULL;
    } else {
        nodo->idStock = idStock;
        nodo->idOpcion = idOpcion;
        nodo->cantidad = cantidad;
        nodo->estado = 1;
        nodo->sgte = NULL;
    }
    return nodo;
}

void altaMateriales(struct materiales **ini,int idOpcion, struct stock *Rstc) {
    struct materiales *n = NULL, *r = NULL;
	int idStock;
    r = (*ini);

    FILE *arch1 = fopen("materiales.dat", "a+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo materiales.dat");
    } else {
        // Obtener idOpcion e idStock
        materiales.idOpcion = idOpcion;
        listarStock(Rstc);
        int idRef = -1;
        do{
        	printf("\nIngrese el ID del material que quiere agregar:");
        	scanf("%d",&idStock);
        	buscarIdStock(idStock,Rstc,&idRef);
        	if(idRef < 1){
        		printf("ID no valida:");
			}
		}while(idRef < 1);
        
        materiales.idStock = idStock;
		fflush(stdin);
		
        do{
        	printf("Ingrese la cantidad del material: ");
        	scanf("%d", &materiales.cantidad);
        	fflush(stdin);
        	if(materiales.cantidad < 0){
        		printf("intente de nuevo con un numero valido mayor a 0.\n");
			}
		}while(materiales.cantidad < 0);

		materiales.estado=1;

		fwrite(&materiales, sizeof(struct materiales), 1, arch1);
		printf("\nMaterial cargado exitosamente\n");
		
        // Crear el nodo
        n = nuevoNodoMaterial(materiales.idStock, materiales.idOpcion, materiales.cantidad);
        if (n == NULL) {
            printf("No hay memoria.\n");
            fclose(arch1);
            return;
        }


        // Insertar en la lista
        if (*ini == NULL) {
            (*ini) = n;
        } else {
            while (r->sgte != NULL) {
                r = r->sgte;
            }
            r->sgte = n;
        }
        fclose(arch1);
    }
}

void recorrerMateriales(struct materiales *rc) {
    while (rc != NULL) {
        printf("\nID Stock: %d, ID Opcion: %d, Cantidad: %d", rc->idStock, rc->idOpcion, rc->cantidad);
        rc = rc->sgte;
    }
}

void bajaMaterial(int idOp, struct materiales **ini) {
    int materialesEliminados = 0;

    if (*ini == NULL) {
        printf("La lista de materiales está vacía.\n");
        return;
    }
    
    struct materiales *actual = *ini;
    struct materiales *anterior = NULL;

    FILE *arch1 = fopen("materiales.dat", "r+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo materiales.dat");
        return;
    } else {
        fread(&materiales, sizeof(materiales),1,arch1);
        while (!feof(arch1)) {
            if (materiales.idOpcion == idOp) {
                fseek(arch1, sizeof(materiales)*(-1),SEEK_CUR);
                materiales.estado = 0;
                fwrite(&materiales, sizeof(materiales),1,arch1);
				fseek(arch1, 0, SEEK_CUR);
            }
                fread(&materiales, sizeof(materiales),1,arch1);
            
        }
        fclose(arch1);

        while (actual != NULL) {
        if (actual->idOpcion == idOp) {
            struct materiales *aEliminar = actual;
            actual = actual->sgte;

            if (anterior == NULL) {
                *ini = aEliminar->sgte;
            } else {
                anterior->sgte = aEliminar->sgte;
            }

            free(aEliminar);
            materialesEliminados++;
        } else {
            anterior = actual;
            actual = actual->sgte;
        }
    }

    if (materialesEliminados > 0) {
        printf("Se eliminaron %d materiales con idOpcion %d.\n", materialesEliminados, idOp);
    } else {
        printf("No se encontraron materiales con idOpcion %d.\n", idOp);
    }
    }

}

void modificarMaterial(struct materiales *ini, int idOp, struct stock *Rstc) {
    if (ini == NULL) {
        printf("La lista de materiales está vacía.\n");
        return;
    }
    recorrerMateriales(ini);

    int idMat;
	int idRef = -1;
        do{
        	printf("\nIngrese el ID de stock para modificar: ");
    		scanf("%d", &idMat);
    		fflush(stdin);
    		if(idMat == 0){
    			return;
			}
        	buscarIdStock(idMat,Rstc,&idRef);
        	if(idRef < 1){
        		printf("ID no valida:");
			}
		}while(idRef < 1);

    struct materiales *actual = ini;
    while ((actual != NULL) && (actual->idStock != idMat || actual->idOpcion != idOp)) {
        actual = actual->sgte;
    }

    if (actual == NULL) {
        printf("El material con ID %d e ID Opcion %d no se encontro en la lista.\n", idMat,idOp);
        return;
    }

    int bandM = 1, band = 0;
    char opcion;
    while (bandM != 0) {
        printf("¿Qué desea modificar?\n");
        printf("1. Cantidad del material\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);
        fflush(stdin);

        switch (opcion) {
            case '0':
                printf("Saliendo del menú de modificación.\n");
                bandM = 0;
                break;
            case '1':
                do{
        			printf("Ingrese la nueva cantidad del material: ");
                	scanf("%d", &actual->cantidad);
                	fflush(stdin);
                	if(actual->cantidad < 0){
                		printf("intente de nuevo con un numero valido mayor a 0.\n");
					}
				}while(actual->cantidad < 0);
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }

    FILE *arch1 = fopen("materiales.dat", "r+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo materiales.dat");
        return;
    } else {
        fread(&materiales, sizeof(materiales), 1, arch1);
        while (!feof(arch1) && band == 0) {
            if (materiales.idStock == idMat) {
                materiales.cantidad = actual->cantidad;
                fseek(arch1, sizeof(materiales) * (-1), SEEK_CUR);
                fwrite(&materiales, sizeof(materiales), 1, arch1);
                band = 1;
            } else {
                fread(&materiales, sizeof(materiales), 1, arch1);
            }
        }
        fclose(arch1);
    }
}

void listarMateriales() {
    FILE *arch1;
    
    arch1 = fopen("materiales.dat", "rb");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo materiales.dat");
    } else {
        fread(&materiales, sizeof(struct materiales), 1, arch1);
        while (!feof(arch1)) {
        	if(materiales.estado == 1){
        		printf("\nID Stock: %d -", materiales.idStock);
            	printf(" ID Opcion: %d", materiales.idOpcion);
            	printf(" Cantidad: %d", materiales.cantidad);
            	printf("\n----------------");    
			}
			fread(&materiales, sizeof(struct materiales), 1, arch1);
			
            
        }
        fclose(arch1);
    }
}

float precioMateriales(int idOp, struct materiales *rMat, struct stock *rStock) {
	struct materiales *aux;
	aux = rMat;
    float totalPrecio = 0.0;
    while (aux != NULL) {
        if (aux->idOpcion == idOp) {
            int band = 0;
            float precio = 0.0;
            buscarPrecio(rStock, aux->idStock, &band, &precio);
            if (band) {
                totalPrecio += precio * aux->cantidad;
            }
        }
        aux = aux->sgte;
    }
    return totalPrecio;
}


void buscarMaterialesPorId(int idOpcion,struct materiales *rc) {
	printf("\n\n\t\tMateriales:");
    while (rc != NULL) {
    	if(rc->idOpcion == idOpcion){
    		printf("\n\tID Stock: %d, ID Opcion: %d, Cantidad: %d", rc->idStock, rc->idOpcion, rc->cantidad);	
		}
        rc = rc->sgte;
    }
}

void buscarCantidadMateriales(int idOpcion, int *idStock, int *cantidadMateriales){
	int band=0;
	
	FILE *arch1 = fopen("materiales.dat", "r+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo materiales.dat");
        return;
    } else {
        fread(&materiales, sizeof(materiales), 1, arch1);
        while (!feof(arch1) && band == 0) {
            if (idOpcion==materiales.idOpcion){
                (*idStock)=materiales.idStock;
                (*cantidadMateriales)=materiales.cantidad;
                band = 1;
            } else {
                fread(&materiales, sizeof(materiales), 1, arch1);
            }
        }
        fclose(arch1);
    }
	

}


