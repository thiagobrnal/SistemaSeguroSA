#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct fech{
	int dia, mes, anio;
}fech;

typedef struct tiempo{
	int hora, minuto;
}tiempo;

//LES
typedef struct opciones{
	int id;
	char nombre[50];
	float costoBase;
	struct opciones *sgte;
}opciones;

//LDE
typedef struct tareas{
	int id, idOpcion,orden;
	struct tiempo duracion;
	struct tareas *ant,*sgte;
}tareas;

//ARBOL DE BUSQUEDA BINARIA
typedef struct stock{
	int id, stock;
	char denominacion[50], unidad[10];
	float precio;
	struct stock *izq, *der;
}stock;

//LES
typedef struct trabajos{
	int id, idOpcion, altura, idTecnico, idCliente, finalizado;
	char ubicacion[50];
	struct fech fechaFin;
	float costoTotal; //la suma de la mano de obra(20% si es > 4 mts), materiales y costo base
	struct trabajos *sgte;
}trabajos;

//PILA
typedef struct clientes{
	int id, dni;
	char nombre[50];
	struct clientes *sgte;
}clientes;

//COLA
typedef struct tecnicos{
	int id, dni;
	char nombre[50];
	struct tecnicos *sgte;
}tecnicos;

