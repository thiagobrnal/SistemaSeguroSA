#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CARGA(struct opciones **L1, struct tareas **L2, struct materiales **L3, struct stock **R, struct trabajos **L4, struct clientes **TP, struct tecnicos **E, struct tecnicos **S);

void procOpciones(struct opciones **La);
void insertarOpciones(struct opciones **n, struct opciones **ini);
struct opciones* buscarAnterior1(int id, struct opciones *rc);

void procTareas(struct tareas **Lb);
void insertarTareas(struct tareas **nv, struct tareas **ini);
struct tareas* buscarAnterior2(int id, struct tareas *rc);

void procMateriales(struct materiales **Lc);
void insertarMat(struct materiales **n, struct materiales **ini);
struct materiales* buscarAnterior3(int idO, struct materiales *rc);

void procStock(struct stock **R1);
struct stock* insertStock(struct stock *r, struct stock *n);

void procTrabajos(struct trabajos **Ld);
void insertarTrabajos(struct trabajos **n, struct trabajos **ini);
struct trabajos* buscarAnterior4(int id, struct trabajos *rc);

void procClientes(struct clientes **TP1);
void apilarClientes(struct clientes **nv, struct clientes **tope);

void procTecnicos(struct tecnicos **E1, struct tecnicos **S1);
void encolarTecnicos(struct tecnicos **nv, struct tecnicos **Ent, struct tecnicos **Sa);

void CARGA(struct opciones **L1, struct tareas **L2, struct materiales **L3, struct stock **R, struct trabajos **L4, struct clientes **TP, struct tecnicos **E, struct tecnicos **S){
	
	procOpciones(&(*L1));
	
	procTareas(&(*L2));
	
	procMateriales(&(*L3));	
	
	procStock(&(*R));
	
	procTrabajos(&(*L4));
	
	procClientes(&(*TP));
	
	procTecnicos(&(*E), &(*S));
	
}

void procOpciones(struct opciones **La){

	FILE *opc;
	struct opciones *n=NULL; 	

	opc = fopen("opciones.dat","r+b");
	if(opc==NULL){
		printf("Error de apertura de archivo tareas.dat");
		printf("\n");
	} else {
		fread(&opciones, sizeof(opciones),1,opc);
		
		while((!feof(opc))){
			
			if(opciones.estado == 1){
				n = (struct opciones *) malloc(sizeof(struct opciones));			
				if(n != NULL){
					n->sgte = NULL;
					n->id = opciones.id;
					strcpy(n->nombre, opciones.nombre);
					n->costoBase = opciones.costoBase;
					
					insertarOpciones(&n, &(*La));
				}																				
			}			
			fread(&opciones, sizeof(opciones),1,opc);				
		}												
	}
	
	fclose(opc);
}
			
void insertarOpciones(struct opciones **n, struct opciones **ini){
	struct opciones *ant;
	ant = buscarAnterior1((*n)->id, *ini);
	
	if(ant != NULL){
		(*n)->sgte = ant->sgte;
		ant->sgte = (*n);	
	}else{
		(*n)->sgte = (*ini);
		(*ini) = (*n);
	}
	*n = NULL;
}

struct opciones* buscarAnterior1(int id, struct opciones *rc){
	struct opciones *ant=NULL;
	while(rc != NULL){
		if(rc->id > id){
			rc = NULL;
		}else{
			ant = rc;
			rc = rc->sgte;
		}
	}
	return ant;
}
		
		
void procTareas(struct tareas **Lb){
	
	FILE *tar;
	struct tareas *n=NULL;
	
	tar = fopen("tareas.dat","r+b");
	
	if(tar==NULL){
		printf("Error de apertura de archivo tareas.dat");
		printf("\n");
	} else{
		fread(&tareas, sizeof(tareas),1,tar);
		
		while(!feof(tar)){
		
			if(tareas.estado == 1){
				n = (struct tareas *) malloc(sizeof(struct tareas));
				if(n!=NULL){
					n->ant = NULL;
					n->sgte = NULL;
					n->id = tareas.id;
					n->idOpcion = tareas.idOpcion;
					n->orden = tareas.orden;
					n->estado = tareas.estado;
					n->duracion.hora = tareas.duracion.hora;
					n->duracion.minuto = tareas.duracion.minuto;
			
					insertarTareas(&n, &(*Lb));
								
				}
			}
			
			fread(&tareas, sizeof(tareas),1,tar);
		}
	}
			
	fclose(tar);		
}	

void insertarTareas(struct tareas **nv, struct tareas **ini){
	struct tareas *anterior=NULL, *aux=NULL;
	
	anterior = buscarAnterior2((*nv)->id, *ini);
		if(*ini != NULL){
			if(anterior != NULL){
				aux = anterior->sgte;
				(*nv)->ant = anterior;
				anterior->sgte = (*nv);
				
				if(aux != NULL){
					(*nv)->sgte = aux;
					aux->ant = (*nv);
				}			
			}else{
				(*nv)->sgte = (*ini);
				(*ini)->ant = (*nv);
				(*ini) = (*nv);							
			}																								
		}else{			
			(*ini) = (*nv);			
		}
		
		(*nv) = NULL;	
}

struct tareas* buscarAnterior2(int id, struct tareas *rc){
	struct tareas *ant=NULL;
	while(rc != NULL){
		if(rc->id > id){
			rc = NULL;
		}else{
			ant = rc;
			rc = rc->sgte;
		}
	}
	return ant;
}


void procMateriales(struct materiales **Lc){
	
	FILE *mat;
	struct materiales *n=NULL;
	int band=0;
	
	mat = fopen("materiales.dat","r+b");
	
	if(mat==NULL){
		printf("Error de apertura de archivo materiales.dat");
		printf("\n");
	}else{
		fread(&materiales, sizeof(materiales),1,mat);
		
		while((!feof(mat)) && (band!=1)){
			
			n = (struct materiales *) malloc(sizeof(struct materiales));			
			if(n != NULL){
				n->sgte = NULL;
				n->idStock = materiales.idStock;
				n->idOpcion = materiales.idOpcion;
				n->cantidad = materiales.cantidad;
				
				insertarMat(&n, &(*Lc));
				
				
			}else{
				printf("\nError al crear el nodo, no hay memoria disponible");
				band=1;
			}
			
			fread(&materiales, sizeof(materiales),1,mat);			
		}				
	}
	
	fclose(mat);		
}	

void insertarMat(struct materiales **n, struct materiales **ini){
	struct materiales *ant;
	ant = buscarAnterior3((*n)->idOpcion, *ini);
	
	if(ant != NULL){
		(*n)->sgte = ant->sgte;
		ant->sgte = (*n);	
	}else{
		(*n)->sgte = (*ini);
		(*ini) = (*n);
	}
	*n = NULL;
}

struct materiales* buscarAnterior3(int idO, struct materiales *rc){
	struct materiales *ant = NULL;
	while(rc != NULL){
		if(rc->idOpcion > idO){
			rc = NULL;
		}else{
			ant = rc;
			rc = rc->sgte;
		}
	}
	return ant;
}


void procStock(struct stock **R1){
	FILE *stck=NULL;
	struct stock *n=NULL;
	int band=0;
	
	stck = fopen("stock.dat","r+b");
	if(stck==NULL){
		printf("Error de apertura de archivo stock.dat");
		printf("\n");
	}else{
		fread(&stock, sizeof(stock),1,stck);
		
		while(!feof(stck)){
			
			if(stock.estado == 1){
				n = (struct stock *) malloc(sizeof(struct stock));			
				if(n != NULL){
					n->izq = NULL;
					n->der = NULL;
					n->id = stock.id;
					strcpy(n->denominacion, stock.denominacion);
					strcpy(n->unidad, stock.unidad);
					n->precio = stock.precio;
					n->stock = stock.stock;
					n->estado = stock.estado;
								
					*R1 = insertStock(*R1, n);
				}else{
				printf("\nError al crear el nodo, no hay memoria disponible");
				band=1;
				}			
			}
			
			fread(&stock, sizeof(stock),1,stck);			
		}		
	}
	
	fclose(stck);	
}

struct stock* insertStock(struct stock *r, struct stock *n){
	
	if(r != NULL){
		if(strcmp(r->denominacion, n->denominacion) == 0){
			if(r->id == n->id){
				printf("\nEl material ya esta registrado en el stock");
				
			}else if(r->id < n->id){
				r->izq = insertStock(r->izq, n);
								
			}else{
				r->der = insertStock(r->der, n);
			}
		}else if(strcmp(r->denominacion, n->denominacion) < 0){
			r->izq = insertStock(r->izq, n);
		
		}else{
			r->der = insertStock(r->der, n);
		}
	}else{
		r = n;
	}	
		
	return r;
}


void procTrabajos(struct trabajos **Ld){
	FILE *trab;
	struct trabajos *n=NULL;
	int band=0;
	
	trab = fopen("trabajos.dat", "r+b");
	
	if(trab==NULL){
		printf("Error de apertura de archivo trabajos.dat");
		printf("\n");
	} else {
		fread(&trabajos, sizeof(trabajos),1,trab);
		
		while((!feof(trab)) && (band!=1)){
						
			n = (struct trabajos *) malloc(sizeof(struct trabajos));			
			if(n != NULL){
				n->sgte = NULL;
				n->id = trabajos.id;
				n->idOpcion = trabajos.idOpcion;
				n->altura = trabajos.altura;
				n->idTecnico = trabajos.idTecnico;
				n->idCliente = trabajos.idCliente;
				n->finalizado = trabajos.finalizado;
				strcpy(n->ubicacion, trabajos.ubicacion);
				n->fechaFin.dia = trabajos.fechaFin.dia;	
				n->fechaFin.mes = trabajos.fechaFin.mes;
				n->fechaFin.anio = trabajos.fechaFin.anio;
				
				insertarTrabajos(&n, &(*Ld));
								
			}
			else{
				printf("\nError al crear el nodo, no hay memoria disponible");
				band=1;
			}
			
			fread(&trabajos, sizeof(trabajos),1,trab);
		}
	}
}

void insertarTrabajos(struct trabajos **n, struct trabajos **ini){
	struct trabajos *ant;
	ant = buscarAnterior4((*n)->id, *ini);
	
	if(ant = NULL){
		(*n)->sgte = ant->sgte;
		ant->sgte = (*n);	
	}else{
		(*n)->sgte = (*ini);
		(*ini) = (*n);
	}
	*n = NULL;
}

struct trabajos* buscarAnterior4(int id, struct trabajos *rc){
	struct trabajos *ant=NULL;
	while(rc != NULL){
		if(rc->id > id){
			rc = NULL;
		}else{
			ant = rc;
			rc = rc->sgte;
		}
	}
	return ant;
}


void procClientes(struct clientes **TP1){
	FILE *clt;
	struct clientes *p=NULL; 	

	clt = fopen("clientes.dat","r+b");
	if(clt==NULL){
		printf("Error de apertura de archivo clientes.dat");
		printf("\n");
	} else {
		fread(&clientes, sizeof(clientes),1,clt);
		
		while(!feof(clt)){
			
			if(clientes.estado == 1){			
				p = (struct clientes *) malloc(sizeof(struct clientes));			
				if(p != NULL){
					p->sgte = NULL;
					p->id = clientes.id;
					p->dni = clientes.dni;
					p->estado = clientes.estado;
					strcpy(p->nombre, clientes.nombre);
										
					apilarClientes(&p, &(*TP1));
				}
			}
				
			fread(&clientes, sizeof(clientes),1,clt);
		}
		fclose(clt);				
	}	
	
}

void apilarClientes(struct clientes **nv, struct clientes **tope){
	
	(*nv)->sgte = (*tope);
	(*tope) = (*nv);
	(*nv) = NULL;
}


void procTecnicos(struct tecnicos **E1, struct tecnicos **S1){
	FILE *tec;
	struct tecnicos *n=NULL; 	

	tec = fopen("tecnicos.dat","r+b");
	if(tec==NULL){
		printf("Error de apertura de archivo tecnicos.dat");
		printf("\n");
	} else {
		fread(&tecnicos, sizeof(tecnicos),1,tec);
		
		while(!feof(tec)){
			
			if(tecnicos.estado == 1){
				n = (struct tecnicos *) malloc(sizeof(struct tecnicos));			
				if(n != NULL){
					n->sgte = NULL;
					n->id = tecnicos.id;
					n->dni = tecnicos.dni;
					strcpy(n->nombre, tecnicos.nombre);
					n->estado = tecnicos.estado;
					
					encolarTecnicos(&n, &(*E1), &(*S1));
				}
			}			
															
				
			fread(&tecnicos, sizeof(tecnicos),1,tec);
		}
		
		fclose(tec);			
	}
	
}	

void encolarTecnicos(struct tecnicos **nv, struct tecnicos **Ent, struct tecnicos **Sa){
	
	if(*Ent == NULL){
		(*Sa) = (*nv);
		
	}else{
		(*Ent)->sgte = (*nv);
	}	
	(*Ent) = (*nv);
	(*nv) = NULL;
		
}
		
		
		
		
