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
	int ultId = 0;

    if ((archivoStock = fopen("stock.dat", "a+b")) != NULL) {
        // LEER DATOS
        fread(&temp, sizeof(temp),1,archivoStock);
		while(!feof(archivoStock)){
			ultId = temp.id;
			fread(&temp, sizeof(temp),1,archivoStock);
		}
		temp.id = ultId + 1;
		fflush(stdin);
        printf("Ingrese stock: ");
        scanf("%d", &temp.stock);
        fflush(stdin);
        printf("Ingrese denominacion: ");
        scanf("%s", temp.denominacion);
        fflush(stdin);
        printf("Ingrese unidad: ");
        scanf("%s", temp.unidad);
        fflush(stdin);
        printf("Ingrese precio: ");
        scanf("%f", &temp.precio);
        fflush(stdin);
         
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
		        fclose(archivoStock);
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

void mostrarStock(struct stock *r){
	FILE *arch1;
	arch1=fopen("stock.dat","rb");
	if(arch1==NULL){
		printf("\nError al abrir el archivo opciones.dat");
	}else{
		fread(&stock, sizeof(stock),1,arch1);
		while(!feof(arch1)){
    		printf("\n%d -",stock.id);
    		printf(" Nombre: ");
    		puts(stock.denominacion);
    		printf(" unidad: ");
    		puts(stock.unidad);
    		printf(" Stock: %d",stock.stock);
    		printf(" Precio: %f",stock.precio);
			fread(&stock, sizeof(stock),1,arch1);
		}
		fclose(arch1);
	}
}
