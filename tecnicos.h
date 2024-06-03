#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void altaTecnicos(struct tecnicos **e, struct tecnicos **s);
void encolar(struct tecnicos **n, struct tecnicos **e, struct tecnicos **s);

void altaTecnicos(struct tecnicos **e, struct tecnicos **s){
    struct tecnicos *n = NULL;
    struct tecnicos temp;
    FILE *archivoTecnicos;
	long ultId;
	
    if ((archivoTecnicos = fopen("tecnicos.dat", "a+b")) != NULL) {
        // LEER DATOS
        
        fread(&temp, sizeof(temp),1,archivoTecnicos);
		while(!feof(archivoTecnicos)){
			ultId = temp.id;
			fread(&temp, sizeof(temp),1,archivoTecnicos);
		}
		
		temp.id = ultId + 1;
        printf("Ingrese DNI: ");
        scanf("%d", &temp.dni);
        printf("Ingrese nombre: ");
        scanf("%s", temp.nombre);

        fwrite(&temp, sizeof(struct tecnicos), 1, archivoTecnicos);
        
        
        // CREAR NODO E INSERTARLO
        n = (struct tecnicos*)malloc(sizeof(struct tecnicos));
        if (n != NULL) {
            n->id = temp.id;
            n->dni = temp.dni;
            strcpy(n->nombre, temp.nombre);
            n->sgte = NULL;
            encolar(&n,&(*e),&(*s));
        } else {
            printf("No hay memoria suficiente para cargar los nodos");
        }
        fclose(archivoTecnicos);
    } else {
        printf("\nError al abrir el archivo tecnicos.dat");
    }
}

void encolar(struct tecnicos **n, struct tecnicos **e, struct tecnicos **s){
	if(*e == NULL) {
		*s = *n;
	} else{
		(*e)->sgte = *n;
		(*e) = (*n);
		(*n) = NULL;
	}
}
