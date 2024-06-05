#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void altaClientes(struct clientes **tp);
void cargarClientes(struct clientes **nv, struct clientes **top);
void listarClientes(struct clientes **tope);
int vacia(struct clientes *topeP);
void desapilar(struct clientes **ds, struct clientes **topeP);
void apilar(struct clientes **nv, struct clientes **topeP);
void bajaclientes(struct clientes **tope);
void modificarClientes(struct clientes **tope);
void modificarNod(struct clientes **top, int idx);

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
			clientes.estado = 1;
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
				p->estado = 1;
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
		
		if(p->estado == 1){
			printf("\nID: %d", p->id);
			printf("\nDNI: %ld",p->dni);
			printf("\nNombre: ");
			puts(p->nombre);
			printf("\n----------------");			
		}
		
		
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


void bajaclientes(struct clientes **tope){
	FILE *archC=NULL;
	struct clientes *p=NULL, *tp2=NULL;
	int idAux, encontro=0;
	
	fflush(stdin);
	listarClientes(&(*tope));
	printf("\nIngrese el ID del cliente a dar de baja: ");
	scanf("%d", &idAux);
	fflush(stdin);
	
	archC=fopen("clientes.dat","r+b");
	if(archC==NULL){
		printf("\nError al abrir el archivo clientes.dat");
	}
	else{	
		// BUSCAR POR EL ID								
		fread(&clientes, sizeof(clientes),1,archC);
			
		while((!feof(archC))&&(encontro == 0)){
				
			if(clientes.id == idAux){
				clientes.estado = 0;
				fseek(archC,sizeof(clientes)*(-1),SEEK_CUR);
				fwrite(&clientes,sizeof(clientes),1,archC);
				encontro = 1;	
			}else{
				fread(&clientes, sizeof(clientes),1,archC);
			}			
		}
								
			fclose(archC);	
			
		while(vacia((*tope)) != 1){
			desapilar(&p, &(*tope));
		
			if(p->id == idAux){
				free(p);
			}else{
				apilar(&p, &tp2);
			}											
		}
			
		while(vacia(tp2) != 1){
			desapilar(&p, &tp2);
			apilar(&p, &(*tope));		
		}
	}						
}


void modificarClientes(struct clientes **tope){
	int idAux=0;
	
	listarClientes(&(*tope));
	fflush(stdin);
	printf("Ingrese el ID del cliente que desea modificar\n");
	scanf("%d",&idAux);
	fflush(stdin);
	modificarNod(&(*tope),idAux);	
}


void modificarNod(struct clientes **top, int idx){
	FILE *archC=NULL;
	struct clientes *p=NULL, *tp2=NULL;
	int encontro=0;
	
	while(vacia((*top)) != 1){
			desapilar(&p, &(*top));
		
			if(p->id == idx){
				int opcion;
				do {
		        	printf("\n¿Que desea modificar?\n");
		        	printf("1. DNI\n");
		        	printf("2. Nombre\n");
		        	printf("3. Salir\n");
		        	printf("Seleccione una opcion: ");
		        	scanf("%d", &opcion);

		        	switch (opcion) {
		            	case 1:
		                	printf("Ingrese el DNI a modificar: ");
		                	scanf("%ld", &p->dni);
		                	break;
		            	case 2:
		                	printf("Ingrese el nombre a modificar: ");
		                	scanf("%s", p->nombre);
		                	break;
		            	case 3:
		                	printf("Saliendo del menu de modificacion.\n");
		                	break;
		            	default:
		                	printf("Opción no válida.\n");
		                	break;
       				}
    			} while (opcion != 3);
    			
    			archC=fopen("clientes.dat","r+b");
				if(archC==NULL){
					printf("\nError al abrir el archivo clientes.dat");
				}else{	
					// BUSCAR POR EL ID								
					fread(&clientes, sizeof(clientes),1,archC);
			
					while((!feof(archC))&&(encontro == 0)){
				
						if(clientes.id == idx){
							clientes.dni = p->dni;
							strcpy(clientes.nombre, p->nombre);
							
							fseek(archC,sizeof(clientes)*(-1),SEEK_CUR);
							fwrite(&clientes,sizeof(clientes),1,archC);
							encontro = 1;	
						}else{
							fread(&clientes, sizeof(clientes),1,archC);
						}			
					} 					
					fclose(archC);			
    			}    			
			}
			
			apilar(&p, &tp2);								
		}
			
		while(vacia(tp2) != 1){
			desapilar(&p, &tp2);
			apilar(&p, &(*top));		
		}	
}






