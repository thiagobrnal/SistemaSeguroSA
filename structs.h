#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct fech{
	int dia, mes, anio;
}fech;

struct tiempo{
	int hora, minuto;
}tiempo;

//LES
struct opciones{
	int id,estado;
	char nombre[50];
	float costoBase;
	struct opciones *sgte;
}opciones;

//LDE
struct tareas{
	int id, idOpcion,orden,estado;
	struct tiempo duracion;
	struct tareas *ant,*sgte;
}tareas;

//LES
struct materiales{
	int idStock, idOpcion, cantidad,estado;
	struct materiales *sgte;
}materiales;

//ARBOL DE BUSQUEDA BINARIA
struct stock{
	int id, stock,estado;
	char denominacion[50], unidad[10];
	float precio;
	struct stock *izq, *der;
}stock;

//LES
struct trabajos{
	int id, idOpcion, altura, idTecnico, idCliente, finalizado;
	char ubicacion[50];
	struct fech fechaFin;
	float costoTotal; //la suma de la mano de obra(20% si es > 4 mts), materiales y costo base
	struct trabajos *sgte;
}trabajos;

//PILA
struct clientes{
	int id;
	long dni;
	char nombre[50];
	struct clientes *sgte;
}clientes;

//COLA
struct tecnicos{
	int id, estado;
	long dni;
	char nombre[50];
	struct tecnicos *sgte;
}tecnicos;

