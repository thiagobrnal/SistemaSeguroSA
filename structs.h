#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct fech{
	int dia, mes, anio;
};

typedef struct tiempo{
	int hora, minuto;
};

//LES
typedef struct opciones{
	int id;
	char nombre[50];
	float costoBase;
	opciones *sgte;
}opciones;

//LDE
typedef struct tareas{
	int id, idOpcion,orden;
	tiempo duracion;
	tareas *ant,*sgte;
}tareas;

//ARBOL DE BUSQUEDA BINARIA
typedef struct stock{
	int id, stock;
	char denominacion[50]; unidad[10];
	float precio;
	stock *izq,*der;
}stock;

//LES
typedef struct trabajos{
	int id, idOpcion, altura, idTecnico, idCliente, finalizado;
	char ubicacion[50];
	fech fechaFin;
	float costoTotal; //la suma de la mano de obra(20% si es > 4 mts), materiales y costo base
	trabajos *sgte;
}trabajos;

//PILA
typedef struct clientes{
	int id, dni;
	char nombre[50];
	clientes *sgte;
}clientes;

//COLA
typedef struct tecnicos{
	int id, dni;
	char nombre[50];
	tecnicos *sgte;
}tecnicos;

