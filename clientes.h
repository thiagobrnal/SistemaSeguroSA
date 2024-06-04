#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void altaClientes(struct clientes **tp);
void cargarClientes(struct clientes **nv, struct clientes **top);
void listarClientes(struct clientes **tope);
int vacia(struct clientes *topeP);
void desapilar(struct clientes **ds, struct clientes **topeP);
void apilar(struct clientes **nv, struct clientes **topeP);


void altaClientes(struct clientes **tp){
	FILE *archC=NULL;
	struct clientes *p=NULL;
	long dniAux=0;
	int ultId=0;
	
	printf("\nIngrese su DNI o 0 para volver: ");
	while(scanf("%ld", &dniAux) != 1){
		fflush(stdin);
		printf(" Valor invalido\n");
	 }
	 
	if(dniAux != 0){
		archC=fopen("clientes.dat","a+b");
		if(archC==NULL){
			printf("\nError al abrir el archivo clientes.dat");
		}
		else{	
			// LEER DATOS								
			fread(&clientes, sizeof(clientes),1,archC);
			while(!feof(archC)){
				ultId = clientes.id;
				fread(&clientes, sizeof(clientes),1,archC);
			}
			
			clientes.id = ultId + 1;
			fflush(stdin);
			clientes.dni = dniAux;
			fflush(stdin);
			printf("\nIngrese su nombre y apellido: ");
			gets(clientes.nombre);
			fflush(stdin);
			
			fwrite(&clientes,sizeof(clientes),1,archC);
			
			// CREAR NODO E INSERTARLO
			p = (struct clientes*)malloc(sizeof(struct clientes));
		    if (p != NULL) {
		    	p->sgte = NULL;
				p->id = clientes.id;
				p->dni = clientes.dni;
				strcpy(p->nombre, clientes.nombre);


		    } else {
		        printf("No hay memoria suficiente para cargar los nodos");
		        
		    }
			
			cargarClientes(&p, &(*tp));
			
			fclose(archC);			
							
		}
	}
}

void cargarClientes(struct clientes **nv, struct clientes **top){
	(*nv)->sgte = (*top);
	(*top) = (*nv);
	(*nv) = NULL;
}


void listarClientes(struct clientes **tope){
	struct clientes *p=NULL, *tp2=NULL;
	
	while(vacia((*tope)) != 1){
		desapilar(&p, &(*tope));
		
		printf("\nID: %d", p->id);
		printf("\nDNI: %ld",p->dni);
		printf("\nNombre: ");
		puts(p->nombre);
		printf("\n----------------");
		
		apilar(&p, &tp2);				
	}
	
	while(vacia(tp2) != 1){
		desapilar(&p, &tp2);
		apilar(&p, &(*tope));		
	}
	
	
}

int vacia(struct clientes *topeP){
	int vac;
	
	if(topeP == NULL){
		vac=1;
	}else{
		vac=0;
	}
		
return vac;
		
}

void desapilar(struct clientes **ds, struct clientes **topeP){
	
	(*ds) = (*topeP);
	(*topeP) = (*topeP)->sgte;
	(*ds)->sgte = NULL;	
}

void apilar(struct clientes **nv, struct clientes **topeP){
	
	(*nv)->sgte = (*topeP);
	(*topeP) = (*nv);
	(*nv) = NULL;	
}
