#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "opciones.h"

void altaTrabajos(struct trabajos *L){
    FILE *archivoTrabajos;
    trabajos *n = NULL;
    trabajos temp;
	int band=0;
	
    if ((archivoTrabajos = fopen("trabajos.dat", "a+b")) != NULL) {
        // LEER DATOS
        printf("Ingrese ID del trabajo: ");
        scanf("%d", &temp.id);
        /*printf("Ingrese ID de la Opcion: "); //listar opciones y guardar el id
        scanf("%d", &temp.idOpcion); */
        printf("Ingrese altura: ");
        scanf("%d", &temp.altura);
        if(temp.altura>4){
        	band=1;
        }
        printf("Ingrese ID del Tecnico: "); //de donde
        scanf("%d", &temp.idTecnico);
        printf("Ingrese ID del Cliente: "); //de donde
        scanf("%d", &temp.idCliente);
        printf("Ingrese ubicacion: ");
        scanf("%s", temp.ubicacion);
        printf("Ingrese dia de finalizacion: ");
        scanf("%d", &temp.fechaFin.dia);
        printf("Ingrese mes de finalizacion: ");
        scanf("%d", &temp.fechaFin.mes);
        printf("Ingrese anio de finalizacion: ");
        scanf("%d", &temp.fechaFin.anio);
        if(band==1){
        	costoBase*=1.20;
        	temp.costoTotal=materiales+costoBase;
        }else{
        	temp.costoTotal=materiales+costoBase;
        }
        printf("El trabajo esta finalizado? (1 para si, 0 para no): ");
        scanf("%d", &temp.finalizado);

        // Guardar en el archivo
        fwrite(&temp, sizeof(struct trabajos), 1, archivoTrabajos);
        
        // CREAR NODO E INSERTARLO
        n = (struct trabajos*)malloc(sizeof(struct trabajos));
        if (n != NULL) {
            *n = temp; // Copiar datos
            n->sgte = NULL; 
            L=insertarLES(L,n);
            fclose(archivoTrabajos);
        } else {
            printf("No hay memoria suficiente para cargar los nodos a la LES");
            fclose(archivoTrabajos);
        }
    } else {
        printf("\nError al abrir el archivo trabajos.dat");
    }
}

struct trabajos* insertarLES(lista *L,lista *nv){
	if(L!=NULL){
		if((nv->num)<(L->num)){
			nv->sig=L;
			L=nv;
		}else{
			L->sig=insertar(L->sig,nv);
		}
	}else{
		L=nv;
	}
	return L;
}

