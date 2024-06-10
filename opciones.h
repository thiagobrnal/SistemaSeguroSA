#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//OPCIONES
void altaOpciones(struct opciones **ini, struct tareas **Ltar,struct stock *Rstc, struct materiales **Lmat);
struct opciones* nuevoNodo(int id, char* nombre, float costoBase);
void bajaOpcion(struct opciones **ini, struct tareas **Ltar, struct materiales **rMat, struct stock *rStock);
void modificarOpcion(struct opciones *ini, struct tareas **Ltar, struct materiales **rMat, struct stock *rStock);
void listarOpciones(struct tareas *Ltar, struct materiales *rMat, struct stock *rStock);
float obtenerCostoBase(int idOpcion,struct opciones *r);

void listarOpcionesTarMat(struct tareas *Ltar, struct materiales *rMat, struct stock *rStock);
void listarOpcionesTarMatPorId(int idOpc,struct tareas *Ltar, struct materiales *rMat, struct stock *rStock);

void crearPunteroRanking(struct trabajos *Ltrab, struct opciones *L);
void opcionesMasVendidas(struct opciones *L, struct trabajos *Ltrab,struct ranking *Lranking);
struct ranking *insertarRanking(struct ranking *n, struct ranking *r);
void mostrarRanking(struct ranking *r);
struct ranking *liberarRanking(struct ranking *ini);
void obtenerCantidadDeVentas(struct trabajos *L, int id,int *cont,struct fech fechaInicio,struct fech fechaFin);

int compararFechas(struct fech fechaInicio, struct fech fechaFin);
int fechaEstaEntre(struct fech fechaBuscar, struct fech fechaInicio, struct fech fechaFin);

struct opciones* nuevoNodo(int id, char* nombre, float costoBase) {
	
    struct opciones* nodo = (struct opciones*)malloc(sizeof(struct opciones));
    
    if(nodo==NULL){
    	return NULL;
	}else{
		nodo->id = id;
    	strcpy(nodo->nombre, nombre);
    	nodo->costoBase = costoBase;
    	nodo->sgte = NULL;
    	nodo->estado = 1;
	}
	return nodo;
}

void altaOpciones(struct opciones **ini, struct tareas **Ltar,struct stock *Rstc, struct materiales **Lmat){
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
        opciones.estado=1;
        
    	// Leer datos
    	printf("Ingrese el nombre de la opcion: ");
    	gets(opciones.nombre);
    	fflush(stdin);
   		
   		do{
   			printf("Ingrese el costo de esta operacion (sin mano de obra ni materiales): ");
    		scanf("%f", &opciones.costoBase);
    		fflush(stdin);
    		if(opciones.costoBase < 0.1){
    			printf("intente de nuevo con un numero valido mayor a 0.\n");
			}
		}while(opciones.costoBase < 0.1);
		
    	
    	
    	fwrite(&opciones, sizeof(opciones), 1, arch1);
    	printf("\nOpcion cargada exitosamente\n");
    	
    	
    	//Creo el nodo
    	n = nuevoNodo(opciones.id, opciones.nombre, opciones.costoBase);
    	if (n == NULL) {
    	    printf("No hay memoria.\n");
    	    fclose(arch1);
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

    	char auxiliar, auxiliar2;
    	int idOp = 0;
    	idOp = ultId + 1;
    	printf("\n\t\tTareas\n");
    	do{
    		altaTarea(&(*Ltar),idOp);
    		fflush(stdin);

    	    printf("\nDesea ingresar otra tarea? y/n: ");
   	    	scanf(" %c", &auxiliar);  // El espacio antes de %c es para consumir cualquier carácter de nueva línea residual
    	    fflush(stdin);

    	} while (auxiliar == 'y' || auxiliar == 'Y');
    
    	printf("\n\t\tMateriales\n");
    	do{
    		altaMateriales(&(*Lmat),idOp,Rstc);
   		 	fflush(stdin);
		
    	    printf("\nDesea ingresar otro material? y/n: ");
    	    scanf(" %c", &auxiliar2);  // El espacio antes de %c es para consumir cualquier carácter de nueva línea residual
   		    fflush(stdin);
    	} while (auxiliar2 == 'y' || auxiliar2 == 'Y');

	}
}

void bajaOpcion(struct opciones **ini, struct tareas **Ltar, struct materiales **rMat, struct stock *rStock) {
    int band = 0;

    if (*ini == NULL) {
        printf("La lista de opciones está vacía.\n");
        return;
    }
    listarOpcionesTarMat(*Ltar,*rMat,rStock);

    int idOp;
    printf("\nADVERTENCIA: Al eliminar una opcion se borran las tareas y materiales relacionadas a esta.");
    printf("\nIngrese el ID de la opción que desea eliminar: ");
    scanf("%d", &idOp);
    fflush(stdin);

    struct opciones *actual = *ini;
    struct opciones *anterior = NULL;

    while (actual != NULL && actual->id != idOp) {
        anterior = actual;
        actual = actual->sgte;
    }
    if (actual == NULL) {
        printf("La opción con ID %d no se encontró en la lista.\n", idOp);
        return;
    }
    bajaTarea(idOp,Ltar);
    bajaMaterial(idOp,rMat);

    FILE *arch1 = fopen("opciones.dat", "r+b");
    if (arch1 == NULL) {
        printf("\nError al abrir el archivo opciones.dat");
        return;
    } else {
        fread(&opciones, sizeof(struct opciones), 1, arch1);
        while (!feof(arch1) && band == 0) {
            if (opciones.id == idOp) {
                fseek(arch1, sizeof(struct opciones) * (-1), SEEK_CUR);
                opciones.estado = 0;
                fwrite(&opciones, sizeof(struct opciones), 1, arch1);
                band = 1;
            } else {
                fread(&opciones, sizeof(struct opciones), 1, arch1);
            }
        }
        fclose(arch1);

        if (anterior == NULL) {
            *ini = actual->sgte;
        } else {
            anterior->sgte = actual->sgte;
        }

        free(actual);
    }

    printf("Opción con ID %d eliminada exitosamente.\n", idOp);
}

void modificarOpcion(struct opciones *ini, struct tareas **Ltar, struct materiales **rMat, struct stock *rStock) {
    if (ini == NULL) {
        printf("La lista de opciones está vacia.\n");
        return;
    }
    listarOpcionesTarMat(*Ltar,*rMat,rStock);

    int idOp;
    printf("\nIngrese el ID de la opcion para modificar (Opcion, Tarea o Material): ");
    scanf("%d", &idOp);
    fflush(stdin);
    if(idOp == 0){
    	return;
	}

    struct opciones *actual = ini;
    while (actual != NULL && actual->id != idOp) {
        actual = actual->sgte;
    }

    if (actual == NULL) {
        printf("La opcion con ID %d no se encontro en la lista.\n", idOp);
        return;
    }
    
    int fBand = 1;
    char fop;
    while(fBand != 0){
    	system("cls");
    	listarOpcionesTarMatPorId(idOp,*Ltar,*rMat,rStock);
    	printf("\n¿Que desea modificar de la opcion %d?\n",idOp);
        printf("1. Opcion\n");
        printf("2. Tarea\n");
        printf("3. Material\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%c", &fop);
        fflush(stdin);
        
        switch (fop) {
            case '0':
                printf("Saliendo del menu de modificacion.\n");
                fBand = 0;
                break;
            case '1':{
                	int bandOp = 1, band = 0;
    				char opcion;
    				while (bandOp != 0) {
        				printf("\n¿Que desea modificar?\n");
        				printf("1. Nombre de la opcion\n");
        				printf("2. Costo base de la opcion\n");
       					printf("0. Salir\n");
        				printf("Seleccione una opcion: ");
        				scanf("%c", &opcion);
        				fflush(stdin);

        				switch (opcion) {
            				case '0':
                				printf("Saliendo del menu de modificacion.\n");
                				bandOp = 0;
                			break;
            				case '1':
                				printf("Ingrese el nuevo nombre de la opcion: ");
                				gets(actual->nombre);
                				fflush(stdin);
                				break;
            				case '2':
            					do{
   									printf("Ingrese el nuevo costo base de la opcion: ");
                					scanf("%f", &actual->costoBase);
                					fflush(stdin);
    								if(actual->costoBase < 0.1){
    									printf("intente de nuevo con un numero valido mayor a 0.\n");
									}
								}while(actual->costoBase < 0.1);
                				break;
            				default:
                				printf("Opcion no válida.\n");
                			break;
        				}
    			}

    			FILE *arch1 = fopen("opciones.dat", "r+b");
    			if (arch1 == NULL) {
        			printf("\nError al abrir el archivo opciones.dat");
        			return;
    			} else {
        			fread(&opciones, sizeof(struct opciones), 1, arch1);
        			while (!feof(arch1) && band == 0) {
            			if (opciones.id == idOp) {
                			strcpy(opciones.nombre, actual->nombre);
                			opciones.costoBase = actual->costoBase;
                			fseek(arch1, sizeof(struct opciones) * (-1), SEEK_CUR);
                			fwrite(&opciones, sizeof(struct opciones), 1, arch1);
                			band = 1;
            			} else {
                			fread(&opciones, sizeof(struct opciones), 1, arch1);
            			}
					}
        			fclose(arch1);
    			}
    		}
                break;
                
            case '2':{
				
                int tarBand = 1;
    			char opTar;
    				while(tarBand != 0){
    					system("cls");
    					listarOpcionesTarMatPorId(idOp,*Ltar,*rMat,rStock);
    					printf("\n¿Que desea hacer en Tareas?\n",idOp);
        				printf("1. Modificar\n");
        				printf("2. Eliminar\n");
        				printf("3. Alta\n");
        				printf("0. Volver\n");
        				printf("Seleccione una opcion: ");
        				scanf("%c", &opTar);
        				fflush(stdin);
        				
        				switch (opTar) {
            				case '0':
                				printf("Saliendo del menu de modificacion.\n");
                				tarBand = 0;
                			break;
            				case '1':
                				modificarTarea(*Ltar,idOp);
                				break;
            				case '2':
                				bajaTarea(idOp,&(*Ltar));
                				break;
                			case '3':
                				altaTarea(&(*Ltar),idOp);
                			break;
            				default:
                				printf("Opcion no valida.\n");
                			break;
                		}
                	}
            break;
        	}
            case '3':{
                int matBand = 1;
    			char opMat;
    				while(matBand != 0){
    					system("cls");
    					listarOpcionesTarMatPorId(idOp,*Ltar,*rMat,rStock);
    					printf("\n¿Que desea hacer en Materiales?\n",idOp);
        				printf("1. Modificar\n");
        				printf("2. Eliminar\n");
        				printf("3. Alta\n");
        				printf("0. Volver\n");
        				printf("Seleccione una opcion: ");
        				scanf("%c", &opMat);
        				fflush(stdin);
        				
        				switch (opMat) {
            				case '0':
                				printf("Saliendo del menu de modificacion.\n");
                				matBand = 0;
                			break;
                			case '1':
                				modificarMaterial(*rMat,idOp,rStock);
                				break;
            				case '2':
                				bajaMaterial(idOp,&(*rMat));
                				break;
                			case '3':
                				altaMateriales(&(*rMat),idOp,rStock);
                			break;
            				default:
                				printf("Opcion no válida.\n");
                			break;
                		}
                	}
            break;
        	}
            default:
                printf("Opcion no valida.\n");
                break;
        }
	}

}

//Listar Opciones
//id,nombre,hora = duracionTareasH(idOpcion), min = duracionTareasM(idOpcion), costoBase + 20% si "trabajos.altura>=4", materiales.cantidad * stock.precio, trabajos.costoTotal

void listarOpcionesTarMat(struct tareas *Ltar, struct materiales *rMat, struct stock *rStock){
	FILE *arch1;
	int hora, min;
	float precioMat=0,costoTotal=0;
	
	
	arch1=fopen("opciones.dat","rb");
	if(arch1==NULL){
		printf("\nError al abrir el archivo opciones.dat");
	}else{
		fread(&opciones, sizeof(opciones),1,arch1);
    	while(!feof(arch1)){
    		if(opciones.estado == 1){
    			printf("\n%d -",opciones.id);
    			printf(" Nombre: %s ",opciones.nombre);
    			sumaHorasMinutosTareas(opciones.id,Ltar);
    			printf(" Costo: $%.2f",opciones.costoBase);
    			precioMat = precioMateriales(opciones.id,rMat,rStock);
    			printf(" Costo de materiales: $%.2f",precioMat);
    			costoTotal = precioMat + opciones.costoBase;
    			printf(" Costo Total: $%.2f",costoTotal);
    			
    			buscarTareasPorId(opciones.id,Ltar);
    			buscarMaterialesPorId(opciones.id,rMat);
    			printf("\n-----------------------------------------------------------------------------------------------");	
			}
    		
			fread(&opciones, sizeof(opciones),1,arch1);
		}
		fclose(arch1);
	}
}

void listarOpcionesTarMatPorId(int idOpc,struct tareas *Ltar, struct materiales *rMat, struct stock *rStock){
	FILE *arch1;
	int hora, min;
	float precioMat=0,costoTotal=0;
	
	
	arch1=fopen("opciones.dat","rb");
	if(arch1==NULL){
		printf("\nError al abrir el archivo opciones.dat");
	}else{
		fread(&opciones, sizeof(opciones),1,arch1);
    	while(!feof(arch1)){
    		if((opciones.estado == 1) && (opciones.id == idOpc)){
    			printf("\n%d -",opciones.id);
    			printf(" Nombre: %s ",opciones.nombre);
    			sumaHorasMinutosTareas(opciones.id,Ltar);
    			printf(" Costo: $%.2f",opciones.costoBase);
    			precioMat = precioMateriales(opciones.id,rMat,rStock);
    			printf(" Costo de materiales: $%.2f",precioMat);
    			costoTotal = precioMat + opciones.costoBase;
    			printf(" Costo Total: $%.2f",costoTotal);
    			
    			buscarTareasPorId(opciones.id,Ltar);
    			buscarMaterialesPorId(opciones.id,rMat);
    			printf("\n-----------------------------------------------------------------------------------------------");	
			}
    		
			fread(&opciones, sizeof(opciones),1,arch1);
		}
		fclose(arch1);
	}
}

void listarOpciones(struct tareas *Ltar, struct materiales *rMat, struct stock *rStock){
	FILE *arch1;
	int hora, min;
	float precioMat=0,costoTotal=0;
	
	
	arch1=fopen("opciones.dat","rb");
	if(arch1==NULL){
		printf("\nError al abrir el archivo opciones.dat");
	}else{
		fread(&opciones, sizeof(opciones),1,arch1);
    	while(!feof(arch1)){
    		if(opciones.estado == 1){
    			printf("\n%d -",opciones.id);
    			printf(" Nombre: %s ",opciones.nombre);
    			sumaHorasMinutosTareas(opciones.id,Ltar);
    			printf(" Costo: $%.2f",opciones.costoBase);
    			precioMat = precioMateriales(opciones.id,rMat,rStock);
    			printf(" Costo de materiales: $%.2f",precioMat);
    			costoTotal = precioMat + opciones.costoBase;
    			printf(" Costo Total: $%.2f",costoTotal);
    			printf("\n-----------------------------------------------------------------------------------------------");	
			}
    		
			fread(&opciones, sizeof(opciones),1,arch1);
		}
		fclose(arch1);
	}
}

float obtenerCostoBase(int idOpcion,struct opciones *r){
	float costo = 0;
	
	while(r != NULL){
		if(r->id == idOpcion){
			costo = r->costoBase;
		}
		r= r->sgte;
			
	}
	return costo;
}

void crearPunteroRanking(struct trabajos *Ltrab, struct opciones *L){
	struct ranking *Lranking=NULL;
	Lranking = (struct ranking*) malloc (sizeof(struct ranking));
		if(Lranking!=NULL){
			Lranking->sgte=NULL;
			opcionesMasVendidas(L,Ltrab,Lranking);
		}else{
			printf("\nNo hay suficiente memoria para mostrar las opciones mas vendidas");
		}
	
}

void opcionesMasVendidas(struct opciones *L, struct trabajos *Ltrab,struct ranking *Lranking){
	int cont=0,band=0;
	char opcion;
	struct fech fechaInicio;
	struct fech fechaFin;
	do{
		printf("\nIngrese la fecha de inicio con numeros.");
		printf("\nDia:");
		scanf("%d", &fechaInicio.dia);
		printf("Mes:");
		scanf("%d", &fechaInicio.mes);
		printf("A%co:", 164);
		scanf("%d", &fechaInicio.anio);
		printf("\nIngrese la fecha de final con numeros.");
		printf("\nDia:");
		scanf("%d", &fechaFin.dia);
		printf("Mes:");
		scanf("%d", &fechaFin.mes);
		printf("A%co:", 164);
		scanf("%d", &fechaFin.anio);
		
		fflush(stdin);
		
		printf("\nFecha de Inicio: %d/%d/%d",fechaInicio.dia,fechaInicio.mes,fechaInicio.anio);
		printf("\nFecha de Fin: %d/%d/%d",fechaFin.dia,fechaFin.mes,fechaFin.anio);
		printf("\n----------------------");
		printf("\nEsto es correcto? s/n");
		printf("\n----------------------\n");
		scanf("%c", &opcion);
		fflush(stdin);
		
		if(opcion == 's'){
			band= 1;
		}
	}while(band==0);
	
	if((compararFechas(fechaInicio,fechaFin))>0){
		puts("Las fechas no son validas.");
	}else{    
			while(L!=NULL){
				obtenerCantidadDeVentas(Ltrab,L->id,&cont,fechaInicio,fechaFin); 
					if(cont!=0){
						struct ranking *n = NULL;
						n = (struct ranking*) malloc (sizeof(struct ranking));
							if(n!=NULL){
								n->idOp=L->id;
								strcpy(n->nombre,L->nombre);
								n->ventas=cont;
								n->sgte=NULL;
								Lranking=insertarRanking(n,Lranking);
							}else{
								printf("\nNo hay suficiente memoria para mostrar las opciones mas vendidas");
							}
							
					}
				L=L->sgte;
				cont=0;	
			}
				
	}
		
	
	
		mostrarRanking(Lranking);
		Lranking=liberarRanking(Lranking);
}

struct ranking *insertarRanking(struct ranking *n, struct ranking *r){
	if(r!=NULL){
		if((n->ventas)>(r->ventas)){
			n->sgte=r;
			r=n;
		}else{
			r->sgte=insertarRanking(n,r->sgte);
		}
	}else{
		r=n;
	}
	return r;
}

void mostrarRanking(struct ranking *r){
	int cont=1;
	
	while((r!=NULL)&&(cont!=5)){
		if(r->ventas!=0){
			printf("\nTOP %d------------------\n",cont);
			printf("\nNombre de la opcion: %s",r->nombre);
			printf("\nCantidad de ventas: %d\n",r->ventas);	
		}
		cont++;
		r=r->sgte;
	}
	
}

struct ranking *liberarRanking(struct ranking *ini){
	struct ranking *aux=NULL;
	while(ini!=NULL){
		aux=ini;
		ini=ini->sgte;
		aux->sgte=NULL;
		free(aux);
	}
	return NULL;
}


void buscarNombre(struct opciones *Lop, int idx){
	while(Lop!=NULL){
		if(Lop->id == idx){
			printf("\nOpcion: %s", Lop->nombre);		
		}	
		
		Lop = Lop->sgte;
	}
}


int compararFechas(struct fech fechaInicio, struct fech fechaFin) {
    if (fechaInicio.anio < fechaFin.anio) {
        return -1;
    } else if (fechaInicio.anio > fechaFin.anio) {
        return 1;
    } else {
        if (fechaInicio.mes < fechaFin.mes) {
            return -1;
        } else if (fechaInicio.mes > fechaFin.mes) {
            return 1;
        } else {
            if (fechaInicio.dia < fechaFin.dia) {
                return -1;
            } else if (fechaInicio.dia > fechaFin.dia) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

int fechaEstaEntre(struct fech fechaBuscar, struct fech fechaInicio, struct fech fechaFin) {
    return (compararFechas(fechaBuscar, fechaInicio) >= 0 && compararFechas(fechaBuscar, fechaFin) <= 0);
}



