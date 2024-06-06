#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void altaTrabajos(struct trabajos **L, struct tareas *Ltar, struct materiales *rMat, struct stock *rStock, struct opciones *r, struct tecnicos **e, struct tecnicos **s, struct clientes **tope );
struct trabajos* insertarLES(struct trabajos *L,struct trabajos *nv);
void buscarDniTecnico(int *encontro,long dniTecnico, int *id);
void listarTecnicos(struct tecnicos **e, struct tecnicos **s);
void listarClientes(struct clientes **tope);
void buscarDniCliente(int *encontro, long dniCliente,int *id);
void altaClientes(struct clientes **tp);
void listarTrabajosNoFinalizados(struct trabajos *L );
float obtenerCostoBase(int idOpcion,struct opciones *r);
float precioMateriales(int idOpcion, struct materiales *rMat, struct stock *rStock);
void listarTrabajosFinalizados(struct trabajos *L);
void bajaTrabajos(struct trabajos **L);
void modificarTrabajos(struct trabajos **L,struct tecnicos **e, struct tecnicos **s);


void altaTrabajos(struct trabajos **L, struct tareas *Ltar, struct materiales *rMat, struct stock *rStock, struct opciones *r, struct tecnicos **e, struct tecnicos **s, struct clientes **tope ){
    FILE *archivoTrabajos;
    struct trabajos *n = NULL;
    struct trabajos temp;
	int band=0,ultId=0, band1=0;
	int encontro=0;
	long dniCliente=0.0, dniTecnico=0.0;
	float materiales=0 , costoBase=0;
	int opcion=0,opcion2=0;

    if((archivoTrabajos = fopen("trabajos.dat", "a+b")) != NULL){
	        // LEER DATOS
	        fread(&temp, sizeof(temp),1,archivoTrabajos);
			while(!feof(archivoTrabajos)){
				ultId = temp.id;
				fread(&temp, sizeof(temp),1,archivoTrabajos);
			}
			temp.id = ultId + 1;
			
			//OPCIONES
			system("cls");
			puts("OPCIONES----------------------------------\n");
			listarOpciones(Ltar,rMat,rStock);
			printf("Seleccione el ID de la opcion que desea usar: ");
			scanf("%d",&temp.idOpcion);
	        
	        printf("Ingrese altura: ");
	        scanf("%d", &temp.altura);
	
	        if(temp.altura>4){
	        	band=1;
	        }
	        
	        printf("Ingrese ubicacion: ");
	        scanf("%s", temp.ubicacion);
	        
			//CLIENTE
			system("cls");
			puts("CLIENTES----------------------------------\n");
			listarClientes(&(*tope));
	        do {
	        printf("\nMenu:\n");
	        printf("1. Usar un cliente de la lista\n");
	        printf("2. Registrar un nuevo cliente\n");
	        printf("3. Salir\n");
	        printf("Ingrese una opción: ");
	        scanf("%d", &opcion);
				switch (opcion){
					case 1:
				        printf("Ingrese DNI del Cliente: ");
				        scanf("%ld",&dniCliente);
				        buscarDniCliente(&encontro,dniCliente,&temp.idCliente);
							if(encontro==0){
									do{
										system("cls");
										printf("El cliente no está registrado.\n");
							            printf("1. Ingresar DNI nuevamente\n");
							            printf("2. Registrar nuevo cliente\n");
							            printf("Ingrese una opción: ");
							            scanf("%d", &opcion2);
							
							             switch (opcion2) {
							               case 1:
							                   opcion=1;
							                   break;
							               case 2:
							                   opcion=2;
							                   break;
							               default:
							                   printf("Opción no válida. Intente de nuevo.\n");
							             }
							                            
							            	if(opcion==1){
							                	break;
							                }else if(opcion==2){
							                	break;	
							                }
												
									}while (encontro == 0 && opcion2 != 2);
							}else{
										band1=1;
							}
				                break;
				    case 2:
				        altaClientes(&(*tope));
				        break;
				    case 3:
				        printf("Saliendo del programa...\n");
				        break;
				    default:
				        printf("Opción no válida. Intente de nuevo.\n");
				
				}				
			        
	    	} while (band1==0 && opcion != 3);
			
		//TECNICOS
		system("cls");
		puts("TECNICOS----------------------------------\n");
	    encontro=0;
	    listarTecnicos(&(*e),&(*s));
		printf("Ingrese DNI del Tecnico: ");
		scanf("%ld",&dniTecnico);
		buscarDniTecnico(&encontro,dniTecnico,&temp.idTecnico);
			do {
				if(encontro==0){
					printf("El dni del Tecnico que usted ingreso no existe.\n");
					printf("1. Ingresar DNI nuevamente\n");
					printf("2. Salir y asignar luego\n");
					printf("Ingrese una opción: ");
					scanf("%d", &opcion2);
					
						switch (opcion2) {
					        case 1:
					        	printf("Ingrese DNI del Tecnico: ");
								scanf("%ld",&dniTecnico);
								buscarDniTecnico(&encontro,dniTecnico,&temp.idTecnico);
					        	break;
					       case 2:
					            printf("Saliendo del programa...\n");
			                	break;
					       default:
					             printf("Opción no válida. Intente de nuevo.\n");
					    }
				}
			} while (opcion2 != 2 && encontro == 0);
								
			                
			materiales = precioMateriales(temp.idOpcion,rMat,rStock);
	        costoBase = obtenerCostoBase(temp.idOpcion,r);
	        
	        if(band==1){
	        	costoBase = costoBase*1.20;
	        	temp.costoTotal=materiales+costoBase;
	        }else{
	        	temp.costoTotal=materiales+costoBase;
	        }
	        
	        //system("cls");
	        printf("El trabajo esta finalizado? (1 para si, 0 para no): ");
	        scanf("%d", &temp.finalizado);
	        	if(temp.finalizado==1){
	        		printf("Ingrese dia de finalizacion: ");
			        scanf("%d", &temp.fechaFin.dia);
			        printf("Ingrese mes de finalizacion: ");
			        scanf("%d", &temp.fechaFin.mes);
			        printf("Ingrese anio de finalizacion: ");
			        scanf("%d", &temp.fechaFin.anio);
	        	}
	
	        // Guardar en el archivo
	        fwrite(&temp, sizeof(struct trabajos), 1, archivoTrabajos);
	        
	        // CREAR NODO E INSERTARLO
	        n = (struct trabajos*)malloc(sizeof(struct trabajos));
	        if (n != NULL) {
	            n->altura = temp.altura;
	            n->costoTotal = temp.costoTotal;
	            n->fechaFin.dia = temp.fechaFin.dia;
	            n->fechaFin.mes = temp.fechaFin.mes;
	            n->fechaFin.anio = temp.fechaFin.anio;
	            n->finalizado = temp.finalizado;
	            n->id = temp.id;
	            n->idCliente = temp.idCliente;
	            n->idTecnico = temp.idTecnico;
	            n->idOpcion = temp.idOpcion;
	            strcpy(n->ubicacion,temp.ubicacion);
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

//modificar altura, ubicacion, tecnico

void modificarTrabajos(struct trabajos **L,struct tecnicos **e, struct tecnicos **s){
	int idAux=0,encontro=0;
	FILE *trab;
	
	listarTrabajosNoFinalizados(*L);
	printf("\nIngrese el ID del trabajo que desea dar por modificar");
	scanf("%d",&idAux);
	struct trabajos *R=*L;
	
	while (R != NULL) {
	    if (R->id == idAux) {
	    		int opcion=0;
			        do {
						printf("\n¿Qué desea modificar?\n");
						printf("1. Altura\n");
						printf("2. Ubicacion\n");
						printf("3. Asignar a otro tecnico\n");
						printf("4. Salir\n");
						printf("Seleccione una opción: ");
						scanf("%d", &opcion);
										
							switch (opcion) {
								case 1:
									printf("Ingrese la nueva Altura: ");
									scanf("%d", &R->altura);
									break;
								case 2:
									printf("Ingrese la nueva ubicacion: ");
									scanf("%s", R->ubicacion);
									break;
								case 3:
									puts("TECNICOS----------------------------------\n");
									    long dniTecnico;
									    listarTecnicos(&(*e),&(*s));
										printf("Ingrese DNI del Tecnico: ");
										scanf("%ld",&dniTecnico);
										buscarDniTecnico(&encontro,dniTecnico,&R->idTecnico);
										if(encontro==0){
											puts("DNI incorrecto, ingrese nuevamente\n");
										}
									break;
								case 4:
									printf("Saliendo del menú de modificación.\n");
									break;
								default:
									printf("Opción no válida.\n");
									break;
							}
					} while (opcion != 4);
	           
	           		encontro=0;
				    if((trab = fopen("trabajos.dat", "r+b")) != NULL){
							fread(&trabajos, sizeof(trabajos),1,trab);
								while((!feof(trab)) && (encontro==0)){
									if(trabajos.id==idAux){
											trabajos.altura = R->altura;
											trabajos.idTecnico = R->idTecnico;
											strcpy(trabajos.ubicacion,R->ubicacion);
											encontro=1;
											fseek(trab,sizeof(trabajos)*(-1),SEEK_CUR);
											fwrite(&trabajos,sizeof(trabajos),1,trab);
									}else{
										fread(&trabajos, sizeof(trabajos),1,trab);
									}	
								}
								fclose(trab);
					}else{
						printf("\nError al abrir el archivo trabajos.dat");
					}
	           
	    }
    	R = R->sgte;
	}
	
	
	
}

void bajaTrabajos(struct trabajos **L){
	int idAux=0,encontro=0;
	FILE *trab;
	
	listarTrabajosNoFinalizados(*L);
	printf("\nIngrese el ID del trabajo que desea dar por finalizado");
	scanf("%d",&idAux);
	
	if((trab = fopen("trabajos.dat", "r+b")) != NULL){
		fread(&trabajos, sizeof(trabajos),1,trab);
		
				while((!feof(trab)) && (encontro==0)){
					if(trabajos.id==idAux){
						trabajos.finalizado=1;
						printf("Ingrese dia de finalizacion: ");
				        scanf("%d", &trabajos.fechaFin.dia);
				        printf("Ingrese mes de finalizacion: ");
				        scanf("%d", &trabajos.fechaFin.mes);
				        printf("Ingrese anio de finalizacion: ");
				        scanf("%d", &trabajos.fechaFin.anio);
						encontro=1;
						fseek(trab,sizeof(trabajos)*(-1),SEEK_CUR);
						fwrite(&trabajos,sizeof(trabajos),1,trab);
					}else{
						fread(&trabajos, sizeof(trabajos),1,trab);
					}	
				}
		fclose(trab);
	}else{
		 printf("\nError al abrir el archivo trabajos.dat");
	}
	
	struct trabajos *R=*L;
	
	while (R != NULL) {
    if (R->id == idAux) {
        R->finalizado = 1;
        R->fechaFin.dia = trabajos.fechaFin.dia;
        R->fechaFin.mes = trabajos.fechaFin.mes;
        R->fechaFin.anio = trabajos.fechaFin.anio;
    }
    R = R->sgte;
	}
	
	
}

void listarTrabajosFinalizados(struct trabajos *L){
	if(L!=NULL){
		if(L->finalizado==1){
			puts("\n");
			printf("\nID trabajo: %d",L->id);
			printf("\nID cliente: %d",L->idCliente);
			printf("\nID opcion: %d",L->idOpcion);
			printf("\nID tecnico %d",L->idTecnico);
			printf("\nUbicacion: %s",L->ubicacion);
			fflush(stdin);
			printf("\nAltura del trabajo: %d",L->altura);
			printf("\nCosto total del trabajo: %f",L->costoTotal);
			printf("\nFECHA:");
			printf("\nDIA : %d",L->fechaFin.dia);
			printf("\nMES : %d",L->fechaFin.mes);
			printf("\nAÑO : %d",L->fechaFin.anio);
		}
		listarTrabajosFinalizados(L->sgte);
	}
	
}

void listarTrabajosNoFinalizados(struct trabajos *L ){
	if(L!=NULL){
		if(L->finalizado==0){
			puts("\n");
			printf("\nID trabajo: %d",L->id);
			printf("\nID cliente: %d",L->idCliente);
			printf("\nID opcion: %d",L->idOpcion);
			printf("\nID tecnico %d",L->idTecnico);
			printf("\nUbicacion: %s",L->ubicacion);
			fflush(stdin);
			printf("\nAltura del trabajo: %d",L->altura);
			printf("\nCosto total del trabajo: %f",L->costoTotal);
		}
		listarTrabajosNoFinalizados(L->sgte);
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

