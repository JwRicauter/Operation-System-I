#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Alumnos:
// 		Denylson Romero, 13-11270.
//		Jawil Ricauter, 13,11199.


int main(int argc, char*argv[]){

	if(argc != 3){
		printf("El uso adecuado es el siguiente: pscheduler archivo-entrada archivo-salida\n");
		exit(-1);
	}

	printf("BIENVENIDO\nA continuacion se le mostraran algunas opciones.\n\n");
	int opciones;
	while (opciones != 8){
		printf("\n1. Insertar Proceso.\n");
		printf("2. Eliminar Proceso.\n");
		printf("3. Eliminar Proceso en Ejecucion.\n");
		printf("4. Proximo Proceso a Planificar.\n");
		printf("5. Cambiar Estado de Proceso.\n");
		printf("6. Construir Estructura de Procesos.\n");
		printf("7. Imprimir Estructura de Procesos.\n");
		printf("8. Salir del sistema.\n");

		printf("\nIntroduzca la opcion de su preferencia\n\n");
		scanf("%d", &opciones);
		while(getchar() != '\n');


		EstrucSched * estructura;

		long identificador;
		Estado estado;
		int prioridad;
		float tiempo;
		char comando[50];

		Proceso *  x;

		switch(opciones){
			case 1:


				printf("Ingrese los datos del proceso a ingresar de la siguiente manera: \n");
				printf("PID Estado Prioridad Tiempo Comando\n");		
				scanf("%ld %c %d %f %s", &identificador, &estado, &prioridad, &tiempo, comando);
				while(getchar() != '\n');

				x = crear_proceso(identificador, estado, tiempo, comando);
				InsertarProceso(estructura, x, prioridad);
				break;

			case 2:

				printf("Ingrese los datos del proceso a eliminar de la siguiente manera: \n");
				printf("PID Prioridad\n");
				scanf("%ld %d", &identificador, &prioridad);
				while(getchar() != '\n');
				ElimProceso(estructura, identificador, prioridad);

				break;

			case 3:

				ElimProcesoE(estructura);
				break;

			case 4:
				ProxProceso(estructura);
				break;

			case 5:

				printf("Ingrese los datos del proceso al cual se le va a cambiar de estado de la siguiente manera: \n");
				printf("PID ESTADONUEVO Prioridad Tiempo Comando\n");		
				scanf("%ld %c %d %f %s", &identificador, &estado, &prioridad, &tiempo, comando);
				while(getchar() != '\n');

				if (estado == 'L'){
					printf("No se puede cambiar el estado a un proceso listo. \n");
					break;
				}
				else{
					x = crear_proceso(identificador, estado, tiempo, comando);
					CambiarEstado(estructura, x, 'L');
					ElimProceso(estructura, identificador, prioridad);

					break;
				}
				

			case 6:

				estructura = Construye(argv[1]);
				break;

			case 7:

				Imprime(estructura);
				break;

			case 8:
				escribir_procesos(estructura, argv[2]);
				break;	
		}
	}

	return 0;
}
