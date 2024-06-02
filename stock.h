#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stock {
    int id, stock;
    char denominacion[50], unidad[10];
    float precio;
    struct stock *izq, *der;
} stock;

void recorrerIRD(stock *r, int dato, int *band);
stock* insertar(stock *r, stock *n);
stock* busBor(stock *r, int dato);
stock* borrarNodo(stock *bor);
void modificarNodo(stock *r, int id);
void listarMateriales(stock *r);
void altaStock(stock **r);

int main() {
    stock *r = NULL;
    int id;
    int opcion, dato;
    int cont = 0, band = 0;
    float acum = 0;

    do {
        // Menú de opciones
        printf("\n--- Menu ---\n");
        printf("1. Alta de un material\n");
        printf("2. Buscar un material\n");
        printf("3. Baja un material\n");
        printf("4. Modificar un material\n");
        printf("5. Listar los materiales\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaStock(&r);
                break;
            case 2:
                printf("Ingrese el ID a buscar:\n");
                scanf("%d", &dato);
                recorrerIRD(r, dato, &band);
                if (band == 0) {
                    printf("No se encontro el dato\n");
                }
                band = 0;
                break;
            case 3:
                printf("Ingrese el ID a buscar y borrar: ");
                scanf("%d", &dato);
                r = busBor(r, dato);
                break;
            case 4:
                printf("Ingrese el ID del nodo a modificar: ");
                scanf("%d", &id);
                modificarNodo(r, id);
                break;
            case 5:
                listarMateriales(r);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor ingrese una opcion valida.\n");
        }
    } while (opcion != 6);

    return 0;
}

void altaStock(stock **r) {
    FILE *archivoStock;
    stock temp;
    stock *n;

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
        
        fwrite(&temp, sizeof(stock), 1, archivoStock);
		// CREAR NODO E INSERTARLO
		    n = (stock*)malloc(sizeof(stock));
		    if (n != NULL) {
		        n->id = temp.id;
		        n->stock = temp.stock;
		        strcpy(n->denominacion, temp.denominacion);
		        strcpy(n->unidad, temp.unidad);
		        n->precio = temp.precio;
		        n->der = NULL;
		        n->izq = NULL;
		        *r = insertar(*r, n);
		        fclose(archivoStock);
		    } else {
		        printf("No hay memoria suficiente para cargar los nodos");
		    }
		
    } else {
        printf("\nError al abrir el archivo stock.dat");
    }

   
}

stock* insertar(stock *r, stock *n) {
    if (r != NULL) {
        if (r->id == n->id) {
            printf("El nodo ya esta en el arbol\n");
        } else {
            if (r->id > n->id) {
                r->izq = insertar(r->izq, n);
            } else {
                r->der = insertar(r->der, n);
            }
        }
    } else {
        r = n;
    }
    return r;
}

void recorrerIRD(stock *r, int dato, int *band) {
    if (r != NULL) {
        recorrerIRD(r->izq, dato, band);
        if (r->id == dato) {
            printf("Nodo encontrado: ID=%d, Stock=%d, Denominacion=%s, Unidad=%s, Precio=%.2f\n", r->id, r->stock, r->denominacion, r->unidad, r->precio);
            *band = 1;
        }
        recorrerIRD(r->der, dato, band);
    }
}

stock* busBor(stock *r, int dato) {
    if (r != NULL) {
        if (r->id == dato) {
            r = borrarNodo(r);
        } else if (r->id > dato) {
            r->izq = busBor(r->izq, dato);
        } else {
            r->der = busBor(r->der, dato);
        }
    } else {
        printf("No se encontro el dato\n");
    }
    return r;
}

stock* borrarNodo(stock *bor) {
    stock *ant = NULL;
    stock *r = bor->izq;
    if (r != NULL) {
        while (r->der != NULL) {
            ant = r;
            r = r->der;
        }
        r->der = bor->der;
        if (ant != NULL) {
            ant->der = r->izq;
            r->izq = bor->izq;
        }
    } else {
        r = bor->der;
    }
    free(bor);
    printf("Nodo borrado\n");
    return r;
}

void modificarNodo(stock *r, int id) {
    if (r != NULL) {
        if (r->id == id) {
            printf("Nodo encontrado: ID=%d, Stock=%d, Denominacion=%s, Unidad=%s, Precio=%.2f\n", r->id, r->stock, r->denominacion, r->unidad, r->precio);
            printf("Ingrese nuevo stock: ");
            scanf("%d", &r->stock);
            printf("Ingrese nueva denominacion: ");
            scanf("%s", r->denominacion);
            printf("Ingrese nueva unidad: ");
            scanf("%s", r->unidad);
            printf("Ingrese nuevo precio: ");
            scanf("%f", &r->precio);
            printf("Nodo modificado\n");
        } else if (r->id > id) {
            modificarNodo(r->izq, id);
        } else {
            modificarNodo(r->der, id);
        }
    } else {
        printf("No se encontro el nodo con ID=%d\n", id);
    }
}

void listarMateriales(stock *r) {
    if (r != NULL) {
        listarMateriales(r->izq);
        printf("ID=%d, Stock=%d, Denominacion=%s, Unidad=%s, Precio=%.2f\n", r->id, r->stock, r->denominacion, r->unidad, r->precio);
        listarMateriales(r->der);
    }
}

