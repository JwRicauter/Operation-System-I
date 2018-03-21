#include <stdio.h>
#include <getopt.h>
#include "funciones.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  																												//
//   Creación de un pthread ls como Proyecto número 2 para Sistemas Operativos I.									//
//   Universidad Simón Bolívar.																						//
//   Valle de Sartenejas, Miranda.																					//
//																													//
//   Elaborado por:																									//
//			  		    Denylson Romero, 13-11270																	//
//						Jawil Ricauter,  13-11199																	//
//																													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main(int argc, char *argv[]){

	int c;							// Variable que devuelve getopt, da -1 si hay error.
	int activarMensajeAyuda = 0;	// Entero que indica si se activa el mensaje de ayuda
	int activarSalida = 0;

	/* Variables iniciadas por defecto */
	int numeroDeHilos = 1;			
	char * ruta = ruta_actual();
	char * archivoSalida;

	/* Variables que indican si son activados diferentes tipos de error */
	int errorMensaje = 0;
	int errorHilos = 0;
	int errorInput = 0; 
	

	while ((c = getopt(argc, argv, "h n: d:")) != -1) {
		switch(c){
			case 'h':
				if (argc == 2) activarMensajeAyuda = 1;		// Si solo fue ingresado ./tls -h se activa el mensaje
				else errorMensaje = 1;						// Si no, se muestra un error.
				break;
			case 'n':
				if (activarMensajeAyuda == 0) numeroDeHilos = atoi(optarg);
				if (numeroDeHilos < 1) errorHilos = 1;
				break;
			case 'd':
				if (activarMensajeAyuda == 0) ruta = optarg;
				break;
			case '?':
				errorInput = 1;
				break;
		}
	}

	/* Condicionales que muestran el error */
	if (errorMensaje){
		// perror produce un mensaje estándar de error.
		printf("Disculpe, sólo se puede mostrar el mensaje si fue el único requerimiento del programa.");
		return(-1);
	}
	if (errorHilos){
		perror("Disculpe, tiene que ingresar un numero de hilos mayor o igual a uno");
		return(-1);
	}
	if (errorInput){
		printf("Disculpe, no cumple con los requerimientos de entrada, que es: \n tls[-h] | [-n i] [-d directorio] [ salida ]");
		return(-1);
	}

	/* Condicional que toma el archivo de salida */
	if (argv[optind] != NULL && activarMensajeAyuda == 0){
		// La variable optind es el indice del proximo argumento a ser procesado en el arreglo argv.
		archivoSalida = argv[optind];
		activarSalida = 1;
	}

	/* Llamamos a la función que genera el mensaje de ayuda */
	if(activarMensajeAyuda){
		generar_mensaje_ayuda();
	}

	Argumentos * arg;
	arg = inicializarArgumentos();
	arg->directoriosListos = explorarDirectorio(ruta);
	//imprimirCola(arg->directoriosListos, archivoSalida, activarSalida);
	NodoCola * nodo = eliminar(arg->directoriosListos);
	arg->directoriosListos = asignacionHilos(arg, nodo, numeroDeHilos);
    imprimirCola(arg->directoriosListos, archivoSalida, activarSalida);
	
	return 0;	
}