#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//includes propios del sistema
#include "structs.h"
#include "CARGA.h"
#include "stock.h"
#include "tareas.h"
#include "materiales.h"
#include "opciones.h"
#include "trabajos.h"
#include "tecnicos.h"
#include "clientes.h"


//Funciones del Menu

void menuOpciones(struct opciones **ini, struct tareas **iniTarea, struct materiales **Lmat, struct stock *Rstc);
void menuStockMateriales(struct stock **Rstc);
void menuTrabajos(struct trabajos **Ltrab,struct tareas *Ltar,struct materiales *Lmat,struct stock *Rstc ,struct opciones *Lop);
void subMenuTrabajos();
void menuTecnicos(struct tecnicos **Etec,struct tecnicos **Stec);
void menuClientes(struct clientes **TPclt);

int main(){
	
	struct opciones *Lop=NULL;  
	struct tareas *Ltar=NULL;
	struct materiales *Lmat=NULL;
	struct stock *Rstc=NULL;
	struct trabajos *Ltrab=NULL;
	struct clientes *TPclt=NULL;
	struct tecnicos *Etec=NULL, *Stec=NULL;
	
	
	CARGA(&Lop, &Ltar, &Lmat, &Rstc, &Ltrab, &TPclt, &Etec, &Stec);
	

	
	//carga
	
	char op;
	int band = 1;
	
	
	while(band!= 0){
		
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\t\tSistemaSeguroSA\n");
		printf("-------------------------------------------------------------------------------\n");
		
		printf("1- Opciones.\n");
		printf("2- Stock Materiales.\n");
		printf("3- Trabajos.\n");
		printf("4- Tecnicos.\n");
		printf("5- Clientes.\n");
		printf("0- Salir.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		system("cls");
		
		switch(op){
			
			case '0':
				band=0;
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tSaliendo...");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			case '1':
				//Opciones
				menuOpciones(&Lop,&Ltar,&Lmat,Rstc);
			break;
			case '2':
				//Stock de Materiales
				menuStockMateriales(&Rstc);
			break;
			case '3':
				//Trabajos
				menuTrabajos(&Ltrab,Ltar,Lmat,Rstc,Lop);
			break;
			case '4':
				//Tecnicos
				menuTecnicos(&Etec,&Stec);
			break;
			case '5':
				//Clientes
				menuClientes(&TPclt);
			break;
			
			default:
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
	}
	return 0;
}

void menuOpciones(struct opciones **ini, struct tareas **iniTarea, struct materiales **Lmat, struct stock *Rstc){
	
	char op;
	int band = 1;
	struct opciones *rc=NULL;
	rc = (*ini);
	
	while(band != 0){
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\t\tSistemaSeguroSA Opciones\n");
		printf("-------------------------------------------------------------------------------\n");
		printf("1- Alta Opciones.\n");
		printf("2- Baja Opciones.\n");
		printf("3- Modificacion Opciones.\n");
		printf("4- Listar Opciones.\n");
		printf("0- Volver.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		switch(op){
			case '0':
				band=0;
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tVolviendo al Menu.");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			
			case '1':
				system("cls");				
				//Alta Opciones
				altaOpciones(&(*ini),&(*iniTarea),Rstc,&(*Lmat));
			break;
			
			case '2':
				system("cls");
				//Baja Opciones
			break;
			
			case '3':
				system("cls");
				//Modificacion Opciones
			break;
			
			case '4':
				system("cls");
				//Listar Opciones
				listarOpciones(*iniTarea,*Lmat,Rstc);
			break;

			
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
		
	}
}

void menuStockMateriales(struct stock **Rstc){
	
	char op;
	int band = 1;
	
	while(band != 0){
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\t\tSistemaSeguroSA Stock\n");
		printf("-------------------------------------------------------------------------------\n");
		printf("1- Alta Materiales.\n");
		printf("2- Baja Materiales.\n");
		printf("3- Modificacion Materiales.\n");
		printf("4- Listar Stock Materiales.\n");
		printf("0- Volver.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		switch(op){
			case '0':
				band=0;
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tVolviendo al Menu.");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			
			case '1':
				system("cls");				
				altaStock(&(*Rstc));
			break;
			
			case '2':
				system("cls");
				//Baja Materiales
				bajaStock(&(*Rstc));
			break;
			
			case '3':
				system("cls");
				//Modificacion Materiales
				modificarStock(&(*Rstc));
			break;
			
			case '4':
				system("cls");
				listarStock(*Rstc);
			break;
			
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
		
	}
}

void menuTrabajos(struct trabajos **Ltrab,struct tareas *Ltar,struct materiales *Lmat,struct stock *Rstc ,struct opciones *Lop){
	
	char op;
	int band = 1;
	
	while(band != 0){
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\t\tSistemaSeguroSA Trabajos\n");
		printf("-------------------------------------------------------------------------------\n");
		printf("1- Alta Trabajos.\n");
		printf("2- Baja Trabajos.\n");
		printf("3- Modificacion Trabajos.\n");
		printf("4- Listar Trabajos no finalizados.\n");
		printf("5- Listar Trabajos.\n");
		printf("0- Volver.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		switch(op){
			case '0':
				band=0;
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tVolviendo al Menu.");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			
			case '1':
				system("cls");				
				//Alta Trabajos
				altaTrabajos(&(*Ltrab),Ltar,Lmat,Rstc,Lop);
			break;
			
			case '2':
				system("cls");
				//Baja Trabajos
			break;
			
			case '3':
				system("cls");
				//Modificacion Trabajos
			break;
			
			case '4':
				system("cls");
				//Listar Trabajos no finalizados
			break;
			
			case '5':
				system("cls");
				//Listar Trabajos
				subMenuTrabajos();
			break;
			
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
		
	}
}

void subMenuTrabajos(){
	
	char op;
	int band = 1;
	
	while(band != 0){
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\tSistemaSeguroSA Trabajos Finalizados\n");
		printf("-------------------------------------------------------------------------------\n");
		printf("1- Listar Trabajos.\n");
		printf("2- TOP 4 Opciones mas vendidas.\n");
		printf("3- Trabajos vendidos entre dos fechas.\n");
		printf("0- Volver.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		switch(op){
			case '0':
				band=0;
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tVolviendo al Menu.");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			
			case '1':
				system("cls");			
				//Listar Trabajos	
			break;
			
			case '2':
				system("cls");
				//TOP 4
			break;
			
			
			case '3':
				system("cls");
				//Trabajos vendidos entre dos fechas
			break;
			
			
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
		
	}
	
}

void menuTecnicos(struct tecnicos **Etec,struct tecnicos **Stec ){
	
	char op;
	int band = 1;
	
	while(band != 0){
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\t\tSistemaSeguroSA Tecnicos\n");
		printf("-------------------------------------------------------------------------------\n");
		printf("1- Alta Tecnicos.\n");
		printf("2- Baja Tecnicos.\n");
		printf("3- Modificacion Tecnicos.\n");
		printf("4- Listar Tecnicos.\n");
		printf("0- Volver.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		switch(op){
			case '0':
				band=0;
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tVolviendo al Menu.");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			
			case '1':
				system("cls");				
				//Alta Tecnicos
				altaTecnicos(&(*Etec),&(*Stec));
			break;
			
			case '2':
				system("cls");
				//Baja Tecnicos
				bajaTecnicos(&(*Etec),&(*Stec));
			break;
			
			case '3':
				system("cls");
				//Modificacion Tecnicos
				modificarTecnicos(&(*Etec),&(*Stec));
			break;
			
			case '4':
				system("cls");
				//Listar Tecnicos
				listarTecnicos(&(*Etec),&(*Stec));
			break;
			
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
		
	}
}

void menuClientes(struct clientes **tope){
	
	char op;
	int band = 1;
	
	while(band != 0){
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\t\tSistemaSeguroSA Clientes\n");
		printf("-------------------------------------------------------------------------------\n");
		printf("1- Alta Clientes.\n");
		printf("2- Baja Clientes.\n");
		printf("3- Modificacion Clientes.\n");
		printf("4- Listar Clientes.\n");
		printf("0- Volver.\n");
		
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		fflush(stdin);
		
		switch(op){
			case '0':
				band=0;
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\t\tVolviendo al Menu.");
				printf("-------------------------------------------------------------------------------\n\n");
			break;
			
			case '1':
				system("cls");				
				//Alta Clientes
				altaClientes(&(*tope));
			break;
			
			case '2':
				system("cls");
				//Baja Clientes
				bajaclientes(&(*tope));
			break;
			
			case '3':
				system("cls");
				//Modificacion Clientes
				modificarClientes(&(*tope));
			break;
			
			case '4':
				system("cls");
				//Listar Clientes				
				listarClientes(&(*tope));
			break;
			
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------------------");
				puts("\n\t\t\tOpcion no valida, intente nuevo.");
				printf("-------------------------------------------------------------------------------\n\n");
		}
		
	}
}


