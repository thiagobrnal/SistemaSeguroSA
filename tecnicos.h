#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void altaTecnicos(struct tecnicos **e, struct tecnicos **s);
void listarTecnicos(struct tecnicos **e, struct tecnicos **s);
int vaciaTecnicos(struct tecnicos *s);
void desencolarTecnicos(struct tecnicos **d, struct tecnicos **e, struct tecnicos **s);
void encolarTecnicosH(struct tecnicos **n, struct tecnicos **e, struct tecnicos **s);

void altaTecnicos(struct tecnicos **e, struct tecnicos **s){
    struct tecnicos *n = NULL;
    struct tecnicos temp;
    FILE *archivoTecnicos;
	int ultId=0;
	long dniAux;
	
	
	printf("\nIngrese su DNI o 0 para volver: ");
	while(scanf("%ld", &dniAux) != 1){
		fflush(stdin);
		printf(" Valor invalido\n");
	 }
	
	if(dniAux != 0){
		if ((archivoTecnicos = fopen("tecnicos.dat", "a+b")) != NULL) {
        // LEER DATOS
        
        fread(&temp, sizeof(temp),1,archivoTecnicos);
		while(!feof(archivoTecnicos)){
			ultId = temp.id;
			fread(&temp, sizeof(temp),1,archivoTecnicos);
		}
		
		temp.id = ultId + 1;
        temp.dni = dniAux;
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

void listarTecnicos(struct tecnicos **e, struct tecnicos **s){
	 struct tecnicos *n = NULL;
	 struct tecnicos *eAux=NULL;
	 struct tecnicos *sAux=NULL;
 	 int band= vaciaTecnicos((*s));
		while(band!=0){
			desencolarTecnicos(&n,&(*e),&(*s));	
				printf("\nID: %d", n->id);
		        printf("\nDNI: %ld", n->dni);
		        printf("\nNombre: %s", n->nombre);
				printf("\n----------------");		
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
	(*n) = NULL;
}
