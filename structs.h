#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct fech{
	int dia, mes, anio;
};

typedef struct tiempo{
	int hora, minuto;
};

typedef struct opciones{
	int id;
	char nombre[50];
	float costoBase;
	tiempo instalacion;
	opciones *sgte;
}opciones;

typedef struct tareas{
	int id, idOpcion,orden;
	tiempo duracion;
	tareas *ant,*sgte;
}tareas;

typedef struct stock{
	int id, stock;
	char denominacion[50]; unidad[10];
	float precio;
	stock *izq,*der;
}stock;

typedef struct trabajos{
	int id, idOpcion, altura, idTecnico, idCliente, finalizado;
	char ubicacion[50];
	fech fechaFin;
	float costoTotal;
	trabajos *sgte;
}trabajos;

typedef struct clientes{
	int id, dni;
	char nombre[50];
	clientes *sgte;
}clientes;

typedef struct tecnicos{
	int id, dni;
	char nombre[50];
	tecnicos *sgte;
}tecnicos;

typedef struct trabajosPendientes{
	int idTrabajos;
	trabajosPendientes *sgte;
}trabajosPendientes;


typedef struct tareasPendientes{
	int idTrabajosPendientes, idTareas;
	tareasPendientes *sgte;
}tareasPendientes;
