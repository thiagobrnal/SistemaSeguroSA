#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void altaStock(struct stock **r);
void buscarPrecio(struct stock *r, int dato, int *band, float *precio);
struct stock* insertarStock(struct stock *r,struct stock *n);
void listarStock(struct stock *r);
void bajaStock(struct stock **r);
struct stock* borrarNodo(struct stock *bor);
struct stock* busBor(struct stock *r, int dato);
void modificarNodo(struct stock *r,int dato);
void modificarStock(struct stock **r);
void buscarCantidadStock(int idStock, int *cantidadStock);
void descontarStock(int idStock, int cantidadMateriales);
void editarArbolStock(struct stock *r, int idStock, int cantidad);
int buscarIdStock(int idBusc, struct stock *r, int *idRef);

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
		temp.estado=1;
		temp.id = ultId + 1;
		fflush(stdin);
        printf("Ingrese stock: ");
        scanf("%d", &temp.stock);
        fflush(stdin);
        printf("Ingrese denominacion: ");
        fflush(stdin);
		gets(temp.denominacion);
        fflush(stdin);
        printf("Ingrese unidad: ");
        fflush(stdin);
		gets(temp.unidad);
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
		        n->estado=1;
		        (*r) = insertarStock(*r, n);
		        
		    } else {
		        printf("No hay memoria suficiente para cargar los nodos");
		        fclose(archivoStock);
		    }
		    
		    fclose(archivoStock);
		
    } else {
        printf("\nError al abrir el archivo stock.dat");
    }

   
}

void modificarStock(struct stock **r){
	int idAux=0;
	
	listarStock((*r));
	printf("Ingrese el ID del stock que desea modificar\n");
	scanf("%d",&idAux);
	modificarNodo((*r),idAux);
	
	
}

void modificarNodo(struct stock *r,int dato){
	int encontro=0;
	
	if (r != NULL) {
        modificarNodo(r->izq,dato);
		if((r->estado==1)&&(r->id==dato)){
			FILE *stck=NULL;
        	int opcion;
			do {
		        printf("\n¿Que desea modificar?\n");
		        printf("1. Stock\n");
		        printf("2. Denominacion\n");
		        printf("3. Unidad\n");
		        printf("4. Precio\n");
		        printf("5. Salir\n");
		        printf("Seleccione una opcion: ");
		        scanf("%d", &opcion);

		        switch (opcion) {
		            case 1:
		                printf("Ingrese el nuevo stock: ");
		                scanf("%d", &r->stock);
		                break;
		            case 2:
		                printf("Ingrese la nueva denominacion: ");
		                fflush(stdin);
		                gets(r->denominacion);
		                fflush(stdin);
		                break;
		            case 3:
		                printf("Ingrese la nueva unidad: ");
		                fflush(stdin);
		                gets(r->unidad);
		                fflush(stdin);
		                break;
		            case 4:
		                printf("Ingrese el nuevo precio: ");
		                scanf("%f", &r->precio);
		                break;
		            case 5:
		                printf("Saliendo del menú de modificacion.\n");
		                break;
		            default:
		                printf("Opcion no valida.\n");
		                break;
       			}
    		} while (opcion != 5);
    		
			    stck = fopen("stock.dat","r+b");
				if(stck==NULL){
					printf("Error de apertura de archivo stock.dat");
					printf("\n");
				}else{
					fread(&stock, sizeof(stock),1,stck);
					while((!feof(stck))&&(encontro==0)){
						if(stock.id==r->id){
							stock.stock=r->stock;
							strcpy(stock.denominacion,r->denominacion);
							strcpy(stock.unidad,r->unidad);
							stock.precio=r->precio;	
							encontro=1;
							fseek(stck,sizeof(stock)*(-1),SEEK_CUR);
							fwrite(&stock,sizeof(stock),1,stck);		
						}else{
							fread(&stock, sizeof(stock),1,stck);
						}
									
					}		
				}
				
				fclose(stck);
		}
			modificarNodo(r->der,dato);
    }
}

void bajaStock(struct stock **r){
	FILE *stck=NULL;
	struct stock *n=NULL;
	int idAux=0;
	int encontro=0;
	
	listarStock((*r));
	printf("Ingrese el ID del stock a dar de baja\n");
	scanf("%d",&idAux);
	(*r)=busBor((*r),idAux);
	
	
	stck = fopen("stock.dat","r+b");
	if(stck==NULL){
		printf("Error de apertura de archivo stock.dat");
		printf("\n");
	}else{
		fread(&stock, sizeof(stock),1,stck);
		
		while((!feof(stck))&&(encontro==0)){
			if(stock.id==idAux){
					stock.estado=0;
					encontro=1;
					fseek(stck,sizeof(stock)*(-1),SEEK_CUR);
					fwrite(&stock,sizeof(stock),1,stck);
			}else{
				fread(&stock, sizeof(stock),1,stck);
			}
			
						
		}
		fclose(stck);		
	}
	
	
}


struct stock* busBor(struct stock *r, int dato){
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

struct stock* borrarNodo(struct stock *bor){
    struct stock *ant = NULL;
    struct stock *r = bor->izq;
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


void listarStock(struct stock *r){
    if (r != NULL) {
        listarStock(r->izq);
        if(r->estado==1){
        	printf("ID=%d, Stock=%d, Denominacion=%s, Unidad=%s, Precio=%.2f\n", r->id, r->stock, r->denominacion, r->unidad, r->precio);	
        }
        listarStock(r->der);
    }
}

struct stock* insertarStock(struct stock *r, struct stock *n){
	
	if(r != NULL){
		if(strcmp(r->denominacion, n->denominacion) == 0){
			if(r->id == n->id){
				printf("\nEl material ya esta registrado en el stock");
				
			}else if(r->id < n->id){
				r->izq = insertStock(r->izq, n);
								
			}else{
				r->der = insertStock(r->der, n);
			}
		}else if(strcmp(r->denominacion, n->denominacion) < 0){
			r->izq = insertStock(r->izq, n);
		
		}else{
			r->der = insertStock(r->der, n);
		}
	}else{
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
			if(stock.estado==1){
				printf("\n%d -",stock.id);
	    		printf(" Nombre: ");
	    		puts(stock.denominacion);
	    		printf(" unidad: ");
	    		puts(stock.unidad);
	    		printf(" Stock: %d",stock.stock);
	    		printf(" Precio: %f",stock.precio);
			}
			fread(&stock, sizeof(stock),1,arch1);
		}
		fclose(arch1);
	}
}

void buscarCantidadStock(int idStock, int *cantidadStock){
	int encontro=0;
	
	FILE *stck = fopen("stock.dat","r+b");
	if(stck==NULL){
		printf("Error de apertura de archivo stock.dat");
		printf("\n");
	}else{
		fread(&stock, sizeof(stock),1,stck);
		
		while((!feof(stck))&&(encontro==0)){
			if(stock.id==idStock){
					(*cantidadStock)=stock.stock;
					encontro=1;
			}else{
				fread(&stock, sizeof(stock),1,stck);
			}
			
						
		}
		fclose(stck);		
	}
	
}

void descontarStock(struct stock **r , int idStock, int cantidadMateriales){
	int encontro=0;
	
	FILE *stck = fopen("stock.dat","r+b");
	if(stck==NULL){
		printf("Error de apertura de archivo stock.dat");
		printf("\n");
	}else{
		fread(&stock, sizeof(stock),1,stck);
		
		while((!feof(stck))&&(encontro==0)){
			if(stock.id==idStock){
					stock.stock-=cantidadMateriales;
					encontro=1;
					editarArbolStock((*r),stock.id,stock.stock);
					fseek(stck,sizeof(stock)*(-1),SEEK_CUR);
					fwrite(&stock,sizeof(stock),1,stck);
			}else{
				fread(&stock, sizeof(stock),1,stck);
			}
			
						
		}
		fclose(stck);
	}
	
}

void editarArbolStock(struct stock *r, int idStock, int cantidad){
	if (r != NULL) {
        editarArbolStock(r->izq,idStock,cantidad);
        if(r->id==idStock){
        		r->stock=cantidad;
        }
        editarArbolStock(r->der,idStock,cantidad);
    }
	
	
}

int buscarIdStock(int idBusc, struct stock *r, int *idRef){

	if (r != NULL) {
        buscarIdStock(idBusc,r->izq,idRef);
        if(r->id==idBusc){
        	*idRef = r->id;	
        }
        buscarIdStock(idBusc,r->der,idRef);
    }
}
