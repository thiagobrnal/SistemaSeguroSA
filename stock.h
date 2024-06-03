#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void altaStock(struct stock **r);
void buscarPrecio(struct stock *r, int dato, int *band, float *precio);
struct stock* insertarStock(struct stock *r,struct stock *n);
void listarStock(struct stock *r);

void altaStock(struct stock **r){
    FILE *archivoStock;
    struct stock temp;
    struct stock *n=NULL;


    if ((archivoStock = fopen("stock.dat", "a+b")) != NULL) {
        // LEER DATOS
        printf("Ingrese ID: ");
        scanf("%d", &temp.id);
        printf("Ingrese stock: ");
        scanf("%d", &temp.stock);
        printf("Ingrese denominacion: ");
        scanf("%s", temp.denominacion);
        printf("Ingrese unidad: ");
        scanf("%s", temp.unidad);
        printf("Ingrese precio: ");
        scanf("%f", &temp.precio);
        
        fwrite(&temp, sizeof(struct stock), 1, archivoStock);
		// CREAR NODO E INSERTARLO
		    n = (struct stock*)malloc(sizeof(struct stock));
		    if (n != NULL) {
		        n->id = temp.id;
		        n->stock = temp.stock;
		        strcpy(n->denominacion, temp.denominacion);
		        strcpy(n->unidad, temp.unidad);
		        n->precio = temp.precio;
		        n->der = NULL;
		        n->izq = NULL;
		        (*r) = insertarStock(*r, n);
		        fclose(archivoStock);
		    } else {
		        printf("No hay memoria suficiente para cargar los nodos");
		    }
		
    } else {
        printf("\nError al abrir el archivo stock.dat");
    }

   
}

void listarStock(struct stock *r) {
    if (r != NULL) {
        listarStock(r->izq);
        printf("ID=%d, Stock=%d, Denominacion=%s, Unidad=%s, Precio=%.2f\n", r->id, r->stock, r->denominacion, r->unidad, r->precio);
        listarStock(r->der);
    }
}

struct stock* insertarStock(struct stock *r,struct stock *n){
    if (r != NULL) {
        if (r->id == n->id) {
            printf("El nodo ya esta en el arbol\n");
        } else {
            if (r->id > n->id) {
                r->izq = insertarStock(r->izq, n);
            } else {
                r->der = insertarStock(r->der, n);
            }
        }
    } else {
        r = n;
    }
    return r;
}

void buscarPrecio(struct stock *r, int dato, int *band,float *precio) {
    if (r != NULL) {
        buscarPrecio(r->izq, dato, band, precio);
        if (r->id == dato) {
            (*precio)=r->precio;
            *band = 1;
        }
        buscarPrecio(r->der, dato, band, precio);
    }
}


