#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long leerDni();

long leerDni() {
    long dnix;
    printf("\nIngrese su DNI o 0 para volver: ");
    while (1) {
        if (scanf("%ld", &dnix) != 1) {
            // Limpiar el buffer de entrada en caso de entrada no válida
            fflush(stdin);
            printf("Valor invalido. Ingrese un numero positivo/ 0 para volver: ");
        } else if (dnix < 0) {
            // Condición para manejar el caso de DNI negativo
            printf("DNI no puede ser negativo. Ingrese un numero positivo/ 0 para volver: ");
        } else {
            // Entrada válida
            break;
        }
    }
    return dnix;
}

int leerId(int op) {
    int idx;
    
    if(op==11){
    	 printf("\nIngrese el ID del cliente a dar de baja/ 0 para volver: ");
	}else if(op==12){
		 printf("\nIngrese el ID del cliente a modificar/ 0 para volver: ");
	}else if(op==21){
		printf("\nIngrese el ID del tecnico a dar de baja/ 0 para volver: ");
	}else if(op==22){
		printf("\nIngrese el ID del tecnico a modificar/ 0 para volver: ");
	}else if(op==23){
		printf("\nIngrese el ID del tecnico a mostrar sus trabajos/ 0 para volver: ");
	}
    while (1) {
        if (scanf("%d", &idx) != 1) {
            // Limpiar el buffer de entrada en caso de entrada no válida
            fflush(stdin);
            printf("Valor invalido. Ingrese un numero positivo/ 0 para volver: ");
        } else if (idx < 0) {
            // Condición para manejar el caso de DNI negativo
            printf("ID no puede ser negativo. Ingrese un numero positivo/ 0 para volver: ");
        } else {
            // Entrada válida
            break;
        }
    }
    return idx;
}
