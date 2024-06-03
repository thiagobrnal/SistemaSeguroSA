#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "tareas.h"
#include "stock.h"


//OPCIONES
void altaOpciones(struct opciones **ini);
void bajaOpciones();
void modificarOpciones();
void listarOpciones();
struct opciones* nuevoNodo(int id, char* nombre, float costoBase);
int obtenerId(struct opciones *r);
float obtenerCostoBase(int idOpcion,struct opciones *r);

void recorrer(struct opciones *rc);

struct opciones* nuevoNodo(int id, char* nombre, float costoBase) {
	
    struct opciones* nodo = (struct opciones*)malloc(sizeof(struct opciones));
    
    if(nodo==NULL){
    	return NULL;
	}else{
		nodo->id = id;
    	strcpy(nodo->nombre, nombre);
    	nodo->costoBase = costoBase;
    	nodo->sgte = NULL;
	}
	return nodo;
}

void altaOpciones(struct opciones **ini){
	struct opciones *n = NULL, *r = NULL;
    char nombre[50];
    float costoBase;
    int ultId= 0;

	r = (*ini);
	
	FILE *arch1 = fopen("opciones.dat", "a+b");
	if (arch1 == NULL) {
        printf("\nError al abrir el archivo opciones.dat");
    } else {
    	
    	fread(&opciones, sizeof(opciones),1,arch1);
    	while(!feof(arch1)){
    		ultId = opciones.id;
			fread(&opciones, sizeof(opciones),1,arch1);
			
		}
        opciones.id = ultId + 1;
        fflush(stdin);
        
    	// Leer datos
    	printf("Ingrese el nombre de la opcion: ");
    	gets(opciones.nombre);
    	fflush(stdin);
   		
		printf("Ingrese el costo de esta operacion (sin mano de obra ni materiales): ");
    	scanf("%f", &opciones.costoBase);
    	fflush(stdin);
    	
    	
    	fwrite(&opciones, sizeof(opciones), 1, arch1);
    	printf("\nOpcion cargada exitosamente\n");
    	
    	
    	//Creo el nodo
    	n = nuevoNodo(opciones.id, opciones.nombre, opciones.costoBase);
    	if (n == NULL) {
    	    printf("No hay memoria.\n");
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

int obtenerId(struct opciones *r){
	if (r == NULL) {
        return 1;
    }
    while (r->sgte != NULL) {
        r = r->sgte;
    }
    return r->id + 1;
	
}

void recorrer(struct opciones *rc){
	while(rc != NULL){
		printf("\n%f", rc->costoBase);
		rc = rc->sgte;
	}
}
//Listar Opciones
//id,nombre,hora = duracionTareasH(idOpcion), min = duracionTareasM(idOpcion), costoBase + 20% si "trabajos.altura>=4", materiales.cantidad * stock.precio, trabajos.costoTotal

void listarOpciones(){
	FILE *arch1;
	int hora, min;
	float precioMateriales,costoTotal;
	
	
	arch1=fopen("opciones.dat","rb");
	if(arch1==NULL){
		printf("\nError al abrir el archivo opciones.dat");
	}else{
		fread(&opciones, sizeof(opciones),1,arch1);
    	while(!feof(arch1)){
    		printf("\n%d -",opciones.id);
    		printf(" Nombre: ");
    		puts(opciones.nombre);
    		printf("tiempo estimado: %d:%d",hora = sumaHorasTareas(opciones.id),min = sumaMinutosTareas(opciones.id));
    		printf(" Costo: %f",opciones.costoBase);
    		precioMateriales = precioMateriales(opciones.id);
    		printf(" Costo de materiales: %f",precioMateriales);
    		costoTotal = costoTotal(opciones.id);
    		printf(" Costo Total: %f",costoTotal);
    		printf("\n----------------");	
			fread(&opciones, sizeof(opciones),1,arch1);
		}
		fclose(arch1);
	}
}

float obtenerCostoBase(int idOpcion,struct opciones *r){
	while(r!=NULL){
		if(idOpcion == r->id){
			return r->costoBase;
		}else{
			r= r->sgte;
		}
	}
	return 0;
}
