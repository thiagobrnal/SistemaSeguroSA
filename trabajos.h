#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void altaTrabajos(struct trabajos **L);
struct trabajos* insertarLES(struct trabajos *L,struct trabajos *nv);


void altaTrabajos(struct trabajos **L, struct tareas *Ltar, struct materiales *rMat, struct stock *rStock, struct opciones *r){
    FILE *archivoTrabajos;
    struct trabajos *n = NULL;
    struct trabajos temp;
	int band=0;
	long ultId;
	float materiales=0,costoBase=0;
	
    if ((archivoTrabajos = fopen("trabajos.dat", "a+b")) != NULL) {
        // LEER DATOS
        fread(&temp, sizeof(temp),1,archivoTrabajos);
		while(!feof(archivoTrabajos)){
			ultId = temp.id;
			fread(&temp, sizeof(temp),1,archivoTrabajos);
		}
		temp.id = ultId + 1;
		
		printf("Seleccione el ID de la opcion que desea usar: ");
		listarOpciones(Ltar,rMat,rStock);
		scanf("%d",&temp.idOpcion);
        
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
        
    	materiales=precioMateriales(temp.idOpcion,rMat,rStock);
        costoBase=obtenerCostoBase(temp.idOpcion,r);
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
            (*L)=insertarLES(*L,n);
            fclose(archivoTrabajos);
        } else {
            printf("No hay memoria suficiente para cargar los nodos a la LES");
            fclose(archivoTrabajos);
        }
    } else {
        printf("\nError al abrir el archivo trabajos.dat");
    }
}

struct trabajos* insertarLES(struct trabajos *L,struct trabajos *nv){
	if(L!=NULL){
		if((nv->id)<(L->id)){
			nv->sgte=L;
			L=nv;
		}else{
			L->sgte=insertarLES(L->sgte,nv);
		}
	}else{
		L=nv;
	}
	return L;
}

