#include <stdio.h>
#include "funciones.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  Proyecto I  ///////////////////////////////////////////////////////////////
////////////////////////////////   Comunicación entre Procesos y Manejo de Archivos   //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//		Integrantes:
//			Denylson Romero, 13-11270.
//			Jawil Ricauter, 13-11199.



int main(int argc, char*argv[]){

	if(argc != 2){
		printf("El uso adecuado es el siguiente: els <output_file> \n");
		exit(-1);
	}

	char * path = ruta_actual();
    els(path, argv[1]);
	return 0;	
}