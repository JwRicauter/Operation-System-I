#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FUNCIONESH
#define FUNCIONESH


// Definicion de Estado

typedef char Estado;

// Definicion de Estructuras.

typedef struct Proceso Proceso;

typedef struct ElementoLista Elemento;

typedef struct ListaIdentificar Lista;

typedef struct EstructuraDeListas EstrucSched;


// Firmas de Funciones:

/////////////////////// Funciones Auxiliares /////////////////////////

Proceso * crear_proceso(long id, Estado state, float tm, char command[50]);

Lista * inicializacion();

int insercion(Lista * lista, Proceso * p);

int eliminar_primero(Lista * l);

Proceso * extraccion_primero(Lista * lista);

int eliminacion(Lista * lista, long identificador);

void visualizacion(Lista * l);

void cambiar_estado_proceso(Lista * lista, Proceso * p, Estado nuevoEstado);

Proceso * proceso_planificado(Lista * lista);

long encontrar_proceso_en_ejecucion(Lista * lista);

int escribir_procesos(EstrucSched * s, char * filename);

/////////////////////// Funciones Obligatorias /////////////////////////

void InsertarProceso(EstrucSched * s, Proceso* p, short prioridad);

void ElimProceso(EstrucSched *s, long pid, short prio);

void ElimProcesoE(EstrucSched *s);

Proceso * ProxProceso(EstrucSched *s);

void CambiarEstado(EstrucSched *s, Proceso* p, Estado newestado);

EstrucSched *Construye(char *filename);

void Imprime(EstrucSched *s);

#endif