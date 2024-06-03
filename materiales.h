#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Prototipos de funciones
struct materiales* nuevoNodoMaterial(int idStock, int idOpcion, int cantidad);
void altaMateriales(struct materiales **ini,int idOpcion, struct stock *Rstc);
void recorrerMateriales(struct materiales *rc);
void listarMateriales();
float precioMateriales(int idOpcion, struct materiales *rMat, struct stock *rStock);


struct materiales* nuevoNodoMaterial(int idStock, int idOpcion, int cantidad) {
    struct materiales* nodo = (struct materiales*)malloc(sizeof(struct materiales));
    if (nodo == NULL) {
        return NULL;
    } else {
        nodo->idStock = idStock;
        nodo->idOpcion = idOpcion;
        nodo->cantidad = cantidad;
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
        scanf("%d",&idStock);
        
        materiales.idStock = idStock;
		fflush(stdin);
		
        printf("Ingrese la cantidad del material: ");
        scanf("%d", &materiales.cantidad);
        fflush(stdin);


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
        printf("\nID Stock: %d, ID Opción: %d, Cantidad: %d", rc->idStock, rc->idOpcion, rc->cantidad);
        rc = rc->sgte;
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
            printf("\nID Stock: %d -", materiales.idStock);
            printf(" ID Opción: %d", materiales.idOpcion);
            printf(" Cantidad: %d", materiales.cantidad);
            printf("\n----------------");    
            fread(&materiales, sizeof(struct materiales), 1, arch1);
        }
        fclose(arch1);
    }
}

float precioMateriales(int idOpcion, struct materiales *rMat, struct stock *rStock) {
    float totalPrecio = 0.0;
    while (rMat != NULL) {
        if (rMat->idOpcion == idOpcion) {
            int band = 0;
            float precio = 0.0;
            buscarPrecio(rStock, rMat->idStock, &band, &precio);
            if (band) {
                totalPrecio += precio * rMat->cantidad;
            }
        }
        rMat = rMat->sgte;
    }
    return totalPrecio;
}

