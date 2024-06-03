#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//OPCIONES
void altaOpciones(struct opciones **ini, struct tareas **Ltar,struct stock *Rstc, struct materiales *Lmat);
void bajaOpciones();
void modificarOpciones();
void listarOpciones(struct tareas *Ltar, struct materiales *rMat, struct stock *rStock);
struct opciones* nuevoNodo(int id, char* nombre, float costoBase);
float obtenerCostoBase(int idOpcion,struct opciones *r);

void recorrer(struct opciones *rc);

struct opciones* nuevoNodo(int id, char* nombre, float costoBase) {
	
    struct opciones* nodo = (struct opciones*)malloc(sizeof(struct opciones));
    
    if(nodo==NULL){
    	return NULL;
	}else{
		nodo->id = id;
    	strcpy(nodo->nombre, nombre);
    	nodo->costoBase = costoBase;
    	nodo->sgte = NULL;
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
        
    	// Leer datos
    	printf("Ingrese el nombre de la opcion: ");
    	gets(opciones.nombre);
    	fflush(stdin);
   		
		printf("Ingrese el costo de esta operacion (sin mano de obra ni materiales): ");
    	scanf("%f", &opciones.costoBase);
    	fflush(stdin);
    	
    	
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

//Listar Opciones
//id,nombre,hora = duracionTareasH(idOpcion), min = duracionTareasM(idOpcion), costoBase + 20% si "trabajos.altura>=4", materiales.cantidad * stock.precio, trabajos.costoTotal

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
    		printf("\n%d -",opciones.id);
    		printf(" Nombre: %s ",opciones.nombre);
    		//puts(opciones.nombre);
    		sumaHorasMinutosTareas(opciones.id,Ltar);
    		printf(" Costo: %f",opciones.costoBase);
    		precioMat = precioMateriales(opciones.id,rMat,rStock);
    		printf(" Costo de materiales: %f",precioMat);
    		costoTotal = precioMat + opciones.costoBase;
    		printf(" Costo Total: %f",costoTotal);
    		printf("\n----------------");	
			fread(&opciones, sizeof(opciones),1,arch1);
		}
		fclose(arch1);
	}
}


float obtenerCostoBase(int idOpcion,struct opciones *r){
	while(r!=NULL){
		if(idOpcion == r->id){
			return r->costoBase;
		}else{
			r= r->sgte;
		}
	}
	return 0;
}
