#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void altaTecnicos(struct tecnicos **e, struct tecnicos **s);
void listarTecnicos(struct tecnicos **e, struct tecnicos **s);
int vaciaTecnicos(struct tecnicos *s);
void desencolarTecnicos(struct tecnicos **d, struct tecnicos **e, struct tecnicos **s);
void encolarTecnicosH(struct tecnicos **n, struct tecnicos **e, struct tecnicos **s);
void bajaTecnicos(struct tecnicos **e, struct tecnicos **s);
void modificarTecnicos(struct tecnicos **e, struct tecnicos **s);
void buscarDniTecnico(int *encontro,long dniTecnico, int *id);


void altaTecnicos(struct tecnicos **e, struct tecnicos **s){
    struct tecnicos *n = NULL;
    struct tecnicos temp;
    FILE *archivoTecnicos;
	int ultId=0;
	long dniAux = leerDni();
	
	if(dniAux != 0){
		if ((archivoTecnicos = fopen("tecnicos.dat", "a+b")) != NULL) {
        // LEER DATOS
        
        fread(&temp, sizeof(temp),1,archivoTecnicos);
		while(!feof(archivoTecnicos)){
			ultId = temp.id;
			fread(&temp, sizeof(temp),1,archivoTecnicos);
		}
		
		temp.estado=1;
		temp.id = ultId + 1;
        temp.dni = dniAux;
        printf("Ingrese nombre: ");
        fflush(stdin);
        gets(temp.nombre);
		fflush(stdin);
        fwrite(&temp, sizeof(struct tecnicos), 1, archivoTecnicos);
        
        
        // CREAR NODO E INSERTARLO
      		 n = (struct tecnicos*)malloc(sizeof(struct tecnicos));
        	 if (n != NULL) {
			 	n->id = temp.id;
           	 	n->dni = temp.dni;
            	strcpy(n->nombre, temp.nombre);
           		n->sgte = NULL;
           		n->estado=1;
           		encolarTecnicosH(&n,&(*e),&(*s));
       		 }else{
            	printf("No hay memoria suficiente para cargar los nodos");
        	 }
        	 
      		 fclose(archivoTecnicos);
        
   		}else{
     		printf("\nError al abrir el archivo tecnicos.dat");
    	}		
	}
    
}

void bajaTecnicos(struct tecnicos **e, struct tecnicos **s){
	FILE *tec=NULL;	
	struct tecnicos *n = NULL;
	struct tecnicos *eAux=NULL;
	struct tecnicos *sAux=NULL;
	int encontro=0;
	
	fflush(stdin);
	listarTecnicos(&(*e),&(*s));
		
	int idAux = leerId(21);
	fflush(stdin);
	
	if(idAux!=0){
			tec = fopen("tecnicos.dat","r+b");
			if(tec==NULL){
				printf("Error de apertura de archivo tecnicos.dat");
				printf("\n");
			} else {
				fread(&tecnicos, sizeof(tecnicos),1,tec);
		
				while((!feof(tec))&&(encontro==0)){
					if(tecnicos.id==idAux){
						tecnicos.estado=0;
					
						fseek(tec,sizeof(tecnicos)*(-1),SEEK_CUR);
						fwrite(&tecnicos,sizeof(tecnicos),1,tec);
						encontro=1;
					}else{
						fread(&tecnicos, sizeof(tecnicos),1,tec);
					}			
				}
		
				fclose(tec);			
			}	
	
	
	int band= vaciaTecnicos((*s));
		while(band!=0){
			desencolarTecnicos(&n,&(*e),&(*s));	
				if(n->id!=idAux){
					encolarTecnicosH(&n,&eAux,&sAux);
				}else{
					free(n);
				}
				band= vaciaTecnicos((*s));							
		}
		
		band= vaciaTecnicos(sAux);
		while(band!=0){
			desencolarTecnicos(&n,&eAux,&sAux);
			encolarTecnicosH(&n,&(*e),&(*s));
			band= vaciaTecnicos(sAux);
		}
		
	}

}

void modificarTecnicos(struct tecnicos **e, struct tecnicos **s){
	FILE *tec;	
	struct tecnicos *n = NULL;
	struct tecnicos *eAux=NULL;
	struct tecnicos *sAux=NULL;
	int encontro=0;
		
	listarTecnicos(&(*e),&(*s));
	
	int idAux = leerId(22);
	
	
	int band = vaciaTecnicos((*s));
		while(band!=0){
			desencolarTecnicos(&n,&(*e),&(*s));	
				if(n->id==idAux){
					int opcion;
						    do {
						        printf("\n�Que desea modificar?\n");
						        printf("1. DNI\n");
						        printf("2. Nombre\n");
						        printf("3. Salir\n");
						        printf("Seleccione una opcion: ");
						        scanf("%d", &opcion);
						
						        switch (opcion) {
						            case 1:
						                printf("Ingrese el nuevo DNI: ");
						                scanf("%ld", &n->dni);
						                break;
						            case 2:
						                printf("Ingrese el nuevo nombre: ");
						                scanf("%s", n->nombre);
						                break;
						            case 3:
						                printf("Saliendo del menu de modificacion.\n");
						                break;
						            default:
						                printf("Opci�n no valida.\n");
						                break;
						        }
						    } while (opcion != 3);
						    
						    tec = fopen("tecnicos.dat","r+b");
								if(tec==NULL){
									printf("Error de apertura de archivo tecnicos.dat");
									printf("\n");
								} else {
									fread(&tecnicos, sizeof(tecnicos),1,tec);
									while((!feof(tec)) && (encontro == 0)){
											if(tecnicos.id==idAux){
												tecnicos.dni=n->dni;
												strcpy(tecnicos.nombre,n->nombre);
												
												fseek(tec,sizeof(tecnicos)*(-1),SEEK_CUR);
												fwrite(&tecnicos,sizeof(tecnicos),1,tec);
												encontro = 1;
											}else{
												fread(&tecnicos, sizeof(tecnicos),1,tec);
											}
										
									}
					
								}
								fclose(tec);
				}
				encolarTecnicosH(&n,&eAux,&sAux);
				band= vaciaTecnicos((*s));			
		}
		
	    band = vaciaTecnicos(sAux);
		while(band!=0){
			desencolarTecnicos(&n,&eAux,&sAux);
			encolarTecnicosH(&n,&(*e),&(*s));
			band = vaciaTecnicos(sAux);
		}	
}

void listarTecnicos(struct tecnicos **e, struct tecnicos **s){
	 struct tecnicos *n = NULL;
	 struct tecnicos *eAux=NULL;
	 struct tecnicos *sAux=NULL;
	 
 	 int band= vaciaTecnicos((*s));
		while(band!=0){
			desencolarTecnicos(&n,&(*e),&(*s));	
			if(n->estado==1){
				printf("\nID: %d", n->id);
		        printf("\nDNI: %ld", n->dni);
		        printf("\nNombre: %s", n->nombre);
				printf("\n----------------");
			}		
			encolarTecnicosH(&n,&eAux,&sAux);
			band= vaciaTecnicos((*s));
		}
		
		band= vaciaTecnicos(sAux);
		while(band!=0){
			desencolarTecnicos(&n,&eAux,&sAux);
			encolarTecnicosH(&n,&(*e),&(*s));
			band= vaciaTecnicos(sAux);
		}
	
}

int vaciaTecnicos(struct tecnicos *s){
	if(s==NULL){
        return 0;
    }else{
        return 1;
    }
}

void desencolarTecnicos(struct tecnicos **d, struct tecnicos **e, struct tecnicos **s){
    (*d) = (*s);
	(*s)=(*s)->sgte;
	if (*s == NULL) {
		(*e) = NULL;
	}
}

void encolarTecnicosH(struct tecnicos **n, struct tecnicos **e, struct tecnicos **s){
	if(*e == NULL) {
		*s = *n;
	} else{
		(*e)->sgte = *n;		
	}
	(*e) = (*n);
	(*e)->sgte=NULL;
	(*n) = NULL;
}

void buscarDniTecnico(int *encontro,long dniTecnico, int *id){
	FILE *tec=NULL;
	
	tec = fopen("tecnicos.dat","r+b");
		if(tec==NULL){
			printf("Error de apertura de archivo tecnicos.dat");
			printf("\n");
		} else {
			fread(&tecnicos, sizeof(tecnicos),1,tec);
			
			while((!feof(tec))&&(*encontro==0)){
					if(tecnicos.dni==dniTecnico){
						(*id)=tecnicos.id;
						(*encontro)=1;
					}else{
						fread(&tecnicos, sizeof(tecnicos),1,tec);
					}			
			}
			
			fclose(tec);			
		}
}
