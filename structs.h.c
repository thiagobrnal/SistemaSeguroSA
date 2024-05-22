#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct opciones{
	int id;
	char nombre[50];
	float precio;
	struct opciones_les *sig;
};

typedef struct fecha{
	int dia,mes,anio;
};

typedef struct tiempo{
	int hora,minuto;
};

typedef struct tareas{
	int id,id_opcion,orden;
	tiempo duracion;
	struct tareas *ant,*sig;
};

typedef struct stock{
	int id, stock;
	char denominacion[50]; unidad[10];
	float precio;
	struct stock *izq,*der;
};

typedef struct trabajos{
	int id,id_opcion,altura,id_tecnico,id_cliente;
	char ubicacion[50];
	struct trabajos *sig;
};

typedef struct clientes{
	int id,dni;
	char nombre[50];
	struct clientes *sig;
};

typedef struct tecnicos{
	int id,dni;
	char nombre[50];
	struct tecnicos *sig;
};

typedef struct trabajos_pendientes{
	int id_trabajos,finalizado;
	struct trabajos_pendientes *sig;
};


typedef struct tareas_pendientes{
	int id_tareas;
};
