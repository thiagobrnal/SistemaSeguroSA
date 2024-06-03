#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void altaClientes(struct clientes );


void altaClientes(struct clientes **tp){
	
	FILE *archC=NULL;
	struct clientes *p=NULL;
	long dniAux=0, ultId=0;
	
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
			fread(&clientes, sizeof(clientes),1,archC);
			while(!feof(archC)){
				ultId = clientes.id;
				fread(&clientes, sizeof(clientes),1,archC);
			}
			
			clientes.id = ultId + 1;
			fflush(stdin);
			printf("Ingrese su DNI.\n");
			scanf("%ld", &clientes.dni);
			fflush(stdin);
			printf("\nIngrese su nombre: ");
			gets(clientes.nombre);
			fflush(stdin);
			
			cargarClientes(&p, &(*tp))
			
			fwrite(&chofer,sizeof(chofer),1,arch1);
			
			fclose(arch1);				
}

void cargarClientes(struct clientes **nv, struct clientes **top){
	
	(*nv)->sgte = (*top);
	(*top) = (*nv);
	(*nv) = NULL;
}
